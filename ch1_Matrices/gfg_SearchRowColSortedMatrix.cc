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

int main() {
	// your code goes here
	vector< vector <int> > matrix({{1,7,15,21},{2,8,16,24},{3,10,18,26}});
	int elem;
    cin >> elem;
    
	int col = searchCol(matrix,elem);
	int rows = searchRow(matrix, col, elem);
    
	if (rows==-1)
	    cout << "False\n";
	else
	    cout << "True\n";
	return 0;
}