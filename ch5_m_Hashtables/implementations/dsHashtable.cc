#include "dsHashtable.h"


// -- helpers --
int Hashtable::getHtablesize()
{
	return this->htable_size;
}

int Hashtable::getHtableOccupantsSize()
{
	int totalSize = 0;
	for (vector<slists>::iterator ht_itr = htable.begin(); ht_itr != htable.end(); ht_itr++)
		totalSize += ht_itr->size();
    
	return totalSize;
    
}

// --- main funcs ----
unsigned int Hashtable::getHash(const string& keyToInsert)
{
	unsigned int value = 0;
	for (int i = 0; i < keyToInsert.length(); i++)
		value += keyToInsert[i];
	return (value % htable_size);
}

void Hashtable::insert(const string& keyToInsert)
{
	int hashvalue = getHash(keyToInsert);
	if (!this->contains(keyToInsert))
		htable[hashvalue].push_back(keyToInsert);
	else
		cout << "Duplicate key" << endl;
}
void Hashtable::remove(const string& keyToRemove)
{
	int hashvalue = getHash(keyToRemove);
	if (this->contains(keyToRemove))
		htable[hashvalue].remove(keyToRemove);
    this->htable_size--;
    
}
bool Hashtable::contains(const string& keyToLookup)
{
	const list<string> &whichList = htable[getHash(keyToLookup)];
	return ( find(whichList.begin(), whichList.end(), keyToLookup) != whichList.end() );
}

int main()
{
	Hashtable ht;
	cout << ht.getHtablesize() << endl;
    
	ht.insert("first key");
	ht.insert("second key");
    
	cout << "Size before removal: " << ht.getHtableOccupantsSize() << endl;
    
	ht.remove("first key");
    
	cout << "Size after removal: " << ht.getHtableOccupantsSize() << endl;
    
    
	return 0;
}