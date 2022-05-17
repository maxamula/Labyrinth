#pragma once

template <typename T>
class Queue
{
public:
	Queue(int cap)
	{
		m_initCap = cap;
		m_cap = cap;
		m_container = (T*)malloc(cap*sizeof(T));
	}

	Queue()
	{
		m_initCap = 4;
		m_cap = 4;
		m_container = (T*)malloc(4 * sizeof(T));
	}
public:
	int Size()
	{
		return m_size;
	}

	bool Empty()
	{
		bool rtn;
		m_size == 0 ? rtn = true : rtn = false;
		return rtn;
	}

	T Front()
	{
		if (m_size > 0)
			return m_container[0];
	}

	void Push(T item)
	{
		if (m_size + 1 > m_cap)
			IncreaseCapacity();
		m_container[m_size] = item;
		m_size++;
	}

	void Pop()
	{
		if (m_size == 0)
			return;
		m_size--;
		memcpy(m_container, &m_container[1], m_size * sizeof(T));
		if (m_size == m_cap / 2 && m_size > m_initCap)
			DecreaseCapacity();
	}

	T operator[](int index)
	{
		if (index < m_size && index >= 0)
		{
			return m_container[index];
		}
	}

	void operator+=(Queue q)
	{
		while (!q.Empty())
		{
			this->Push(q.Front());
			q.Pop();
		}
	}

	void operator=(Queue q)
	{
		for (int i = 0; i < q.Size(); i++)
		{
			this->Push(q[i]);
		}
	}

private:
	T* m_container;
	int m_cap;
	int m_initCap;
	int m_size = 0;

	void IncreaseCapacity()
	{
		m_cap *= 2;
		T* newmem = (T*)malloc(m_cap*sizeof(T));
		memcpy(newmem, m_container, m_size*sizeof(T));
		free(m_container);
		m_container = newmem;
	}

	void DecreaseCapacity()
	{
		m_cap /= 2;
		T * newmem = (T*)malloc(m_cap * sizeof(T));
		memcpy(newmem, m_container, m_size * sizeof(T));
		free(m_container);
		m_container = newmem;
	}
};

