/*
 Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 
 The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 
 Return 0 / 1 ( 0 for false, 1 for true ) for this problem
 */
bool isPair(char a, char b)
{
    if(a=='{' && b=='}') return true;
    else if(a=='(' && b==')') return true;
    else if(a=='[' && b==']') return true;
    return false;
}
int Solution::isValid(string A) {
    std::stack<char> st;
    char ch;
    
    for (int i = 0; i < A.size();i++)
    {
        if (A[i]=='{' || A[i]=='(' || A[i]=='[')
            st.push(A[i]);
        else if (A[i]=='}' || A[i]==')' || A[i]==']')
        {
            if (st.empty() || !isPair(st.top(),A[i]))
                return false;
            else
                st.pop();
        }
        
    }
    int val = (st.empty() ? true:false);
    return val;
}

/* COMMENTS, NOTES and OBSERVATIONS.
 
 [1]. Time = O(n) since every character of the string has to be looked at.
 
 [2]. Mistakes made:
      -> implementation of isPair. Double check the order of params passed and args.
      -> implementation of isPair. switch logic is not needed, have to compare a pair. No use in storing the complement in a variable, store the result of comparison in a variable instead.
 

 */