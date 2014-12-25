
#include "Opaccel.h"
#include "OpaccelEmptyOpcodeHandlerArray.h"

ZEND_EXTENSION();

#include "OpaccelStrlen.c"

static int OpaccelStartup(zend_extension *extension) {
	// We don't want to use ugly ZEND_USER_OPCODE so let's just modify zend_opcode_handlers
	static opcode_handler_t handlers[] = OPACCEL_EMPTY_OPCODE_HANDLER_ARRAY;

	memcpy(handlers, zend_opcode_handlers, 168 * 25 * sizeof(opcode_handler_t));

#ifdef HAVE_OPACCEL_STRLEN
	handlers[5773] = OPACCEL_STRLEN_SPEC_CV_HANDLER;
	handlers[5758] = OPACCEL_STRLEN_SPEC_TMP_VAR_HANDLER;
	handlers[5763] = OPACCEL_STRLEN_SPEC_VAR_HANDLER;
#endif

	zend_opcode_handlers = (opcode_handler_t*) handlers;

	return SUCCESS;
}

static void OpaccelCompile(zend_op_array *array) {
	int i;
	zend_op *op;

	for(op = array->opcodes; op < array->opcodes + array->last; op++) {
		switch(op->opcode) {
			case ZEND_SEND_VAR:
			case ZEND_SEND_VAL:
			case ZEND_SEND_VAR_NO_REF:
				if((op + 1)->opcode == ZEND_DO_FCALL) {

#ifdef HAVE_OPACCEL_STRLEN
					if(Z_STRLEN(array->literals[(op + 1)->op1.constant].constant) == sizeof("strlen") - 1
						&& !memcmp(Z_STRVAL(array->literals[(op + 1)->op1.constant].constant), "strlen", sizeof("strlen") - 1)) {
						if(UNEXPECTED(!RETURN_VALUE_USED(op + 1))) {
							// Call is useless, optimize away
							OpaccelMakeNOP(op);
							OpaccelMakeNOP(op + 1);
							break;
						}

						op->opcode = OPACCEL_STRLEN;
					} else
#endif
					break;

					op->result_type = (op + 1)->result_type;
					op->result.var = (op + 1)->result.var;
					OpaccelMakeNOP(op + 1);
				}

				break;
		}
	}
}

zend_extension zend_extension_entry = {
	"opaccel",
	"devel",
	"Yussuf Khalil",
	"",
	"2014 ",
	OpaccelStartup,
	NULL,
	NULL,
	NULL,
	NULL,
	OpaccelCompile,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	STANDARD_ZEND_EXTENSION_PROPERTIES
};
