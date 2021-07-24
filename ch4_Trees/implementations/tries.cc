#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

/* Trie implementations and applications 
Links : 
1. https://gist.github.com/hrsvrdhn/1ae71c25ef1c620c022a544d52df8928
2. https://leetcode.com/problems/implement-trie-prefix-tree/
3. Autocomplete : https://leetcode.com/problems/design-search-autocomplete-system/
                  https://leetcode.com/problems/search-suggestions-system/
                  https://www.geeksforgeeks.org/auto-complete-feature-using-trie/ 

   Dictionary :  https://www.geeksforgeeks.org/implement-a-dictionary-using-trie/?ref=rp


*/

// {TODO} : Figure out how to link a separate struct and class.
//          Getting seg fault on using TrieNode * root within the methods.
/*struct TrieNode
{
    unordered_map<char, TrieNode*> children;
    int prefix_count;
    int search_count;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false), prefix_count(0), search_count(0){};
};*/


class Trie
{
    private:
        unordered_map<char, Trie*> children;
        int prefix_count;
        int search_count; // helpful for autocomplete
        string meaning;   // helpful for dictionary
        bool isEndOfWord;
        

    public:
        Trie() : isEndOfWord(false), prefix_count(0), search_count(0){};
        void insert(const string & keyToInsert, const string & meaning);
        bool search(const string & keyToSearch);
        bool startsWith(const string & keyPrefix);
        string getWordMeaning(const string & word);
};


void Trie::insert(const string &keyToInsert, const string & meaning)
{
    cout << "TrieNode::insert() : Enter" << endl;
    Trie * current = this;
    Trie * node;
    for ( auto key_char : keyToInsert) {
        cout << "TrieNode::insert() key_char being inserted : " << key_char << endl;
        if (!current->children[key_char]) {
            node = new Trie();
            current->children[key_char] = node;
            cout << "TrieNode::insert() current->children[key_char] : " << current->children[key_char] << endl;
        }
        current = node;
        current->prefix_count++;
    }
    current->isEndOfWord = true;
    current->meaning = meaning;
}

bool Trie::search(const string &keyToSearch)
{
    Trie * current = this;
    for (auto key_char : keyToSearch) {
        if (!current->children[key_char]) {
            return false;
        }
        current = current->children[key_char];
    }
    return current->isEndOfWord; //at this point we're guaranteed that
                                 // we reached here only if all of key is found. Now we only have to see that 
}

bool Trie::startsWith(const string & prefix)
{
    Trie * current = this;
    for (auto key_char : prefix) {
        if (!current->children[key_char]) {
            return false;
        }
        current = current->children[key_char];
    }

    return true;
}

string Trie::getWordMeaning(const string & word)
{
    Trie * current = this;
    for (auto key_char : word) {
        if (!current->children[key_char]) {
            return "";
        }
        current = current->children[key_char];
    }

    if (current->isEndOfWord) {
        return current->meaning;
    }
    return "";
}

int main()
{
    Trie * root = new Trie();
    root->insert("pooja","");
    root->insert("lalala","bleh");
   
    cout << " Found / Not : " << root->search("poo") << endl; // expect 0
    cout << " Found prefix / Not : " << root->startsWith("poo") << endl; // expect 1
    cout << " Found / Not : " << root->search("pooja") << endl; // expect 1
    cout << " Found. Meaning : " << root->getWordMeaning("lalala") << endl; // expect 0
   

    return 0;
}