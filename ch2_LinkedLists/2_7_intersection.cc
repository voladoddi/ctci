#include "util.h"


Node* intersectingNode(Node *L1, Node* L2)
{
    
    // traverse first to their tails, and check if tails are same node.
    Node *pCurrentL1 = L1;
    Node *pCurrentL2 = L2;
    
    while(pCurrentL1->next!=nullptr)
        pCurrentL1 = pCurrentL1->next;
    while(pCurrentL2->next!=nullptr)
        pCurrentL2 = pCurrentL2->next;
    if (pCurrentL1 != pCurrentL2) return nullptr;
    

    
    // check if equal lengths so as to figure out the common starting node NUMBER (ignore extra few initial nodes of the longer list).
    int lenL1 = length(L1);                      //:: MISTAKE:: HAD passed this by reference.
    int lenL2 = length(L2);                      //   Which resulted in getting the tail of L1 and L2 from "length" fn.
    int count = 0;
    if(lenL1 > lenL2)
    {
        cout << "Entered case where len1 > len2" << endl;
        while((lenL1-lenL2))
        {
            count = count + 1;
            L1 = L1->next;
        }

    }
    else if (lenL1 < lenL2)
    {
        cout << "Entered case where len2 > len1 " <<endl;
        while(count<(lenL2 - lenL1))
        {
            count = count + 1;
            L2 = L2->next;
        }
    }
    
    // traverse both lists until there's a collision.
    while(L1!=L2)
    {
        L1 = L1->next;
        L2 = L2->next;
    }
    return L2;      // return either L1 OR L2 (which is the intersecting node)
}



int main()
{
    // build L1 and L2
    vector<int> vecf{0,7,1,9,1};
    Node *L1 = buildList(vecf);
    printList(L1);
    vector<int> vecs{9,2,4,3,1};
    Node *L2 = buildList(vecs);
    printList(L2);
    
    // form an intersecting LL
    L2->next->next->next = L1->next->next;
    printList(L1);
    printList(L2);
    
    Node *resultNode = intersectingNode(L1,L2);
    cout << "\n Result node address: " << resultNode << "\n";
    cout << "\n Result node data: "    << resultNode->data << "\n" << endl;;
   
    return 0;
}