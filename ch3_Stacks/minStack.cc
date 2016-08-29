#include <iostream>
using namespace std;

class Stack
{
private:
    int *superStack;
    int *minStack;
    int top, minTop;
    
public:
    Stack();
    Stack(int max)
    {
        superStack = new int[max];
        minStack = new int[max];
        top = 0;
        minTop = 0;
    }
    void push(int data)
    {
        // if superstack is null, push to both stacks.
        // if not, check if the element being pushed is lesser than minStack[top]
        // is yes, push to min stack.
        if (top==0)
        {
            superStack[top++]  = data;
            minStack[minTop++] = data;
            return;
        }
        if (data < minStack[minTop-1])
            minStack[minTop++] = data;
        superStack[top++] = data;
    }
    int pop()
    {
        // check if element being popped from superStack is equal to top of minStack
        // if yes, pop from minStack also. else, just pop from superStack
        if (superStack[top-1]==minStack[minTop-1])
            minTop--;
        return superStack[--top];
    }
    int getMin()
    {
        return minStack[minTop-1];
    }
    
};

int main() {
	// your code goes here
	Stack st(10);
	st.push(5);
	st.push(1);
	st.push(3);
	st.push(-12);
	st.push(0);
	
	cout << st.getMin();
	
	return 0;
}
