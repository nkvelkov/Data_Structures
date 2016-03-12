#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include <iostream>

using namespace std;

template <typename K, typename V>
class AVLTree
{
    friend ostream& operator <<(ostream&, const AVLTree&); // to do <<

    struct Node
    {
        K key;
        V value;
        Node* left;
        Node* right;
        Node* parent;
        Node() : right(NULL), left(NULL), parent(NULL)
        { }
        Node(const K& key, const V& value) : key(key), value(value), left(NULL), right(NULL), parent(NULL)
        { }

        bool isLeftChild()const
        {
            return (this == parent->left);
        }

        bool isRightChild()const
        {
            return (this == parent->right);
        }
    };

public:

    AVLTree();
    AVLTree(const AVLTree&);
    AVLTree& operator = (const AVLTree&);
    ~AVLTree();

    Node* getRoot()const;

    bool insert(const K&, const V&);
    bool remove(const K&, V&);
    bool find(const K&, V&)const;

    bool empty()const;
private:
    Node * root;

    void copyAVLTree(const AVLTree&);
    void deleteAVLTree();
    void deleteNode(Node* &);
    void copyNode(Node* &, const Node* &);
    void print(ostream&, Node*)const;
    bool isHere(Node* &,const K&, V&)const;
    Node* addNode(const K&, const V&);
    Node** lookup(const K&);
    Node** lookupParent(const K&);

    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    int getHeight(const Node*)const;
    int getBalance(const Node*)const;
    void splay(Node*);
    Node** findSubtreeMaximum(Node** node);
    Node** findSubtreeMinimum(Node** node);
    bool insertBSTWay(Node* &, Node* &);

    Node** swap(Node* x, Node* y);
};

template <typename K, typename V>
AVLTree<K, V>:: AVLTree() : root(NULL)
{}

template <typename K, typename V>
AVLTree<K, V>:: AVLTree(const AVLTree& other) : root(NULL)
{
    copyAVLTree(other);
}

template <typename K, typename V>
AVLTree<K, V>& AVLTree<K, V>:: operator = (const AVLTree& other)
{
    if(this != &other)
    {
        deleteAVLTree();
        copyAVLTree(other);
    }

    return *this;
}

template <typename K, typename V>
AVLTree<K, V>:: ~AVLTree()
{
    deleteAVLTree();
}

template <typename K, typename V>
void AVLTree<K, V>:: deleteAVLTree()
{
    deleteNode(root);
   // Node<K, V>* p;
   // delete root;
   // deleteNode(root);
}

template <typename K, typename V>
void AVLTree<K, V>:: deleteNode(Node* &cur)
{
    if(cur != NULL)
    {
        deleteNode(cur->left);
        deleteNode(cur->right);
        delete cur;
        cur = NULL;
    }
}

template <typename K, typename V>
void AVLTree<K, V>:: copyAVLTree(const AVLTree& other)
{   //Node * p = other.root; copyNode(root, other.root) ?
    root = new Node(other.root->key, other.root->value);
    copyNode(root, other.root);
}

template <typename K, typename V>
void AVLTree<K, V>:: copyNode(Node* &curParent, const Node* &cur)
{
  //  this->curParent = new Node(cur.key, cur.value);
    if(cur->left)
    {
        Node* newLeft = new Node(cur->left->key, cur->left->value);
        curParent->left = newLeft;
        newLeft->parent = curParent;
        copyNode(newLeft ,cur->left);
    }

    if(cur->right)
    {
        Node* newRight = new Node(cur->right->key, cur->right->value);
        curParent->right = newRight;
        newRight->parent = curParent;
        copyNode(newRight, cur->right);
    }
}

template <typename K, typename V>
ostream& operator << (ostream& out, const AVLTree<K, V>& tree)
{
    print(out, tree.root);

    return out;
}

template <typename K, typename V>
typename AVLTree<K, V>:: Node* AVLTree<K, V>:: getRoot()const
{
    return this->root;
}

template <typename K, typename V>
void AVLTree<K, V>:: print(ostream& out, Node* curNode)const
{
    if(curNode != NULL)
    { // lqvo koren dqsno
        print(out, curNode->left);

        out << "key " << curNode->key << " value " << curNode->value << endl;

        print(out, curNode->right);
    }
}

template <typename K, typename V>
bool AVLTree<K, V>:: find(const K& key, V& value)const
{
    Node** ptr = lookup(key);

    if (*ptr)
    {
        value = (*ptr)->value;

        return true;
    }

    return false;
}

template <typename K, typename V>
bool AVLTree<K, V>:: insert(const K& key, const V& value)
{
    Node* node = new Node(key, value);
    bool b = insertBSTWay(root, node);

    if(!b)
        return false;

    Node** par = lookupParent(key);
    node->parent = *par;

    Node** gpar = lookupParent((*par)->key );
    splay(*gpar);

    return true;
}

template <typename K, typename V>
bool AVLTree<K, V>:: remove(const K& key, V& value)
{
    if(!find(key, value))
    {
        return false;
    }

    Node** ptr = lookup(key);
    value = (*ptr)->value;

    Node** par; // = lookupParent(key);

    if (*ptr)
    {
        if (!(*ptr)->right && (*ptr)->left)
            par = swap(*ptr, (*ptr)->left);
        else if (!(*ptr)->left && (*ptr)->right)
            par = swap(*ptr, (*ptr)->right);
        else
        {
            Node** node = findSubtreeMinimum(&(root->right));
            if ((*node)->parent != *ptr)
            {
                swap(*node, (*node)->right);
                (*node)->right = (*ptr)->right;
                (*node)->right->parent = *node;
            }
                par = swap(*ptr, *node);
                (*node)->left = (*ptr)->left;
                (*node)->left->parent = *node;
        }

        delete *ptr;

        splay(*par);
    }
    return true;
}

template <typename K, typename V>
bool AVLTree<K, V>:: insertBSTWay(Node* &node, Node* &newNode)
{
    while(node)
    {
        if(node->key == newNode->key)
        {
            return false;
        }else if(node->key > newNode->key)
        {
            node = node->left;
        }else
        {
            node = node->right;
        }
    }
    node = newNode;
    return true;
}

template <typename K, typename V>
typename AVLTree<K, V>:: Node** AVLTree<K, V>:: lookup(const K& key)
{
    Node** cur = &root;

    while(*cur)
    {
        if((*cur)->key == key)
        {
            return cur;
        }else if((*cur)->key < key)
        {
            cur = &((*cur)->right);
        }else
        {
            cur = &((*cur)->left);
        }
    }
    return cur;
}
template <typename K, typename V>
typename AVLTree<K, V>:: Node** AVLTree<K, V>:: lookupParent( const K& key)
{
    Node** cur = &root, **previous = &root;

    while(*cur)
    {
        if((*cur)->key == key)
        {
            return previous;
        }else if((*cur)->key < key)
        {
            previous = cur;
            cur = &((*cur)->right);
        }else
        {
            previous = cur;
            cur = &((*cur)->left);
        }
    }

    return previous;
}
template <typename K, typename V>
typename AVLTree<K, V>:: Node* AVLTree<K, V>:: addNode(const K& key, const V& value)
{
    Node** cur = lookup(key);

    Node* node = new Node(key, value);
    (*cur) = node;

    Node** par = lookupParent(cur);
    node->parent = *par;

    return cur;
}

template <typename K, typename V>
bool AVLTree<K, V>:: empty()const
{
    return root == NULL;
}
template <typename K, typename V>
void AVLTree<K, V>:: rotateLeft(Node* x)
{
    Node *y = x->right;

    x->right = y->left;

    if (y->left)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (!x->parent)
    {
        root = y;
    }
    else if (x->isLeftChild())
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

        y->left = x;
        x->parent = y;
}

template <typename K, typename V>
void AVLTree<K, V>:: rotateRight(Node* x)
{
    Node *y = x->left;

    x->left = y->right;

    if (y->right)
    {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (!x->parent)
    {
        root = y;
    }
    else if (x->isLeftChild())
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
        y->right = x;
        x->parent = y;
}

template <typename K, typename V>
int AVLTree<K, V>:: getHeight(const Node* curNode)const
{
    if(curNode == NULL)
    {
        return 0;
    }
    int leftHeight = getHeight(curNode->left);
    int rightHeight = getHeight(curNode->right);
    return 1 + leftHeight < rightHeight ? rightHeight : leftHeight;
}

template <typename K, typename V>
typename AVLTree<K, V>:: Node** AVLTree<K, V>:: findSubtreeMaximum(Node** node)
{
    if (*node)
    {
        if ((*node)->right)
        {
            return findSubtreeMinimum(&((*node)->right));
        }
    }
    return node;
}

template <typename K, typename V>
typename AVLTree<K, V>:: Node** AVLTree<K, V>:: findSubtreeMinimum(Node** node)
{
    if (*node)
    {
        if ((*node)->left)
        {
            return findSubtreeMinimum(&((*node)->left));
        }
    }

    return node;
}

template <typename K, typename V>
int AVLTree<K, V>:: getBalance(const Node* curNode)const
{
    return getHeight(curNode->left) - getHeight(curNode->right);
}

template <typename K, typename V>
void AVLTree<K, V>:: splay(Node* node)
{
    int balance = getBalance(node);
    if(balance == 2)
    {
        int rightBalance = getBalance(node->right);
        if(rightBalance == -1)
            rotateRight(node->right);
        rotateLeft(node);
    }else if(balance == -2)
    {
        int leftBalance = getBalance(node->left);
        if(leftBalance == 1)
            rotateLeft(node->left);
        rotateRight(node);
    }
}

template <typename K, typename V>
typename AVLTree<K, V>:: Node** AVLTree<K, V>:: swap(Node* x, Node* y)
{
    if(x == root)//if (x->parent != NULL)
    {
        root = y;
    }
    else if (x->isLeftChild())
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    if (y)
    {
        y->parent = x->parent;
    }

    return &(x->parent);
}

template <typename K, typename V>
bool AVLTree<K, V>:: isHere(Node* &curNode, const K& key, V& value)const
{
    if(curNode != NULL)
    {
        if(curNode->key == key)
        {
            value = curNode->value;
            return true;
        }

        return isHere(curNode->left, key, value) || isHere(curNode->right, key, value);
    }
    return false;
}


#endif // AVLTREE_H_INCLUDED
