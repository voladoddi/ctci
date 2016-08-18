/*
 Insert Node at a given position in a linked list
 head can be NULL
 First element in the linked list is at position 0
 Node is defined as
 struct Node
 {
 int data;
 struct Node *next;
 }
 */
Node* InsertNth(Node *head, int data, int position)
{
    Node *newNode = new Node;
    newNode->data = data;
    
    Node *current = head;
    // add in front -- check if head is null, or a list exists.
    if (position==0){
        if (head==nullptr)
            newNode->next = nullptr;
        else
            newNode->next = head;
        head = newNode;
    } // add in any other position.
    else{
        Node *temp;
        for(int i = 0; i< (position-1); i++)
            current = current -> next;
        temp = current->next;
        current -> next = newNode;
        newNode -> next = temp;
        
    }
    return head;
    // Complete this method only
    // Do not write main function.
    
}
