#ifndef RED_BLACK_TREE_NODE_H
#define RED_BLACK_TREE_NODE_H

enum ColorType { RED, BLACK };

class RedBlackTree;

class RedBlackTreeNode {
    friend class RedBlackTree;

private:
    int value;
    ColorType Color;
    RedBlackTreeNode* parent;
    RedBlackTreeNode* left;
    RedBlackTreeNode* right;

public:
    // Constructor
    RedBlackTreeNode()
        :value(0), Color(RED), left(nullptr), right(nullptr), parent(nullptr)
    {}

    // Explicit Value Constructor
    RedBlackTreeNode(int inValue, ColorType color, RedBlackTreeNode* inLeft = nullptr,
        RedBlackTreeNode* inRight = nullptr, RedBlackTreeNode* inParent = nullptr)
        :value(inValue), left(inLeft), right(inRight), parent(inParent), Color(color)
    {}

    // Getter Functions
    inline int getValue() const {
        return value;
    }

    inline ColorType getColor() const {
        return Color;
    }

    // Setter Functions
    inline void setValue(int newVal) {
        value = newVal;
    }

    inline void setColor(ColorType color) {
        Color = color;
    }
};

#endif // RED_BLACK_TREE_NODE_H
