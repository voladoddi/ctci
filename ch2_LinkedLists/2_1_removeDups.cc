#include "util.h"

// ---------------------------- 2_1_removeDups -------------------------------------------

/*
    [APPROACH 1] : 
 
    - Take current node,
    - Check all further nodes for duplicate data.
    - Increment current node.
 
    Time  : O(N^2)
    Space : O(1)
 */
void removeDupsA(Node *&head)
{
    Node *current = head;
    while (current!=nullptr)
    {
        Node *runner = current;
        while ( runner->next != nullptr)
        {
            if (runner->next-> data == current->data) {
                runner->next = runner->next->next;
            }
            else{
                runner = runner->next;
            }
        }
        current = current -> next;
    }
}



/*
    [APPROACH 2] :
    
    - Take current node.
    - If current_node[data] not in HTABLE, insert data, increment current_node 
      (keep track of current in another node to be able to remove current node)
    - Else increment node.
 
    Time  : O(N)
    Space : O(N)
 
 
 */
void removeDupsB(Node *&head)
{
    unordered_map<int,bool> htable;
    Node *current = head;
    Node *previous = nullptr;
    
    while (current!=nullptr)
    {
        // if the hashtable already contains the node's data
        if(!htable[current->data]){
            htable[current->data] = true;
            previous = current;
            current  = current->next;
        }
        // else
        else{
            previous->next = current->next; //removing traces of link [from]previous [to]current.
            current        = previous->next;
        }
    }
}


/* ---------------------------- MAIN --------------------------------------- */
int main()
{
    vector<int> populateList{0,1,1,2,3,3,1,24,5};
    Node *listHead = buildList(populateList);
    
    printList(listHead);
    
    removeDupsB(listHead);
    
    printList(listHead);
    
    return 0;
}