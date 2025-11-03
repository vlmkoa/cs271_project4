#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

using namespace std;

template <class Data, class Key>
class BST
{
private:
    struct Node
    {
        Data data;
        Key key;
        Node *left;
        Node *right;
        Node *p;
        Node(const Data &d, const Key &k) : data(d), key(k), left(nullptr), right(nullptr), p(nullptr) {}
        Node(const Data &d, const Key &k, Node *p) : data(d), key(k), left(nullptr), right(nullptr), p(p) {}
    };

    Node *root;

    // helper
    void transplant(Node *u, Node *v);
    void move_to_key(Node *&cur, const Key &k);
    void move_to_min(Node *&cur); // moves a node to min node of the subtree rooted at the node
    void move_to_max(Node *&cur);
    void move_to_successor(Node *&cur);
    void in_order_helper(Node *curr, stringstream &ss, bool &first);
    void clear_subtree(Node *n);
    Node *trim_helper(Node *n, const Key &low, const Key &high, Node *parent);

public:
    BST();
    ~BST();

    bool empty();
    void insert(const Data &d, const Key &k);
    Data get(const Key &k);
    void remove(const Key &k);
    Data max_data();
    Key max_key();
    Data min_data();
    Key min_key();
    Key successor(const Key &k);
    string in_order();
    void trim(const Key &low, const Key &high);
    string to_string();
};

#include "bst.cpp"

#endif