#include "dsHeap.h"

//5.
template<class type>
void binaryHeap<type>::insert(const type& item)
{
    if (heapSize==heapArray.size()-1)
        heapArray.resize(heapArray.size()*2);
    
    int hole;
    for(hole = heapSize+1; hole>1 && item<heapArray[hole/2]; hole/=2)
        heapArray[hole] = heapArray[hole/2];
    heapArray[hole] = item;
}

//6.
template<class type>
void binaryHeap<type>::deleteMin(type &minItem)
{
    if(isEmpty())
        throw underflow_error("Empty heap");
    minItem = heapArray[1];
    heapArray[1] = heapArray[heapSize--];
    downHeap(1);
}

// 2.
template<class type>
void binaryHeap<type>::downHeap(int hole)
{
    int child;
    type temp = heapArray[hole];
    for (; hole *2<=heapSize; hole = child)
    {
        child = hole*2;
        if(child!=heapSize && heapArray[child+1]<heapArray[child]) //right child less than left
            child++; // pick up right child.
        if(heapArray[child]<temp)
            heapArray[hole] = heapArray[child];
        else
            break;
    }
    heapArray[hole] = temp;
}



// 1.
template<class type>
void binaryHeap<type>::buildHeap()
{
    for(int i= heapSize/2; i>0; i--)
        downHeap(i);
}

// 4.
template<class type>
bool binaryHeap<type>::isEmpty() const
{
    return (heapSize==0);
}


int main()
{
    // add test code.
    return 0;
}

