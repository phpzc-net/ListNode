//
// Created by 张成 on 16/4/26.
//

#ifndef LISTNODE_CLISTNODE_H
#define LISTNODE_CLISTNODE_H

extern "C" {
#include "php.h"
};

typedef struct list_node{
    zval *value;
    list_node *prev;
    list_node *next;
}list_node;

class CListNode {
public:

    static CListNode* create();

    int add_head(zval *value);

    int add_tail(zval *value);

    int del_index(int index);

    int fetch_index(int index,zval **retval);

    int get_length() const;
private:

    CListNode(){};
    ~CListNode(){};
    int size;
    list_node *head;
    list_node *tail;
};


#endif //LISTNODE_CLISTNODE_H
