#ifndef H_linkedlistStackType
#define H_linkedlistStackType

#include <stdexcept>
#include <iostream>
#include <cassert>

#include "adtStack.h"
using namespace std;

// Definition of the node.
template <class type>
struct node
{
    type data;
    node<type> *next;
};                                                              // [?] What if I "typedef" ?

// ******* Implementation of the abstract class *******

// --- Declaration ---
template <class type>
class linkedStack : public stackADT<type>
{
    private:
        node<type> *stackTop;     // [?]Head? [A]Yes.
        void copyStack(const linkedStack<type>& otherStack); // [?] Why is this required
                                                                 // when I can have copy constructor directly,
                                                                 // and why is this private?
    
    public:
        linkedStack();
        linkedStack(const linkedStack<type>& otherStack);
        ~linkedStack();
        const linkedStack<type>& operator=(const linkedStack<type>&);
    
        bool isEmptyStack() const;
        bool isFullStack() const;
    
        void initializeStack();
        void push(const type& newItem);
        type top() const;
        void pop();
    
};

// --- Definition ----
// 0. (a)  Constructor
template <class type>
linkedStack<type>::linkedStack()
{
    stackTop = nullptr;
}

// 0. (b) copy constructor, destructor, assignment operator overloading - later.

// 1. Empty stack
template <class type>
bool linkedStack<type>::isEmptyStack() const
{
    return(stackTop==nullptr);
}
// 2. Full stack --- for brevity since included in ABSTRACT CLASS definition.
template <class type>
bool linkedStack<type>::isFullStack() const
{
    return false;
}

// 3. Initialize stack
template <class type>
void linkedStack<type>::initializeStack()
{
    // if a stack exists, delete all nodes, initialize stackTop to nullptr.
    node<type> *temp;
    while(stackTop != nullptr)
    {
        temp = stackTop;
        stackTop = stackTop->next;
        delete temp;
    }
}

// 4. push
template<class type>
void linkedStack<type>::push(const type& newItem)
{
    node<type> *newNode = new node<type>;
    newNode ->data = newItem;
    newNode ->next = stackTop;
    stackTop       = newNode;
}

// 5. Top
template<class type>
type linkedStack<type>::top() const
{
    assert(stackTop!=nullptr);
    return stackTop->data;
    
}

// 6. Pop
template <class type>
void linkedStack<type>::pop()
{
    node<type> *temp;
    if (stackTop!=nullptr)
    {
        temp = stackTop;
        stackTop = stackTop->next;
        delete temp;
    }
    else
        cout << "Stack UNDERFLOW: empty stack." << endl;
    
}

// 0. (b) Copy stack
template <class type>
void linkedStack<type>::copyStack(const linkedStack<type>& otherStack)
{
    node<type> *newNode, *current, *last;
    if (stackTop==nullptr)  initializeStack();
    else if (otherStack.stackTop==nullptr)  stackTop =nullptr;
    else
    {
        // point current to the stack top from other stack to copy.
        current = otherStack.stackTop;
        // create the object stack's stack top, and copy over from the CURRENT pointing to otherstack.
        stackTop = new node<type>;
        stackTop->data = current->data;
        stackTop->next = nullptr;
        // iterate through the other stack, and keep a track of the stackTop of the destination stack.
        last = stackTop;
        current = current->next;
        while(current!=nullptr)
        {
            newNode = new node<type>;
            newNode-> data = current->data;
            newNode-> next = nullptr;
            
            last = newNode;
            current = current->next;
        }
    }
        
}

// 0. (b) copy constructor.
template <class type>
linkedStack<type>::linkedStack(const linkedStack<type>& otherStack)
{
    stackTop = nullptr;         // this is important. what happens if I don't do this.
    copyStack(otherStack);
}

// 0. (b) Overloaded assigment operator.
template<class type>
const linkedStack<type>& linkedStack<type>::operator=(const linkedStack<type>& otherStack)
{
    if(this != &otherStack)
        copyStack(otherStack);
    return *this;
}

// 0. (b) Destructor
template<class type>
linkedStack<type>::~linkedStack()
{
    initializeStack();
}


#endif

