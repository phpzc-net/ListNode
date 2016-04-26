//
// Created by 张成 on 16/4/26.
//

#include "CListNode.h"
#include <iostream>
using namespace std;

static CListNode* CListNode::create()
{
    return nullptr;
}

int CListNode::add_head(zval *value)
{
    return 0;
}

int CListNode::add_tail(zval *value)
{
    return 0;
}


int CListNode::del_index(int index)
{
    return 0;
}

int CListNode::fetch_index(int index,zval **retval)
{
    return 0;
}

int CListNode::get_length() const
{
    return this->size;
}