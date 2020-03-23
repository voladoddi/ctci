#include <bits/c++config.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>
#include <cassert>
using namespace std;

// #define MAX_TRANSACTIONS 2
// #define MAX_MEMORY 5

/* NOTE:
    These are the assumptions of operation of this database.

    {TODO} (1) Add transactional max capacity handling.
               If the number of active transactions queued up are > MAX_TRANSACTIONS, WE DISCARD TRANSACTIONS.
           (2) Add eviction policy.
               In case the size of the database exceeds MAX_MEMORY, we DO NOT PROCESS FURTHER COMMANDS.
           (3) DB transactions are atomic. However, add support for concurrent I/O
              
*/
class RedisLikeDB {
    private:
        map<string, int> database_;                             // (log n) - search, insert, delete to maintain all elements
        multiset<pair<int, string>> value_ordered_keys_;        // (log n) - find by value. Extends to (log n) for finding all keys with value v.
        queue <pair<string, int>> transactions_to_discard_;     // transactional block to retrieve original data in case of DISCARD trans
        bool transaction_in_progress_;                          // Track if basic / transactional command
        int count_transactions_;                                // Count (SET|INCR|DEL|DELVALUE) transactions within transaction block
        
    public:
        RedisLikeDB(): transaction_in_progress_(false),
                       count_transactions_(0) {};
        ~ RedisLikeDB() {};
        void Set(string & key, int value);
        int Get(string & key);
        void Incr(string & key);
        void Del(string &key);
        void DelValue(int value);
        void StartTransaction();
        int StopTransaction();
        void DiscardTransaction();
        string processDBCommand(string & cmd, RedisLikeDB & db_object);
};


void RedisLikeDB::Set(string & key, int value)
{
    pair<int, string> old_value_key_pair;
    int transactional_value; 
    if (database_.find(key)==database_.end()) {
        database_.insert({key, value});
        value_ordered_keys_.insert({value, key});
        transactional_value = -1;
    } else {
        transactional_value = database_[key];
        old_value_key_pair = {transactional_value, key};
        database_[key] = value;
        value_ordered_keys_.erase(old_value_key_pair);
        value_ordered_keys_.insert({value, key});
    }
    if (transaction_in_progress_) { // if key was not there before and got inserted, we save value as -1 to delete. else save old value.
        if (transactions_to_discard_.empty() || transactions_to_discard_.front().first != key) {
            transactions_to_discard_.push({key,transactional_value});
        }
        count_transactions_++;
    }
}

int RedisLikeDB::Get(string & key)
{
    if (database_.find(key)==database_.end()) {
        return -1;
    }
    return database_[key];
}

void RedisLikeDB::Incr(string & key)
{
    int transactional_value = 0;
    if(database_.find(key)==database_.end()) { // key was not in DB
        Set(key, 0);
        transactional_value = -1;
    }
    if (transactional_value != -1) { // key was already in DB so save the old value for DISCARD
        transactional_value = database_[key];
    }

    pair <int, string> old_value = {database_[key], key}; // save old value to update set value.
    database_[key]++;
    if (value_ordered_keys_.find(old_value)!=value_ordered_keys_.end()) {
        value_ordered_keys_.erase(old_value);
        value_ordered_keys_.insert({database_[key], key});  // should reflect {new_value, key}
    }

    if (transaction_in_progress_) { // if key was not there before and got incremented, we save value as -1 to delete. else save old value.
        if (transactions_to_discard_.empty() || transactions_to_discard_.front().first != key) {
            transactions_to_discard_.push({key,transactional_value});
        }
        count_transactions_++;
    }
}

/* DEL key : Delete key from database_ if exists. Else ignore */
void RedisLikeDB::Del(string & key)
{
    if(transaction_in_progress_) {
        if (transactions_to_discard_.empty() || transactions_to_discard_.front().first != key) {
            if (database_.find(key)!=database_.end()) {
                transactions_to_discard_.push({key, database_[key]}); // only save to set in case the key actually gets deleted.
            }
        }
        count_transactions_++;
    }
    pair <int, string> old_value_key_pair = {database_[key], key};
    database_.erase(key);
    value_ordered_keys_.erase(old_value_key_pair);
}

// Reference: https://stackoverflow.com/questions/47615977/how-to-find-the-pair-in-the-set-using-first-element-of-the-pair-only
//            https://stackoverflow.com/questions/30217956/error-variable-cannot-be-implicitly-captured-because-no-default-capture-mode-h
void RedisLikeDB::DelValue(int value)
{
    string key;
    for (auto pair_tracker = 0; pair_tracker < value_ordered_keys_.size(); pair_tracker++) {
        // find by value in our {value, key} pair in multiset
        auto it = std::find_if(value_ordered_keys_.begin(), value_ordered_keys_.end(),
                            [&value](const pair<int,string> &p )
                            { return p.first == value;}
                        );
        if (it==value_ordered_keys_.end()) {    // multiset stores in sorted order. Repeatedly find pair to delete in (log n)
            return;
        } else {
            if (transaction_in_progress_) {
                if (transactions_to_discard_.empty() || transactions_to_discard_.front().first != key) {
                    transactions_to_discard_.push({it->second, it->first});
                }
                count_transactions_++;
            }
            key = it->second;
            database_.erase(key);
            value_ordered_keys_.erase(it);
        }
    }
}

void RedisLikeDB::StartTransaction()
{
    transaction_in_progress_ = true; // begin transaction block
}

int RedisLikeDB::StopTransaction()
{
    int num_transactions = -1;                  // Reset transaction block defaults
    if(transaction_in_progress_) {
        num_transactions = count_transactions_;
        transaction_in_progress_ = false;
        count_transactions_ = 0;
    }
    return num_transactions;
}

void RedisLikeDB::DiscardTransaction()
{
    while(!transactions_to_discard_.empty()) {              // "Undo" all the transactions from current transaction block
        auto transaction = transactions_to_discard_.front();
        if (transaction.second == -1) {
            Del(transaction.first);
        } else {
            Set(transaction.first, transaction.second);
        }
        transactions_to_discard_.pop();
    }
}

string RedisLikeDB::processDBCommand(string & cmd, RedisLikeDB & db)
{
    cout << cmd << endl;
    int first_space = cmd.find_first_of(" ");
    int second_space = cmd.find_last_of(" ");
    string key;
    int value; 

    string result("");

    if (cmd.find("SET")!= string::npos) {
        int len_key = second_space - first_space - 1;
	    key = cmd.substr(first_space+1, len_key);
	    value = atoi((cmd.substr(second_space+1)).c_str());
        db.Set(key, value);
    } else if (cmd.find("GET")!= string::npos) {
        key = cmd.substr(first_space+1);
        int process_value;
        process_value = db.Get(key);
        (process_value== -1) ? (result = "<nil>") : (result = to_string(process_value));
    } else if (cmd.find("INCR")!= string::npos) {
        key = cmd.substr(first_space+1);
        db.Incr(key);
    } else if ((cmd.find("DEL")!= string::npos) && (cmd.find("DELVALUE")==string::npos)) {
        key = cmd.substr(first_space+1);
        db.Del(key);
    } else if (cmd.find("DELVALUE")!= string::npos) {
        value = atoi(cmd.substr(first_space+1).c_str());
        db.DelValue(value);
    } else if (cmd.find("MULTI")!= string::npos) {
        db.StartTransaction();
    } else if (cmd.find("EXEC")!= string::npos) {
        int num_transactions_executed = db.StopTransaction();
        if(num_transactions_executed == -1) {
            result = "NOT IN TRANSACTION";
        } else {
            result = to_string(num_transactions_executed);
        }
    } else if (cmd.find("DISCARD")!= string::npos) {
        int num_transactions_discarded = db.StopTransaction();
        if (num_transactions_discarded == -1) {
            result = "NOT IN TRANSACTION";
        } else {
            db.DiscardTransaction();
            result = to_string(num_transactions_discarded);
        }
    } else {
        // Not a valid command.
    }
    return result;
}

int main()
{
    char arr[100];
    char c;
    
    RedisLikeDB test_db;
    // First running through all the test cases. 
    vector<vector<string>> tests{
				{"SET key 7", "GET key", "DEL key", "GET key", "INCR key", "GET key"},
				{"SET key1 7", "SET key2 7", "SET key3 8", "DELVALUE 7", "GET key1", "GET key2", "GET key3"},
                {"SET key1 12", "MULTI", "DEL key1", "DISCARD", "GET key1"},
                {"EXEC"},
                {"DISCARD"}};

    vector<vector<string>> tests_outputs{
				{"", "7", "", "<nil>", "", "1"},
				{"", "", "", "", "<nil>", "<nil>", "8"},
                {"", "", "", "1", "12"},
                {"NOT IN TRANSACTION"},
                {"NOT IN TRANSACTION"}};

    for(auto test: tests) { // {TODO: Fix test checks}
        vector <string> test_result;
        int i;
        for (i = 0; i <test.size(); i++) {
            test_result.push_back(test_db.processDBCommand(test[i],  test_db));
        }
        cout << (test==test_result) << endl;
    }
  
  // This is interactive.
  RedisLikeDB interactive_db;

  cout << "NOTE: (1) Press Enter until you see a \"> \" to enter the next command." << endl;
  cout << "      (2) Press ESC and Enter to quit (or) Ctrl+C" << endl;
  while ((c = std::cin.get()) != 27) {
    cout << "> ";
    cin.getline(arr, 100, '\n');
    string command(arr);
    string result = interactive_db.processDBCommand(command,interactive_db);
    if(!result.empty()) {
        cout << result << endl;
    }
  }
    return 0;
}