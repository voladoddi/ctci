#include "DSLINKEDLIST.h"

// ----- Constructors -----
template <typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
    //size = 0;
    
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list){
    head = nullptr;
    tail = nullptr;
    //size = 0;
    
    Node<T>* current = list.head;
    while(current!= nullptr)
    {
        this->element = current->element;
    }
}

template<typename T>
LinkedList<T>::~LinkedList(){
    clear();
}

//  ---- Mem Fns. -----
// ----------- 1. Add element in the beginning of the list ---------------
template <typename T>
void LinkedList<T>::addInFront(T element)
{
    Node<T>* temp = new Node<T>(element);
    if(head == nullptr)
        head = temp;
    else{
        temp->next   = head;
        head = temp;
    }
}

// ------------ 2. Append element to the linked list. --------------------
template<typename T>
void LinkedList<T>::addAtBack(T element)
{
    if (tail == NULL)
    {
        head = tail = new Node<T>(element);
    }
    else
    {
        tail->next = new Node<T>(element);
        tail = tail -> next;
    }
}


// --------------- 3. Add element to linked list at "index" position. ------------
template<typename T>
void LinkedList<T>::addAtIndex(int index, T element)
{
    Node<T>* temp;
    Node<T>* current = head;
    if (index==1) addInFront(element);
    else{
        for(int i = 0; i < (index-2); i++)
            current = current->next;
        temp = current->next;
        current -> next = new Node<T>(element);
        (current-> next)->next = temp;
    }
    
}


// -------------- 4. get size of Linked List --------------------
template <typename T>
int LinkedList<T>::getSize() const
{
    if (head==nullptr && tail==nullptr) return 0;
    
    Node<T>* temp = head;
    int counter = 0;
    while(temp!=nullptr)
    {
        counter++;
        temp = temp->next;
    }
    return counter;
}

// ------------- 5. is Linked List empty ------------------------
template<typename T>
bool LinkedList<T>::isEmpty() const
{
    if (head==nullptr && tail==nullptr) return true;
    else return false;
}


// ----------- 6. return the first element of the Linked List -------
template<typename T>
T LinkedList<T>::getFirst() const
{
    if (head==nullptr)
        throw runtime_error("List empty\n");
    else
        return head->element;
}

// ----------- 7. return the LAST element of the Linked List -------
template<typename T>
T LinkedList<T>::getLast() const
{
    if (head==nullptr && tail==nullptr)
        throw runtime_error("List empty\n");
    else
        return tail->element;
}


// ------------ 8. get element at "index" in list -----------
template<typename T>
T LinkedList<T>::get(int index) const
{
    Node<T>* current = head;
    if (head==nullptr && tail==nullptr)
        throw runtime_error("List empty\n");
    else if (index==1)
        getFirst();
    else
        for(int i=1; i<index; i++)
            current = current->next;
        return current->element;
    
    // should add check for index greater than tail.
}


// ----------- 9. index of some element in the list ------------
template<typename T>
int LinkedList<T>::indexOf(T element) const
{
    int size = getSize();
    Node<T>* temp = head;
    for (int i = 0; i < size; i++)
    {
        if (element == temp->element)
            return i+1;
        else
            temp = temp->next;
    }
    return -1;
    
}


// ----------- 10. Last occurrence of element in list ----------
template<typename T>
int LinkedList<T>::lastIndexOf(T element) const
{
    Node<T>* temp = head;
    int index = 1, fIndex;
    if (head==nullptr)
        return -1;
    else{
        while(temp!=nullptr)
        {
            cout<< index << "\n";
            if(temp->element==element)
                fIndex = index;
            temp=temp->next;
            index++;
        }
        return fIndex;
    }
    

}

// ----------- 11. List contains given element or not? ---------
template<typename T>
bool LinkedList<T>::contains(T element) const
{
    Node<T>*temp = head;
    if(head==nullptr)
        return false;
    while(temp!=nullptr)
    {
        if(temp->element==element)
            return true;
        temp=temp->next;
    }
    return false;
}


// ----------- 12. Delete node in front ----------------
template<typename T>
T LinkedList<T>::removeFirst()
{
    Node<T>* temp= head;
    if(getSize()==0) throw runtime_error("No elements\n");
    else
    {
        head=head->next;
        T elem = temp->element;
        delete temp;
        return elem;
    }
        
}


// ------------ 13. Delete node in back. -------------
template<typename T>
T LinkedList<T>::removeLast()
{

    int size = getSize();
    if (size==0) throw runtime_error("No elements\n");
    else
    {
        Node<T>* current = head;
        for(int i=0; i<(size-2); i++)
            current = current->next;
        
        Node<T>* temp = tail;
        tail  = current;
        tail-> next = nullptr;
        T elem = temp->element;
        delete temp;
        
        return elem;
    }
}

// ------------- 14. Delete node at given index -----------
template<typename T>
T LinkedList<T>::removeAt(int index)
{
    int size = getSize();
    if (size==0) throw runtime_error("No elements\n");
    if(index==1)
        return removeFirst();
    else
    {
        Node<T>* previous = head;
        for(int i=1; i<(index-1); i++)
            previous = previous->next;
        
        Node<T>* current = previous->next;
        previous->next  = current->next;
        T elem = current->element;
        delete current;
        
        return elem;
    }
}

// ----------- 15. Delete given element if found in list --------
template<typename T>
void LinkedList<T>::remove(T element)
{
    
}


// ----------- 16. Print Linked List ----------------
template<typename T>
void LinkedList<T>::printList()
{
    if(this->head==nullptr) {
        cout << "End " <<endl;
    }
    else {
        Node<T>* temp = this->head;
        while(temp!=nullptr)
        {
            cout << temp->element;
            temp = temp->next;
            cout << " ";
        }
        
    }
    cout<<"\n";
}
// ----------- 17. Clear the list (delete all elements) and resource allocated(mem)---
template<typename T>
void LinkedList<T>::clear()
{
    //Node<T*> current = head;
    //Node<T*> next = new Node<T*>;
    while(head!=nullptr)
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}



// -------------------------------
//          MAIN
//--------------------------------

int main()
{
    LinkedList<int> list;
    
    list.addAtBack(10);
    list.addAtBack(20);
    list.addAtBack(-30);
    list.addInFront(0);
    list.addInFront(-1);
    list.addAtIndex(2,3);
    list.addAtIndex(5,55);
    list.addInFront(-30);
    
    list.printList();
    
    int firstElem = list.getFirst();
    cout <<"\n" << firstElem << "\n"<< endl;
    
    int lastElem = list.getLast();
    cout <<"\n" << lastElem << "\n"<< endl;
    
    int idxElem = list.get(8);
    cout <<" Element at Index: " << idxElem <<"\n" <<endl;
    
    int foundElem = list.indexOf(-30);
    cout << "-30 at ... " << foundElem << "\n" << endl;
    
    foundElem = list.lastIndexOf(-30);
    cout << "-30 at ... " << foundElem << "\n" << endl;
    
    int contains = list.contains(9);
    cout << contains << "\n";
    
    // remove one -30 here and check again
    foundElem = list.removeFirst();
    list.printList();
    foundElem = list.indexOf(-30);
    cout << "-30 at ... " << foundElem << "\n" << endl;
    
    foundElem = list.removeLast();
    list.printList();
    
    foundElem = list.removeLast();
    list.printList();
    
    foundElem=list.removeAt(list.getSize());
    list.printList();
    
    list.remove(0);
    list.printList();
    
    return 0;
}







