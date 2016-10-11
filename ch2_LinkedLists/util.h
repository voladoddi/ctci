#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using std::endl;
using std::cout;
using std::vector;
using std::unordered_map;
using std::string;

/* ------------------------ CLASS DEFINITIONS and FUNCTIONS ------------ */

// Node definition.
struct Node
{
    int data;
    struct Node *next;
    
};

// Helper 1 - build List
Node* buildList(vector<int> &useThisVectorToBuildList)
{
    Node *newNode, *head = nullptr, *tail = nullptr;  //::MISTAKE:: essential to initialize. Else undefined behaviour.
    
    for(vector<int>::iterator vecItr = useThisVectorToBuildList.begin(); vecItr!=useThisVectorToBuildList.end() ; vecItr++)
    {
        
        //create new node
        newNode = new Node;
        newNode->data = *vecItr;
        newNode->next = nullptr;
        
        // if first node - head - hasn't been created yet
        if(head==nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            tail       = newNode;
        }
        
    }
    cout << "\n" << endl;
    return head;
}

// Helper 2 - print List
void printList(Node* &head)
{
    Node* temp = head;
    while(temp!=nullptr){
        cout << temp->data << " ";
        temp = temp->next;                        //::MISTAKE:: Missed this. Infinite loop.
    }
    cout << '\n' << endl;
}

// Helper 3 - reverse List
Node *reverseList(Node* &head)
{
    Node *current = head;
    Node *prev = nullptr, *next = nullptr;
    
    while(current!=nullptr)
    {
        // keep a track of the "next node" so you can still access it after reversing the link.
        next = current->next;
        // reverse link.
        current->next = prev;
        prev          = current;
        current       = next;
    }
    head = prev;
    return head;
}

// Helper 4 --- copy list
Node *copyList(Node* head)
{
    Node *newhead = nullptr, *newtail = nullptr;
    while(head!=nullptr)
    {
        Node *newNode = new Node;
        newNode->data = head->data;
        newNode->next = nullptr;
       
        if(newhead==nullptr){
            newhead = newNode;
            newtail = newNode;
        }
        else{
            newtail->next = newNode;
            newtail       = newNode;
        }

        
    }
    return newhead;
}
