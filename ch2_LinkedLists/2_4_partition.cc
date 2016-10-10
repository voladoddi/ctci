#include "util.h"

// ------------ PARTITION list --------------------
Node* partitionList(Node *node, int x)
{
    Node *head = node;
    Node *tail = node;
    
    while(node!=nullptr)
    {
         Node* next = node->next;
        
        if(node->data < x)
        {
            node->next = head;
            head       = node;
        }
        else
        {
            tail->next = node;
            tail       = node;
        }
        
        node = node->next; // WHY CAN'T THIS WORK.
        // "node = node->next" should be the same as
        // "node = next"       ?
    }
    tail->next = nullptr;
    return head;
}

/* ---------------------------- MAIN --------------------------------------- */
int main()
{
    vector<int> populateList{10,4,1,5,8,3,0,24,5};
    
    Node *listHead = buildList(populateList);
    Node *newHead = partitionList(listHead, 8);
    
    printList(newHead);
    
    return 0;
}