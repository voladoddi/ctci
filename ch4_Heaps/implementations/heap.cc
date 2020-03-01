#include "heap.h"
#include <vector>
#include <iostream>

Heap::Heap(const std::vector<int> & nums) : heap(nums)
{
}

Heap::~Heap()
{
    heap.clear();
}

void Heap::printHeap()
{
    for (auto heap_elem: heap) {
        std::cout << heap_elem;
    }
    std::cout << std::endl;
}

// --------------------------------------- MIN HEAP ------------------------------------
void Heap::minHeapify(int parent)
{
    int smallest = parent;
    int left_child = 2*parent + 1; // 0-based idx
    int right_child = 2*parent + 2;

    // find smallest in the current heap
    if(left_child<heap.size() && heap[left_child]<heap[parent]) {
        smallest = left_child;
    } if (right_child<heap.size() && heap[right_child]<heap[parent]) {
        smallest = right_child;
    }
    // swap with smallest if smallest is not the parent, and repeatedly 
    if (smallest != parent) {
        std::swap(heap[smallest], heap[parent]);
        minHeapify(parent);
    }
}

void Heap::buildMinHeap()
{
    // For every parent, build a heap and make sure that the heap at node i (parent) is a min heap
    for (int i = (heap.size()-1)/2; i>=0; i--) {
        minHeapify(i);
    }
}

// ---------------------------------------- MAX HEAP -----------------------------------
void Heap::maxHeapify(int parent)
{
    int largest = parent;
    int left_child = 2*parent + 1;  //0-based idx
    int right_child = 2*parent + 2;

    // find smallest in the current heap
    if(left_child<heap.size() && heap[left_child] > heap[parent]) {
        largest = left_child;
    } if (right_child<heap.size() && heap[right_child] > heap[parent]) {
        largest = right_child;
    }
    // swap with smallest if smallest is not the parent, and repeatedly 
    if (largest != parent) {
        std::swap(heap[largest], heap[parent]);
        maxHeapify(parent);
    }
}

void Heap::buildMaxHeap()
{
    int n = (heap.size()-1)/2;
    for (int i = n; i>=0; i--) {
        maxHeapify(i);
    }
}