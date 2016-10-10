#include "util.h"

// ------------------------ FORWARD sum lists -----------------------------------------------
Node* sumListsForward(Node *L1, Node* L2, int carry)
{
    
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