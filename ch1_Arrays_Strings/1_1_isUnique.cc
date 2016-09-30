#include "1_1_isUnique.h"
using namespace std;

bool isUniqueOne(const string &s){
    for(int i=0; i<s.length(); i++)
        for(int j=0; j<s.length(); j++){
            if (i==j) continue;
            if (s.at(i)==s.at(j)) return false;
        }
    return true;
    }


bool isUniqueTwoA(const std::string &s){
    if (s.length()>128) return false;               // length more than character set can accommodate?
    vector<bool> char_set(128);                     // create a flag bool vector of character set size.
    
    for (int i= 0;i < s.length(); i++){
        int flag = s.at(i);
        
        if (char_set[flag]) return false;            // check if already set, return false if set. else set true .
        char_set[flag]=true;
    }
    return true;                                     // if it didn't return false at any point till now, str is unique.
}

bool isUniqueTwoB(const std::string &s){
    unsigned int checker = 0;
    for(int i =0 ; i < s.length(); i++){
        int val = s.at(i);
        //if
        if ((checker & (1 << val))!=0)
            return false;
        //else
        checker|=(1<<val);
    }
    return true;
}


int main()
{
    string str1 ="abcde";
    string str2 ="aaa";
    
    cout << isUniqueTwoB(str1) << "\t"<< isUniqueTwoB(str2)<<endl;
    
}