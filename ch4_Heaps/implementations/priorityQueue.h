#ifndef _H_PRI_QUEUE_
#define _H_PRI_QUEUE_

#include <vector>
#include "heap.h"

class PriorityQueue : public Heap
{
    private:
    
    public:
    PriorityQueue(const std::vector<int> & nums);
    ~PriorityQueue();

    // operations for PQ from a stream
    int getMax();
    int deleteMax();
    void changePriority(int key, int new_priority);
    void insertKey(int key);
};

#endif //_H_PRI_QUEUE_