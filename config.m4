dnl $Id$
dnl config.m4 for extension ListNode

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(ListNode, for ListNode support,
Make sure that the comment is aligned:
[  --with-ListNode             Include ListNode support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(ListNode, whether to enable ListNode support,
dnl Make sure that the comment is aligned:
dnl [  --enable-ListNode           Enable ListNode support])


if test "$PHP_LISTNODE" != "no"; then
  dnl 使用C++编写扩展 首先编写m4文件
  PHP_REQUIRE_CXX()

  dnl 添加C++标准库文件
  PHP_ADD_LIBRARY(stdc++,"","")


  dnl Write more examples of tests here...

  dnl # --with-ListNode -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/ListNode.h"  # you most likely want to change this
  dnl if test -r $PHP_LISTNODE/$SEARCH_FOR; then # path given as parameter
  dnl   LISTNODE_DIR=$PHP_LISTNODE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for ListNode files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       LISTNODE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$LISTNODE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the ListNode distribution])
  dnl fi

  dnl # --with-ListNode -> add include path
  dnl PHP_ADD_INCLUDE($LISTNODE_DIR/include)

  dnl # --with-ListNode -> check for lib and symbol presence
  dnl LIBNAME=ListNode # you may want to change this
  dnl LIBSYMBOL=ListNode # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LISTNODE_DIR/$PHP_LIBDIR, LISTNODE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_LISTNODELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong ListNode lib version or lib not found])
  dnl ],[
  dnl   -L$LISTNODE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(LISTNODE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(ListNode, ListNode.c CListNode.h CListNode.cpp,$ext_shared)
fi
