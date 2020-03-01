#include "priorityQueue.h"
#include "heap.h"
#include <vector>

PriorityQueue::PriorityQueue(const std::vector<int> & nums) : Heap(nums)
{
}

PriorityQueue::~PriorityQueue()
{
}

// operations for PQ from a stream
int PriorityQueue::getMax()
{
    return heap[0];
}

// delete max from PQ
int PriorityQueue::deleteMax()
{
    // if heap is empty nothing to remove
    if (heap.empty()) {
        return -1;
    }
    // class supports both max heap and min heap so just buildMaxHeap
    int max = heap[0];
    std::swap(heap[0], heap[heap.size()-1]);
    heap.pop_back(); 
    maxHeapify(0);

    return max;
}

void PriorityQueue::changePriority(int key, int new_priority)
{
    // if new priority is less, then don't change
    if(heap[key] > new_priority) {
        return;
    }
    // Change the priority, and check if parent needs to bubble up.
    heap[key] = new_priority;
    while(key>=0 && heap[(key-1)/2]<heap[key]) {
        std::swap(heap[(key-1)/2], heap[key]);
        key = (key-1)/2; // Note dividing by parent key, not by key.
    }
}

void PriorityQueue::insertKey(int priority)
{
    // push back to vector
    heap.push_back(priority); //resize to 1 extra, else redundant assignment in the next function
    changePriority(heap.size()-1, priority);
}