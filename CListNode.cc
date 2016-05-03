//
// Created by 张成 on 16/4/26.
//
#include "CListNode.h"
#include <cstddef>
#include <iostream>
#include <memory>
#include "php.h"

using namespace std;

CListNode::CListNode()
{
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

CListNode::~CListNode()
{
    cout << "CListNode Destory" << endl;
    
    if (this->head != nullptr){
        list_node *current = this->head;
        list_node *pNext = head->next;

        while (current != nullptr)
        {

            cout << "CListNode Destory -- node->" << Z_STRVAL_P(current->value) << endl;
            //zval_dtor(current->value);
            efree(current);
            current = nullptr;
            if (pNext){
                current = pNext;
                pNext = current->next;
            }

            cout << "CListNode Destory -- while" << endl;
        }

    }
    
}

CListNode* CListNode::create()
{
    CListNode* obj = new CListNode;
    return obj;
}


int CListNode::get_length() const
{
    return this->size;
}

int CListNode::add_value(zval* val) {
    
    list_node* node = (list_node*)emalloc(sizeof(list_node));
    if (node == nullptr){
        return -1;
    }
    zval *new_val;
    MAKE_STD_ZVAL(new_val);
    *new_val = *val;
    zval_copy_ctor(new_val);
    convert_to_string(new_val);//转成string
    
    node->value = new_val;
    node->next = nullptr;

    if (this->head == nullptr){
        head = node;
        head->prev = nullptr;
        tail = node;
    }
    else{
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    
    this->size = this->size + 1;
    cout << "CListNode Add" << endl;
    return 0;
}

// fetch出指定 索引节点的值
zval* CListNode::fetch_index(int index) {

    if (index <= 0 || index > this->size){
        return nullptr;
    }

    list_node* pHead = head;
    if (pHead != nullptr){
        while (index > 1){
            pHead = pHead->next;
            --index;
        }

        return pHead->value;
    }
    else{
        return nullptr;
    }

}
