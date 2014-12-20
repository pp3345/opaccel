
#include "Opaccel.h"
#include "OpaccelEmptyOpcodeHandlerArray.h"

ZEND_DECLARE_MODULE_GLOBALS(opaccel);
ZEND_EXTENSION();

zend_module_entry opaccel_module_entry = {
	STANDARD_MODULE_HEADER,
	"opaccel",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"devel",
	STANDARD_MODULE_PROPERTIES
};

#include "OpaccelStrlen.c"

static int OpaccelStartup(zend_extension *extension) {
	// We don't want to use ugly ZEND_USER_OPCODE so let's just modify zend_opcode_handlers
	static opcode_handler_t handlers[] = OPACCEL_EMPTY_OPCODE_HANDLER_ARRAY;

	memcpy(handlers, zend_opcode_handlers, 168 * 25 * sizeof(opcode_handler_t));

#ifdef HAVE_OPACCEL_STRLEN
	handlers[5773] = OPACCEL_STRLEN_SPEC_CV_HANDLER;
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
				if(op->op1_type == IS_CV /* ZEND_SEND_VAR_SPEC_CV */
						&& (op + 1)->opcode == ZEND_DO_FCALL
						&& (op + 1)->op1_type == IS_CONST /* ZEND_DO_FCALL_SPEC_CONST */) {

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
