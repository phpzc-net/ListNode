//
// Created by 张成 on 16/4/26.
//

#include "CListNode.h"
#include <cstddef>
#include <iostream>
using namespace std;

CListNode* CListNode::create()
{
    CListNode* obj = new CListNode;
    obj->head = nullptr;
    obj->tail = nullptr;
    return obj;
}


int CListNode::get_length() const
{
    return this->size;
}

int CListNode::add_value(int val) {

    list_node* node = (list_node*)malloc(sizeof(list_node));
    if(node == nullptr){
        return -1;
    }
    node->value = val;
    node->next = nullptr;

    if(this->head == nullptr){
        head = node;
        node->prev = nullptr;
        tail = node;
    }else{
        tail->next = node;
        node->prev = tail;
        tail = node;
    }

    this->size = this->size + 1;

    return 0;
}

// fetch出指定 索引节点的值
int CListNode::fetch_index(int index, int &data) {

    if(index <= 0 || index > this->size){
        return 0;
    }

    list_node* pHead = head;
    if(pHead != nullptr){
        while(index > 1){
            pHead = pHead->next;
            --index;
        }

        data = pHead->value;
    }else{
        return 0;
    }

    return 1;

}
