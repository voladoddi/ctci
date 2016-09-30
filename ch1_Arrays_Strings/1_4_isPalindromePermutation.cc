#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

int getNumericValue(char s)
{
    switch(s){
        case 'a':
            return 0;
            break;
        case 'b':
            return 1;
            break;
        case 'c':
            return 2;
            break;
            // ... case 'z'
        case 'z':
            return 25;
            break;
        default:
            return -1;
            break;
    }
}

int main() {
	string str = "abcbc aba";
	
	vector<int> table(getNumericValue('z')-getNumericValue('a')+1);
	
	int countOdd = 0;
	for (int i = 0; i < str.size(); i++)
	{
	    int r = getNumericValue(str[i]);
	    
	    if(r!=-1)
	    {
	        table[r]++;
            
	        if (table[r]%2 == 1)
	            countOdd++;
	        else
	            countOdd--;
	    }
	}
	
	string result = (countOdd<=1)? "is palindrome of perm": "no palindrome exists!";
	
	cout << result << endl;
	
	return 0;
}