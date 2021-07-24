
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> 

using namespace std;

// Used when #querying and #updates are equal
// Array :          Update - O(1) and Query - O(n)
// Sum Array :      Update - O(n) and Query - O(1)
// Segment Tree :   Update - O(log n) and Query - O(log n)

/* Based off references :
    1. https://www.geeksforgeeks.org/segment-tree-efficient-implementation/
    2. http://codeforces.com/blog/entry/18051

    https://www.quora.com/What-is-the-simplest-implementation-of-segment-trees-that-you-have-seen
    https://kartikgill3.blogspot.com/2016/09/segment-tree-range-updaterange.html?view=flipcard
*/


const int N = 100000;       // limit for array size 
int n;                      // array size   
vector<int> tree(2*N);      // Max size of tree 

void buildSegmentTree(const vector<int> & arr)
{
    // insert tree leaves first. 
    for ( int i = 0; i < arr.size(); i++) {
        tree[n+i] = arr[i];
    }
    // populate parents. 
    for(int i = n-1; i > 0; --i) {
        tree[i] = tree[2*i] + tree[2*i+1];
    }

    
}

void updateTreeNode(int parent, int value)
{
    parent = n + parent;
    tree[parent] = value;
    // move upward and update parents 
    for (int i=parent; i > 1; i >>= 1) 
        tree[i>>1] = tree[i] + tree[i^1]; 

    //for (tree[parent += n] = value; parent > 1; parent >>= 1)
    //  tree[parent >> 1] = t[parent] + t[parent ^ 1];

}

// function to get sum on interval [l, r) 
int query(int l, int r)  
{  
    int res = 0; 
      
    // loop to find the sum in the range 
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) 
    { 
        if (l&1)  
            res += tree[l++]; 
      
        if (r&1)  
            res += tree[--r]; 
    }
    return res; 
}


int main()
{
    vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    n = arr.size();
    
    // Build segment tree
    buildSegmentTree(arr);

    // print the sum in range(1,2) index-based 
    cout << query(1, 3)<<endl; 
      
    // modify element at 2nd index 
    updateTreeNode(2, 1);
      
    // print the sum in range(1,2) index-based 
    cout << query(0, n) << endl; 
    cout << accumulate(arr.begin(), arr.end(), 0); 
  
    return 0; 

}