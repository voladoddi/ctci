#ifndef _H_HEAPS
#define _H_HEAPS

#include <vector>

class Heap
{
    protected:
    std::vector<int> heap;
    
    public:

    // Constructor / Destructor
    Heap(const std::vector<int> & nums);
    ~Heap();

    // Utils
    void printHeap();

    // Operations on building a heap
    void buildMaxHeap();
    void maxHeapify(int parent);

    void buildMinHeap();
    void minHeapify(int parent);

    // Operations on a heap
};

#endif //_H_HEAPS