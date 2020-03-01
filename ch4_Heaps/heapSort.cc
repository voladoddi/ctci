#include <vector>
#include <iostream>

// {TODO: Linker issues in including implementations. Need to include a Makefile }

void printHeap(const std::vector<int> &heap)
{
    for (auto heap_elem: heap) {
        std::cout << heap_elem << " ";
    }
    std::cout << std::endl;
}

// ---------------------------------------- MAX HEAP -----------------------------------
void maxHeapify(std::vector<int> & heap, int parent)
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
        maxHeapify(heap, parent);
    }
}

void buildMaxHeap(std::vector<int> & heap)
{
    int n = (heap.size()-1)/2;
    for (int i = n; i>=0; i--) {
        maxHeapify(heap, i);
    }
}

// delete max from PQ
int deleteMax(std::vector<int> &heap)
{
    // if heap is empty nothing to remove
    if (heap.empty()) {
        return -1;
    }
    // class supports both max heap and min heap so just buildMaxHeap
    int max = heap[0];
    std::swap(heap[0], heap[heap.size()-1]);
    heap.pop_back(); 
    maxHeapify(heap, 0);

    return max;
}

void changePriority(std::vector<int> &heap, int key, int new_priority)
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

void insertKey(std::vector<int> &heap, int priority)
{
    // push back to vector
    heap.push_back(priority); //resize to 1 extra, else redundant assignment in the next function
    changePriority(heap, heap.size()-1, priority);
}

int main()
{
    std::vector<int> heap{3,1,80,42,7,2};
 
    // buildMaxHeap
    buildMaxHeap(heap);
    std::cout << "Max heap: \n";
    printHeap(heap);

    // insert key
    insertKey(heap, 69);
    std::cout << "After insert: \n";
    printHeap(heap);

    // delete max
    std::cout << deleteMax(heap) <<std::endl;
    printHeap(heap);

}