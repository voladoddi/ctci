#include "util.h"


/***** [APPROACH 1] *******
 -- ITERATIVE

 - If both lists are empty (NULL) and carry is empty , return false.
 - Else, 
   <-> While one of the lists' head is not a nullptr, iterate through -- add, and take carry forward to next sum node.
       <<->> If one of the lists' head is a nullptr, then iterate through the longer list, add and take carry forward.
   <-> If carry remains and both lists are iterated through completely, create a new node with carry result and add to tail. 
 
 Time     : O(max(M,N)) -- time to iterate through the longer list of L1 (length M), L2 (length N)
 Space    : O(max(M,N)) -- length equivalent to #nodes of the longer of the lists L1,L2.

*/

Node *sumListsIterative(Node* L1, Node* L2)
{
    int carry = 0;
    int value = 0;
    
    Node *resultNode;
    Node *resultHead = nullptr;
    Node *resultTail = nullptr;
    
    if(L1==nullptr && L2==nullptr && carry==0) return nullptr; //if lists are empty and carry is empty.
    else
    {
        while(L1!=nullptr || L2!=nullptr)
        {
            resultNode = new Node;
            value = L1->data + L2->data + carry;
            carry = (value>9) ? 1 : 0;
            
            resultNode->data = value%10;
            resultNode->next = nullptr;
            
            if(resultHead==nullptr){
                resultHead = resultNode;
                resultTail = resultNode;
            }
            else{
                resultTail->next = resultNode;
                resultTail       = resultNode;
            }
        
            L1 = L1->next;
            L2 = L2->next;
        
            
            if(L2==nullptr){
                while(L1!=nullptr){                  //::MISTAKE:: These while loops should exist within the main while loop since
                                                     //            we're OR-ing the condition L1!=null||L2!=null
                resultNode = new Node;               //            Results in SEG FAULT if lists are of unequal length and the check
                                                     //            for handling the longer list does not exist.
                value = L1->data + carry;
                carry = (value>9) ? 1:0;
                resultNode->data = value%10;
                resultNode->next = nullptr;
                
                resultTail->next = resultNode;
                resultTail       = resultNode;
            
                L1    = L1->next;
                }
            }
        
            if(L1==nullptr){
            while(L2!=nullptr){
                resultNode = new Node;
            
                value = L2->data + carry;
                carry = (value>9) ? 1:0;
                resultNode->data = value%10;
                resultNode->next = nullptr;
                
                resultTail->next = resultNode;
                resultTail       = resultNode;
            
                L2    = L2->next;
            
                }
            }
        }
   }
    
    if(carry)                       // ::MISTAKE:: Missed this. When head's sum > 10, add a new head node with carry.
    {
        resultNode = new Node;
        resultNode->data = carry;
        resultNode->next = nullptr;
        
        resultTail->next = resultNode;
        resultTail       = resultNode;
        
    }
    
    
        return resultHead;

}

/***** [APPROACH 2] *******
 -- RECURSIVE
 
 - If both lists are empty (NULL) and carry is empty , return false.
 - Else,
 <-> While one of the lists' head is not a nullptr, iterate through -- add, and take carry forward to next sum node.
 <<->> If one of the lists' head is a nullptr, then iterate through the longer list, add and take carry forward.
 <-> If carry remains and both lists are iterated through completely, create a new node with carry result and add to tail.
 
 Time     : O(max(M,N)) -- time to iterate through the longer list of L1 (length M), L2 (length N)
 Space    : O(max(M,N)) -- length equivalent to #nodes of the longer of the lists L1,L2.
 
 */
Node* sumListsRecursive(Node* L1, Node* L2, int carry)
{
    // Base Case.
    if (L1==nullptr && L2==nullptr && carry==0)
        return nullptr;
    
    // Recurse
    int value = carry;
    if(L1)
        value += L1->data;
    if(L2)
        value += L2->data;
    Node *resultNode = new Node;        // |
    resultNode->data = (value%10);      // |--> new node creation. 
    resultNode->next = nullptr;         // |
    
    
    resultNode->next = sumListsRecursive( (L1 ? (L1->next) : nullptr) , (L2 ? (L2->next) : nullptr), (value>9 ? 1 :0));
    
    return resultNode;
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
    
    Node *summedIterative = sumListsIterative(L1, L2);
    printList(summedIterative);
    
    Node *summedRecursive = sumListsRecursive(L1, L2, 0);
    printList(summedRecursive);
    
    return 0;
}