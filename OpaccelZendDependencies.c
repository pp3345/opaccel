
#include "Opaccel.h"

#ifndef _OPACCEL_ZEND_C
#define _OPACCEL_ZEND_C
/* This code is copied from Zend Engine source code since they do not export it */

#undef EX
#define EX(element) execute_data->element
#define EX_T(offset) (*EX_TMP_VAR(execute_data, offset))

#define USE_OPLINE zend_op *opline = EX(opline);
#define OPLINE EX(opline)

#define ZEND_VM_INC_OPCODE() \
	OPLINE++

#define ZEND_VM_CONTINUE()         return 0
#define ZEND_VM_RETURN()           return 1
#define ZEND_VM_ENTER()            return 2
#define ZEND_VM_LEAVE()            return 3
#define ZEND_VM_DISPATCH(opcode, opline) return zend_vm_get_opcode_handler(opcode, opline)(ZEND_OPCODE_HANDLER_ARGS_PASSTHRU);

#define ZEND_VM_NEXT_OPCODE() \
	ZEND_VM_INC_OPCODE(); \
	ZEND_VM_CONTINUE()

#define _CONST_CODE  0
#define _TMP_CODE    1
#define _VAR_CODE    2
#define _UNUSED_CODE 3
#define _CV_CODE     4

#define CV_DEF_OF(i) (EG(active_op_array)->vars[i])

#define RETURN_VALUE_USED(opline) (!((opline)->result_type & EXT_TYPE_UNUSED))

static zend_never_inline zval **_get_zval_cv_lookup_BP_VAR_R(zval ***ptr, zend_uint var TSRMLS_DC)
{
	zend_compiled_variable *cv = &CV_DEF_OF(var);

	if (!EG(active_symbol_table) ||
	    zend_hash_quick_find(EG(active_symbol_table), cv->name, cv->name_len+1, cv->hash_value, (void **)ptr)==FAILURE) {
		zend_error(E_NOTICE, "Undefined variable: %s", cv->name);
		return &EG(uninitialized_zval_ptr);
	}
	return *ptr;
}

static zend_always_inline zval *_get_zval_ptr_cv_BP_VAR_R(const zend_execute_data *execute_data, zend_uint var TSRMLS_DC)
{
	zval ***ptr = EX_CV_NUM(execute_data, var);

	if (UNEXPECTED(*ptr == NULL)) {
		return *_get_zval_cv_lookup_BP_VAR_R(ptr, var TSRMLS_CC);
	}
	return **ptr;
}

static zend_always_inline zval *_get_zval_ptr_tmp(zend_uint var, const zend_execute_data *execute_data, zend_free_op *should_free TSRMLS_DC)
{
	return should_free->var = &EX_T(var).tmp_var;
}

static zend_always_inline zval *_get_zval_ptr_var(zend_uint var, const zend_execute_data *execute_data, zend_free_op *should_free TSRMLS_DC)
{
	zval *ptr = EX_T(var).var.ptr;

	return should_free->var = ptr;
}


#endif
