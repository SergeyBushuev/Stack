#ifndef Stack_H
#define Stack_H

#include <cassert> 
#include <iostream>

#pragma once
template <typename T>
class stack
{
public:
	stack();
	~stack();
	size_t count() const;
	void push(T const &);
	T pop();
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
template <typename T>
stack<T>::stack() :
	array_size_(0) 
{
	array_ = new T[array_size_]; 
	count_ = 0; 
}
template <typename T>
stack<T>::~stack()
{
	delete[] array_;
}
template <typename T>
void stack<T>::push(const T &value)
{
	assert(count_ < array_size_); 

	array_[count_++] = value;
}
template <typename T>
T stack<T>::pop()
{
	assert(count_ > 0);

	array_[--count_]; 
}
template <typename T>
size_t stack<T>::count() const
{
	return count_;
}
#endif // Stack_H
