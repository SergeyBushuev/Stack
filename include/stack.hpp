#include <cstring>
#include <iostream>
#include <memory>
#pragma once

template<typename T>
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

//-------------------------------------------------------------------------------------------------------------------------------

template<typename T> 
allocator<T>::allocator(size_t size) :
	ptr_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))){
}

template<typename T> 
allocator<T>::~allocator() {
	operator delete(ptr_);
}

template<typename T> 
auto allocator<T>::swap(allocator & other) -> void {
	std::swap(ptr_, other.ptr_);
	std::swap(count_, other.count_);
	std::swap(size_, other.size_);
}

//-------------------------------------------------------------------------------------------------------------------------------

template <typename T>
class stack : private allocator<T>
{
public:
	stack(size_t size = 0);										/*noexcept*/
	stack(const stack &); 							/*strong*/
	~stack(); 										/*noexcept*/
	size_t count() const; 							/*noexcept*/
	void push(T const &); 							/*strong*/
	void pop(); 									/*strong*/
	const T& top(); 								/*strong*/
	stack & operator=(stack & newst);				/*strong*/
	bool empty() const; 									/*noexcept*/
};

//-------------------------------------------------------------------------------------------------------------------------------


template <typename T1, typename T2>
void construct(T1 * ptr, T2 const & value) {
    new(ptr) T1 (value);
}

template <typename T>
void destroy(T * ptr) noexcept
{
    ptr->~T();
}

template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept
{
    for (; first != last; ++first) {
        destroy(&*first);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------

template<typename T>
stack<T>::stack(size_t s) : allocator<T>(s) {}

template<typename T>
stack<T>::~stack()
{
	destroy(allocator<T>::ptr_, allocator<T>::ptr_ + allocator<T>::count_);
}

template <typename T>
stack<T>::stack(const stack& otherStack) : allocator<T>(otherStack.size_) {
	if (otherStack.count_ != 0) {
		stack<T> array(otherStack.size_);
		for (size_t t = 0; t < otherStack.count_; ++t) {
                           construct(array.ptr_ + t, otherStack.ptr_[t]);
                           array.count++;
                                                               }
		std::swap(array.ptr_, this->ptr_);
	}
	this->count_ = otherStack.count_;
};

template<typename T>
stack<T>& stack<T>::operator=(stack & newst) {
	if (this != &newst) {
		(stack(newst)).swap(*this);
	}
	return *this;
}

template<typename T>
void stack<T>::push(const T &value)
{
	if (this->size_ == this->count_) {
		if (this->size_ == 0) { this->size_ = 1; }
		size_t size = this->size_ * 2;
		stack<T> array(size);
		for (size_t t = 0; t < this->count_; ++t) {
			construct(array.ptr_ + t, this->ptr_[t]);
		}
		std::swap(array.ptr_, this->ptr_);
		this->size_ = size;
	}
	construct(this->ptr_ + this->count_, value);
        ++this->count_;

}

template<typename T>
const T& stack<T>::top()
{
	if (allocator<T>::count_ > 0) {
		return allocator<T>::ptr_[allocator<T>::count_ - 1];
	}
	else throw("Stack is empty");
}

template<typename T>
void stack<T>::pop()
{
	if (allocator<T>::count_> 0) {
		--allocator<T>::count_;
	}
	else throw ("Stack is empty");
}

template<typename T>
size_t stack<T>::count() const
{
	return allocator<T>::count_;
}

template<typename T>
bool stack<T>::empty() const
{
	return(allocator<T>::count_ == 0);
}
