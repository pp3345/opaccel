
#include "Opaccel.h"

#ifdef HAVE_OPACCEL_STRLEN

#include "OpaccelZendDependencies.c"

static void OpaccelStrlen(zval *string, temp_variable *retval) {
	MAKE_STD_ZVAL(retval->var.ptr);
	retval->var.ptr_ptr = &retval->var.ptr;
	retval->var.fcall_returned_reference = 0;

	if(UNEXPECTED(Z_TYPE_P(string) != IS_STRING)) {
		switch(Z_TYPE_P(string)) {
			case IS_NULL:
				ZVAL_LONG(retval->var.ptr, 0);
				break;
			case IS_BOOL:
				if(Z_LVAL_P(string)) {
					ZVAL_LONG(retval->var.ptr, 1);
				} else {
					ZVAL_LONG(retval->var.ptr, 0);
				}
				break;
			case IS_LONG: {
				long x = Z_LVAL_P(string) < 0 ? (-1 * Z_LVAL_P(string)) : Z_LVAL_P(string);

#if LONG_MAX == 9223372036854775807L // 64 bit
				if(x > 1000000000000000000) { ZVAL_LONG(retval->var.ptr, 19); }
				else if(x > 100000000000000000) { ZVAL_LONG(retval->var.ptr, 18); }
				else if(x > 10000000000000000) { ZVAL_LONG(retval->var.ptr, 17); }
				else if(x > 1000000000000000) { ZVAL_LONG(retval->var.ptr, 16); }
				else if(x > 100000000000000) { ZVAL_LONG(retval->var.ptr, 15); }
				else if(x > 10000000000000) { ZVAL_LONG(retval->var.ptr, 14); }
				else if(x > 1000000000000) { ZVAL_LONG(retval->var.ptr, 13); }
				else if(x > 100000000000) { ZVAL_LONG(retval->var.ptr, 12); }
				else if(x > 10000000000) { ZVAL_LONG(retval->var.ptr, 11); }
				else
#endif
				if(x > 1000000000) { ZVAL_LONG(retval->var.ptr, 10); }
				else if(x > 100000000) { ZVAL_LONG(retval->var.ptr, 9); }
				else if(x > 10000000) { ZVAL_LONG(retval->var.ptr, 8); }
				else if(x > 1000000) { ZVAL_LONG(retval->var.ptr, 7); }
				else if(x > 100000) { ZVAL_LONG(retval->var.ptr, 6); }
				else if(x > 10000) { ZVAL_LONG(retval->var.ptr, 5); }
				else if(x > 1000) { ZVAL_LONG(retval->var.ptr, 4); }
				else if(x > 100) { ZVAL_LONG(retval->var.ptr, 3); }
				else if(x > 10) { ZVAL_LONG(retval->var.ptr, 2); }
				else { ZVAL_LONG(retval->var.ptr, 1); }

				if(Z_LVAL_P(string) < 0) {
					Z_LVAL_P(retval->var.ptr) += 1;
				}
			} break;
			case IS_DOUBLE: {
				char *buf;

				ZVAL_LONG(retval->var.ptr, spprintf(&buf, 0, "%.*G", (int) EG(precision), Z_DVAL_P(string)));

				efree(buf);
			} break;
			case IS_OBJECT: {
				zval copy;

				/* Partial copy & paste from zend.c */
				if (zend_std_cast_object_tostring(string, &copy, IS_STRING TSRMLS_CC) == SUCCESS) {
					ZVAL_LONG(retval->var.ptr, Z_STRLEN(copy));
					break;
				}

				if (Z_OBJ_HANDLER_P(string, cast_object)) {
					zval *val;

					ALLOC_ZVAL(val);
					INIT_PZVAL_COPY(val, string);
					zval_copy_ctor(val);

					if (Z_OBJ_HANDLER_P(string, cast_object)(val, &copy, IS_STRING TSRMLS_CC) == SUCCESS) {
						zval_ptr_dtor(&val);
						ZVAL_LONG(retval->var.ptr, Z_STRLEN(copy));
						break;
					}

					zval_ptr_dtor(&val);
				}

				if (!Z_OBJ_HANDLER_P(string, cast_object) && Z_OBJ_HANDLER_P(string, get)) {
					int use_copy = 0;

					zval *z = Z_OBJ_HANDLER_P(string, get)(string TSRMLS_CC);

					Z_ADDREF_P(z);
					if (Z_TYPE_P(z) != IS_OBJECT) {
						zend_make_printable_zval(z, &copy, &use_copy);
						if (use_copy) {
							ZVAL_LONG(retval->var.ptr, Z_STRLEN(copy));
						} else {
							ZVAL_LONG(retval->var.ptr, Z_STRLEN_P(z));
						}

						zval_ptr_dtor(&z);
						break;
					}

					zval_ptr_dtor(&z);
				}

				// not every object can be converted to a string value
				ZVAL_NULL(retval->var.ptr);
				zend_error(E_WARNING, "strlen() expects parameter 1 to be string, object given");
			} break;
			case IS_RESOURCE:
				zend_error(E_WARNING, "strlen() expects parameter 1 to be string, resource given");
				ZVAL_NULL(retval->var.ptr);
				break;
			case IS_ARRAY:
				zend_error(E_WARNING, "strlen() expects parameter 1 to be string, array given");
				ZVAL_NULL(retval->var.ptr);
		}
	} else {
		ZVAL_LONG(retval->var.ptr, Z_STRLEN_P(string));
	}
}

static int ZEND_FASTCALL OPACCEL_STRLEN_SPEC_CV_HANDLER(ZEND_OPCODE_HANDLER_ARGS) {
	USE_OPLINE
	temp_variable *retval;
	zval *cv;

	retval = EX_TMP_VAR(execute_data, opline->result.var);
	cv = _get_zval_ptr_cv_BP_VAR_W(execute_data, opline->op1.var);

	OpaccelStrlen(cv, retval);

	ZEND_VM_NEXT_OPCODE();
}

static int ZEND_FASTCALL OPACCEL_STRLEN_SPEC_TMP_VAR_HANDLER(ZEND_OPCODE_HANDLER_ARGS) {
	USE_OPLINE
	temp_variable *retval;
	zval *arg;
	zend_free_op free;

	retval = EX_TMP_VAR(execute_data, opline->result.var);
	arg = _get_zval_ptr_tmp(opline->op1.var, execute_data, &free);

	OpaccelStrlen(arg, retval);

	zval_ptr_dtor(&free.var);

	ZEND_VM_NEXT_OPCODE();
}

#endif
