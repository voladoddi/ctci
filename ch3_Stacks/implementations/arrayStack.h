#ifndef H_StackType
#define H_StackType

#include <stdexcept>
#include <iostream>
#include <cassert>

#include "adtStack.h"
using namespace std;

/*
// For Linked list implementation of a STACK.
class Node
{
    private:
        int data;
        Node *next;
};

class listStack
{
    public:
    // Constructors/Destructors
    
    
    // Functions
};
*/

// --------- IMPLEMENTATION of the ABSTRACT class above ---------
template <class type>
class stackType: public stackADT<type>
{
    private:
        int maxStackSize;
        int stackTop;
        type *list;
    
        /*
         The function copyStack is included as a private member. 
         It contains the code that is common to the functions to overload the assignment operator and the copy constructor.
         We use this function only to implement the copy constructor and overload the assignment operator. To copy a stack
         into another stack, the program can use the assignment operator.
        */
        void copyStack(const stackType<type>& otherStack);
    
    public:
        // constructors/destructors.
        stackType(int stackSize = 100);
        stackType(const stackType<type>& otherStack);               // use copyStack for copy constructor
        ~stackType();
    
        // member fns.
        const stackType<type>& operator=(const stackType<type>& );  // use copyStack for overload assign.
        void initializeStack();
        bool isEmptyStack() const;
        bool isFullStack() const;
        void push(const type& newItem);
        type top() const;
        void pop();
    
    
};


// ---------- Class member function definitions.

// 0.    Constructor
template <class type>
stackType<type>::stackType(int stackSize)
{
    //check for size validity
    if (stackSize <= 0){
        cout << "Size is positive. Created array of size 100" << endl;
        maxStackSize = 100;
    }
    else
        maxStackSize = stackSize;
    
    // create list.
    stackTop = 0;
    list = new type[maxStackSize];
    
}

// 1.    Copy constructor
// Later.

// 0.    Destructor
template<class type>
stackType<type>::~stackType()
{
    delete []list;
}

// 1.    Initialize.
template <class type>
void stackType<type>::initializeStack() {
    stackTop = 0;
}

// 2.   Empty ?
template <class type>
bool stackType<type>::isEmptyStack() const{
    return(stackTop==0);
}
// 3.   Full ?
template <class type>
bool stackType<type>::isFullStack() const{
    return(stackTop == maxStackSize);
}

// 4. PUSH
template <class type>
void stackType<type>::push(const type& newItem)
{
    if(!isFullStack()){
        list[stackTop] = newItem;
        stackTop++;
    }
    else
        cout << "Cannot add to a full stack." << endl;
}

// 5. TOP
template <class type>
type stackType<type>::top() const
{
    assert(stackTop!=0);
    return list[stackTop-1];
}

// 6. POP
template <class type>
void stackType<type>::pop()
{
    if(!isEmptyStack())
        stackTop--;
    else
        cout << "Cannot remove from empty stacks." << endl;
}

// ------ copy stack, copy constructor, and overloaded = .
template <class type>
void stackType<type>::copyStack(const stackType<type>& otherStack)
{
    /*
     1. delete existing list.
     2. initialize all mem variables.
     3. copy other stack into this stack.
     */
    delete []list;
    
    maxStackSize = otherStack.maxStackSize;
    stackTop = otherStack.stackTop;
    list = new type[maxStackSize];
    
    for (int i = 0; i < stackTop; i++)
        list[i] = otherStack.list[i];
    
}

template <class type>
stackType<type>::stackType(const stackType<type>& otherStack)
{
    list = nullptr;
    copyStack(otherStack);
}

template <class type>
const stackType<type>& stackType<type>::operator=(const stackType<type>& otherStack)
{
    if(this!=&otherStack)
        copyStack(otherStack);
    return *this;
}

#endif







