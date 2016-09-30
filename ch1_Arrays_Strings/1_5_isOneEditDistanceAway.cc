#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

int isOneEditDistance(string s1, string s2)
{
    
    string sstr = (s1.size() < s2.size())? s1 : s2;
    string lstr = (s1.size() > s2.size())? s1 : s2;
    
    if ( (lstr.size()-sstr.size()) > 1 )
        return 0;
    
    int sIdx = 0, lIdx = 0;
    bool mismatch = false;
    
    while(sIdx < sstr.size() && lIdx < lstr.size())
    {
        // if characters don't match , count mismatches and check for replacement.
        if(sstr[sIdx]!=lstr[lIdx])
        {
            if (mismatch) return 0;
            mismatch = true;
            
            if (sstr.size()==lstr.size())
                sIdx++;
        }
        // else if characters match
        else
        {
            sIdx++;
        }
        lIdx++;
    }
    return 1;
    
}

int main() {
    
    string s1 = "pooja";
    string s2 = "poojas";
    
    cout << isOneEditDistance(s1,s2) << endl;
    
	return 0;
}
