#ifndef HW2_RANK_H
#define HW2_RANK_H
#include "Node.h"
#include "RankTreeExceptions.h"
#include <iostream>
#include <cmath>

template<class T, class Pred, class RankFunc>
class RankTree
{
public:
    //fields

    //a>b -> a_bigger_b(a,b) = true
    Pred a_bigger_b;
    Node<T, RankFunc>* root;
    Node<T, RankFunc>* max_n;
    Node<T, RankFunc>* min_n;
    long long size;

    RankTree() : root(nullptr), max_n(nullptr), min_n(nullptr), size(0) {
        a_bigger_b = Pred();
    }

    virtual ~RankTree() {

        if(root!=nullptr){
            delete root;
        }
    }

    bool equal(const T& a,const T& b) const
    {
        return (! a_bigger_b(a,b) && ! a_bigger_b(b,a));
    }

    //main functions
    Node<T, RankFunc>* find(const T& element);

    Node<T, RankFunc>* select(long long element_rank);
    T* selectElement(long long element_rank);

    Node<T, RankFunc>* selectAux(long long element_rank, Node<T, RankFunc>* loc);


    long long findRank(const T& element);

    void insert(const T& element);
    void remove(const T& element);


    //internal functions

    //LL rotation
    void LL(Node<T, RankFunc>* rotation_root);
    //LR rotation
    void LR(Node<T, RankFunc>* rotation_root);
    //RL rotation
    void RL(Node<T, RankFunc>* rotation_root);
    //RR rotation
    void RR(Node<T, RankFunc>* rotation_root);
    void fixBalance(Node<T, RankFunc>* from);


    //for tests
    void printTree(long long space) const;

    void removeLeaf(Node<T, RankFunc>* to_remove, Node<T, RankFunc>* p, bool is_right);
    void removeOneSonLeft(Node<T, RankFunc>* to_remove, Node<T, RankFunc>* p , bool is_right);
    void removeOneSonRight(Node<T, RankFunc>* to_remove, Node<T, RankFunc>* p , bool is_right);
    void removeTwoSons(Node<T, RankFunc>* to_remove, Node<T, RankFunc>* p, bool is_right);

    void merge(RankTree<T,Pred, RankFunc>& source);
    void nullifyTree();
    void setMin()
    {
        Node<T, RankFunc>* m = root;
        while(m->left != nullptr)
            m = m->left;
        min_n = m;
    }
    void setMax()
    {
        Node<T, RankFunc>* m = root;
        while(m->right != nullptr)
            m = m->right;
        max_n = m;
    }

};

template<class T, class RankFunc>
void RankTreeToArr(Node<T, RankFunc>* root, Node<T, RankFunc>* arr[], long long* loc);

template<class T, class Pred, class RankFunc>
void margeNodeArr(Node<T, RankFunc>* a_arr[], long long a_size, Node<T, RankFunc>* b_arr[], long long b_size, 
                                                Node<T, RankFunc>* ab_arr[], Pred cond);

template<class T, class RankFunc>
Node<T, RankFunc>* fromArrToNodes(Node<T, RankFunc>*& root, Node<T, RankFunc>* ab_arr[], long long start, long long end);


template<class T, class Pred, class RankFunc>
Node<T, RankFunc>* RankTree<T,Pred ,RankFunc>::find(const T& element)
{
    Node<T, RankFunc>* temp = root;
    while(true)
    {
        if(temp == nullptr)
        {
            throw not_in_tree();
        }
        //temp>element
        if( a_bigger_b(*(temp->data), element))
        {
            temp = temp->left;
        }
            //temp<element
        else if( a_bigger_b(element, *(temp->data)))
        {
            temp = temp->right;
        }
        else {
            return temp;
        }
    }
}

template<class T, class Pred, class RankFunc>
T* RankTree<T, Pred, RankFunc>::selectElement(long long element_rank)
{
    return select(element_rank)->data;
}


template<class T, class Pred, class RankFunc>
Node<T, RankFunc>* RankTree<T, Pred, RankFunc>::select(long long element_rank)
{
    return selectAux(element_rank, root);
}

template<class T, class Pred, class RankFunc>
Node<T, RankFunc>* RankTree<T,Pred,RankFunc>::selectAux(long long element_rank, Node<T, RankFunc>* loc)
{
    if(loc == nullptr)
    {
        throw not_in_tree();
    }
    long long left_rank = calcNodeRank(loc->left);
    long long loc_size = getElementsSize(loc);
    if(left_rank == element_rank - loc_size)
    {
        return loc;
    }
    else if(left_rank > element_rank - loc_size)
    {
        return selectAux(element_rank, loc->left);
    }
    else
    {
        return selectAux(element_rank - left_rank - loc_size, loc->right);
    }
}

template<class T, class Pred, class RankFunc>
long long RankTree<T,Pred,RankFunc>::findRank(const T& element)
{
    long long r = 0;
    Node<T, RankFunc>* temp = root;
    while(true)
    {
        if(temp == nullptr)
        {
            throw not_in_tree();
        }
        //temp>element
        if( a_bigger_b(*(temp->data), element))
        {
            temp = temp->left;
        }
        //temp<element
        else if( a_bigger_b(element, *(temp->data)))
        {
            r += calcNodeRank(temp->left) + getElementsSize(temp);
            temp = temp->right;
        }
        //temp == elemnt
        else {
            r += calcNodeRank(temp->left) + getElementsSize(temp);
            return r;
        }
    }
}

template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::insert(const T& element)
{
    Node<T, RankFunc>* temp = root;
    Node<T, RankFunc>* last = root;
    if(temp == nullptr)
    {
        Node<T, RankFunc>* n_element = new Node<T, RankFunc>(element);
        root = n_element;
        min_n = n_element;
        max_n = n_element;
        size++;
        return;
    }
    bool is_right = false;
    while(temp != nullptr)
    {
        //temp>element
        if( a_bigger_b(*(temp->data), element))
        {
            last = temp;
            is_right = false;
            temp = temp->left;
        }
        else if(a_bigger_b(element,*(temp->data)))
        {
            last = temp;
            is_right = true;
            temp = temp->right;
        }
        else{
            throw already_in_tree();
        }
    }
    Node<T, RankFunc>* n_node = new Node<T, RankFunc>(element);
    n_node->parent = last;

    if(is_right)
        last->right = n_node;
    else
        last->left = n_node;
    size++;

    if(max_n == nullptr)
        max_n = n_node;
    else if( a_bigger_b(element ,*(max_n->data)))
        max_n = n_node;

    if(min_n == nullptr)
        min_n = n_node;
    else if( a_bigger_b(*(min_n->data), element))
        min_n = n_node;
    calcNodeHeight(n_node);
    calcNodeRank(n_node);
    fixBalance(n_node);
}



template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::remove(const T& element)
{
    Node<T, RankFunc>* to_remove = find(element);
    Node<T, RankFunc>* r_parent = to_remove->parent;

    bool is_right = false;
    if (r_parent != nullptr)
    {
        if(r_parent->right == to_remove)
        {
            is_right = true;
        }
    }

    //to_remove is a leaf
    if(to_remove->isALeaf())
    {
        removeLeaf(to_remove, r_parent, is_right);
    }

    //to_remove have only the right son
    else if(to_remove->left == nullptr)
    {
        removeOneSonRight(to_remove, r_parent, is_right);
    }

    else if(to_remove->right == nullptr)
    {
        removeOneSonLeft(to_remove,r_parent,is_right);
    }

    //to_remove have two sons
    else
    {
        removeTwoSons(to_remove, r_parent, is_right);
        return;
    }
}

template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::removeLeaf(Node<T, RankFunc> *to_remove, Node<T, RankFunc> *p, bool is_right) {

    //the only one node in the tree
    if(p == nullptr)
    {
        root = nullptr;
        max_n = nullptr;
        min_n = nullptr;
    }
    else if(is_right)
    {
        p->right = nullptr;
        //to_remove > p -> to_remove != min_n
        if(to_remove == max_n)
            max_n = p;
    }
    //to_remove is the left son of p
    else{
        p->left = nullptr;
        //to_remove < p -> to_remove != max_n
        if(to_remove == min_n)
            min_n = p;
    }

    size--;
    deleteOnlyThisNodePtr(to_remove);
    fixBalance(p);
}

//to_remove->right == nullptr && to_remove->left != nullptr
template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::removeOneSonLeft(Node<T, RankFunc> *to_remove, Node<T, RankFunc> *p, bool is_right) {
    if(p == nullptr)
    {
        root = to_remove->left;
        if(max_n == to_remove)
            max_n = to_remove->left;
        //to_remove > to_remove->left --> min_n != to_remove
    }
    else if(is_right)
    {
        p->right = to_remove->left;
        if(max_n == to_remove)
            max_n = to_remove->left;
        //to_remove > to_remove->left --> min_n != to_remove
    }
    else
    {
        p->left = to_remove->left;
        //p>to_remove>to_remove->left --> min_n!= to_remove != max_n
    }
    to_remove->left->parent = p;
    size--;
    deleteOnlyThisNodePtr(to_remove);
    fixBalance(p);
}

//to_remove->left == nullptr && to_remove->right != nullptr
template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::removeOneSonRight(Node<T, RankFunc> *to_remove, Node<T, RankFunc> *p, bool is_right) {
    if(p == nullptr)
    {
        root = to_remove->right;
        if(min_n == to_remove)
            min_n = to_remove->right;
        //to_remove < to_remove->right --> max_n != to_remove
    }
    else if(is_right)
    {
        p->right = to_remove->right;
        //p<to_remove < to_remove->right --> min_n != to_remove != max_n
    }
    else
    {
        p->left = to_remove->right;
        if(min_n == to_remove)
            min_n = to_remove->right;
        //to_remove < to_remove->right < p --> min_n!= to_remove != max_n
    }
    to_remove->right->parent = p;

    size--;
    deleteOnlyThisNodePtr(to_remove);
    fixBalance(p);
}

template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::removeTwoSons(Node<T, RankFunc> *to_remove, Node<T, RankFunc> *p, bool is_right) {
    //to_remove->left < to_remove < to_remove->right --> max_n != to_remove != min_n

    bool is_son = true;
    Node<T, RankFunc>* to_switch = to_remove->right;
    while(to_switch->left != nullptr)
    {
        is_son = false;
        to_switch = to_switch->left;
    }

    Node<T, RankFunc>* to_switch_p = to_switch->parent;
    Node<T, RankFunc>* to_switch_r = to_switch->right;
    Node<T, RankFunc>* to_remove_r = to_remove->right;

    if(p == nullptr)
    {
        to_switch->parent = nullptr;
        root = to_switch;

    }
    else
    {
        to_switch->parent = p;
        if(is_right)
            p->right = to_switch;
        else
            p->left = to_switch;
    }

    if(is_son)
    {
        to_remove->parent = to_switch;
        to_switch->right = to_remove;
    }
    else
    {
        to_remove->parent = to_switch_p;
        to_switch_p->left = to_remove;
        to_switch->right =to_remove_r;
        to_remove_r->parent = to_switch;
    }
    to_switch->left = to_remove->left;
    to_remove->left->parent =to_switch;
    to_remove->left = nullptr;
    to_remove->right = to_switch_r;
    if(to_switch_r != nullptr)
        to_switch_r->parent = to_remove;

    //is_son==true -> to_remove is the right son
    if(to_remove->isALeaf())
        removeLeaf(to_remove,to_remove->parent,is_son);
    else
    {
        removeOneSonRight(to_remove,to_remove->parent,is_son);
    }
}

template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::fixBalance(Node<T, RankFunc>* from)
{
    Node<T, RankFunc>* temp = from;
    while (temp!= nullptr)
    {
        temp->calcRank();
        temp->calcHeight();
        if(temp->getBalance() > 1)
        {
            if(temp->left->getBalance() >= 0)
            {
                LL(temp);
            }
            else{
                LR(temp);
            }
        } else if(temp->getBalance() < -1)
        {
            if(temp->right->getBalance() <= 0)
            {
                RR(temp);
            } else {
                RL(temp);
            }
        }
        temp = temp->parent;
    }
}

template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::LL( Node<T, RankFunc>* rotation_root)
{
    Node<T, RankFunc>* rotrootParent = rotation_root->parent;
    Node<T, RankFunc>* switch_with = rotation_root->left;
    Node<T, RankFunc>* T2 = switch_with->right;

    //make rotroot.left -> switch.right
    rotation_root->left = T2;
    if(T2!= nullptr)
        T2->parent = rotation_root;

    // make switch.right -> rotroot
    switch_with->right = rotation_root;
    rotation_root->parent = switch_with;

    switch_with->parent = rotrootParent;

    // fix rotrootParent child
    if(rotation_root == root)
    {
        root = switch_with;
    }
    else
    {
        if (rotrootParent->left == rotation_root) {
            rotrootParent->left = switch_with;
        }
        else {
            rotrootParent->right =  switch_with;
        }
    }

    rotation_root->calcHeight();
    rotation_root->calcRank();

    switch_with->calcHeight();
    switch_with->calcRank();
}

template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::RR( Node<T, RankFunc>* rotation_root)
{
    Node<T, RankFunc>* rotrootParent = rotation_root->parent;
    Node<T, RankFunc>* switch_with = rotation_root->right;
    Node<T, RankFunc>* T2 = switch_with->left;

    //make rotroot.right -> switch.left
    rotation_root->right = T2;
    if(T2!= nullptr)
        T2->parent = rotation_root;

    // make switch.left -> rotroot
    switch_with->left = rotation_root;
    rotation_root->parent = switch_with;

    switch_with->parent = rotrootParent;

    // fix rotrootParent child
    if(rotation_root == root)
    {
        root = switch_with;
    }
    else
    {
        if (rotrootParent->left == rotation_root) {
            rotrootParent->left = switch_with;
        }
        else {
            rotrootParent->right =  switch_with;
        }
    }

    rotation_root->calcHeight();
    rotation_root->calcRank();

    switch_with->calcHeight();
    switch_with->calcRank();
}

template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::LR( Node<T, RankFunc>* rotation_root)
{
    RR(rotation_root->left);
    LL(rotation_root);
}

template<class T, class Pred, class RankFunc>
void RankTree<T,Pred, RankFunc>::RL( Node<T, RankFunc>* rotation_root)
{
    LL(rotation_root->right);
    RR(rotation_root);
}


template<class T, class Pred, class RankFunc>
void storeInOrder( Node<T, RankFunc>* root, T arr[], long long *ind)
{
    if( root == nullptr)
        return;

    storeInOrder<T,Pred>(root->left, arr, ind);

    arr[*ind] = *(root->data);
    (*ind)++;

    storeInOrder<T,Pred>(root->right, arr, ind);
}


template<class T, class RankFunc>
Node<T, RankFunc>* fromArrToNodes(Node<T, RankFunc>*& root, Node<T, RankFunc>* ab_arr[], long long start, long long end)
{
    if(start > end)
        return nullptr;
    long long mid = (long long)((start + end)/2);
    root = ab_arr[mid];

    root->right = fromArrToNodes(root->left, ab_arr, mid+1 , end);
    if(root->right != nullptr)
        root->right->parent = root;
    root->left = fromArrToNodes(root->left, ab_arr, start, mid-1);
    if(root->left != nullptr)
        root->left->parent = root;


    calcNodeHeight(root);
    calcNodeRank(root);
    return  root;
}

template<class T , class  Pred , class RankFunc>
void RankTree<T,Pred, RankFunc>::merge(RankTree<T,Pred, RankFunc> &source) {
    Node<T, RankFunc>** arr1 = new Node<T, RankFunc>*[size];
    Node<T, RankFunc>** arr2 = new Node<T, RankFunc>*[source.size];
    long long i =0 , j=0;
    RankTreeToArr<T>(this->root, arr1, &i);
    RankTreeToArr<T>(source.root, arr2, &j);
    Node<T, RankFunc>** merged_arr = new Node<T, RankFunc>*[size + source.size];
    margeNodeArr(arr1, size , arr2, source.size , merged_arr , a_bigger_b);
    fromArrToNodes<T>(root , merged_arr , 0 , size + source.size - 1);
    if(min_n == nullptr)
    {
        min_n = source.min_n;
    }
    else if(source.min_n != nullptr)
    {
        min_n =(a_bigger_b(*(source.min_n->data),*(min_n->data)) ? min_n: source.min_n);
    }
    if(max_n == nullptr)
    {
        max_n = source.max_n;
    }
    else if(source.max_n != nullptr)
    {
        max_n = (a_bigger_b(*(max_n->data),*(source.max_n->data)) ? max_n: source.max_n);
    }
    size += source.size;

    delete[] arr1;
    delete[] arr2;
    delete[] merged_arr;
    source.nullifyTree();
}

template<class T, class Pred, class RankFunc>
void RankTree<T,Pred,RankFunc>::nullifyTree()
{
    max_n = nullptr;
    min_n = nullptr;
    root = nullptr;
    size = 0;
}



template<class T, class Pred, class RankFunc>
void margeNodeArr(Node<T, RankFunc>* a_arr[], long long a_size, Node<T, RankFunc>* b_arr[], long long b_size, Node<T, RankFunc>* ab_arr[], Pred cond)
{
    long long it_a =0;
    long long it_b =0;
    long long it_ab =0;
    while(it_a < a_size && it_b < b_size)
    {
        if(cond(*(a_arr[it_a]->data), *(b_arr[it_b]->data)))
        {
            ab_arr[it_ab] = b_arr[it_b];
            it_b++;
            it_ab++;
        }
        else{
            ab_arr[it_ab] =a_arr[it_a];
            it_a++;
            it_ab++;
        }
    }

    while (it_a < a_size)
    {
        ab_arr[it_ab] = a_arr[it_a];
        it_ab++;
        it_a++;
    }

    while (it_b < b_size)
    {
        ab_arr[it_ab] =b_arr[it_b];
        it_b++;
        it_ab++;
    }
}


template<class T, class RankFunc>
void RankTreeToArr(Node<T, RankFunc>* root, Node<T, RankFunc>* arr[], long long* loc)
{
    if(root == nullptr)
        return;

    Node<T, RankFunc>* left = root->left;
    Node<T, RankFunc>* right = root->right;

    RankTreeToArr<T>( left, arr, loc);

    root->right = nullptr;
    root->left = nullptr;
    root->parent = nullptr;
    root->height = 0;

    arr[*loc] = root;
    (*loc)++;
    RankTreeToArr<T>( right ,arr ,loc);
}


#endif //HW2_RANK_H