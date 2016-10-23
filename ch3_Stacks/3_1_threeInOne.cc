
#include "3_1_threeInOne.h"

// -----(0)-------- CONSTRUCTOR ------------
Multistack::Multistack(int stackCapacity)
{
    
    this->kthStackCapacity = stackCapacity;
    this->stackArray = new int[numStacks * stackCapacity];
    this->kthStackUsedSize   = new int[numStacks];
}


// -----(1)--------- DESTRUCTOR --------------
Multistack::~Multistack()
{
    delete []stackArray; // [?] "delete * vs delete []"
    delete []kthStackUsedSize;
    
    
}

// -------------- isEMPTY ----------------------
bool Multistack::isEmpty(int stackNumber) const
{
    return (kthStackUsedSize[stackNumber]==0);
}

// -------------- isFULL -------------------------
bool Multistack::isFull(int stackNumber) const
{
    return (kthStackUsedSize[stackNumber]==kthStackCapacity);
}

// ---------------- PUSH ---------------------
void Multistack::push(int stackNumber, int value)
{
    if (isFull(stackNumber)){
        cout << "Stack " << stackNumber << " is full" << endl;
        return;
    }
    else
    {
        
        kthStackUsedSize[stackNumber]++;
        
        int topIdx = kthStackTop(stackNumber);
        stackArray[topIdx++] = value;
        
        
    }
}


// ------------- POP ----------------
void Multistack::pop(int stackNumber)
{
    if (isEmpty(stackNumber)){
        cout << "Stack " << stackNumber << "underflow" << endl;
        return;
    }
    else
    {
        int topIdx = kthStackTop(stackNumber);
       // stackArray[topIdx] = 0;              //[?] Required
        kthStackUsedSize[stackNumber]--;
        
    }
}

// -------- TOP ----------------
int Multistack::top(int stackNumber) const
{
    if (isEmpty(stackNumber))
    {
        cout << "Stack empty " << endl;
        exit(-1);
    }
    else
        return stackArray[kthStackTop(stackNumber)];
}

// ------------ kth stack Top --------------------------
int Multistack::kthStackTop(int stackNumber) const
{
    int sIdx = stackNumber * kthStackCapacity;
    int usedCapacity = kthStackUsedSize[stackNumber];
    return (sIdx + usedCapacity - 1);
}

// ------------- Main ----------------------------------
int main()
{
    Multistack myStack(3);
    myStack.push(0,2);
    myStack.push(0,3);
    myStack.push(0,3);
    
    myStack.push(1,3);
    myStack.push(1,3);
    myStack.push(1,3);
    
    int topelem = myStack.top(0);
    
    
    cout << topelem << endl;
    cout << "\nHello\n"<<endl;
    
    myStack.pop(0);
    myStack.pop(0);
    //myStack.pop(0);
    
    
    topelem = myStack.top(0);
    
    
    cout << topelem << endl;
    cout << "\nHello\n"<<endl;
    
    return 0;
}
 

/*
    NOTES, COMMENTS AND OBSERVATIONS 
    
    [1] Mistake: pushing onto the stack without incrementing the top first. 
                 This has to happen if during the start of the stack (when push is carried out on an initially empty stack), your idx = -1
 
                 which is what is happening in -
                
                    Multistack::push(){
                    ...
                    return (sIdx + usedCapacity - 1);
                    }
                
                 If
            
                    Multistack::kthStackTop(){
                    ...
                    return (sIdx + usedCapacity);
                    }
 
                 Then
                    Multistack::top(){
                    ...
                    return stackArray[kthStackTop(stackNumber)-1];
                    }
 
                    Multistack::push(){
                    ...
                    else
                    {
                    ...
                    int topIdx = kthStackTop(stackNumber);
                    stackArray[topIdx] = value;
 
                    kthStackUsedSize[stackNumber]++;
 
                    ... }
 
    [2]
 
 
 */

