#ifndef OPACCEL_H
#define OPACCEL_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "Zend/zend_alloc.h"
#include "Zend/zend_extensions.h"
#include "Zend/zend_compile.h"
#include "Zend/zend_vm_opcodes.h"
#include "Zend/zend_execute.h"
#include "Zend/zend_hash.h"
#include "Zend/zend_globals.h"
#include "Zend/zend_globals_macros.h"
#include "Zend/zend_modules.h"

extern zend_module_entry opaccel_module_entry;
#define phpext_opaccel_ptr &opaccel_module_entry

#ifdef ZTS
#define OPACCEL_GLOBALS(v) TSRMG(opaccel_globals_id, zend_opaccel_globals *, v)
#else
#define OPACCEL_GLOBALS(v) (opaccel_globals.v)
#endif

ZEND_BEGIN_MODULE_GLOBALS(opaccel)
ZEND_END_MODULE_GLOBALS(opaccel)
extern ZEND_DECLARE_MODULE_GLOBALS(opaccel);

PHP_MINIT_FUNCTION(opaccel);

#ifndef ZEND_EXT_API
# if defined(__GNUC__) && __GNUC__ >= 4
#  define ZEND_EXT_API __attribute__ ((visibility("default")))
# else
#  define ZEND_EXT_API
# endif
#endif

#define OPACCEL_FOREACH(table, value) \
		for(zend_hash_internal_pointer_reset(table); \
				zend_hash_get_current_data(table, (void**) &value) == SUCCESS; \
				zend_hash_move_forward(table))

#define OPACCEL_STRLEN 230

#define OpaccelMakeNOP(op) \
	(op)->opcode = ZEND_NOP; \
	(op)->op1_type = IS_UNUSED; \
	(op)->op2_type = IS_UNUSED; \
	(op)->result_type = IS_UNUSED;

#endif
