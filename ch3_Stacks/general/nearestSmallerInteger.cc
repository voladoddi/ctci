/*
 Given an array, find the nearest smaller element G[i] for every element A[i] in the array such that the element has an index smaller than i.
 
 More formally,
 
 G[i] for an element A[i] = an element A[j] such that
 j is maximum possible AND
 j < i AND
 A[j] < A[i]
 Elements for which no smaller element exist, consider next smaller element as -1.
 
 Example:
 
 Input : A : [4, 5, 2, 10]
 Return : [-1, 4, -1, 2]
 
 Example 2:
 
 Input : A : [3, 2, 1]
 Return : [-1, -1, -1]
 */

vector<int> Solution::prevSmaller(vector<int> &A) {
    stack <int> st;
    vector <int> v;
    
    for(int i=0; i<A.size();i++)
    {
        while(!st.empty() && st.top()>=A[i])
            st.pop();
        if(!st.empty())
            v.push_back(st.top());
        else
            v.push_back(-1);
        st.push(A[i]);
    }
    return v;
}

/*
 [1] Understand and double check the importance of "&&" in the while statement.
     -> If there's an "||", while works until the very end of stack regardless of having found an element smaller or not.
     -> It's essential that you pop out ONLY all the greater elements than the current one in consideration. Therefore, if there is a smaller element found, and there's an "||" in that statement, since stack is not empty (if at all), it's popped out, which is not something we want.
 
 [2.?] Time complexity == O(n^2)
     -> Outer loop runs for the length "n".
     -> while loop runs until worst case all the previous elements (n=i-1 to 0),
        for e.g. [2,15,16,17,10]
                              ^while loop runs from 17 until 2.
 
 [3.?] Any other approach than stacks? 
     -> Iterative array? 
     Same time bound?
     If yes, what's the advantage of stacks?
 
*/