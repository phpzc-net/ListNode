cmake_minimum_required(VERSION 3.5)
project(ListNode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ListNode.c php_ListNode.h CListNode.cpp CListNode.h)
INCLUDE_DIRECTORIES(
        "/Users/zhangcheng/App/php-5.6.20"
        "/Users/zhangcheng/App/php-5.6.20/main"
        "/Users/zhangcheng/App/php-5.6.20/Zend"
        "/Users/zhangcheng/App/php-5.6.20/TSRM"
)
add_library(ListNode ${SOURCE_FILES})