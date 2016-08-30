int Solution::evalRPN(vector<string> &A) {
    
    std::stack<int> st;
    int op1, op2;
    int i = 0;
    
    for(i=0; i<A.size();i++)
    {
        if (A[i]=="+" || A[i]=="-" || A[i]=="*" || A[i]=="/")
        {
            op2 = st.top();
            st.pop();
            op1 = st.top();
            st.pop();
            if (A[i]=="+")
                st.push(op1 + op2);
            else if (A[i]=="-")
                st.push(op1 - op2);
            else if (A[i]=="*")
                st.push(op1 * op2);
            else if (A[i]=="/")
                st.push(op1 / op2);
            else{
                cout << "Illegal operator" << endl;
                break;
            }
        }
        else
            st.push(atoi(A[i].c_str())); //c_str() usage essential to use atoi
                                         // since A[i] in a vec<str> is const char*
        
    }
    return st.top();
}