#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;


int main() {
    
    // ---------  initial input details
    char str[] = "po oj a            ";
    int trueStrLen = 7;
    
    // ----------- count spaces for new length calculation to shift string
    int spaceCount = 0;
    for(int i = 0; i < trueStrLen ; i++)
    {
        if (str[i]==' ')
            spaceCount+=1;
    }
    
    int newStrLen = trueStrLen + spaceCount*2; //trueStrLen + spaceCount * (length of string to be inserted-1).
    str[newStrLen]='\0';
    
    // ---------   shift and insert %20.
    for (int i = trueStrLen-1 ; i >=0 ; i--)
    {
        if (str[i] != ' ')
        {
            str[newStrLen - 1] = str[i];
            newStrLen = newStrLen - 1;
        }
        else
        {
            str[newStrLen - 1] = '0';
            str[newStrLen - 2] = '2';
            str[newStrLen - 3] = '%';
            newStrLen= newStrLen - 3;
        }
        
    }
    cout << str << endl;
    
	return 0;
}
