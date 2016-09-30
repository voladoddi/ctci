#ifndef H_heap_data_structure
#define H_heap_data_structure

#include<iostream>
#include<vector>
#include<stdexcept>
using namespace std;

template <class type>
class binaryHeap
{
    private:
        int heapSize;
        vector<type> heapArray;
        void buildHeap();                                   // 1.
        void downHeap(int hole);                            // 2.
    
    public:
        //explicit binaryHeap(int capacity = 100);
    
        //explicit binaryHeap(const vector<type> &items);     // 3.
        // refer http://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-in-c-mean for
        // explanation on "explicit" KWD.
        // 3.
        explicit binaryHeap(const vector<type>& items): heapArray(items.size()+10), heapSize(items.size())
        {
            for(int i=0; i < items.size();i++)
            {
                heapArray[i+1] = items[i];
                buildHeap();
            }
        }
    
        bool isEmpty() const;                               // 4.
        //void makeEmpty() const;
    
        void insert(const type& item);                      // 5.
        //const type & findMin() const;
        //void deleteMin();
        void deleteMin(type & minItem);                     // 6.
    
};



#endif
