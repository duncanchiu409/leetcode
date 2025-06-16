#include <iostream>
#include <vector>
#include <functional>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

template <typename T>
class Node
{
public:
    T value;
    Node<T> *left;
    Node<T> *right;

    Node<T>(T value)
    {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }
};

template <typename T>
class BST
{
private:
    Node<T> *insertValue(Node<T> *, T);
    Node<T> *searchValue(Node<T> *, T);
    Node<T> *getInorderSuccessor(Node<T> *);
    Node<T> *deleteValue(Node<T> *, T);

public:
    void inorderStoreItems(Node<T> *, std::vector<T> &);
    Node<T> *rebuildBST(std::vector<T>, int, int);
    Node<T> *root;

    BST<T>();
    void insertNode(T);
    Node<T> *searchNode(T);
    void deleteNode(T);
    void rebalanceTree();
    ~BST<T>();

    void inorderTraversal(Node<T> *);
};

template <typename T>
BST<T>::BST()
{
    this->root = NULL;
}

template <typename T>
Node<T> *BST<T>::insertValue(Node<T> *node, T value)
{
    if (node == NULL)
        return new Node<T>(value);
    if (node->value < value)
        node->right = this->insertValue(node->right, value);
    else if (node->value > value)
        node->left = this->insertValue(node->left, value);
    return node;
}

template <typename T>
void BST<T>::insertNode(T value)
{
    this->root = this->insertValue(this->root, value);
}

template <typename T>
Node<T> *BST<T>::searchValue(Node<T> *node, T value)
{
    if (node == NULL)
        return NULL;
    if (node->value == value)
        return node;
    else if (node->value < value)
        return this->searchValue(node->right, value);
    else
        return this->searchValue(node->left, value);
}

template <typename T>
Node<T> *BST<T>::searchNode(T value)
{
    return this->searchValue(this->root, value);
}

template <typename T>
Node<T> *BST<T>::getInorderSuccessor(Node<T> *node)
{
    node = node->right;
    while (node != NULL && node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

template <typename T>
Node<T> *BST<T>::deleteValue(Node<T> *node, T value)
{
    if (node == NULL)
        return node;
    if (node->value < value)
        node->right = this->deleteValue(node->right, value);
    else if (node->value > value)
        node->left = this->deleteValue(node->left, value);
    else
    {
        if (node->right == NULL)
        {
            Node<T> *temp = node->left;
            delete node;
            return temp;
        }

        if (node->left == NULL)
        {
            Node<T> *temp = node->right;
            delete node;
            return temp;
        }

        Node<T> *temp = this->getInorderSuccessor(node);
        node->value = temp->value;
        node->right = this->deleteValue(node->right, temp->value);
    }
    return node;
}

template <typename T>
void BST<T>::deleteNode(T value)
{
    this->root = this->deleteValue(this->root, value);
}

template <typename T>
void BST<T>::inorderStoreItems(Node<T> *node, std::vector<T> &store)
{
    if (node == NULL)
        return;
    this->inorderStoreItems(node->left, store);
    store.push_back(node->value);
    this->inorderStoreItems(node->right, store);
}

template <typename T>
Node<T> *BST<T>::rebuildBST(std::vector<T> store, int left, int right)
{
    if (left > right)
        return NULL;
    int middle = (left + right) / 2;
    Node<T> *temp = new Node<T>(store[middle]);
    temp->left = this->rebuildBST(store, left, middle - 1);
    temp->right = this->rebuildBST(store, middle + 1, right);
    return temp;
}

template <typename T>
void BST<T>::rebalanceTree()
{
    std::vector<T> result;
    this->inorderStoreItems(this->root, result);
    this->root = this->rebuildBST(result, 0, result.size() - 1);
}

template <typename T>
void BST<T>::inorderTraversal(Node<T> *node)
{
    if (node == NULL)
        return;
    this->inorderTraversal(node->left);
    std::cout << node->value << " ";
    this->inorderTraversal(node->right);
}

template <typename T>
void deleteTree(Node<T> *node)
{
    if (node == NULL)
        return;

    if (node->left)
        deleteTree(node->left);
    if (node->right)
        deleteTree(node->right);

    delete node;
}

template <typename T>
BST<T>::~BST()
{
    deleteTree(this->root);
}

TEST_CASE("Test BST::insertNode")
{
    BST<int> bst;
    bst.insertNode(50);
    bst.insertNode(30);
    bst.insertNode(70);
    bst.insertNode(20);
    bst.insertNode(40);

    REQUIRE(bst.root != NULL);
    CHECK_EQ(bst.root->value, 50);
    CHECK_EQ(bst.root->left->value, 30);
    CHECK_EQ(bst.root->right->value, 70);
    CHECK_EQ(bst.root->left->left->value, 20);
    CHECK_EQ(bst.root->left->right->value, 40);

    std::cout << "Inorder traversal after insertion: ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;
}

TEST_CASE("Test BST::searchNode")
{
    BST<int> bst;
    bst.insertNode(50);
    bst.insertNode(30);
    bst.insertNode(70);
    bst.insertNode(20);
    bst.insertNode(40);

    Node<int> *found = bst.searchNode(30);
    REQUIRE(found != NULL);
    CHECK_EQ(found->value, 30);

    bool isNull = (bst.searchNode(100) == NULL);
    CHECK(isNull);

    std::cout << "Inorder traversal after search: ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;
}

TEST_CASE("Test BST::deleteNode")
{
    BST<int> bst;
    bst.insertNode(50);
    bst.insertNode(30);
    bst.insertNode(70);
    bst.insertNode(20);
    bst.insertNode(40);
    bst.insertNode(60);
    bst.insertNode(80);

    bst.deleteNode(20);
    bool isDeleted = (bst.searchNode(20) == NULL);
    CHECK(isDeleted);

    std::cout << "Inorder traversal after deleting leaf node (20): ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;

    bst.deleteNode(60);
    isDeleted = (bst.searchNode(60) == NULL);
    CHECK(isDeleted);

    std::cout << "Inorder traversal after deleting node with one child (60): ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;

    bst.deleteNode(30);
    isDeleted = (bst.searchNode(30) == NULL);
    CHECK(isDeleted);

    std::cout << "Inorder traversal after deleting node with two children (30): ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;

    bst.deleteNode(50);
    isDeleted = (bst.searchNode(50) == NULL);
    CHECK(isDeleted);

    std::cout << "Inorder traversal after deleting root (50): ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;
}

TEST_CASE("Test BST::rebalanceTree")
{
    BST<int> bst;
    bst.insertNode(10);
    bst.insertNode(20);
    bst.insertNode(30);
    bst.insertNode(40);
    bst.insertNode(50);

    std::cout << "Inorder traversal before rebalancing: ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;

    bst.rebalanceTree();

    bool rootIsMiddleValue = (bst.root->value == 30 || bst.root->value == 20 || bst.root->value == 40);
    CHECK(rootIsMiddleValue);

    std::cout << "Inorder traversal after rebalancing: ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;
}

TEST_CASE("Test BST with empty tree")
{
    BST<int> bst;

    bool isRootNull = (bst.root == NULL);
    CHECK(isRootNull);

    bool isSearchNull = (bst.searchNode(10) == NULL);
    CHECK(isSearchNull);

    bst.deleteNode(10);
    isRootNull = (bst.root == NULL);
    CHECK(isRootNull);

    bst.rebalanceTree();
    isRootNull = (bst.root == NULL);
    CHECK(isRootNull);

    std::cout << "Inorder traversal of empty tree: ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;
}

TEST_CASE("Test BST with duplicate values")
{
    BST<int> bst;
    bst.insertNode(50);
    bst.insertNode(30);
    bst.insertNode(30);
    bst.insertNode(20);

    REQUIRE(bst.root != NULL);
    CHECK_EQ(bst.root->value, 50);
    REQUIRE(bst.root->left != NULL);
    CHECK_EQ(bst.root->left->value, 30);
    REQUIRE(bst.root->left->left != NULL);
    CHECK_EQ(bst.root->left->left->value, 20);

    std::cout << "Inorder traversal with duplicates: ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;
}

TEST_CASE("Test BST with different data types")
{
    BST<double> doubleBst;
    doubleBst.insertNode(50.5);
    doubleBst.insertNode(30.5);
    doubleBst.insertNode(70.5);

    REQUIRE(doubleBst.root != NULL);
    CHECK_EQ(doubleBst.root->value, 50.5);
    REQUIRE(doubleBst.root->left != NULL);
    CHECK_EQ(doubleBst.root->left->value, 30.5);
    REQUIRE(doubleBst.root->right != NULL);
    CHECK_EQ(doubleBst.root->right->value, 70.5);

    std::cout << "Inorder traversal of double BST: ";
    doubleBst.inorderTraversal(doubleBst.root);
    std::cout << std::endl;

    BST<char> charBst;
    charBst.insertNode('M');
    charBst.insertNode('G');
    charBst.insertNode('T');

    REQUIRE(charBst.root != NULL);
    CHECK_EQ(charBst.root->value, 'M');
    REQUIRE(charBst.root->left != NULL);
    CHECK_EQ(charBst.root->left->value, 'G');
    REQUIRE(charBst.root->right != NULL);
    CHECK_EQ(charBst.root->right->value, 'T');

    std::cout << "Inorder traversal of char BST: ";
    charBst.inorderTraversal(charBst.root);
    std::cout << std::endl;
}

TEST_CASE("Test BST::inorderStoreItems")
{
    BST<int> bst;
    bst.insertNode(50);
    bst.insertNode(30);
    bst.insertNode(70);
    bst.insertNode(20);
    bst.insertNode(40);

    std::vector<int> items;
    bst.inorderStoreItems(bst.root, items);

    REQUIRE(items.size() == 5);
    CHECK_EQ(items[0], 20);
    CHECK_EQ(items[1], 30);
    CHECK_EQ(items[2], 40);
    CHECK_EQ(items[3], 50);
    CHECK_EQ(items[4], 70);

    std::cout << "Inorder traversal after storing items: ";
    bst.inorderTraversal(bst.root);
    std::cout << std::endl;
}
