#ifndef BST_H
#define BST_H

#include <iostream>

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
    };

    Node *root;
    int size;

public:
    BST();
    ~BST();

    bool empty();
    void insert(const Data &d, const Key &key);
    Data get(const Key &Key);
    void remove(const Key &key);
    Data max_data();
    Key max_key();
    Data min_data();
    Key min_key();
    Key successor(const Key &key);
    string in_order();
    void trim(const Key &low, const Key &high);
};

#endif