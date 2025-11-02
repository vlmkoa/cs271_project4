#include "bst.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <queue>

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
    Node *cur = root;
    Node *p = nullptr;
    while (cur != nullptr)
    {
        p = cur;
        if (cur->key < k)
            cur = cur->right;
        else
            cur = cur->left;
    }
    if (!p)
    {
        root = new Node(d, k);
    }
    else if (k < p->key)
    {
        p->left = new Node(d, k, p);
    }
    else
    {
        p->right = new Node(d, k, p);
    }
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
    return cur->data;
}
template <class Data, class Key>
void BST<Data, Key>::transplant(Node *u, Node *v)
{
    if (!u->p)
    {
        root = v;
    }
    else if (u == u->p->left)
    {
        u->p->left = v;
    }
    else
    {
        u->p->right = v;
    }
    if (v)
    {
        v->p = u->p;
    }
}

template <class Data, class Key>
void BST<Data, Key>::remove(const Key &k)
{
    Node *cur = root;
    while (cur != nullptr && cur->key != k)
    {
        if (cur->key < k)
            cur = cur->right;
        else
            cur = cur->left;
    }
    if (!cur)
    {
        cout << "No node with provided key" << endl;
        return;
    }
    if (!cur->left)
    {
        transplant(cur, cur->right);
    }
    else if (!cur->right)
    {
        transplant(cur, cur->left);
    }
    else
    {
        Node *suc = cur->right;
        while (suc->left)
        {
            suc = suc->left;
        }
        if (suc->p != cur)
        {
            transplant(suc, suc->right);
            suc->right = cur->right;
            suc->right->p = suc;
        }
        transplant(cur, suc);
        suc->left = cur->left;
        suc->left->p = suc;
    }
    delete cur;
}

template <class Data, class Key>
string BST<Data, Key>::to_string()
{
    stringstream ss;
    queue<Node *> q;
    if (root)
        q.push(root);
    bool doOnce = false;
    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();
        if (doOnce)
            ss << " ";
        ss << cur->key;
        if (cur->left)
            q.push(cur->left);
        if (cur->right)
            q.push(cur->right);
        doOnce = true;
    }
    return ss.str();
}