#include "util.h"



// ---------------------------- 2_2_returnKthToLast ---------------------------------------
//
//  Find the kth to last element of an unsorted linked list.
//
// ----------------------------------------------------------------------------------------

/***** [APPROACH 1] : ********
 
  ++++ Assumption: Length is known ++++

   - Traverse until (N-k) nodes, print data.
     
     Time  : O(N)   {If k=0, traverse until last node}
     Space : O(1)
******/



/***** [APPROACH 2] : ********
 
 ++++ Length unknown: ++++
 - Traverse the entire linkedlist and get length.
 Time  : O(N)
 Space : O(1)
 
 - Traverse until (N-k) nodes, print data.
 Time  : O(N)   {If k=0, traverse until last node}
 Space : O(1)
 
 TOTAL Time  : O(N)
 Space       : O(1)
 */

/***** [APPROACH 3] : *********
 

 - Initalize CURRENT and RUNNER.
 - Traverse list with RUNNER until "k" nodes. 
 - Traverse list with CURRENT and RUNNER until RUNNER hits end. 
 - Return CURRENT->data. 
 
 Time  : O(N)
 Space : O(1)
 
*/

void returnKthToLastA(Node *&head, int k)
{
    Node *current = head;
    Node *runner  = head;
    int count = 0;
    
    while (count<=k)                // ::NOTE:: The "="
    {
        if (runner==nullptr) break; // ::MISTAKE:: forgot this check for nullptr.
        runner = runner->next;
        count += 1;
        
    }
    
    while(runner!=nullptr)
    {
        runner = runner->next;
        current = current->next;
    }
    cout << "Kth to Last element: " << current->data << " \n" << endl;
}



/* ---------------------------- MAIN --------------------------------------- */
int main()
{
    vector<int> populateList{0,1,1,2,3,3,1,24,5};
    Node *listHead = buildList(populateList);
    
    printList(listHead);
    
    returnKthToLastA(listHead, 1);
    
    
    return 0;
}