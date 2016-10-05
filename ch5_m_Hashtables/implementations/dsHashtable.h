#ifndef H_hashtable
#define H_hashtable

#include<vector>
#include<list>
#include<string>
#include<iostream>
using std::list;
using std::vector;
using std::string;
using std::cout;
using std::endl;

/*
 The functions for any hashtable are as follows:
 Properties/Operations:
 -- insert.
 -- remove.
 -- lookup/search/find. => contains.
 Essential:
 -- getHash.
 The data variables are :
 1. an array of lists: vector<list<string> > htable;
 2. size				: total number of elements in htable.
 */

#define TABLE_SIZE 13
typedef list<string> slists;
typedef vector<slists> htableType;

class Hashtable
{
private:
    htableType htable;
    unsigned int getHash(const string& keyToInsert);
    int htable_size;
public:
    // constructor
    Hashtable(int ht_size = TABLE_SIZE) :htable_size(ht_size), htable(ht_size) {}
    // destructor
    ~Hashtable()
    {                                                   //std::vector<list<string> >::iterator it;
        for (int i = 0; i < htable_size; i++)           //for (it = htable.begin(); it != htable.end(); it++)
            htable[i].clear();                          // htable.erase(it);
    }
    
    // --- helper functions ---
    // hashtable size
    int getHtablesize();
    // hashtable total num elements
    int getHtableOccupantsSize();
    
    void insert(const string& keyToInsert);
    void remove(const string& keyToRemove);
    bool contains(const string& keyToLookup);
};

#endif
