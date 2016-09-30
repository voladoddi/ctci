#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

// Checks if strB is a permutation of strA.

/* 
 [Approach 1]
    ? Allowed to modify strings.
 
    - Sort strA, strB. Then check both the strings if the characters are same.
    - [Time]: O(nlogn) for sort, O(n) for comparison. => O(nlogn)
    - [Space]: O(1) [or space of sort if sort not in place]
*/


bool isPermutationA(string &strA, string &strB)
{
    sort(strA.begin(), strA.end());
    sort(strB.begin(), strB.end());
    
    cout << strA << endl;
    cout << strB << endl;
    
    if (strA.compare(strB)!=0)
        return false;
    else
        return true;
}


/*
 [Approach 2]]
    ? Use a look-up table to keep a count of characters.
    ? ASCII set => 128 characters. 
 
    - Maintain count of each character in string A.
    - Decrement count for the same character encountered in string B.
    - if the count of any character is not equal to 0, then return false.
    
    - [Time]: O(n) 
              i.e. 1st,2nd for loop - O(n), 3rd for loop, maximum time - O(c) => O(2n+c)
      [Space]: O(c)
 
 */
bool isPermutationB(string &strA, string &strB)
{
    vector <int> charCount(128);
    
    for(auto c: strA)
    {
        charCount[(int)c]++;
    }
    
    for(auto c: strB)
    {
        charCount[(int)c]--;
    }
    
    for(auto i: charCount)
    {
        if(i<0) // this should work fine if lengths of the strings are same. Else put a check for lengths==, or change to (i!=0)
            return false;
        //else
        //    return true;
    }
    return true;
}


int main()
{
    string strA = "pooja";
    string strB = "ajoopa";
    
    cout << isPermutationB(strA,strB) << endl;

}