#idndef H_arrayQueue
#define H_arrayQueue

#include <iostream>
#include "adtQueue.h"
using namespace std;

// ------------------- CLASS DEFINITION --------------------
template <class type>
class arrayQueue : public queueADT<type>
{
    private:
        type *list;
    
        int queueFront;
        int queueRear;
    
        int maxQueueSize;
        int count;
    
    public:
    arrayQueue(int queueSize = 100); // this not initialization of any variable, it's default value of arg.
   // arrayQueue(const arrayQueue<type>& otherQueue);
    ~arrayQueue();
    
    //const arrayQueue<type>& operator=(const arrayQueue<type>& otherQueue);
    
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    
    type front() const;
    type back() const;
    
    void enQueue(const type& qElement);
    void deQueue();
};

// -------------- FUNCTION IMPLEMENTATIONS ----------------

//  ------ 0. [a] constructor -----
template <class type>
arrayQueue<type>::arrayQueue(int queueSize)
{
    if(queueSize<=0)
        maxQueueSize = 100;
    else
        maxQueueSize = queueSize;
    
    queueFront = 0;
    queueRear  = maxQueueSize - 1;
    count      = 0;
    list       = new Type[maxQueueSize];
}

// ----- 0. [b] destructor ------
template <class type>
arrayQueue<type>::~queueType()
{
    delete [] list;
}
// --------------------------------------

// 1. is Empty?
template <class type>
bool arrayQueue<type>::isEmptyQueue() const
{
    return (count==0);
}

// 2. is Full?
template <class type>
bool arrayQueue<type>::isFullQueue() const
{
    return (count==maxQueueSize);
}

// 3. intialize ==> front is 0, back is max -1, count begins from front.
template <class type>
void arrayQueue<type>::initializeQueue()
{
    queueFront = 0;
    queueRear  = maxQueueSize - 1;
    count      = 0;
}

// 4. front
template<class type>
type arrayQueue<type>::front() const
{
    assert(!isEmptyQueue());
    return list[queueFront];
}

// 5. back
template<class type>
type arrayQueue<type>::back() const
{
    assert(!isFullQueue());
    return list[queueRear];
}

// 6. enqueue
template<class type>
type arrayQueue<type>::enQueue(const type& qElement)
{
    // if queue is not empty, advance queuerear and assign data to list[queuerear]. increment count.
    // else print overflow.
    if(!isFullQueue())
    {
        queueRear = (queueRear + 1) % maxQueueSize;
        count++;
        list[queueRear] = qElement;
    }
    else
        cout << " Overflow.\n" << endl;
}

// 7. dequeue
template<class type>
type arrayQueue<type>::deQueue()
{
    if(!isEmptyQueue())
    {
        count --;
        queueFront = (queueFront + 1) % maxQueueSize;
    }
    else
        cout << "Cannot remove from empty queue.\n"<<endl;
}

#endif