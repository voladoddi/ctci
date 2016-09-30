#ifndef __1_1_isUnique_H__
#define __1_1_isUnique_H__

#include <iostream>
#include <string>
#include <vector>
#include<algorithm>

class Solution
{
    public:
        // 1. Using Brute Force approach.
    bool isUniqueOne(const std::string &s);
        // 2a. Using bool-vector.
    bool isUniqueTwoA(const std::string &s);
        // 2b. Using bit-vector.
    bool isUniqueTwoB(const std::string &s);
        // 3. Sort and compare.
    bool isUniqueThree(const std::string &s);
        // 4. Use Unordered_map.
    bool isUniqueFour(const std::string &s);
    
};

#endif