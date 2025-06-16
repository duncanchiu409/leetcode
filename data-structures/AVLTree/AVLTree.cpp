#include <iostream>
#include <algorithm>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

template <typename T>
class Node; // Forward declaration

template <typename T>
int height(Node<T> *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return node->height;
    }
}

template <typename T>
class Node
{
public:
    Node<T> *left;
    Node<T> *right;
    T value;
    int height;

    Node(T value)
    {
        this->value = value;
        this->height = 1; // New nodes have height 1
        this->left = NULL;
        this->right = NULL;
    }
};

template <typename T>
class AVLTree
{
private:
    Node<T> *leftRotate(Node<T> *);
    Node<T> *rightRotate(Node<T> *);
    // Renamed to be a private recursive helper
    Node<T> *insertValue(Node<T> *node, T value);
    Node<T> *getInorderSuccessor(Node<T> *node);
    Node<T> *deleteValue(Node<T> *node, T value);

public:
    Node<T> *head;

    AVLTree<T>();
    // Public method to start insertion
    void insertValue(T value);
    void deleteValue(T value);
    void preorderTraversal(Node<T> *);
};

template <typename T>
AVLTree<T>::AVLTree()
{
    this->head = NULL;
}

// Public wrapper for insertValue
template <typename T>
void AVLTree<T>::insertValue(T value)
{
    this->head = insertValue(this->head, value);
}

template <typename T>
Node<T> *AVLTree<T>::leftRotate(Node<T> *x)
{
    Node<T> *y = x->right;
    Node<T> *T2 = y->left;

    x->right = T2;
    y->left = x;

    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));

    return y;
}

template <typename T>
Node<T> *AVLTree<T>::rightRotate(Node<T> *x)
{
    Node<T> *y = x->left;
    Node<T> *T2 = y->right;

    x->left = T2;
    y->right = x;

    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));

    return y;
}

template <typename T>
Node<T> *AVLTree<T>::insertValue(Node<T> *node, T value)
{
    if (node == NULL)
    {
        return new Node<T>(value);
    }

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

    // This line is needed to correctly update heights up the tree
    node->height = 1 + std::max(height(node->left), height(node->right));

    int balanceFactor = height(node->left) - height(node->right);

    if (balanceFactor > 1)
    {
        if (value > node->left->value)
        {
            node->left = this->leftRotate(node->left);
        }
        return this->rightRotate(node);
    }

    if (balanceFactor < -1)
    {
        if (value < node->right->value)
        {
            node->right = this->rightRotate(node->right);
        }
        return this->leftRotate(node);
    }

    return node;
}

template <typename T>
Node<T> *AVLTree<T>::getInorderSuccessor(Node<T> *node)
{
    Node<T> *current = node->right;
    while (current != NULL && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

template <typename T>
Node<T> *AVLTree<T>::deleteValue(Node<T> *node, T value)
{
    if (node == NULL)
    {
        return node;
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
        if (node->left == NULL)
        {
            Node<T> *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL)
        {
            Node<T> *temp = node->left;
            delete node;
            return temp;
        }
        else
        {
            Node<T> *temp = this->getInorderSuccessor(node);
            node->value = temp->value;
            node->right = this->deleteValue(node->right, temp->value);
        }
    }

    if (node == NULL)
    {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balanceFactor = height(node->left) - height(node->right);

    if (balanceFactor > 1)
    {
        if ((height(node->left->left) - height(node->left->right)) < 0)
        {
            node->left = this->leftRotate(node->left);
        }
        return this->rightRotate(node);
    }

    if (balanceFactor < -1)
    {
        if ((height(node->right->left) - height(node->right->right)) > 0)
        {
            node->right = this->rightRotate(node->right);
        }
        return this->leftRotate(node);
    }

    return node;
}

template <typename T>
void AVLTree<T>::deleteValue(T value)
{
    this->head = this->deleteValue(this->head, value);
}

template <typename T>
void AVLTree<T>::preorderTraversal(Node<T> *node)
{
    if (node == NULL)
    {
        return;
    }

    std::cout << node->value << " ";
    this->preorderTraversal(node->left);
    this->preorderTraversal(node->right);
}

TEST_CASE("AVLTree insertion TEST CASE 01")
{
    AVLTree<int> tree;
    tree.insertValue(10);
    tree.insertValue(20);
    tree.insertValue(30);
    tree.insertValue(40);
    tree.insertValue(50);
    tree.insertValue(25);

    tree.preorderTraversal(tree.head);
}

TEST_CASE("AVL Tree Deletion TEST CASE 01")
{
    AVLTree<int> tree;
    tree.insertValue(9);
    tree.insertValue(5);
    tree.insertValue(10);
    tree.insertValue(0);
    tree.insertValue(6);
    tree.insertValue(11);
    tree.insertValue(-1);
    tree.insertValue(1);
    tree.insertValue(2);

    std::cout << "Preorder Traversal: ";
    tree.preorderTraversal(tree.head);
    std::cout << std::endl;
    tree.deleteValue(10);
    std::cout << "Preorder Traversal after deletion: ";
    tree.preorderTraversal(tree.head);
    std::cout << std::endl;
}