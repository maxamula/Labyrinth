#pragma once

template <typename T>
class Stack
{
public:
	Stack(int cap)
	{
		m_cap = cap;
		m_arr = (T*)malloc(cap*(sizeof(T)));
		ZeroMemory(m_arr, cap * (sizeof(T)));
		m_size = 0;
	}
	~Stack()
	{
		free(m_arr);
	}
public:
	void Push(T item)
	{
		if (m_size+1 < m_cap)
		{
			m_arr[m_size] = item;
			m_size++;
		}
	}
	T& Pop()
	{
		if (m_size > 0)
		{
			m_size--;
			return m_arr[m_size + 1];
		}	
	}

	T Get()
	{
		if (m_size > 0)
		{
			return m_arr[m_size-1];
		}
	}

	bool isEmpty()
	{
		return m_size == 0;
	}
private:
	T* m_arr;
	int m_size;
	int m_cap;
};

