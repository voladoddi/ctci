#ifndef H_binTrees
#define H_binTrees

#include<iostream>
using namespace std;

/*
 For hierarchical data organization, and not structured trees, binary tree operations are as follows:
 
 1. isEmpty
 2. Height (levels)
 3. #Nodes
 4. #Leaves
 5. Traversal -- inorder, preorder, postorder
 6. Copy the binary tree.
 
 For efficient insert, delete and lookup (search), we go for BSTs instead of just BTs, which would help guide the direction of search/insert and delete operations. 
 1. insert
 2. delete
 3. search/lookup
 
 */

template<class type>
struct binaryTreeNode
{
    type data;
    binaryTreeNode<type>* leftChild;
    binaryTreeNode<type>* rightChild;
};

template<class type>
class binaryTree
{
private:
    void copyTree(binaryTree<type>* &copiedTreeRoot, binaryTree<type>* otherBinaryTreeRoot);
    void destroy(binaryTreeNode<type>* &p);
    
    void inorder(binaryTreeNode<type> *p) const;
    void preorder(binaryTreeNode<type> *p) const;
    void postorder(binaryTreeNode<type> *p) const;
    
    int height(binaryTreeNode<type> *p) const;
    int max(int x, int y) const;
    int nodeCount(binaryTreeNode<type> *p) const;
    int leavesCount(binaryTreeNode<type> *p) const;
    
protected:
    binaryTreeNode<type>* root; //to *derive* special binary trees later.
    
public:
    // class with pointer data members.
    // Therefore explicitly,
    // 1. overload the assignment operator.
    // 2. copy constructor.
    // 3. destructor.
    binaryTree();
    binaryTree(const binaryTree<type>& otherBinaryTree);
    ~binaryTree();
    
    bool isEmpty() const;
    
    int treeHeight() const;
    int treeNodeCount() const;
    int treeLeavesCount() const;
    
    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    
    const binaryTree<type>& operator=(const binaryTree<type>&);
    void destroyTree();
    
};

#endif