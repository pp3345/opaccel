
#include "Opaccel.h"
#include "OpaccelEmptyOpcodeHandlerArray.h"

ZEND_EXTENSION();

ZEND_DECLARE_MODULE_GLOBALS(opaccel)

ZEND_INI_BEGIN()
	STD_ZEND_INI_ENTRY("opaccel.optimizations", "0xffffffff", PHP_INI_ALL, OnUpdateLongGEZero, optimizations, zend_opaccel_globals, opaccel_globals)
ZEND_INI_END()

#include "OpaccelStrlen.c"

static int OpaccelStartup(zend_extension *extension) {
	// We don't want to use ugly ZEND_USER_OPCODE so let's just modify zend_opcode_handlers
	static opcode_handler_t handlers[] = OPACCEL_EMPTY_OPCODE_HANDLER_ARRAY;

	memcpy(handlers, zend_opcode_handlers, 168 * 25 * sizeof(opcode_handler_t));

	handlers[OPACCEL_STRLEN * 25 + _CV_CODE * 5 + _UNUSED_CODE] = OPACCEL_STRLEN_SPEC_CV_HANDLER;
	handlers[OPACCEL_STRLEN * 25 + _TMP_CODE * 5 + _UNUSED_CODE] = OPACCEL_STRLEN_SPEC_TMP_VAR_HANDLER;
	handlers[OPACCEL_STRLEN * 25 + _VAR_CODE * 5 + _UNUSED_CODE] = OPACCEL_STRLEN_SPEC_VAR_HANDLER;

	zend_opcode_handlers = (opcode_handler_t*) handlers;

	if(zend_startup_module(&opaccel_module_entry) != SUCCESS)
		return FAILURE;

	return SUCCESS;
}

ZEND_MINIT_FUNCTION(opaccel) {
	REGISTER_INI_ENTRIES();

	return 1;
}

ZEND_MSHUTDOWN_FUNCTION(opaccel) {
	UNREGISTER_INI_ENTRIES();

	return 1;
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
					if(Z_STRLEN(array->literals[(op + 1)->op1.constant].constant) == sizeof("strlen") - 1
						&& !memcmp(Z_STRVAL(array->literals[(op + 1)->op1.constant].constant), "strlen", sizeof("strlen") - 1)) {
						if(UNEXPECTED(!(OPAG(optimizations) & OPACCEL_OPTIMIZE_STRLEN)
							|| (op->op1_type == IS_CONST)))
							break;

						if(UNEXPECTED(!RETURN_VALUE_USED(op + 1))) {
							// Call is useless, optimize away
							OpaccelMakeNOP(op);
							OpaccelMakeNOP(op + 1);
							break;
						}

						op->opcode = OPACCEL_STRLEN;
					} else
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

zend_module_entry opaccel_module_entry = {
        STANDARD_MODULE_HEADER,
        "opaccel",
        NULL,
        ZEND_MINIT(opaccel),
        ZEND_MSHUTDOWN(opaccel),
        NULL,
        NULL,
        NULL,
        "devel",
        STANDARD_MODULE_PROPERTIES
};
