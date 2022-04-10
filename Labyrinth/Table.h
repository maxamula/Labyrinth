#pragma once
#include <optional>
#include "List.h"

template <typename K, typename V>
class Node
{
public:
	Node(K key, V value)
	{
		this->key = key;
		this->value = value;
	}
	Node(K key)
	{
		this->key = key;
		this->value = 0;
	}
	~Node()
	{

	}
public:
	K key;
	V value;
private:

};

template <typename K, typename V>
class Table
{
public:
	Table()
	{

	}
	~Table()
	{

	}
public:
	void Put(K key, V value)
	{
		bool bFlag = false;
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i]->key == key)
			{
				bFlag = true;
				nodes[i]->value = value;
				break;
			}
		}

		if(!bFlag)
		{
			Node<K, V>* pNewNode = new Node<K, V>(key, value);
			this->nodes.addLast(pNewNode);
		}
	}

	V Get(K key)
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i]->key == key)
			{
				return nodes[i]->value;
			}
		}
	}

private:
	List<Node<K, V>*> nodes;

};

