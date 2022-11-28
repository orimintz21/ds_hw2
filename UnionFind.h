#ifndef UNION_FIND_H
#define UNION_FIND_H

#include "Company.h"
class UnionFind
{
public:
    int _size;
    int *_union_size;
    int *_point_to;
    Company **_company;
    UnionFind(int k);
    ~UnionFind();
    UnionFind(const UnionFind &uf) = delete;
    UnionFind &operator=(const UnionFind &uf) = delete;
    void UnionLeftAcquire(int company_id1, int company_id2,double factor);
    Company *Find(int company_id);
    double FindValue(int company_id);
};

#endif
