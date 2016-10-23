
#ifndef H_ThreeInOne
#define H_ThreeInOne

#include<iostream>
using namespace std;


class Multistack{
  
    private:
        int numStacks = 3;
    
        int kthStackCapacity;
        int kthStackTop(int stackNumber) const;
        int *kthStackUsedSize;
        int *stackArray;
    
    public:
        Multistack(int stackCapacity);
        ~Multistack();
    
        bool isEmpty(int stackNumber) const;
        bool isFull(int stackNumber) const;
    
        void push(int stackNumber, int value);
        void pop(int stackNumber);
        int top(int stackNumber) const;
    
};
#endif