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
    
    if (this->head != nullptr){
        list_node *current = this->head;
        list_node *pNext = head->next;

        while (current != nullptr)
        {
            efree(current);
            current = nullptr;
            if (pNext){
                current = pNext;
                pNext = current->next;
            }
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
    zval_copy_ctor(new_val);//如果是非标量 添加引用计数 
    //convert_to_string(new_val);//转成string
    
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

int CListNode::del_value(int index)
{
    if (index <= 0 || index > this->size)
    {
        return -1;
    }

    list_node* pCurrent = head;
    list_node* tmp = nullptr;

    if (pCurrent != nullptr){
        int i = 1;
        if (i == index){

            head = head->next;
            head->prev = nullptr;
            efree(pCurrent);
            --this->size;
            return 0;
        }
        else{
            while (pCurrent != nullptr){
                ++i;
                tmp = pCurrent;
                pCurrent = pCurrent->next;
                if (i == index && pCurrent != nullptr){
                    tmp->next = pCurrent->next;
                    if (pCurrent->next != nullptr){
                        pCurrent->next->prev = tmp;
                    }
                    else{
                        tail = tmp;
                    }
                    zval_dtor(pCurrent->value);
                    efree(pCurrent);
                    --this->size;
                    return 0;
                }
                
            }

            return -1;
        }

    }
    else{
        return -1;
    }
}