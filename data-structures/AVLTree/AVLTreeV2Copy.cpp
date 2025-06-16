#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

template <typename T>
class Node
{
public:
    T value;
    Node<T> *left;
    Node<T> *right;
    int height;

    Node(T value)
    {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }
};

template <typename T>
class AVLTree
{
private:
    Node<T> *leftRotate(Node<T> *node);
    Node<T> *rightRotate(Node<T> *node);
    Node<T> *getInorderSuccessor(Node<T> *);

public:
    Node<T> *root;

    AVLTree();
    // ~AVLTree();

    void preorderTraversal(Node<T> *);
    void inorderTraversal(Node<T> *);
    void postorderTraversal(Node<T> *);

    Node<T> *insertValue(Node<T> *, T);
    Node<T> *deleteValue(Node<T> *, T);
};

template <typename T>
AVLTree<T>::AVLTree()
{
    this->root = NULL;
}

template <typename T>
void AVLTree<T>::preorderTraversal(Node<T> *node)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        std::cout << node->value << " ";
        this->preorderTraversal(node->left);
        this->preorderTraversal(node->right);
    }
}

template <typename T>
void AVLTree<T>::inorderTraversal(Node<T> *node)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        this->inorderTraversal(node->left);
        std::cout << node->value << " ";
        this->inorderTraversal(node->right);
    }
}

template <typename T>
void AVLTree<T>::postorderTraversal(Node<T> *node)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        this->postorderTraversal(node->left);
        this->postorderTraversal(node->right);
        std::cout << node->value << " ";
    }
}

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
Node<T> *AVLTree<T>::leftRotate(Node<T> *y)
{
    Node<T> *x = y->right;
    Node<T> *T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));

    return x;
}

template <typename T>
Node<T> *AVLTree<T>::rightRotate(Node<T> *y)
{
    Node<T> *x = y->left;
    Node<T> *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));

    return x;
}

template <typename T>
Node<T> *AVLTree<T>::insertValue(Node<T> *node, T value)
{
    if (node == NULL)
    {
        return new Node<T>(value);
    }
    else
    {
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
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balanceFactor = height(node->left) - height(node->right);

    // Left
    if (balanceFactor > 1)
    {
        // Right
        if (node->left->value < value)
        {
            node->left = this->leftRotate(node->left);
        }
        return this->rightRotate(node);
    }

    // Right
    if (balanceFactor < -1)
    {
        // Left
        if (node->right->value > value)
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
    node = node->right;
    while (node == NULL)
    {
        node = node->left;
    }
    return node;
}

template <typename T>
Node<T> *AVLTree<T>::deleteValue(Node<T> *node, T value)
{
    if (node == NULL)
    {
        return NULL;
    }
    else if (node->value > value)
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
            node = temp;
        }
        else if (node->right == NULL)
        {
            Node<T> *temp = node->left;
            delete node;
            node = temp;
        }
        else
        {
            Node<T> *temp = this->getInorderSuccessor(node);
            node->value = temp->value;
            node->right = this->deleteValue(node->right, node->value);
        }
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balanceFactor = height(node->left) - height(node->right);

    // Left
    if (balanceFactor > 1)
    {
        // Right
        if (height(node->left->left) - height(node->left->right) < -1)
        {
            node->left = this->leftRotate(node->left);
        }
        node = this->rightRotate(node);
    }

    // Right
    if (balanceFactor < -1)
    {
        // Left
        if (height(node->right->left) - height(node->right->right) > 1)
        {
            node->right = this->rightRotate(node->right);
        }
        node = this->leftRotate(node);
    }

    return node;
}

TEST_CASE("AVLTree insertValue TEST CASE 01")
{
    AVLTree<int> tree;
    tree.root = tree.insertValue(tree.root, 10);
    tree.root = tree.insertValue(tree.root, 20);
    tree.root = tree.insertValue(tree.root, 30);
    tree.root = tree.insertValue(tree.root, 40);
    tree.root = tree.insertValue(tree.root, 50);
    tree.root = tree.insertValue(tree.root, 25);

    tree.preorderTraversal(tree.root);
    std::cout << std::endl;
    tree.inorderTraversal(tree.root);
}

TEST_CASE("AVL Tree Deletion TEST CASE 01")
{
    AVLTree<int> tree;
    tree.root = tree.insertValue(tree.root, 9);
    tree.root = tree.insertValue(tree.root, 5);
    tree.root = tree.insertValue(tree.root, 10);
    tree.root = tree.insertValue(tree.root, 0);
    tree.root = tree.insertValue(tree.root, 6);
    tree.root = tree.insertValue(tree.root, 11);
    tree.root = tree.insertValue(tree.root, -1);
    tree.root = tree.insertValue(tree.root, 1);
    tree.root = tree.insertValue(tree.root, 2);

    std::cout << std::endl;
    std::cout << "Preorder Traversal: ";
    tree.preorderTraversal(tree.root);
    std::cout << std::endl;
    tree.root = tree.deleteValue(tree.root, 10);
    std::cout << "Preorder Traversal after deletion: ";
    tree.preorderTraversal(tree.root);
    std::cout << std::endl;
}