#ifndef HW2_RANK_NODE_H
#define HW2_RANK_NODE_H

template<class T, class RankFunc>
class Node {
public:
    T* data;
    Node<T, RankFunc>* right;
    Node<T, RankFunc>* left;
    Node<T, RankFunc>* parent;
    RankFunc calcNodeSize;
    long long height;
    long long rank;

    Node(): data(nullptr), right(nullptr), left(nullptr), parent(nullptr), height(0), rank(0) {}

    Node(const T& n_data) : data(nullptr), right(nullptr), left(nullptr), parent(nullptr) , height(0){
        data = new T(n_data);
        rank = calcNodeSize(*data);
    }

    virtual ~Node() {
        delete left;
        delete right;
        delete data;
    }

    long long getBalance() const
    {
        long long l_h =-1;
        long long r_h =-1;
        if(left != nullptr)
            l_h=left->height;
        if(right!= nullptr)
            r_h = right->height;
        return l_h-r_h;
    }

    long long calcHeight()
    {
        long long l_h = -1;
        long long r_h =-1;
        if(left != nullptr)
            l_h = left->height;
        if(right!= nullptr)
            r_h = right->height;
        long long n_height = (l_h<r_h ? r_h+1:l_h+1);
        height = n_height;
        return height;
    }

    long long calcRank()
    {
        long long l_rank = 0;
        long long r_rank = 0;
        
        if(left != nullptr)
            l_rank = left->rank;

        if(right != nullptr)
            r_rank = right->rank;

        rank = l_rank + r_rank + calcNodeSize(*data);
        return rank;
    }


    bool isALeaf() const
    {
        return (left == nullptr && right == nullptr);
    }
};

template<class T ,class RankFunc>
void deleteOnlyThisNodePtr(Node<T, RankFunc>* node)
{
    if(node == nullptr)
        return;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    delete node;
}

template<class T, class RankFunc>
void deleteNodePtr(Node<T, RankFunc>* node)
{
    if(node == nullptr)
        return;
    delete node;
}

template<class T, class RankFunc>
Node<T, RankFunc>* newNode(T& n_data)
{
    Node<T, RankFunc>* node = new Node<T, RankFunc>(n_data);
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;

    return  node;
}

template<class T, class RankFunc>
bool NodeIsALeaf(Node<T, RankFunc>* node)
{
    if(node == nullptr)
        return false;
    return node->isALeaf();
}

template<class T, class RankFunc>
long long calcNodeHeight(Node<T, RankFunc>* node)
{
    if(node == nullptr)
        return -1;
    return node->calcHeight();
}

template<class T, class RankFunc>
long long calcNodeRank(Node<T, RankFunc>* node)
{
    if(node == nullptr)
        return 0;
    return node->calcRank();
}

template<class T, class RankFunc>
long long getElementsSize(Node<T, RankFunc>* node)
{
    if(node == nullptr)
        return 0;
    
    return node->calcNodeSize(*(node->data));
}



template<class T, class RankFunc>
long long getNodesBalance(const Node<T, RankFunc>* node)
{
    if(node == nullptr)
    {
        return 0;
    }
    return  node->getBalance();
}


#endif //HW2_RANK_NODE_H
