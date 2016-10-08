#ifndef Stack_cpp
#include <cassert> 
#include <iostream>

#pragma once
template <typename T>
class allocator {
protected:
	explicit allocator(size_t size = 0);							/*noexcept*/
	~allocator();													/*noexcept*/
	auto swap(allocator & other) -> void;							/*noexcept*/

	allocator(allocator const &) = delete;
	auto operator=(allocator const &)->allocator & = delete;

	T * ptr_;
	size_t size_;
	size_t count_;
};
template<typename T> 
allocator<T>::allocator(size_t size) :
	ptr_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))),
	size_(0),
	count_(size) {
}

template<typename T> 
allocator<T>::~allocator() {
	delete ptr_;
}

template<typename T> 
auto allocator<T>::swap(allocator & other) -> void {
	std::swap(ptr_, other.ptr_);
	std::swap(count_, other.count_);
	std::swap(size_, other.size_);
}
template <typename T>
class stack : protected allocator<T>
{
public:
	stack();										/*noexcept*/
	stack(const stack &); 							/*strong*/
	~stack(); 										/*noexcept*/
	size_t count() const; 							/*noexcept*/
	void push(T const &); 							/*strong*/
	void pop(); 									/*strong*/
	const T& top(); 								/*strong*/
	stack & operator=(stack & newst);				/*strong*/
	bool empty(); 									/*noexcept*/
};		
template <typename T>                  			//COPY
T* newcopy(T const *ptr, size_t count, size_t _size)  /*strong*/
{
	T* nstack = new T[_size];
	try {
		std::copy(ptr, ptr + count, nstack);
	}
	catch (...) {
		delete[] nstack;
		throw;
	}
	return nstack;
}
template <typename T>
stack<T>::stack() :
	allocator<T>()
{
}
template <typename T>
stack<T>::stack(const stack & otherStack) :
	allocator<T>::ptr_(newcopy(otherStack.ptr_, otherStack.count_, otherStack.size_)),
	allocator<T>::count_(otherStack.count_),
	allocator<T>::size_(otherStack.size_)
{
}
template <typename T>
stack<T>::~stack()
{
	delete[] allocator<T>::ptr_;
}

template <typename T>
stack<T>& stack<T>::operator=(stack & newst) {
	if (this != &newst) {
		T *p = allocator<T>::ptr_;
		allocator<T>::ptr_ = newcopy(newst.ptr_, newst.count_, newst.size_);
		delete[] p;
		allocator<T>::size_ = newst.size_;
		allocator<T>::count_ = newst.count_;
	}
	return *this;
}

template <typename T>
void stack<T>::push(const T &value)
{
	if (allocator<T>::count_ >= allocator<T>::size_) {
		size_t size = allocator<T>::size_ * 2 + (allocator<T>::size_ == 0 ? 1 : 0);
		T * nstack = newcopy(allocator<T>::ptr_, allocator<T>::count_, allocator<T>::size_);
		delete[] allocator<T>::ptr_;
		allocator<T>::ptr_ = nstack;
		allocator<T>::size_ = size;
	}
	allocator<T>::ptr_[allocator<T>::count_] = value;
	++allocator<T>::count_;


}
template <typename T>
const T& stack<T>::top()
{
	if (allocator<T>::count_ > 0) {
		return allocator<T>::ptr_[allocator<T>::count_ - 1];
	}
	else throw("Stack is empty");
}

template <typename T>
void stack<T>::pop()
{
	if (allocator<T>::count_> 0) {
		--allocator<T>::count_;
	}
	else throw ("Stack is empty");
}
template <typename T>
size_t stack<T>::count() const
{
	return allocator<T>::count_;
}
template<typename T>
bool stack<T>::empty()
{
	return(allocator<T>::count_ == 0);
}
#endif // Stack_cpp
