#include "linkedStack.h"
#include <iostream>
using namespace std;

int main()
{
    linkedStack<int> stack;
    linkedStack<int> otherStack;
    linkedStack<int> newStack;
    
    //Add elements into stack
    stack.push(34);
    stack.push(43);
    stack.push(27);
    
    
    newStack = stack;
    cout << newStack.top() << endl;
    
    return 0;
}

