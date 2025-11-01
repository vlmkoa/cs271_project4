#include "bst.h"
#include <iostream>

using namespace std;

template <class Data, class Key>
BST<Data, Key>::BST()
{
    root = nullptr;
}

template <class Data, class Key>
BST<Data, Key>::~BST()
{
}

template <class Data, class Key>
bool BST<Data, Key>::empty()
{
    return (root == nullptr);
}

template <class Data, class Key>
void BST<Data, Key>::insert(const Data &d, const Key &k)
{
    if (empty())
    {
        root = new Node *(d, k);
        return;
    }

    Node *cur = root;
    while (cur != nullptr)
    {
        if (cur->key < k)
            cur = cur->right;
        else
            cur = cur->left;
    }
    cur = new Node(d, k);
}

template <class Data, class Key>
Data BST<Data, Key>::get(const Key &k)
{
    Node *cur = root;
    while (cur != nullptr && cur->key != k)
    {
        if (cur->key < k)
            cur = cur->right;
        else
            cur = cur->left;
    }
    if (cur == nullptr)
    {
        return Data{};
    }
    return cur->key;
}

template <class Data, class Key>
void BST<Data, Key>::remove(const Key &k)
{
}