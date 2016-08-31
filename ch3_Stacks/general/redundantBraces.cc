/*
 Write a program to validate if the input string has redundant braces?
 Return 0/1
 0 -> NO 1 -> YES
 
 Input will be always a valid expression
 
 and operators allowed are only + , * , - , /
 
 Example:
 
 ((a+b)) has redundant braces so answer will be 1
 (a + (a + b)) doesn't have have any redundant braces so answer will be 0
 */


int Solution::braces(string A) {
    
    // push until the character encountered is ")".
    // pop and count the number of characters you've to pop to get to "(".
    // if less than 2, that means you couldn't eliminate a subexpression => redundant braces.
    // ----
    // Assuming you've eliminated all the sub expressions, if there are braces still left in the stack, then
    // redundant too.
    stack<char> st;
    for(int i=0; i<A.size();i++)
    {
        if(A[i]==')')
        {
            int count = 0;
            while(st.top()!='(')
            {
                st.pop();
                count++;
            }
            st.pop(); // Missed this the first time around. Closes the expression by removing the "(".
            if (count < 2)
                return 1;
        }
        else
            st.push(A[i]);
    }
    int stillPresent = 0;
    while(!st.empty())
    {
        if (st.top()=='(' || st.top()==')')
            stillPresent = 1;
        break;
    }
    if (stillPresent)
        return 1;
    else
        return 0;
    
}
