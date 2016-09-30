/*
 Implementation of a Queue ADT :
 [1] initializeQueue
 [2] isEmptyQueue / isFullQueue
 [3] front / back
 [4] addQueue/deleteQueue i.e. enqueue, dequeue 
 
 Applications:
 [1] Breadth First Search 
 [2] Resource sharing
 [3] Asynchronoous data transfer.
*/

#ifndef H_queueADT
#define H_queueADT

#include <iostream>
#include <stdexcept>

template <class type>
class queueADT
{
    public:
        virtual void initializeQueue() = 0;
        virtual bool isEmptyQueue() const = 0;
        virtual bool isFullQueue() const = 0;
        virtual type front() const = 0;
        virtual type back() const = 0;
        virtual void enQueue(const type & qElement) = 0;
        virtual void deQueue() = 0;
    
};

#endif