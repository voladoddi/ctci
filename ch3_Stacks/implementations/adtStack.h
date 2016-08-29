#ifndef H_stackADT
#define H_stackADT
#include <stdexcept>
#include <iostream>
using namespace std;

// ---------- ABSTRACT CLASS ----------------
template <class type>
class stackADT
{
public:
    virtual void initializeStack() = 0;
    virtual bool isEmptyStack() const = 0;
    virtual bool isFullStack() const = 0;
    
    virtual void push(const type& newItem) = 0;
    virtual type top() const = 0;
    virtual void pop()  = 0;
};

#endif