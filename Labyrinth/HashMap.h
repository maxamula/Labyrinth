#pragma once
#include <windows.h>
#include <shlwapi.h>

template <typename K, typename V>
class HashMap
{
	struct NODE {
		K key;
		V val;
		NODE* link = NULL;
	};
public:
	HashMap()
	{
		ZeroMemory(m_arr, 256*sizeof(NODE*));
	}
public:

	void Put(K key, V val)
	{
		BYTE hash;
		HashCode(key, &hash);
		NODE* prevNode = NULL;
		NODE* currentNode = m_arr[hash];
		while (currentNode != NULL)
		{
			if (memcmp(&currentNode->key, &key, sizeof(K)) == 0)
			{
				currentNode->val = val;
				return;
			}
			else
			{
				prevNode = currentNode;
				currentNode = currentNode->link;
			}
		}
		NODE* newNode = new NODE{key, val, NULL};
		if (prevNode == NULL)
			m_arr[hash] = newNode;
		else
			prevNode->link = newNode;
	}

	V Get(K key)
	{
		BYTE hash;
		HashCode(key, &hash);
		NODE* currentNode = m_arr[hash];
		while (currentNode != NULL)
		{
			if (memcmp(&currentNode->key, &key, sizeof(K)) == 0)
				return currentNode->val;
			else
				currentNode = currentNode->link;		
		}
		return NULL;
	}

	V* GetP(K key)
	{
		BYTE hash;
		HashCode(key, &hash);
		NODE* currentNode = m_arr[hash];
		while (currentNode != NULL)
		{
			if (memcmp(&currentNode->key, &key, sizeof(K)) == 0)
				return &currentNode->val;
			else
				currentNode = currentNode->link;
		}
		return NULL;
	}

	void Remove(K key)
	{
		BYTE hash;
		HashCode(key, &hash);
		NODE* prevNode = NULL;
		NODE* currentNode = m_arr[hash];
		while (currentNode != NULL)
		{
			if (memcmp(&currentNode->key, &key, sizeof(K)) == 0)
			{
				if (prevNode != NULL)
					prevNode->link = currentNode->link;
				else
					m_arr[hash] = NULL;
				delete currentNode;
				return;
			}
			else
			{
				prevNode = currentNode;
				currentNode = currentNode->link;
			}
		}
	}

private:
	NODE* m_arr[256];

	void HashCode(K key, BYTE* hash)
	{
		HashData((BYTE*)&key, sizeof(K), hash, sizeof(BYTE));				//TODO: replace
	}
};

