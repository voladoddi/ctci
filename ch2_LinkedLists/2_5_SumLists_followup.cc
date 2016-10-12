#include "util.h"

// ------------------------ FORWARD sum lists -----------------------------------------------
Node* sumForwardHelper(Node* L1, Node* L2, int &carry)
{
    if(L1==nullptr && L2==nullptr && carry==0)
        return nullptr;
    Node* result = sumForwardHelper( (L1 ? L1->next: nullptr) ,(L2 ? L2->next : nullptr),(carry));
    
    int value = carry + (L1? (L1->data) : 0) + (L2? (L2->data) : 0);
    insertAtHead(result, value%10);
    carry = (value>9) ? 1:0;
    return result;
    
}


Node* sumListsForward(Node *L1, Node* L2)
{
    /*
     1. check length of longer list ,
     2. pad zeros (|l1-l2|) to minlength(l1,l2).
     3. recurse and then add so that lists are added R->L.
     4. After recursion exits, check if carry case exists. 
     */
    
    //1.
    int length_l1 = length(L1);
    int length_l2 = length(L2);
    cout << length_l1 << length_l2 << endl;
    
    //2.
    if(length_l1<length_l2)
        padList(L1, length_l2-length_l1);
    else
        padList(L2, length_l1-length_l2);
    
    //3.
    int carry = 0;
    Node* resultHead = sumForwardHelper(L1, L2, carry);
   
    //4.
    if(carry)
        insertAtHead(resultHead, carry);
 
    return resultHead;
}

/* ---------------------------- MAIN --------------------------------------- */
int main()
{
    vector<int> L1vec{0,7,1,9,1};
    vector<int> L2vec{5,9,9};
    Node *L1 = buildList(L1vec);
    Node *L2 = buildList(L2vec);
    
    printList(L1);
    printList(L2);
    
    Node *summed = sumListsForward(L1, L2);
    
    printList(summed);
    
    
    return 0;
}