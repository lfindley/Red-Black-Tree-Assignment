#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "RedBlackTreeNode.h"

class RedBlackTree {
private:
    RedBlackTreeNode* root;

    // Utility functions
    void destroyTree(RedBlackTreeNode* node);
    void copyTree(RedBlackTreeNode* src, RedBlackTreeNode*& dest, RedBlackTreeNode* parent);
    void rotateLeft(RedBlackTreeNode* node);
    void rotateRight(RedBlackTreeNode* node);
    RedBlackTreeNode* search(int value);
    void preorder(RedBlackTreeNode* node);
    void inorder(RedBlackTreeNode* node);
    void postorder(RedBlackTreeNode* node);

public:
    // Constructors and Destructor
    RedBlackTree();
    RedBlackTree(const RedBlackTree& other);
    ~RedBlackTree();

    // Assignment Operator Overloading
    RedBlackTree& operator=(const RedBlackTree& other);

    // Public member functions
    void insert(int value);
    void insertFix(RedBlackTreeNode* node);
    void remove(int value);
    void removeFix(RedBlackTreeNode* x, RedBlackTreeNode* xParent);
    bool searchValue(int value);
    void traversePreorder();
    void traverseInorder();
    void traversePostorder();
    void printPreorder();
};

#endif // REDBLACKTREE_H
