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
    clear_subtree(root);
}

template <class Data, class Key>
bool BST<Data, Key>::empty()
{
    return (!root);
}

/**=====================================================
 *   insert(d,k): this function inserts a Node with
 *   provided data and key values. It initialize the root
 *   of the tree if tree is empty. If tree is not empty
 *   then it compares the value of the provided key to find
 *   the inserting Node's valid parent and whether it is
 *   the left or right child of its parent.
 *
 *   Precondition: Key k is not used in the tree.
 *
 *   Postcondition: Node with Data d and Key k is inserted
 *   to its correct position in the tree.
 *=======================================================*/
template <class Data, class Key>
void BST<Data, Key>::insert(const Data &d, const Key &k)
{
    Node *cur = root;
    Node *p = nullptr; // pointer to track parent of cur
    while (cur != nullptr)
    {
        p = cur; // parent becomes cur before cur moves to its child
        if (cur->key < k)
            cur = cur->right;
        else
            cur = cur->left;
    }
    // if p is null, then cur is null, then root need to be initialized
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

/**=====================================================
 *   get(k): this function returns the Data d of the Node
 *   with provided key if key is valid. If key doesn't
 *   exist in the tree, then return default value of type
 *   Data.
 *
 *   Precondition: None
 *
 *   Postcondition: Data d of Node with provided key
 *   returned if key is valid. If not then return Data's
 *   default value.
 *=======================================================*/
template <class Data, class Key>
Data BST<Data, Key>::get(const Key &k)
{
    Node *cur = root;
    // find node with key
    // while (cur && cur->key != k)
    // {
    //     if (cur->key < k)
    //         cur = cur->right;
    //     else
    //         cur = cur->left;
    // }
    move_to_key(cur, k);
    if (cur == nullptr)
    {
        return Data{}; // return initialized value of type Data if no key match
    }
    return cur->data;
}

/**=====================================================
 *   transplant(u,v): this function lets Node v to become
 *   child of Node u's parent, or the root if u is root
 *
 *   Precondition: Node* u is a valid element in the
 *   tree. If v not null, subtree rooted at v do not
 *   violate BST properties when in u's position.
 *
 *   Postcondition: v in u's position. BST properties
 *   maintained.
 *=======================================================*/
template <class Data, class Key>
void BST<Data, Key>::transplant(Node *u, Node *v)
{
    if (!u->p) // if u is root
    {
        root = v;
    }
    // if u is left child of its parent
    else if (u == u->p->left)
    {
        u->p->left = v; // u's parent left child becomes v
    }
    else
    {
        u->p->right = v; // u's parent right child becomes v
    }
    // if v is not null, then v's parent becomes u's parent
    if (v)
    {
        v->p = u->p;
    }
}
template <class Data, class Key>
void BST<Data, Key>::move_to_key(Node *&cur, const Key &k)
{
    while (cur && cur->key != k)
    {
        if (cur->key < k)
            cur = cur->right;
        else
            cur = cur->left;
    }
}

template <class Data, class Key>
void BST<Data, Key>::move_to_min(Node *&cur)
{
    while (cur != nullptr && cur->left != nullptr)
    {
        cur = cur->left;
    }
}

template <class Data, class Key>
void BST<Data, Key>::move_to_max(Node *&cur)
{
    while (cur != nullptr && cur->right != nullptr)
    {
        cur = cur->right;
    }
}

template <class Data, class Key>
void BST<Data, Key>::move_to_successor(Node *&cur)
{
}

/**=====================================================
 *   remove(k): this function removes Node with Key k
 *   from the tree.
 *
 *   Precondition: None
 *
 *   Postcondition: Node with key k is removed if k is
 *   a valid key, if not then no node removed.
 *=======================================================*/
template <class Data, class Key>
void BST<Data, Key>::remove(const Key &k)
{
    // find node with key
    Node *cur = root;
    // while (cur != nullptr && cur->key != k)
    // {
    //     if (cur->key < k)
    //         cur = cur->right;
    //     else
    //         cur = cur->left;
    // }
    move_to_key(cur, k);
    if (!cur)
    {
        cout << "No node with provided key" << endl;
        return;
    }
    // if cur has one child then its only child's subtree maintains
    // comparative property of cur relative to cur's parent. Transplanting
    // the child using transplant(). If cur has no children, then its spot
    // becomes a nullptr.
    // if (!cur->left && !cur->right && root == cur) {
    // root = nullptr;
    // delete cur;
    //}
    /*else */ if (!cur->left)
    {
        transplant(cur, cur->right); // now right child of cur becomes child of cur's parent
    }
    else if (!cur->right)
    {
        transplant(cur, cur->left); // now left child of cur becomes child of cur's parent
    }
    // if both children present
    else
    {
        // find the children successor of the Node
        Node *suc = cur->right;
        // while (suc->left)
        // {
        //     suc = suc->left;
        // }
        move_to_min(suc);
        if (suc->p != cur)
        {
            transplant(suc, suc->right); // replace suc with suc->right so that its parent can get remaining subtree of suc's children
            // suc then takes right child of cur
            suc->right = cur->right;
            suc->right->p = suc;
        }
        transplant(cur, suc); // cur's parent replace cur with subtree rooted at suc
        // suc takes left child of cur
        suc->left = cur->left;
        suc->left->p = suc;
    }
    delete cur;
}

template <class Data, class Key>
Data BST<Data, Key>::max_data()
{
    if (!root)
        return Data{};
    Node *cur = root;
    move_to_max(cur);
    return cur->data;
}

template <class Data, class Key>
Key BST<Data, Key>::max_key()
{
    if (!root)
        return Key{};
    Node *cur = root;
    move_to_max(cur);
    return cur->key;
}

template <class Data, class Key>
Data BST<Data, Key>::min_data()
{
    if (!root)
        return Data{};
    Node *cur = root;
    move_to_min(cur);
    return cur->data;
}

template <class Data, class Key>
Key BST<Data, Key>::min_key()
{
    if (!root)
        return Key{};
    Node *cur = root;
    move_to_min(cur);
    return cur->key;
}

template <class Data, class Key>
Key BST<Data, Key>::successor(const Key &k)
{
    Node *cur = root;
    move_to_key(cur, k);
    if (!cur)
    {
        cout << "Invalid key" << endl;
        return Key{};
    }
    Node *suc = cur->right;
    if (suc)
    {
        move_to_min(suc);
        return suc->key;
    }
    suc = cur->p;
    while ((suc) && (cur == suc->right))
    {
        cur = suc;
        suc = suc->p;
    }
    if (!suc)
        return Key{};
    return suc->key;
}

template <class Data, class Key>
string BST<Data, Key>::in_order()
{
    stringstream ss;
    bool first = true;
    in_order_helper(root, ss, first);
    return ss.str();
}

template <class Data, class Key>
void BST<Data, Key>::in_order_helper(Node *curr, stringstream &ss, bool &first)
{
    if (curr == nullptr)
        return;

    in_order_helper(curr->left, ss, first);
    if (!first)
        ss << " ";
    ss << curr->key;
    first = false;
    in_order_helper(curr->right, ss, first);
}

template <class Data, class Key>
void BST<Data, Key>::clear_subtree(Node *n)
{
    if (!n)
        return;
    clear_subtree(n->left);
    clear_subtree(n->right);
    delete n;
}

template <class Data, class Key>
void BST<Data, Key>::trim(const Key &low, const Key &high)
{
    root = trim_helper(root, low, high, nullptr);
}

template <class Data, class Key>
typename BST<Data, Key>::Node *BST<Data, Key>::trim_helper(Node *n, const Key &low, const Key &high, Node *parent)
{
    if (!n)
        return nullptr;

    // Trim children first (post-order)
    n->left = trim_helper(n->left, low, high, n);
    n->right = trim_helper(n->right, low, high, n);

    // Now decide about n
    if (n->key < low)
    {
        Node *r = n->right; // nodes to keep from this subtree
        // unlink and delete current node
        n->left = nullptr;
        n->right = nullptr;
        n->p = nullptr;
        delete n;
        if (r)
            r->p = parent;
        return r;
    }

    if (n->key > high)
    {
        Node *l = n->left;
        n->left = nullptr;
        n->right = nullptr;
        n->p = nullptr;
        delete n;
        if (l)
            l->p = parent;
        return l;
    }

    // n is within [low, high] — keep it
    n->p = parent;
    return n;
}

/**=====================================================
 *   to_string(): this function returns the string
 *   of keys in the tree. Each node in i-th layer is added
 *   to the stringstream after all nodes in i-1 th layer added,
 *   from left to right order.
 *
 *   Precondition: None
 *
 *   Postcondition: A string of keys in left-right,
 *   top down order
 *=======================================================*/
template <class Data, class Key>
string BST<Data, Key>::to_string()
{
    stringstream ss;
    queue<Node *> q;
    if (root)
        q.push(root);
    bool skip = true; // bool for skipping first space

    // while loop adds the queue's head Node's key to the string stream,
    // removes the head from queue, then adds its child(ren) to the tail of queue.
    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();
        if (!skip)
        {
            ss << " ";
        }
        skip = false; // skipped once

        ss << cur->key;
        if (cur->left)
            q.push(cur->left);
        if (cur->right)
            q.push(cur->right);
    }
    return ss.str();
}
