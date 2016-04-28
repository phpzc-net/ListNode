/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_ListNode.h"


#include "CListNode.h"

/* If you declare any globals in php_ListNode.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(ListNode)
*/

/* True global resources - no need for thread safety here */
static int le_ListNode;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("ListNode.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_ListNode_globals, ListNode_globals)
    STD_PHP_INI_ENTRY("ListNode.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_ListNode_globals, ListNode_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_ListNode_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_ListNode_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "ListNode", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_ListNode_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_ListNode_init_globals(zend_ListNode_globals *ListNode_globals)
{
	ListNode_globals->global_value = 0;
	ListNode_globals->global_string = NULL;
}
*/
/* }}} */

zend_object_handlers ListNode_object_handlers;

struct ListNode_object{
    zend_object std;
    CListNode *listnode;
};


zend_class_entry* listnode_ce;

PHP_METHOD(ListNode,__construct)
{
    CListNode* ln = CListNode::create();
    zval* thisptr = getThis();
    ListNode_object* ln_obj = (ListNode_object*) zend_object_store_get_object(thisptr TSRMLS_CC);
    ln_obj->listnode = ln;
    
    //在与c++配合中 定义类属性 在 __construct 中定义
    zend_update_property_string(listnode_ce,thisptr,"p1",strlen("p1"),"bbb" TSRMLS_CC);
    zend_declare_class_constant_string(listnode_ce,"AAA",strlen("AAA"),"bbb" TSRMLS_CC);
}
static zend_function_entry listnode_methods[]=
{
    ZEND_ME(ListNode,__construct,NULL,ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  {NULL,NULL,NULL}  
};




void free_listnode_object(void* obj TSRMLS_DC)
{
    ListNode_object* listnode_obj = (ListNode_object*)obj;
    delete listnode_obj->listnode;
    
    zend_hash_destroy(listnode_obj->std.properties);
    FREE_HASHTABLE(listnode_obj->std.properties);
    
    efree(listnode_obj);
}

zend_object_value create_listnode_object(zend_class_entry* class_entry TSRMLS_DC)
{
    //zval *tmp;
    zend_object_value retval;
    zval *tmp;
    ListNode_object* listnode_object=(ListNode_object*)emalloc(sizeof(ListNode_object));
    memset(listnode_object,0,sizeof(ListNode_object));
    listnode_object->std.ce = class_entry;
    
    ALLOC_HASHTABLE(listnode_object->std.properties);
    zend_hash_init(listnode_object->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);//不持久 ZVAL_PTR_DTOR销毁函数  引用计数减一 自动销毁
    zend_hash_copy(listnode_object->std.properties, &class_entry->properties_info,(copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));// &class_entry->properties_info 即为 zend_declare_property系列函数 定义类属性时修改的hashtable 这里从他复制初值 倒数第2个参数为兼容之前的 这里用NULL 

    retval.handle = zend_objects_store_put(listnode_object, NULL,free_listnode_object, NULL TSRMLS_CC);
    retval.handlers = &ListNode_object_handlers;
    
    return retval;
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(ListNode)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce,"ListNode",listnode_methods);
    listnode_ce = zend_register_internal_class(&ce TSRMLS_CC);
    
    listnode_ce->create_object = create_listnode_object;
    //初始化 ListNode_object_handlers
    memcpy(&ListNode_object_handlers,zend_get_std_object_handlers(),sizeof(zend_object_handlers));
    ListNode_object_handlers.clone_obj = NULL;
    
    
    //zend_declare_property_string(listnode_ce,"p1",strlen("p1"),"aaa",ZEND_ACC_PUBLIC TSRMLS_CC);
    //zend_declare_class_constant_string(listnode_ce,"LISTNODE_VER",strlen("LISTNODE_VER"),"1.0" TSRMLS_CC);
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(ListNode)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(ListNode)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(ListNode)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(ListNode)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "ListNode support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ ListNode_functions[]
 *
 * Every user visible function must have an entry in ListNode_functions[].
 */
const zend_function_entry ListNode_functions[] = {
	PHP_FE(confirm_ListNode_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in ListNode_functions[] */
};
/* }}} */

/* {{{ ListNode_module_entry
 */
zend_module_entry ListNode_module_entry = {
	STANDARD_MODULE_HEADER,
	"ListNode",
	ListNode_functions,
	PHP_MINIT(ListNode),
	PHP_MSHUTDOWN(ListNode),
	PHP_RINIT(ListNode),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(ListNode),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(ListNode),
	PHP_LISTNODE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_LISTNODE
ZEND_GET_MODULE(ListNode)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
