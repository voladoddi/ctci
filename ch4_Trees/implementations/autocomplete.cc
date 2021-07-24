#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

class TrieNode{
    public:
        unordered_map<char, TrieNode*> child;
        string str;
        int count;
        TrieNode(): str(""), count(0) {}
};

class AutocompleteSystem
{
    private:
        TrieNode * root;
        void insert(string& s, TrieNode* root, int times);
        void dfs(TrieNode* temp);
        struct comp{
            bool operator() (pair<string, int>& a, pair<string, int>& b) {
                return a.second<b.second || a.second==b.second && a.first>b.first;
            }
        };
        priority_queue<pair<string, int>, vector<pair<string, int> >, comp> q;
        string s="";

    public:
        TrieNode *curr;
        AutocompleteSystem(vector<string> sentences, vector<int> times) {
            root = new TrieNode();
            for (int i=0;i<sentences.size();i++){
                insert(sentences[i], root, times[i]);
            }
            curr = root;
        }
        vector<string> input(char c);
};
    
    
vector<string> AutocompleteSystem::input(char c)
{
    q = priority_queue<pair<string, int>, vector<pair<string, int> >, comp>();
    if (c=='#'){
        insert(s, root, 1);
        s="";
        curr = root; //start searching from the beginning node for the next sentence
        return {};
    }
    s += c;
    if (curr && curr->child.count(c)){
        curr = curr->child[c];
    }else{
        curr = NULL; //curr node is null so empty result for any further characters in current input 
        return {};
    }
    
    if (curr->str != "") q.push({curr->str, curr->count});
    for (auto& ele: curr->child){
        dfs(ele.second);
    }
    
    vector<string> res;
    while (!q.empty() && res.size()<3){
        res.push_back(q.top().first);
        q.pop();
    }
    
    return res;
}

void AutocompleteSystem::insert(string& s, TrieNode* root, int times)
{
    TrieNode* curr = root;
    for (int i=0;i<s.size();i++){
        if (!curr->child.count(s[i]))
            curr->child[s[i]] = new TrieNode();
        curr = curr->child[s[i]];
    }
    curr->count += times;
    curr->str = s;
}
void AutocompleteSystem::dfs(TrieNode* temp)
{
    if (temp->str != "") q.push({temp->str, temp->count});
    for (auto& ele: temp->child){
        dfs(ele.second);
    }
}

int main()
{
    vector<string> sentences{"i love you", "i love leetcode", "ironman", "island"};
    vector<int> times{5, 2, 2, 3};

    AutocompleteSystem * obj = new AutocompleteSystem(sentences, times);

    vector<string> param_1 = obj->input('i');
    for (auto p : param_1) {
        cout << p << endl;
    }
    cout << endl;

    vector<string> param_2 = obj->input(' ');
    for (auto p : param_2) {
        cout << p << endl;
    }
    cout << endl;

    vector<string> param_3 = obj->input('a');
    for (auto p : param_3) {
        cout << p << endl;
    }
    cout << endl;

    vector<string> param_4 = obj->input('#');
    for (auto p : param_4) {
        cout << p << endl;
    }
    cout << endl;

    cout << "End" << endl;

    vector<string> param_5 = obj->input('i');
    for (auto p : param_5) {
        cout << p << endl;
    }

    return 0;
}