#include <iostream>
#include <string>
#include "RedBlackTree.h"

using namespace std;

int main() {
    string input;
    RedBlackTree tree;

    // Read values from user input until stop flag is entered
    cout << "Enter values to insert into tree (type 's' to finish):" << endl;
    while (true) {
        cin >> input;
        if (input == "s") {
            break;
        }
        int value = stoi(input);
        tree.insert(value);
    }

    // Test all functionalities
    cout << "Performing tests..." << endl;

    // Test search function
    cout << "Search for value in tree (enter value): ";
    cin >> input;
    int value = stoi(input);
    if (tree.searchValue(value)) {
        cout << "Value " << value << " found in tree." << endl;
    }
    else {
        cout << "Value " << value << " not found in tree." << endl;
    }

    // Test preorder traversal
    cout << "Preorder traversal of tree:" << endl;
    tree.traversePreorder();

    // Test inorder traversal
    cout << "Inorder traversal of tree:" << endl;
    tree.traverseInorder();

    // Test postorder traversal
    cout << "Postorder traversal of tree:" << endl;
    tree.traversePostorder();

    // Test print preorder
    cout << "Printing contents of tree in preorder:" << endl;
    tree.printPreorder();

    // Test remove function
    cout << "Enter value to remove from tree: ";
    cin >> input;
    value = stoi(input);
    tree.remove(value);
    cout << "Value " << value << " removed from tree." << endl;

    // Test copy constructor
    cout << "Testing copy constructor..." << endl;
    RedBlackTree treeCopy(tree);
    cout << "Preorder traversal of copied tree:" << endl;
    treeCopy.traversePreorder();

    // Test assignment operator overloading
    cout << "Testing assignment operator overloading..." << endl;
    RedBlackTree treeAssigned;
    treeAssigned = tree;
    cout << "Preorder traversal of assigned tree:" << endl;
    treeAssigned.traversePreorder();

    cout << "All tests completed." << endl;

    return 0;
}
