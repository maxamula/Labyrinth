#pragma once
#include "List.h"

template<typename K, typename V>
class Table
{
public:
	class Item
	{
	public:
		Item(K key, V val)
		{
			this->key = key;
			this->val = val;			
		}
	public:
		K key;
		V val;
	};
private:
	Item* m_arr;
	int m_size;
	int m_cap;
public:
	Table()
	{
		m_arr = (Item*)malloc(2*sizeof(Item));
		m_cap = 2;
		m_size = 0;
	}
	Table(char* buf)
	{
		memcpy(&m_size, buf, 4);
		int capacity = 2;
		while (m_size > capacity)
			capacity *= 2;
		m_cap = capacity;
		m_arr = (Item*)malloc(capacity * sizeof(Item));
		memcpy(m_arr, buf + 4, m_size * sizeof(Item));
	}
	~Table()
	{
		free(m_arr);
	}
public:
	int Size()
	{
		return m_size;
	}

	void Put(K key, V val)
	{
		int index = Search(key);
		if (index != -1)
		{
			m_arr[index].val = val;
		}
		else
		{
			m_size++;
			if (m_size > m_cap)
				AllocMem(m_cap*2);
			Item item(key, val);
			memcpy(&m_arr[m_size-1], &item, sizeof(Item));
		}
	}

	V Get(K key)
	{
		int index = Search(key);
		if (index != -1)
			return m_arr[index].val;
		return NULL;
	}

	void Remove(K key)
	{
		int index = Search(key);
		if (index == -1)
			return;
		for (int i = index; i < m_size - 1; i++)
		{
			memcpy(&m_arr[i], &m_arr[i+1], sizeof(Item));
		}
		m_size--;
		if (m_size == m_cap / 2)
			AllocMem(m_cap / 2);
	}

	int CopyData(char* buf)
	{
		memcpy(buf, &m_size, 4);
		memcpy(buf + 4, m_arr, m_size * sizeof(Item));
		return 4 + m_size * sizeof(Item);
	}
	

private:

	bool Compare(K k1, K k2)					// Compare bytes
	{
		if (memcmp(&k1, &k2, sizeof(K)) == 0)
			return true;
		return false;
	}

	int Search(K key)							// Returns index of found item
	{
		for (int i = 0; i < m_size; i++)
		{
			if (Compare(m_arr[i].key, key))
				return i;
		}

		return -1;
	}

	void AllocMem(int cap)
	{
		if (cap < m_size)
			return;
		Item* newmem = (Item*)malloc(cap * sizeof(Item));
		memcpy(newmem, m_arr, (m_size-1) * sizeof(Item));
		free(m_arr);
		m_arr = newmem;
	}
};