#ifndef DSLINKEDLIST_H
#define DSLINKEDLIST_H
#include <stdexcept>
#include <iostream>
using namespace std;

// Node class
template <typename T>
class Node {
    public:
        // mem vars
        T element;
        Node<T>* next;
    
        // Constructors
        Node(){
            next = nullptr;
        }
    
        Node(T element){
            this->element = element;
            next = nullptr;
        }
    
};



// Linked List class.
template <typename T>
class LinkedList {
    // mem vars
    private:
        Node<T>* head;
        Node<T>* tail;
        //int size;
    
    public:
        // Constructors
        LinkedList();
        LinkedList(const LinkedList<T>& list); //copy
        ~LinkedList();
       
        // Mem Fns.
        void addInFront(T element);
        void addAtBack(T element); //equivalent to addLast --- add|||append
        void addAtIndex(int index, T element);
    
        
        int getSize() const;
        bool isEmpty() const;
        
        T getFirst() const;
        T getLast() const;
        T get(int index) const;
    
        int indexOf(T element) const;
        int lastIndexOf(T element) const;
        bool contains(T element) const;
        
        T removeFirst();
        T removeLast();
        T removeAt(int index);
        void remove(T element);
    
        void printList();
    
        void clear();
    
    
    
};

#endif