#pragma once
#include <windows.h>

template <typename T>
class List
{
public:
	List()
	{
		m_data = (T*)malloc(2 * sizeof(T));
	}

	~List()
	{
		free(m_data); //release mem space
	}

	int size()
	{
		return m_size;
	}

	void addLast(T item)
	{
		m_size++;
		if (m_size > m_capacity) //if overflow
		{
			T* pData = (T*)malloc(m_capacity * 2 * sizeof(T)); //alloc new mem region
			memcpy(pData, m_data, m_capacity * sizeof(T)); //copy old data
			T* oData = m_data;
			m_data = pData;
			//free(oData); //release old memory
			m_capacity *= 2;
			m_data = pData;
		}
		memcpy(&m_data[m_size - 1], &item, sizeof(T)); //copy item
	}

	void addFirst(T item)
	{
		m_size++;
		if (m_size > m_capacity)
		{
			T* pData = (T*)malloc(m_capacity * 2 * sizeof(T));
			memcpy(pData, &item, sizeof(T));
			memcpy(&pData[1], m_data, m_capacity * sizeof(T));
			free(m_data);
			m_capacity *= 2;
			m_data = pData;
		}
		else
		{
			memcpy(&m_data[1], m_data, m_size * sizeof(T));
			memcpy(m_data, &item, sizeof(T));
		}
	}

	void removeLast()
	{
		if (m_size == 0)
			return;
		m_size--;
		if (m_capacity == m_size * 2)
		{
			T* pData = (T*)malloc((m_capacity / 2) * sizeof(T));
			memcpy(pData, m_data, m_size * sizeof(T));
			free(m_data);
			m_capacity /= 2;
			m_data = pData;
		}
	}

	void removeFirst()
	{
		if (m_size == 0)
			return;
		m_size--;
		if (m_capacity == m_size * 2)
		{
			T* pData = (T*)malloc((m_capacity / 2) * sizeof(T));
			memcpy(pData, &m_data[1], m_size * sizeof(T));
			free(m_data);
			m_capacity /= 2;
			m_data = pData;
		}
		else
		{
			for (int i = 0; i < m_size; i++)
				m_data[i] = m_data[i + 1];
		}
	}

	void Remove(T item)
	{
		for (int i = 0; i < m_size; i++)
		{
			if (this->operator[](i) == item)
			{
				if (m_capacity == (m_size-1)* 2)
				{
					T* pData = (T*)malloc((m_capacity / 2) * sizeof(T));
					memcpy(pData, m_data, (i)*sizeof(T));
					memcpy(&pData[i], &m_data[i+1], (m_size - i + 1) * sizeof(T));
					free(m_data);
					m_size --;
					m_capacity /= 2;
					m_data = pData;
				}
				else
				{
					memcpy(&m_data[i], &m_data[i+1], (m_size-i) * sizeof(T));
					m_size--;
				}
			}
		}
	}

	T operator[](int index)
	{
		if (index >= 0 && index < m_size)
			return m_data[index];
		else
			return NULL;
	}

	void toArray(T** ppArray)
	{
		*ppArray = (T*)malloc(m_size * sizeof(T));
		memcpy(*ppArray, m_data, m_size * sizeof(T));
	}

	void Sort()
	{
		for (int i = 0; i < (int)((m_size * sizeof(T)) / 4); i++)
		{
			int minindex = i;
			int min = (int)m_data[i];
			for (int j = i; j < (int)((m_size * sizeof(T)) / 4); j++)
			{
				if ((int)m_data[j] < min)
				{
					minindex = j;
					min = (int)m_data[j];
				}
			}

			if (minindex != i)
			{
				int temp;
				memcpy(&temp, &m_data[i], 4);
				memcpy(&m_data[i], &m_data[minindex], 4);
				memcpy(&m_data[minindex], &temp, 4);
			}
		}
	}

	bool isSort()
	{
		for (int i = 0; i < m_size; i++)
		{
			if (i + 1 < m_size && (int)m_data[i] >= (int)m_data[i + 1])
			{
				return false;
			}
		}
		return true;
	}

private:
	int m_size = 0;
	int m_capacity = 2;
	T* m_data;
};

