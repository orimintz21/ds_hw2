#include "UnionFind.h"
#include "string.h"

UnionFind::UnionFind(int k) :_size(k),_union_size(nullptr),_point_to(nullptr),_company(nullptr)
{
    if(k<=0)
    {
        throw invalid_input();
    }
    _point_to = new int[_size + 1];
    _union_size = new int[_size + 1];
    _company = new Company*[_size +1];
    _company[0] = nullptr;
    for(int i=1; i<=_size; i++)
    {
        _company[i] = new Company(i);
        _union_size[i] = 1;
        _point_to[i]=i;
    }
}
UnionFind::~UnionFind()
{
    delete[] _point_to;
    delete[] _union_size;
    for(int i=1; i<= _size ; i++)
    {
        delete _company[i];
    }
    delete[] _company;

}


Company *UnionFind::Find(int company_id)
{
    if (company_id > _size)
    {
        return nullptr;
    }
    double sum_value=0;
    int root = company_id;
    while(root != _point_to[root])
    {
        sum_value+=_company[root]->_stock_value;
        root = _point_to[root];
    }
    int index = company_id;
    while(index!=root)
    {
        sum_value-=_company[index]->_stock_value;
        _company[index]->_stock_value += sum_value;
        _point_to[index] = root;
        index = _point_to[index];
    }
    return _company[root];
}

void UnionFind::UnionLeftAcquire(int company_id1, int company_id2,double factor)
{
    Company *c1 = Find(company_id1);
    Company *c2 = Find(company_id2);

    if(c1->_id == c2->_id)
    {
        throw invalid_input();
    }
    if(_union_size[c1->_id]>=_union_size[c2->_id])
    {
        _company[c1->_id]->_stock_value += (_company[c2->_id]->_stock_value)*factor;
        _company[c2->_id]->_stock_value -= _company[c1->_id]->_stock_value;
        c1->mergeWith(*c2);
        _point_to[c2->_id] = c1->_id;
    }
    else
    {
        _company[c1->_id]->_stock_value += (_company[c2->_id]->_stock_value)*(factor-1);
        c2->mergeWith(*c1);
        _point_to[c1->_id] = c2->_id;
    }
}


double UnionFind::FindValue(int company_id)
{
    Find(company_id);
    if(_point_to[company_id] == company_id)
    {
        return _company[company_id]->_stock_value;
    }
    else
    {
        return (_company[company_id]->_stock_value)+(_company[_point_to[company_id]]->_stock_value);
    }
    
}




