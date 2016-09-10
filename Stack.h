#pragma once
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
	void print(int);
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
template <typename T>
stack<T>::stack() :
	count_(0) {
}
template <typename T>
stack<T>::~stack()
{
	delete[] array_;
}
template <typename T>
void stack<T>::push(const T &value)
{
	if (count_ == 0) {
		array_ = new T[count_+1];
		array_[count_] = value;
		++count_;
		array_size_ = count_;

	}
	else if (count_ == array_size_) {
		array_size_++;
		T * nstack = new T[array_size_];
		for (size_t i = 0; i < array_size_; ++i) {
			nstack[i] = array_[i];
		}
		delete[] array_;
		array_ = nstack;
		array_[count_] = value;
		++count_;
	}
	else if (count_ < array_size_) {
		array_[count_] = value;
		count_++;
	}

}
template <typename T>
T stack<T>::pop()
{
	assert(count_ > 0);

	return array_[--count_];

}
template <typename T>
size_t stack<T>::count() const
{
	return count_;
}
template <typename T>
void stack<T>::print(int c)
{
		cout << array_[c] << endl;
}
#endif // Stack_H
