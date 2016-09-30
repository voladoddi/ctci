// -------------- [TO - DO] -------------
// 1. Time complexity ? What's the complexity of operation "+ (strcat)"
//                    ? What's the complexity of "to_string"
// 2. Space complexity ? Worst case : O(n) where n = size of "input" string.
// --------------------------

/* ------- NOTES ----------
 1. Note the presence of (i+1)>=input.size().
 2. Note the ">=" in 1.
 3. can possibly make it cleaner by removing "if... else if" and just putting "if [else if statement]"?
 ------------------------
 */

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

string  compressString(string input)
{
    string compressed    = "";
    int countCompressed  = 0;
    
    for(int i = 0; i < input.size(); i++)
    {
        countCompressed++;
        if(input[i+1]==input[i])
            continue;
        else if ((i+1)>=input.size() || input[i+1]!=input[i]){
            compressed+=input[i];
            compressed+=to_string(countCompressed);
            countCompressed = 0;
        }
    }
    return (compressed.size()>=input.size())? input : compressed;
    
}

int main() {
    
    string str = "aaabbbddddee";
    cout << compressString(str) << endl;
    
	return 0;
}
