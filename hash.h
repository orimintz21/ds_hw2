
#ifndef HASH_H
#define HASH_H

#include "List.h"
#include "Employee.h"
#include "Ex2Exception.h"

template <class T>
class hash
{
public:
    LinkedList<T> *_arr;
    long long _arry_size;
    long long _item_count;
    hash<T>();

    void insert(long long key, T e);
    T find(long long key);
    void remove(long long key);

    template <class Func>
    void updateAndRemove(hash<T> &copy_from, const Func &update)
    {
        for (long long i = 0; i < copy_from._arry_size; i++)
        {
            ListNode<T> *temp = copy_from._arr[i].head;
            while (temp != nullptr)
            {
                update((temp->_data));
                insert(temp->_key, (temp->_data));
                temp = temp->_next;
            }
        }

        // to chack on quit!!!!!!
        delete[] copy_from._arr;
        copy_from._arr = nullptr;
    }
    ~hash();

    long long getItemCount();

    long long getHashIndex(long long key);
    void resizeArry(double factor);
    void copyArry(LinkedList<T> *src, LinkedList<T> *des, long long size);
};

template <class T>
hash<T>::hash() : _arr(nullptr), _arry_size(2), _item_count(0)
{
    _arr = new LinkedList<T>[_arry_size];
    for (long long i = 0; i < _arry_size; i++)
    {
        _arr[i] = LinkedList<T>();
    }
}

template <class T>
void hash<T>::insert(long long key, T e)
{
    if (find(key))
    {
        throw already_in_hash();
    }
    long long hash_input = getHashIndex(key);
    _arr[hash_input].insertNode(key, e);
    _item_count = _item_count + 1;
    if (_item_count == _arry_size)
    {
        resizeArry(2);
    }
}

template <class T>
T hash<T>::find(long long key)
{
    long long hash_input = getHashIndex(key);
    return _arr[hash_input].getValue(key);
}

template <class T>
void hash<T>::remove(long long key)
{
    long long hashValue = getHashIndex(key);

    _arr[hashValue].removeNode(key);
    _item_count--;
    if (_item_count <= _arry_size / 4 && _arry_size > 2)
    {
        resizeArry(0.5);
    }
}

// chack!
template <class T>
hash<T>::~hash()
{
    delete[] _arr;
}

template <class T>
long long hash<T>::getHashIndex(long long key)
{
    return key % _arry_size;
}

template <class T>
void hash<T>::resizeArry(double factor)
{
    LinkedList<T> *arr_backup = new LinkedList<T>[_arry_size];
    copyArry(_arr, arr_backup, _arry_size);
    delete[] _arr;
    long long old_array_size = _arry_size;
    _arry_size = _arry_size * factor;
    _item_count = 0;
    _arr = new LinkedList<T>[_arry_size];
    for (long long i = 0; i < old_array_size; i++)
    {
        ListNode<T> *temp = arr_backup[i].head;
        while (temp != nullptr)
        {
            insert(temp->_key, (temp->_data));
            temp = temp->_next;
        }
    }
    delete[] arr_backup;
}

template <class T>
long long hash<T>::getItemCount()
{
    return _item_count;
}

template <class T>
void hash<T>::copyArry(LinkedList<T> *src, LinkedList<T> *des, long long size)
{
    for (long long i = 0; i < size; i++)
    {
        ListNode<T> *temp = src[i].head;
        while (temp != nullptr)
        {
            des[i].insertNode(temp->_key, (temp->_data));
            temp = temp->_next;
        }
    }
}

#endif // HASH_H