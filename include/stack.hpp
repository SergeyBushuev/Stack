#include <cstring>
#include <iostream>
#include <memory>

class bitset
{
public:
	explicit
	bitset(size_t size) /*strong*/;

	bitset(bitset const & other) = delete;
	auto operator =(bitset const & other)->bitset & = delete;

	bitset(bitset && other) = delete;
	auto operator =(bitset && other)->bitset & = delete;

	auto set(size_t index) /*strong*/ -> void;
	auto reset(size_t index) /*strong*/ -> void;
	auto test(size_t index) /*strong*/ -> bool;

	auto size() /*noexcept*/ -> size_t;
	auto counter() /*noexcept*/ -> size_t;

private:
	std::unique_ptr<bool[]>  ptr_;
	size_t size_;
	size_t counter_;
};

bitset::bitset(size_t size) : ptr_(std::make_unique<bool[]>(size)), size_(size), counter_(0)
{}

auto bitset::set(size_t index)->void 
{ 
	if (index < size_)
	{ 
		ptr_[index] = true; 
		++counter_; 
	} 
    else 
    throw("out of bitset"); 
}

auto bitset::reset(size_t index)->void 
{ 
	if (index < size_) 
	{ 
		ptr_[index] = false; 
		--counter_; 
	} 
	else 
		throw("out of bitset"); }

auto bitset::test(size_t index)->bool 
{ 
	if (index < size_) 
		return !ptr_[index]; 
	else throw("out os bitset"); 
}

auto bitset::size()->size_t
{ 
	return size_; 
}

auto bitset::counter()->size_t
{ 
	return counter_; 
}



template <typename T>
class allocator
{
public:
	explicit
	allocator(std::size_t size = 0) /*strong*/;
	allocator(allocator const & other) /*strong*/;
	auto operator =(allocator const & other)->allocator & = delete;
	~allocator();

	auto resize() /*strong*/ -> void;

	auto construct(T * ptr, T const & value) /*strong*/ -> void;
	auto destroy(T * ptr) /*strong*/ -> void;

	auto get() /*noexcept*/ -> T *;
	auto get() const /*noexcept*/ -> T const *;

	auto count() const /*noexcept*/ -> size_t;
	auto full() const /*noexcept*/ -> bool;
	auto empty() const /*noexcept*/ -> bool;
	auto swap(allocator & other) /*noexcept*/ -> void;
private:
	auto destroy(T * first, T * last) /*strong*/ -> void;
	
	T * ptr_;
	size_t size_;
	std::unique_ptr<bitset> map_;
};

template <typename T>
allocator<T>::allocator(size_t size) : ptr_((T*)operator new(size)), size_(size), map_(std::make_unique<bitset>(size))
{}

template<typename T> /*noexcept*/
allocator<T>::~allocator() {
	if (this->count() > 0)
	{
	    allocator<T>::destroy(ptr_, ptr_ + size_);
	    operator delete(ptr_);
	}
	
}

template <typename T>
auto allocator<T>::construct(T *ptr,T const & val) ->void
{
	if (ptr >= ptr_ && ptr < ptr_ + size_ && map_->test(ptr - ptr_)){
		new(ptr)T(val);
		map_->set(ptr - ptr_);
	}
	else { throw("error"); }
}

template <typename T>
auto allocator<T>::destroy(T *ptr)-> void
{
	ptr->~T();
	map_->reset(ptr - ptr_);
		
}

template<typename T>
auto allocator<T>::resize()->void
{
	allocator<T> all(size_ * 2 + (size_ == 0));
	for (size_t i = 0; i < size_; ++i) 
		all.construct(all.get() + i, ptr_[i]);
	this->swap(all);
}

template<typename T>
auto allocator<T>::get()-> T* 
{ 
	return ptr_; 
}

template<typename T>
auto allocator<T>::get() const -> T const * 
{ 
	return ptr_; 
}

template<typename T>
allocator<T>::allocator(allocator const& other) :allocator<T>(other.size_)
{
	for (size_t i = 0; i < other.size(); ++i) 
		construct(ptr_ + i, other.ptr_[i]);
}

template <typename T>
auto allocator<T>::destroy(T *first,T *last)-> void
{
	if(first>last)
	throw std::logic_error("errror");
	for (; first != last; ++first)
	{
		destroy(first);
	}
	
}

template<typename T>
auto allocator<T>::count() const -> size_t
{ 
	return map_->counter(); 
}

template<typename T>
auto allocator<T>::full() const -> bool 
{
	return (map_->counter() == size_); 
}

template<typename T>
auto allocator<T>::empty() const -> bool 
{ 
	return (map_->counter() == 0); 
}

	
template<typename T> /*noexcept*/
auto allocator<T>::swap(allocator & other) -> void {
	std::swap(ptr_, other.ptr_);
	std::swap(size_, other.size_);
	std::swap(map_, other.map_);
}

template <typename T>
class stack
{
public:
	explicit
	stack(size_t size = 0);
	auto operator =(stack const & other) /*strong*/ -> stack &;
	

	auto empty() const /*noexcept*/ -> bool;
	auto count() const /*noexcept*/ -> size_t;

	auto push(T const & value) /*strong*/ -> void;
	auto pop() /*strong*/ -> void;
	auto top() /*strong*/ -> T &;
	auto top() const /*strong*/ -> T const &;

private:
	allocator<T> allocator_;

	auto throw_is_empty()/*strong*/ const -> void;
};


template <typename T>/*noexcept*/
stack<T>::stack(size_t size) : allocator_(size)
{};



template <typename T>
auto stack<T>::operator=(const stack & st)-> stack &/*strong*/
{
	if (this != &st)
	{
		(allocator<T>(st.allocator_)).swap(this->allocator_);
	}
	return *this;
};

template <typename T>
size_t  stack<T>::count() const/*noexcept*/
{
	return allocator_.count();
};

template <typename T>
void stack<T>::push(T const &value)/*strong*/
{
	if (allocator_.full())
		allocator_.resize();
	allocator_.construct(allocator_.get() + this->count(), value);
};

template <typename T>
void stack<T>::pop()/*strong*/
{
	if (allocator_.count() == 0)
	{
		this->throw_is_empty();
	}
	allocator_.destroy(allocator_.get() + (this->count()-1));
};

template <typename T>
auto stack<T>::top()-> T&/*strong*/
{
	if (this->count() > 0) 
		return(allocator_.get() [count() - 1]);
	else this->throw_is_empty();
}

template<typename T>
auto stack<T>::top()const->T const & 
{
	if (this->count() > 0) 
		return(allocator_.get()[count() - 1]);
	else this->throw_is_empty();
}

template <typename T>/*noexcept*/
auto stack<T>::empty()const->bool 
{
	return(allocator_.empty() == 1);
}

template<typename T>
auto stack<T>::throw_is_empty()const->void
{
	throw std::logic_error("ERROR"); 
}
