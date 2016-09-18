
#ifndef Stack_cpp
#define Stack_cpp
#pragma once
#include <cassert> 
#include <iostream>

#pragma once
template <typename T>
class stack
{
public:
	stack();
	stack(const stack &); // Добавленный конструктор копирования
	~stack();
	size_t count() const;
	void push(T const &); 
	T pop();
	void print(int);
	stack<T> operator=(stack const & newst);

private:

	T* copy(T const *array_, size_t count_,size_t array_size_);
	T * array_;
	size_t array_size_;
	size_t count_;
};
template <typename T>
stack<T>::stack() :
	count_(0)
	{
}
// Добавленный конструктор копирования
template <typename T>
stack<T>::stack(const stack & otherStack) :
	count_(otherStack.count_)
	array_size_(otherStack.array_size_)
	array_(copy(otherStack.array_, otherStack.count_, otherStack.array_size_))
	{
}
template <typename T>
stack<T>::~stack()
{
	delete[] array_;
}

template <typename T>
stack<T> stack<T>::operator=(stack const & newst) {
	assert(this != &newst);
	array_size_ = newst.array_size_;
	count_ = newst.count_;
	array_ = copy(newst.array_, newst.count_, newst.array_size_)
	return *this;
}

template <typename T>                  //COPY
T* stack<T>::copy(T const *ptr, size_t count_, size_t array_size_)
{
	T* nstack = new T[array_size_];
	std::copy(ptr,ptr+count_, nstack);
	return nstack;
}

template <typename T>
void stack<T>::push(const T &value)
{
	if (count_ >= array_size_) {
		array_size_ = array_size_ * 2 + (array_size_ == 0 ? 1 : 0);
		T * nstack = copy(array_, count_, array_size_);
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
#endif // Stack_cpp
