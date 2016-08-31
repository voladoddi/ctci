/*
 Next Greater Element
 Given an array, print the Next Greater Element (NGE) for every element. The Next greater Element for an element x is the first greater element on the right side of x in array. Elements for which no greater element exist, consider next greater element as -1.
 
 Examples:
 a) For any array, rightmost element always has next greater element as -1.
 b) For an array which is sorted in decreasing order, all elements have next greater element as -1.
 c) For the input array [4, 5, 2, 25}, the next greater elements for each element are as follows.
 
 Element       NGE
 4      -->   5
 5      -->   25
 2      -->   25
 25     -->   -1
 d) For the input array [13, 7, 6, 12}, the next greater elements for each element are as follows.
 
 Element        NGE
 13      -->    -1
 7       -->     12
 6       -->     12
 12      -->     -1
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextGreaterElement(vector<int> &A)
{
    stack <int> st;
    vector <int> v;
    
    for(int i=0; i<A.size();i++)
    {
        while(!st.empty() && st.top()<=A[i])
        {
            v.push_back(A[i]);
            st.pop();
        }
        st.push(A[i]);
    }
    while(!st.empty())
    {
        v.push_back(-1);
        st.pop();
    }
    
    return v;
}


int main() {
    vector<int> A = {4,5,2,10};
	vector<int> res;
	res = nextGreaterElement(A);
	
	for(int i=0; i < res.size();i++)
	    cout << res[i] << " ";
    
	return 0;
}

/* TO-DO :
 
 [0.] Comment in code the algorithm.
 
 [1.] Comment on other approaches and pseudo-it.
 
 [2.] Time complexity :
      Alternate approach(es) time complexity :
 
 
 */