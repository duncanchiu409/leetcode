#include <iostream>
#include <functional>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

template <typename T>
class BinarySearchTreeNode
{
public:
    T value;
    BinarySearchTreeNode<T> *left;
    BinarySearchTreeNode<T> *right;

    BinarySearchTreeNode(T);
    ~BinarySearchTreeNode();
};

template <typename T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(T value)
{
    this->value = value;
    this->left = NULL;
    this->right = NULL;
}

template <typename T>
BinarySearchTreeNode<T>::~BinarySearchTreeNode()
{
}

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTreeNode<T> *root;

    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTreeNode<T> *insertValue(BinarySearchTreeNode<T> *, T);
    BinarySearchTreeNode<T> *searchValue(BinarySearchTreeNode<T> *, T);
    BinarySearchTreeNode<T> *deleteValue(BinarySearchTreeNode<T> *, T);
    BinarySearchTreeNode<T> *getInorderSuccessor(BinarySearchTreeNode<T> *);
    void storeInorderTreeNodes(BinarySearchTreeNode<T> *, std::vector<T> &);
    BinarySearchTreeNode<T> *buildBalancedBinarySearchTree(std::vector<T> &, int, int);
    BinarySearchTreeNode<T> *balanceBST(BinarySearchTreeNode<T> *);

    void preorderTraversal(BinarySearchTreeNode<T> *);
    void inorderTraversal(BinarySearchTreeNode<T> *);
    void postorderTraversal(BinarySearchTreeNode<T> *);
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
    this->root = NULL;
}

template <typename T>
BinarySearchTreeNode<T> *BinarySearchTree<T>::insertValue(BinarySearchTreeNode<T> *node, T value)
{
    if (node == NULL)
        return new BinarySearchTreeNode<T>(value);
    if (value < node->value)
        node->left = this->insertValue(node->left, value);
    else if (value > node->value)
        node->right = this->insertValue(node->right, value);
    return node;
}

template <typename T>
BinarySearchTreeNode<T> *BinarySearchTree<T>::searchValue(BinarySearchTreeNode<T> *node, T value)
{
    if (node == NULL)
        return NULL;
    if (node->value == value)
        return node;
    if (node->value < value)
        return this->searchValue(node->right, value);
    if (node->value > value)
        return this->searchValue(node->left, value);
}

template <typename T>
BinarySearchTreeNode<T> *BinarySearchTree<T>::deleteValue(BinarySearchTreeNode<T> *node, T value)
{
    if (node == NULL)
        return node;
    if (node->value > value)
        node->left = this->deleteValue(node->left, value);
    else if (node->value < value)
        node->right = this->deleteValue(node->right, value);
    else
    {
        if (node->left == NULL)
        {
            BinarySearchTreeNode<T> *temp = node->right;
            delete node;
            return temp;
        }

        if (node->right == NULL)
        {
            BinarySearchTreeNode<T> *temp = node->left;
            delete node;
            return temp;
        }

        BinarySearchTreeNode<T> *inorderPresuccessor = this->getInorderSuccessor(node);
        node->value = inorderPresuccessor->value;
        node->right = this->deleteValue(node->right, inorderPresuccessor->value);
    }
    return node;
}

template <typename T>
BinarySearchTreeNode<T> *BinarySearchTree<T>::getInorderSuccessor(BinarySearchTreeNode<T> *node)
{
    node = node->right;
    while (node != NULL && node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

template <typename T>
void BinarySearchTree<T>::storeInorderTreeNodes(BinarySearchTreeNode<T> *node, std::vector<T> &nodes)
{
    if (node == NULL)
        return;
    this->storeInorderTreeNodes(node->left, nodes);
    nodes.push_back(node->value);
    this->storeInorderTreeNodes(node->right, nodes);
}

template <typename T>
BinarySearchTreeNode<T> *BinarySearchTree<T>::buildBalancedBinarySearchTree(std::vector<T> &nodes, int left, int right)
{
    if (left > right)
        return NULL;
    int middle = (right + left) / 2;
    BinarySearchTreeNode<T> *new_node = new BinarySearchTreeNode<T>(nodes[middle]);
    new_node->left = this->buildBalancedBinarySearchTree(nodes, left, middle - 1);
    new_node->right = this->buildBalancedBinarySearchTree(nodes, middle + 1, right);
    return new_node;
}

template <typename T>
BinarySearchTreeNode<T> *BinarySearchTree<T>::balanceBST(BinarySearchTreeNode<T> *node)
{
    std::vector<T> store;
    this->storeInorderTreeNodes(node, store);
    return buildBalancedBinarySearchTree(store, 0, store.size() - 1);
}

template <typename T>
void BinarySearchTree<T>::preorderTraversal(BinarySearchTreeNode<T> *node)
{
    if (node == NULL)
        return;
    std::cout << node->value << " ";
    this->preorderTraversal(node->left);
    this->preorderTraversal(node->right);
}

template <typename T>
void BinarySearchTree<T>::inorderTraversal(BinarySearchTreeNode<T> *node)
{
    if (node == NULL)
        return;
    this->inorderTraversal(node->left);
    std::cout << node->value << " ";
    this->inorderTraversal(node->right);
}

template <typename T>
void BinarySearchTree<T>::postorderTraversal(BinarySearchTreeNode<T> *node)
{
    if (node == NULL)
    {
        return;
    }
    this->postorderTraversal(node->left);
    this->postorderTraversal(node->right);
    std::cout << node->value << " ";
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    // Helper function to recursively delete nodes
    std::function<void(BinarySearchTreeNode<T> *)> deleteTree = [&](BinarySearchTreeNode<T> *node)
    {
        if (node == NULL)
            return;

        // Delete left and right subtrees first
        deleteTree(node->left);
        deleteTree(node->right);

        // Then delete the current node
        delete node;
    };

    // Start deletion from root
    deleteTree(root);
}

TEST_CASE("TEST BinarySearchTree::insertValue CASE 01")
{
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    bst->root = bst->insertValue(bst->root, 50);
    bst->root = bst->insertValue(bst->root, 30);
    bst->root = bst->insertValue(bst->root, 20);

    // bst->inorderTraversal(bst->root);

    CHECK(30 == bst->root->left->value);
    CHECK(20 == bst->root->left->left->value);
    CHECK(50 == bst->root->value);
}

TEST_CASE("TEST BinarySearchTree::searchValue CASE 02")
{
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    bst->root = bst->insertValue(bst->root, 50);
    bst->root = bst->insertValue(bst->root, 30);
    bst->root = bst->insertValue(bst->root, 20);
    bst->root = bst->insertValue(bst->root, 40);
    bst->root = bst->insertValue(bst->root, 60);
    bst->root = bst->insertValue(bst->root, 70);

    // bst->inorderTraversal(bst->root);

    BinarySearchTreeNode<int> *node_1 = bst->searchValue(bst->root, 19);
    BinarySearchTreeNode<int> *node_2 = bst->searchValue(bst->root, 30);
    CHECK(node_1 == NULL);
    CHECK(node_2->value == 30);
}

TEST_CASE("TEST BinarySearchTree::balanceBST CASE 03")
{
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    bst->root = bst->insertValue(bst->root, 50);
    bst->root = bst->insertValue(bst->root, 30);
    bst->root = bst->insertValue(bst->root, 20);
    bst->root = bst->insertValue(bst->root, 40);
    bst->root = bst->insertValue(bst->root, 60);
    bst->root = bst->insertValue(bst->root, 70);
    bst->inorderTraversal(bst->root);
    std::cout << std::endl;
    bst->root = bst->balanceBST(bst->root);
    bst->inorderTraversal(bst->root);
}