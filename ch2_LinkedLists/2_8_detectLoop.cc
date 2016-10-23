#include "util.h"

Node* loopNode (Node* head)
{
    Node *fastPtr = head;
    Node *slowPtr = head;
    // 1. Move fastPtr 2 steps, for every 1 step pf slow Ptr.
    // 2. If at some point, they collide and neithre ptr is null, then loop is detected.
    // 3. Move slowPtr to the start of the head. Then move both slowPtr and fastPtr at one step.
    while(fastPtr!=nullptr && fastPtr->next!=nullptr)
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
        if(slowPtr==fastPtr)
            break;
    }
   
    if (fastPtr==nullptr || fastPtr->next==nullptr) return nullptr;
    
    slowPtr = head;
    while (slowPtr!=fastPtr) {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next;
    }
    
    return fastPtr;
}


int main()
{
    vector<int> vec{1,32,5,11,9, 6, 45,4,0,7};
    Node *L1 = buildList(vec);
    // print list.
    printList(L1);

    // Create a loop node.
    L1->next->next->next->next->next->next->next->next->next->next = L1->next->next->next->next;
 
    // Floyd Warshal's cycle detection algo.
    Node *resultNode = loopNode(L1);
    if(resultNode==nullptr) cout << "End of list reached. No loop\n\n\n" << endl;
    else cout << "Loop detected at Node : " << resultNode->data << "\n" << endl;
    
    return 0;
}