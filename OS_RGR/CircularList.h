#pragma once
#include <iostream>

template <typename T>
class Node
{
private:

protected:
public:
	T data;
	Node* ptrNext;

	Node(const T& data);
};

template <class T>
class CircularList
{
private:
	size_t lsize = 0;
	Node<T>* ptrCur=nullptr;
protected:
public:
	CircularList();
	CircularList(const CircularList&);
	CircularList(CircularList&&);
	CircularList& operator=(const CircularList&);
	CircularList& operator=(CircularList&&);
	~CircularList();

	size_t size();
	void push(const T&);
	void push(T&&);
	void pop();
	void next();
	void rewrite(Node<T>);
	void rewrite(T);
	Node<T>* exist(T);
	Node<T>* getTop();

	T get();

	template <class V>
	friend std::ostream& operator<<(std::ostream&, CircularList<V>&);
};

template <class T>
Node<T>::Node(const T& data) : data(data)
{

}

template <class T> CircularList<T>::CircularList() : lsize(0), ptrCur(nullptr)
{

}

template <class T>
CircularList<T>::CircularList(const CircularList&)
{

}

template <class T>
CircularList<T>::CircularList(CircularList&&)
{

}

template <class T>
CircularList<T>& CircularList<T>::operator=(const CircularList&)
{

}

template <class T>
CircularList<T>& CircularList<T>::operator=(CircularList&&)
{

}

template <class T>
CircularList<T>::~CircularList()
{
	Node<T>* ptrNext;
	while (lsize != 0)
	{
		ptrNext = ptrCur->ptrNext;
		lsize--;
		delete ptrCur;
		ptrCur = ptrNext;
	}
}

template <class T>
size_t CircularList<T>::size()
{
	return this->lsize;
}

template <class T>
void CircularList<T>::push(const T& data)
{
	Node<T>* tmpnode = new Node<T>(data);
	if (lsize == 0)
	{
		this->ptrCur = tmpnode;
		tmpnode->ptrNext = tmpnode;
	}
	else
	{
		Node<T>* ptrtonext = ptrCur->ptrNext;
		ptrCur->ptrNext = tmpnode;
		tmpnode->ptrNext = ptrtonext;
	}
	lsize++;
}

template <class T>
void CircularList<T>::push(T&& data)
{
	T nd = data;
	this->push(nd);
}

template <class T>
void CircularList<T>::pop()
{
	if (lsize == 0) return;
	if (lsize == 1)
	{
		delete ptrCur;
		ptrCur = nullptr;
		return;
	}
	Node<T>* tmp = ptrCur;
	while (ptrCur->ptrNext != ptrCur)
	{
		next();
	}
	ptrCur = ptrCur->ptrNext->ptrNext;
	delete tmp;
}

template <class T>
void CircularList<T>::next()
{
	ptrCur = ptrCur->ptrNext;
}

template <class T>
void CircularList<T>::rewrite(Node<T> node)
{
	ptrCur->data = node.data;
}

template <class T>
void CircularList<T>::rewrite(T data)
{
	ptrCur->data = data;
}

template <class T>
Node<T>* CircularList<T>::exist(T data)
{
	if (ptrCur == nullptr) return nullptr;

	Node<T>* iter = ptrCur;
	do
	{
		if (iter->data == data)
			return iter;
		iter = iter->ptrNext;
	} while (iter != ptrCur);

	return nullptr;
}

template <class T>
Node<T>* CircularList<T>::getTop()
{
	return ptrCur;
}

template <class T>
T CircularList<T>::get()
{
	return ptrCur->data;
}

template <class V>
std::ostream& operator<<(std::ostream& out, CircularList<V>& print)
{

	Node<V>* ptriter = print.ptrCur;
	if (ptriter == nullptr) return out;
	else
	{
		do
		{
			std::cout << ptriter->data << " ";
			ptriter = ptriter->ptrNext;
		} while (ptriter != print.ptrCur);
	}
	return out;
}