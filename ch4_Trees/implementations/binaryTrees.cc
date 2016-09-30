#include<iostream>
#include "binaryTrees.h"


// ----- All private function implementations -------
template<class type>
void binaryTree<type>::copyTree(binaryTree<type>* &copiedTreeRoot, binaryTree<type>* otherBinaryTreeRoot){
    if (otherBinaryTreeRoot == nullptr)
        copiedTreeRoot =nullptr;
    else
    {
        copiedTreeRoot = new binaryTreeNode<type>;
        
        copiedTreeRoot->data = otherBinaryTreeRoot->data;
        copyTree(copiedTreeRoot->leftChild, otherBinaryTreeRoot->leftChild);
        copyTree(copiedTreeRoot->rightChild, otherBinaryTreeRoot->rightChild);
    }
}
template<class type>
void binaryTree<type>::destroy(binaryTreeNode<type>* &p){
    if(p!=nullptr)
    {
        destroy(p->leftChild);
        destroy(p->rightChild);
        delete p;
        p == nullptr;
    }
}

template<class type>
void binaryTree<type>::inorder(binaryTreeNode<type> *p) const{
    if(p!=nullptr)
    {
        inorder(p->leftChild);
        cout << p->data << " ";
        inorder(p->rightChild);
    }
}
template <class type>
void binaryTree<type>::preorder(binaryTreeNode<type> *p) const{
    if(p!=nullptr)
    {
        cout << p->data << " ";
        inorder(p->leftChild);
        inorder(p->rightChild);
    }
}
template <class type>
void binaryTree<type>::postorder(binaryTreeNode<type> *p) const{
    if(p!=nullptr)
    {
        inorder(p->leftChild);
        inorder(p->rightChild);
        cout << p->data << " ";
    }
}
template<class type>
int binaryTree<type>::height(binaryTreeNode<type> *p) const{
    if(p!=nullptr)
        return 1 + max(height(p->leftChild),height(p->rightChild));
    else
        return 0;
}
template<class type>
int binaryTree<type>::max(int x, int y) const{
    if (x>=y) return x;
    else return y;
}

template<class type>
int binaryTree<type>::nodeCount(binaryTreeNode<type> *p) const{
    if (p!=nullptr)
        return 1 + nodeCount(p->leftChild) + nodeCount(p->rightChild);
    else
        return 0;
}
template<class type>
int binaryTree<type>::leavesCount(binaryTreeNode<type> *p) const{
    if (p==nullptr)
        return 0;
    if (p->leftChild==nullptr && p->rightChild==nullptr)
        return 1;
    return leavesCount(p->leftChild) + leavesCount(p->rightChild);
}

// ----- All public function (wrapper) implementations --------
// 0. Copy Constructor
template<class type>
binaryTree<type>::binaryTree(const binaryTree<type>& otherBinaryTree)
{
    if (otherBinaryTree.root==nullptr)
        root = nullptr;
    else
        copyTree(root, otherBinaryTree.root);
}
// 0. Destructor
template<class type>
binaryTree<type>::~binaryTree()
{
    destroy(root);
}

// 1. isEmpty
template<class type>
bool binaryTree<type>::isEmpty() const
{
    return (root==nullptr);
}

// 2. overload the assignment operator
template<class type>
const binaryTree<type>& binaryTree<type>::operator=(const binaryTree<type>& otherBinaryTree)
{
    if(this!= &otherBinaryTree)
    {
        if(root!=nullptr)
            destroy(root);
        else
            if(otherBinaryTree.root==nullptr)
                root = nullptr;
            else
                copyTree(root, otherBinaryTree.root);
    }
    return *this;
}

// 3. destroy tree
template <class type>
void binaryTree<type>::destroyTree()
{
    destroy(root);
}

// 4. treeHeight, treeNodeCount, treeLeavesCount
template <class elemType>
int binaryTreeType<elemType>::treeHeight() const {
    return height(root);
}
template <class elemType>
int binaryTreeType<elemType>::treeNodeCount() const {
    return nodeCount(root);
}
template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount() const {
    return leavesCount(root);
}

// 5. Traversals.
void binaryTreeType<elemType>::inorderTraversal() const {
    inorder(root);
}
template <class elemType>
void binaryTreeType<elemType>::preorderTraversal() const {
    preorder(root);
}
template <class elemType>
void binaryTreeType<elemType>::postorderTraversal() const {
    postorder(root);
}

// ---------- MAIN -------------
int main()
{
    
    return 0;
}