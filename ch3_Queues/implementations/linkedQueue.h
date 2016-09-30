#ifndef H_LINKEDQUEUE
#define H_LINKEDQUEUE

#include<iostream>
#include "adtQeueue.h"
using namespace std;

// ---------------- CLASS DEFINITION --------------------------
template<type>
struct node
{
    type data;
    node<type> *next;
};

template <class type>
class LinkedQueue : public queueADT<type>
{
    private:
    node<type> *queueFront;
    node<type> *queueRear;
    
    public:
    LinkedQueue();
    //LinkedQueue(const LinkedQueue<type>& otherQueue);
    ~LinkedQueue();
    
    //const LinkedQueue<type>& operator=(const LinkedQueue<type>& otherQueue)
    void initializeQueue();
    bool isEmptyQueue() const;
    bool isFullQueue() const; // A linked list cannot be "Full" since not limited by size like an array is.
                              // however, still implemented as an abstract class has the PureVirFn.
    void enQueue(const type& qElement);
    void deQueue();
    type front() const;
    type back() const;
    
};

// ----------------- IMPLEMENTATION -------------------
// 0. Constructor
template <class type>
LinkedQueue<type>::LinkedQueue()
{
    queueFront = nullptr;
    queueRear  = nullptr;
}

// 0. Initialize
template<class type>
LinkedQueue<type>::initializeQueue()
{
    node<type> *temp;
    while(!queueFront==nullptr)
    {
        temp = queueFront;
        queueFront = queueFront -> next;
        delete temp;
    }
    queueRear = nullptr;
}

// 0. Destructor
template <class type>
LinkedQueue<type>::~LinkedQueue()
{
    initializeQueue(); // delete all elements of queue, set both pointers (front/back) to null.
}

// 1. is empty
template <class type>
bool LinkedQueue<type>::isEmptyQueue() const
{
    return (queueFront==nullptr);
}
// 2. is full
template <class type>
bool LinkedQueue<type>::isFullQueue() const
{
    return false;
}
// 3. front
template <class type>
type LinkedQueue<type>::front() const
{
    assert(!queueFront==nullptr)
    return queueFront->data;
}

// 4. back
template <class type>
type LinkedQueue<type>::back() const
{
    assert(!queueRear==nullptr)
    return queueRear->data;
}
// 5. enqueue
template <class type>
void LinkedQueue<type>::enQueue(const type& qElement)
{
    node<type> *newNode;
    newNode = new node<type>;
    newNode->data = qElement;
    newNode->next = nullptr;
    
    if (queueFront==nullptr){
        queueFront = newNode;
        queueRear = newNode;
    }
    else{
        queueRear->next = newNode;
        queueRear = queueRear->next;
    }
}
// 6. dequeue
template <class type>
void LinkedQueue<type>::deQueue()
{
    node<type> *temp;
    if(!isEmptyQueue()){
        temp = queueFront;
        queueFront = queueFront->next;
        delete temp;
        
        if(queueFront==nullptr) queueRear = nullptr; //if queue empty after dequeue.
    }
    else
        cout << "Underflow.\n" << endl;
}

#endif