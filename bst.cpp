#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <queue>

using namespace std;

/**=====================================================
 *   BST(): Constructor that creates an empty binary
 *   search tree by initializing root to nullptr.
 *
 *   Precondition: None
 *
 *   Postcondition: Empty BST created with root = nullptr
 *=======================================================*/
template <class Data, class Key>
BST<Data, Key>::BST()
{
    root = nullptr;
}

/**=====================================================
 *   ~BST(): Destructor that deallocates all nodes in
 *   the tree by calling clear_subtree on the root.
 *
 *   Precondition: None
 *
 *   Postcondition: All nodes in the tree are deleted
 *   and memory is freed.
 *=======================================================*/
template <class Data, class Key>
BST<Data, Key>::~BST()
{
    clear_subtree(root);
}

/**=====================================================
 *   empty(): Checks whether the binary search tree
 *   is empty by testing if root is nullptr.
 *
 *   Precondition: None
 *
 *   Postcondition: Returns true if tree is empty
 *   (root == nullptr), false otherwise.
 *=======================================================*/
template <class Data, class Key>
bool BST<Data, Key>::empty()
{
    return (!root);
}

/**=====================================================
 *   insert(d,k): this function inserts a Node with
 *   provided data and key values. It initializes the root
 *   of the tree if tree is empty. If tree is not empty
 *   then it compares the value of the provided key to find
 *   the inserting Node's valid parent and whether it is
 *   the left or right child of its parent.
 *
 *   Precondition: None
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
        if (k < cur->key)
        {
            cur = cur->left;
        }
        else // k >= cur->key (allows duplicate keys to go right)
        {
            cur = cur->right;
        }
    }
    // if p is null, then cur is null, so root needs to be initialized
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
/**=====================================================
 *   move_to_key(cur, k): Helper function that moves
 *   the current pointer to the node with key k in the
 *   tree, or to nullptr if key not found.
 *
 *   Precondition: cur is a valid pointer (possibly nullptr)
 *
 *   Postcondition: cur points to the node with key k,
 *   or nullptr if no such node exists.
 *=======================================================*/
template <class Data, class Key>
void BST<Data, Key>::move_to_key(Node *&cur, const Key &k)
{
    while (cur && cur->key != k)
    {
        if (k < cur->key)
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }
}

/**=====================================================
 *   move_to_min(cur): Helper function that moves
 *   the current pointer to the node with minimum key
 *   in the subtree rooted at cur.
 *
 *   Precondition: cur is a valid pointer (possibly nullptr)
 *
 *   Postcondition: cur points to the leftmost node
 *   (minimum key) in the subtree, or remains nullptr
 *   if cur was nullptr.
 *=======================================================*/
template <class Data, class Key>
void BST<Data, Key>::move_to_min(Node *&cur)
{
    while (cur != nullptr && cur->left != nullptr)
    {
        cur = cur->left;
    }
}

/**=====================================================
 *   move_to_max(cur): Helper function that moves
 *   the current pointer to the node with maximum key
 *   in the subtree rooted at cur.
 *
 *   Precondition: cur is a valid pointer (possibly nullptr)
 *
 *   Postcondition: cur points to the rightmost node
 *   (maximum key) in the subtree, or remains nullptr
 *   if cur was nullptr.
 *=======================================================*/
template <class Data, class Key>
void BST<Data, Key>::move_to_max(Node *&cur)
{
    while (cur != nullptr && cur->right != nullptr)
    {
        cur = cur->right;
    }
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
    move_to_key(cur, k);
    if (!cur)
    {
        cout << "No node with provided key" << endl;
        return;
    }
    // if cur has >two children, move child's subtree to cur
    if (!cur->left)
    {
        transplant(cur, cur->right);
    }
    else if (!cur->right)
    {
        transplant(cur, cur->left);
    }
    // if both children present
    else
    {
        // find the children successor of the Node
        Node *suc = cur->right;
        move_to_min(suc);
        if (suc->p != cur)
        {
            transplant(suc, suc->right); // replace suc with subtree rooted at suc->right
            suc->right = cur->right;
            suc->right->p = suc;
        }
        transplant(cur, suc); // cur's parent replace cur with subtree rooted at suc
        suc->left = cur->left;
        suc->left->p = suc;
    }
    delete cur;
}

/**=====================================================
 *   max_data(): Returns the data associated with the
 *   maximum key in the tree. Returns default Data value
 *   if tree is empty.
 *
 *   Precondition: None
 *
 *   Postcondition: Returns the data of the node with
 *   the maximum key, or Data{} if tree is empty.
 *=======================================================*/
template <class Data, class Key>
Data BST<Data, Key>::max_data()
{
    if (!root)
        return Data{};
    Node *cur = root;
    move_to_max(cur);
    return cur->data;
}

/**=====================================================
 *   max_key(): Returns the maximum key in the tree.
 *   Returns default Key value if tree is empty.
 *
 *   Precondition: None
 *
 *   Postcondition: Returns the maximum key in the tree,
 *   or Key{} if tree is empty.
 *=======================================================*/
template <class Data, class Key>
Key BST<Data, Key>::max_key()
{
    if (!root)
        return Key{};
    Node *cur = root;
    move_to_max(cur);
    return cur->key;
}

/**=====================================================
 *   min_data(): Returns the data associated with the
 *   minimum key in the tree. Returns default Data value
 *   if tree is empty.
 *
 *   Precondition: None
 *
 *   Postcondition: Returns the data of the node with
 *   the minimum key, or Data{} if tree is empty.
 *=======================================================*/
template <class Data, class Key>
Data BST<Data, Key>::min_data()
{
    if (!root)
        return Data{};
    Node *cur = root;
    move_to_min(cur);
    return cur->data;
}

/**=====================================================
 *   min_key(): Returns the minimum key in the tree.
 *   Returns default Key value if tree is empty.
 *
 *   Precondition: None
 *
 *   Postcondition: Returns the minimum key in the tree,
 *   or Key{} if tree is empty.
 *=======================================================*/
template <class Data, class Key>
Key BST<Data, Key>::min_key()
{
    if (!root)
        return Key{};
    Node *cur = root;
    move_to_min(cur);
    return cur->key;
}

/**=====================================================
 *   successor(k): Returns the successor key for the
 *   given key k. The successor is the smallest key that
 *   is larger than k. Returns Key{} if k is not in tree
 *   or if k has no successor.
 *
 *   Precondition: None
 *
 *   Postcondition: Returns the successor key if k exists
 *   in tree and has a successor. Returns Key{} otherwise.
 *=======================================================*/
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

/**=====================================================
 *   in_order(): Returns a string representation of
 *   all keys in the tree in ascending order, separated
 *   by single spaces.
 *
 *   Precondition: None
 *
 *   Postcondition: Returns a string with keys in
 *   ascending order, space-separated.
 *=======================================================*/
template <class Data, class Key>
string BST<Data, Key>::in_order()
{
    stringstream ss;
    bool first = true;
    in_order_helper(root, ss, first);
    return ss.str();
}

/**=====================================================
 *   in_order_helper(curr, ss, first): Helper function
 *   for in_order() that performs recursive in-order
 *   traversal and builds the string of keys.
 *
 *   Precondition: ss is a valid stringstream, first
 *   indicates if this is the first key being added.
 *
 *   Postcondition: Keys from subtree rooted at curr
 *   are added to ss in ascending order.
 *=======================================================*/
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

/**=====================================================
 *   clear_subtree(n): Helper function that recursively
 *   deletes all nodes in the subtree rooted at n.
 *
 *   Precondition: n is a valid pointer (possibly nullptr)
 *
 *   Postcondition: All nodes in subtree rooted at n
 *   are deleted and memory is freed.
 *=======================================================*/
template <class Data, class Key>
void BST<Data, Key>::clear_subtree(Node *n)
{
    if (!n)
        return;
    clear_subtree(n->left);
    clear_subtree(n->right);
    delete n;
}

/**=====================================================
 *   trim(low, high): Removes all nodes from the tree
 *   whose keys are outside the interval [low, high].
 *   Preserves the relative structure of remaining nodes.
 *
 *   Precondition: low <= high
 *
 *   Postcondition: Only nodes with keys in [low, high]
 *   remain in the tree. The relative parent-child
 *   relationships are preserved.
 *=======================================================*/
template <class Data, class Key>
void BST<Data, Key>::trim(const Key &low, const Key &high)
{
    root = trim_helper(root, low, high, nullptr);
}

/**=====================================================
 *   trim_helper(n, low, high, parent): Helper function
 *   that recursively trims the subtree rooted at n to
 *   remove nodes outside [low, high] interval.
 *
 *   Precondition: low <= high, parent is the parent of n
 *
 *   Postcondition: Returns pointer to the root of the
 *   trimmed subtree. Nodes outside [low, high] are deleted.
 *   If n->key < low, return right subtree. If n->key > high,
 *   return left subtree. Otherwise return n with trimmed children.
 *=======================================================*/
template <class Data, class Key>
typename BST<Data, Key>::Node *BST<Data, Key>::trim_helper(Node *n, const Key &low, const Key &high, Node *parent)
{
    if (!n)
        return nullptr;

    // If current node is less than low, entire left subtree can be ignored
    if (n->key < low)
    {
        Node *r = trim_helper(n->right, low, high, parent);
        delete n;
        return r;
    }

    // If current node is greater than high, entire right subtree can be ignored
    if (n->key > high)
    {
        Node *l = trim_helper(n->left, low, high, parent);
        delete n;
        return l;
    }

    // Current node is within range, trim both children
    n->left = trim_helper(n->left, low, high, n);
    n->right = trim_helper(n->right, low, high, n);
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
