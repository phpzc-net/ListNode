#ifndef _CLISTNODE_H_
#define _CLISTNODE_H_
#include "php.h"
typedef struct list_node{
    zval* value;
    //int value;
    list_node *prev;
    list_node *next;
}list_node;

class CListNode {
public:
    CListNode();
    ~CListNode();
    static CListNode* create();

    int add_value(zval *val);
	int del_value(int index);
    zval* fetch_index(int index);

    int get_length() const;
private:

    int size;
    list_node *head;
    list_node *tail;
};
#endif