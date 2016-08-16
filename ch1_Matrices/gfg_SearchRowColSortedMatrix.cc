#include <iostream>
#include <vector>
using namespace std;

int searchCol(const vector< vector<int> > &a, int elem)
{
    int r=0;
    int cols = a[0].size();
    int c;
    for(c=0; c<cols;c++)
        if (a[r][c]== elem)
            return c;
        else if (a[r][c] > elem)
            break;
    
    return (c-1);
    
}

int searchRow(const vector< vector<int> > &a, int c, int elem)
{
    int rows= a.size();
    int r;
	for(r=0;r<rows;r++)
	    if (a[r][c]==elem){
	        return r;
	    }
	return -1;
}

int main(){
    
    // Initialize a matrix of NxN.
    // This line below compiles only with GCC flag '-std=c++11' or '-std=c++14'
	vector< vector <int> > matrix({{1,7,15,21},{2,8,16,24},{3,10,18,26}});
    
    // read element to be searched.
	int elem;
    cin >> elem;
    
    /*
     The algorithm works in O(N) if matrix is NxN, O(M+N) if matrix is MxN.
     1. Sweep through columns to narrow down search space to a single column.
        Return "c" if elem found in "c", else return "c-1".
     
     2. Search all rows with "c" fixed (returned in step 1.) 
     
     3. Print "True" if found, else print "False".
     
     [Note] Can be modified to print out location if "True".
     */
    
	int col = searchCol(matrix,elem);
	int rows = searchRow(matrix, col, elem);
    
	if (rows==-1)
	    cout << "False\n";
	else
	    cout << "True\n";
    
    
	return 0;
}