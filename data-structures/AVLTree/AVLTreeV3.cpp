#include <iostream>

class Node
{
public:
    int value;
    Node *left;
    Node *right;
    int height;

    Node(int value)
    {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
    }
};

int getBalance(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return node->height;
    }
}

class AVLTree
{
private:
    Node *root;

public:
    AVLTree()
    {
        this->root = nullptr;
    }

    ~AVLTree()
    {
        delete[] this->root;
    }

    Node *leftRotate(Node *y)
    {
        Node *x = y->right;
        Node *l1 = x->left;

        x->left = y;
        y->right = l1;

        return x;
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *r1 = x->right;

        x->right = y;
        y->left = r1;

        return x;
    }

    int inorderSuccessor(Node *node)
    {
        node = node->right;
        while (node != nullptr && node->left != nullptr)
        {
            node = node->left;
        }
        return node->value;
    }

    Node *insertValue(Node *node, int value)
    {
        if (node == nullptr)
            return nullptr;
        if (node->value > value)
        {
            node->left = this->insertValue(node->left, value);
        }
        else if (node->value < value)
        {
            node->right = this->insertValue(node->right, value);
        }
        else
        {
            return node;
        }

        node->height = std::max(getBalance(node->left), getBalance(node->right)) + 1;
        int balanceFactor = getBalance(node->left) - getBalance(node->right);

        // Left Case
        if (balanceFactor > 1)
        {
            // Right Case
            if (balanceFactor < 0)
            {
                node->left = leftRotate(node->left);
            }
            node = rightRotate(node);
        }

        // Right Case
        if (balanceFactor < -1)
        {
            // Left Case
            if (balanceFactor > 0)
            {
                node->right = rightRotate(node->left);
            }
            node = leftRotate(node);
        }

        return node;
    }

    Node *deleteValue(Node *node, int value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->value > value)
        {
            node->left = this->deleteValue(node->left, value);
        }
        else if (node->value < value)
        {
            node->right = this->deleteValue(node->right, value);
        }
        else
        {
            if (node->right == nullptr)
            {
                Node *temp = node;
                node = node->left;
                delete temp;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node;
                node = node->right;
                delete temp;
            }
            else
            {
                int inorderSuccessorValue = this->inorderSuccessor(node);
                node->value = inorderSuccessorValue;
                this->deleteValue(node, inorderSuccessorValue);
            }
        }

        node->height = std::max(getBalance(node->left), getBalance(node->right));
        int balanceFactor = getBalance(node->left) - getBalance(node->right);

        return node;
    }
}