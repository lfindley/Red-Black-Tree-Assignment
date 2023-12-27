#include "RedBlackTree.h"
#include <iostream>

using namespace std;
// Utility functions
void RedBlackTree::destroyTree(RedBlackTreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void RedBlackTree::copyTree(RedBlackTreeNode* src, RedBlackTreeNode*& dest, RedBlackTreeNode* parent) {
    if (src == nullptr) {
        dest = nullptr;
        return;
    }

    dest = new RedBlackTreeNode(src->getValue(), src->getColor(), nullptr, nullptr, parent);
    copyTree(src->left, dest->left, dest);
    copyTree(src->right, dest->right, dest);
}

void RedBlackTree::rotateLeft(RedBlackTreeNode* node) {
    RedBlackTreeNode* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    }
    else if (node == node->parent->left) {
        node->parent->left = rightChild;
    }
    else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(RedBlackTreeNode* node) {
    RedBlackTreeNode* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    }
    else if (node == node->parent->right) {
        node->parent->right = leftChild;
    }
    else {
        node->parent->left = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

RedBlackTreeNode* RedBlackTree::search(int value) {
    RedBlackTreeNode* current = root;

    while (current != nullptr) {
        if (value == current->getValue()) {
            return current;
        }
        else if (value < current->getValue()) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return nullptr;
}

void RedBlackTree::preorder(RedBlackTreeNode* node) {
    if (node != nullptr) {
        cout << node->getValue() << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

void RedBlackTree::inorder(RedBlackTreeNode* node) {
    if (node != nullptr) {
        inorder(node->left);
        cout << node->getValue() << " ";
        inorder(node->right);
    }
}

void RedBlackTree::postorder(RedBlackTreeNode* node) {
    if (node != nullptr) {
        postorder(node->left);
        postorder(node->right);
        cout << node->getValue() << " ";
    }
}

// Constructors and Destructor
RedBlackTree::RedBlackTree() : root(nullptr) {}

RedBlackTree::RedBlackTree(const RedBlackTree& other) {
    copyTree(other.root, root, nullptr);
}

RedBlackTree::~RedBlackTree() {
    destroyTree(root);
}

// Assignment Operator Overloading

RedBlackTree & RedBlackTree::operator=(const RedBlackTree & other) {
    if (this != &other) {
        destroyTree(root);
        root = NULL;
        copyTree(other.root, root, NULL);
    }
    return *this;
}

// Public member functions

void RedBlackTree::insert(int value) {
    // Create new node and initialize it
    RedBlackTreeNode* newNode = new RedBlackTreeNode(value, RED);

    // Insert the new node into the tree
    if (root == nullptr) {
        // Tree is empty, so new node is the root
        root = newNode;
    }
    else {
        RedBlackTreeNode* parent = nullptr;
        RedBlackTreeNode* current = root;
        while (current != nullptr) {
            parent = current;
            if (value < current->getValue()) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        newNode->parent = parent;
        if (value < parent->getValue()) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }

    // Fix any violations of the Red-Black tree properties caused by inserting the new node
    insertFix(newNode);
}

void RedBlackTree::insertFix(RedBlackTreeNode* node) {
    // Rebalance the tree as needed to restore Red-Black properties
    while (node != root && node->parent->getColor() == RED) {
        if (node->parent == node->parent->parent->left) {
            // Node's parent is a left child
            RedBlackTreeNode* aunt = node->parent->parent->right;
            if (aunt != nullptr && aunt->getColor() == RED) {
                // Case 1: Node's aunt is RED
                node->parent->setColor(BLACK);
                aunt->setColor(BLACK);
                node->parent->parent->setColor(RED);
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    // Case 2: Node's aunt is BLACK and node is a right child
                    node = node->parent;
                    rotateLeft(node);
                }
                // Case 3: Node's aunt is BLACK and node is a left child
                node->parent->setColor(BLACK);
                node->parent->parent->setColor(RED);
                rotateRight(node->parent->parent);
            }
        }
        else {
            // Node's parent is a right child
            RedBlackTreeNode* aunt = node->parent->parent->left;
            if (aunt != nullptr && aunt->getColor() == RED) {
                // Case 1: Node's aunt is RED
                node->parent->setColor(BLACK);
                aunt->setColor(BLACK);
                node->parent->parent->setColor(RED);
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    // Case 2: Node's aunt is BLACK and node is a left child
                    node = node->parent;
                    rotateRight(node);
                }
                // Case 3: Node's aunt is BLACK and node is a right child
                node->parent->setColor(BLACK);
                node->parent->parent->setColor(RED);
                rotateLeft(node->parent->parent);
            }
        }
    }

    // Make sure the root is black
    root->setColor(BLACK);
}

void RedBlackTree::remove(int value) {
    RedBlackTreeNode* node = search(value);
    if (!node) {
        return;
    }
    RedBlackTreeNode* child = NULL;
    if (!node->left) {
        child = node->right;
    }
    else if (!node->right) {
        child = node->left;
    }
    else {
        // If the node has two children, replace its value with the successor's value
        RedBlackTreeNode* successor = node->right;
        while (successor->left) {
            successor = successor->left;
        }
        node->value = successor->value;
        node = successor;
        child = node->right;
    }
    if (node->Color == BLACK) {
        // If the node is black, the removal may violate red-black tree properties
        // We need to rebalance the tree starting from the parent of the removed node
        if (!node->parent) {
            root = child;
        }
        else if (node == node->parent->left) {
            node->parent->left = child;
        }
        else {
            node->parent->right = child;
        }
        if (child) {
            child->parent = node->parent;
        }
        // Check whether we need to fix the tree
        if (child) {
            removeFix(child, node->parent);
        }
        else {
            removeFix(NULL, node->parent);
        }
    }
    else {
        // If the node is red, just remove it
        if (!node->parent) {
            root = child;
        }
        else if (node == node->parent->left) {
            node->parent->left = child;
        }
        else {
            node->parent->right = child;
        }
        if (child) {
            child->parent = node->parent;
        }
    }
    delete node;
}

void RedBlackTree::removeFix(RedBlackTreeNode* x, RedBlackTreeNode* xParent) {
    while (x != root && x->getColor() == BLACK) {
        if (x == xParent->left) {
            RedBlackTreeNode* w = xParent->right;
            if (w->getColor() == RED) {
                w->setColor(BLACK);
                xParent->setColor(RED);
                rotateLeft(xParent);
                w = xParent->right;
            }
            if ((w->left == nullptr || w->left->getColor() == BLACK) &&
                (w->right == nullptr || w->right->getColor() == BLACK)) {
                w->setColor(RED);
                x = xParent;
                xParent = xParent->parent;
            }
            else {
                if (w->right == nullptr || w->right->getColor() == BLACK) {
                    if (w->left != nullptr) w->left->setColor(BLACK);
                    w->setColor(RED);
                    rotateRight(w);
                    w = xParent->right;
                }
                w->setColor(xParent->getColor());
                xParent->setColor(BLACK);
                if (w->right != nullptr) w->right->setColor(BLACK);
                rotateLeft(xParent);
                x = root;
            }
        }
        else {
            RedBlackTreeNode* w = xParent->left;
            if (w->getColor() == RED) {
                w->setColor(BLACK);
                xParent->setColor(RED);
                rotateRight(xParent);
                w = xParent->left;
            }
            if ((w->right == nullptr || w->right->getColor() == BLACK) &&
                (w->left == nullptr || w->left->getColor() == BLACK)) {
                w->setColor(RED);
                x = xParent;
                xParent = xParent->parent;
            }
            else {
                if (w->left == nullptr || w->left->getColor() == BLACK) {
                    if (w->right != nullptr) w->right->setColor(BLACK);
                    w->setColor(RED);
                    rotateLeft(w);
                    w = xParent->left;
                }
                w->setColor(xParent->getColor());
                xParent->setColor(BLACK);
                if (w->left != nullptr) w->left->setColor(BLACK);
                rotateRight(xParent);
                x = root;
            }
        }
    }
    x->setColor(BLACK);
}

bool RedBlackTree::searchValue(int value) {
    RedBlackTreeNode* node = search(value);
    if (node != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

void RedBlackTree::traversePreorder() {
    preorder(root);
    cout << endl;
}

void RedBlackTree::traverseInorder() {
    inorder(root);
    cout << endl;
}

void RedBlackTree::traversePostorder() {
    postorder(root);
    cout << endl;
}

void RedBlackTree::printPreorder() {
    preorder(root);
    cout << endl;
}
