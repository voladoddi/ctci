#include "util.h"

// **** 
bool isEqual(Node* listhead,Node* reverselisthead )
{
    cout << "Entering --- isEqual \n"<<endl;
    printList(listhead);
    printList(reverselisthead);
    
    while (listhead && reverselisthead) {
        if(listhead->data != reverselisthead->data) return false;
        listhead = listhead->next;
        reverselisthead = reverselisthead->next;
    }
    return true;
}

bool isPalindrome(Node* &pHead)
{
    Node *copied   = copyList(pHead);
    Node *reversed = reverseList(pHead);
    //:: NOTE :: Copied list is new, while as reversed has changed the original list.
    //           practice deep copy for reversing the list.
    //           i.e. Return a reversed list in a new list (copy of the original).
    
    return isEqual(copied,reversed);
}

int main()
{
    vector<int> vec{0,7,1,9,1};

    Node *L1 = buildList(vec);
    printList(L1);

    int yes = isPalindrome(L1);
    string result = (yes ==1) ? "\nList is a palindrome \n" : "\nNot a palindrome\n";
    cout << result << endl;

    return 0;
}