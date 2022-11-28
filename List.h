#pragma once

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "Ex2Exception.h"


template <class T>
class ListNode {
public:
	int _key;
	T _data;
	ListNode* _next;
	ListNode(int key, T data, ListNode<T>* next) :
								_key(key),_data(data), _next(next) {};
	~ListNode() =default;
};

template <class T>
class LinkedList {
public:
	ListNode<T>* head;

	LinkedList() : head(nullptr) {};

	~LinkedList()
	{
		ListNode<T>* curr_node = head;
		while (curr_node != nullptr)
		{
			ListNode<T>* next_node = curr_node->_next;
			delete curr_node;
			curr_node = next_node;
		}
		head = nullptr;
	}

	void deleteListAndData()
	{
		ListNode<T>* curr_node = head;
		while (curr_node != nullptr)
		{
			ListNode<T>* next_node = curr_node->next;
			delete curr_node->data;
			delete curr_node;
			curr_node = next_node;
		}
		head = nullptr;
	}

	void removeNode(const int& key)
	{
		ListNode<T>* node = head;
		if (key == head->_key)
		{
			head = head->_next;
		}
		else
		{
			node = head->_next;
			ListNode<T>* prev_node = head;
			while (node != nullptr)
			{
				if (node->_key == key)
				{
					prev_node->_next = node->_next;
					break;
				}
				prev_node = node;
				node = node->_next;
			}
		}
		if(node == nullptr)
		{
			throw not_in_hash();
		}
		delete node;
	}

	ListNode<T>* insertNode(const int& key, const T& data)
	{
		ListNode<T>* new_node = new ListNode<T>(key, data, nullptr);
		// First insert
		if (head == nullptr)
		{
			head = new_node;
		}
		else
		{
			new_node->_next = head;
			head = new_node;
		}
		return new_node;
	}

	T getValue(const int& key)
	{
		ListNode<T>* node = head;
		while (node != nullptr)
		{
			if (key == node->_key) 
				return node->_data;

			node = node->_next;
		}
		return nullptr;
	}

};

#endif //LIST_H