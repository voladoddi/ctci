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
using namespace std;

#define MAX_TRANSACTIONS 10

/* TODOs:
    1. Get transactional behaviors right.
    2. Add transactional max capacity handling.
    2. Clean up redundant code
    3. Make OOP. 
    4. Add tests.
    5. Fix prompt
    3. Add eviction policy. 
    4. Add concurrency.
    
*/
map<string, int> database_;                             // (log n) - search, insert, delete to maintain all elements
multiset<pair<int, string>> value_ordered_keys_;        // (log n) - find by value. Extends to (log n) for finding all keys with value v.
queue <pair<string, int>> transactions_to_discard_;     // transactional block to retrieve original data in case of DISCARD trans
bool transaction_in_progress_ = false;                  // Track if basic / transactional command
int count_transactions_ = 0;                            // Count (SET|INCR|DEL|DELVALUE) transactions within transaction block
int transactions_capacity = MAX_TRANSACTIONS;           // If transactions are lined up beyond this, discard the transactions.

void Set(string & key, int value)
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

int Get(string & key)
{
    if (database_.find(key)==database_.end()) {
        return -1;
    } else {
        return database_[key];
    }
}

void Incr(string & key)
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
void Del(string & key)
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
void DelValue(int value)
{
    cout << "Inside DelValue:" << endl;
    cout << "Value to delete:" << value << endl;
    string key;
    for (auto pair_tracker = 0; pair_tracker < value_ordered_keys_.size(); pair_tracker++) {
        // find by value in our {value, key} pair in multiset
        auto it = std::find_if(value_ordered_keys_.begin(), value_ordered_keys_.end(),
                            [&value](const pair<int,string> &p )
                            { return p.first == value;}
                        );
        if (it!=value_ordered_keys_.end()) {    // multiset stores in sorted order. Repeatedly find pair to delete in (log n)
            if (transaction_in_progress_) {
                if (transactions_to_discard_.empty() || transactions_to_discard_.front().first != key) {
                    transactions_to_discard_.push({it->second, it->first});
                }
                count_transactions_++;
            }
            key = it->second;
            database_.erase(key);
            value_ordered_keys_.erase(it);
        } else {
            break;  // Maintain (log n) and break early when all value pairs are removed.
        }
    }

}

void processCmd(string & cmd)
{
    cout << cmd << endl;
    int first_space = cmd.find_first_of(" ");
    int second_space = cmd.find_last_of(" ");
    string op, key;
    int value; 

    if (cmd.find("SET")!= string::npos) {
        int len_key = second_space - first_space - 1;
	    key = cmd.substr(first_space+1, len_key);
	    value = atoi((cmd.substr(second_space+1)).c_str());
        cout << "Inside SET: Key:" << key << " Val:" << value << endl;

        Set(key, value);
    } else if (cmd.find("GET")!= string::npos) {
        key = cmd.substr(first_space+1);
        cout << "Inside GET: Key:" << key << endl;
        int process_value;

        process_value = Get(key);
        (process_value== -1) ? (cout << "<nil>" << endl) : (cout << process_value << endl);
    } else if (cmd.find("INCR")!= string::npos) {
        key = cmd.substr(first_space+1);
        cout << "Inside INCR: Key:" << key << endl;

        Incr(key);
    } else if ((cmd.find("DEL")!= string::npos) && (cmd.find("DELVALUE")==string::npos)) {
        key = cmd.substr(first_space+1);
        cout << "Inside DEL: Key:" << key << endl;

        Del(key);
    } else if (cmd.find("DELVALUE")!= string::npos) {
        value = atoi(cmd.substr(first_space+1).c_str());

        DelValue(value);
    } else if (cmd.find("MULTI")!= string::npos) {
        transaction_in_progress_ = true;
    } else if (cmd.find("EXEC")!= string::npos) {
        if(transaction_in_progress_) {
            cout << count_transactions_ << endl << "> ";
            transaction_in_progress_ = false;
            count_transactions_ = 0;
        } else {
            cout << "NOT IN TRANSACTION" << endl << "> ";
        }
    } else if (cmd.find("DISCARD")!= string::npos) {
        if (transaction_in_progress_) {
            transaction_in_progress_ = false;
            cout << count_transactions_ << endl << "> ";
            count_transactions_ = 0;
            while(!transactions_to_discard_.empty()) {
                auto transaction = transactions_to_discard_.front();
                if (transaction.second == -1) {
                    Del(transaction.first);
                } else {
                    Set(transaction.first, transaction.second);
                }
                transactions_to_discard_.pop();
            }
        } else {
            cout << "NOT IN TRANSACTION" << endl << "> ";
        }
    } else {
    }
}

int main()
{

  char arr[100];
  char c;

  // First running through all the test cases. 
  // {TODO}
  

  // This is interactive.
  cout << "> " << endl;
  while ((c = std::cin.get()) != 27) {
    cout << "> ";
    cin.getline(arr, 100, '\n');
    string command(arr);
    processCmd(command);
  }
    return 0;
}