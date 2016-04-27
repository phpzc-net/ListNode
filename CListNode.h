//
// Created by 张成 on 16/4/26.
//

#ifndef LISTNODE_CLISTNODE_H
#define LISTNODE_CLISTNODE_H


typedef struct list_node{
    int value;
    list_node *prev;
    list_node *next;
}list_node;

class CListNode {
public:

    static CListNode* create();

    int add_value(int val);

    int fetch_index(int index,int &data);

    int get_length() const;
private:

    CListNode(){};
    ~CListNode(){};
    int size;
    list_node *head;
    list_node *tail;
};


#endif //LISTNODE_CLISTNODE_H
