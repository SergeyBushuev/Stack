#include <stack.hpp>
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("Stack: init", "[init]") {
	bool mark=false;
	stack<size_t> a;
	if(sizeof(a) != 0)
	{
		mark=true;
	}
	REQUIRE(mark);
} 
SCENARIO("Stack count", "[count]"){
	bool mark=false;
	stack<int> st;
	if ((st.count()==0))
	{
		mark=true;
	}
	st.push(1);
	if ((st.count()==1))
	{
		mark=true;
	}
	REQUIRE(mark);
}

SCENARIO("Stack push", "[push]"){
	bool mark=false;
	stack<int> st;
	st.push(1);
	if ((st.count()==1)&&(st.top()==1))
	{
		mark=true;
	}
	REQUIRE(mark);
}

SCENARIO("Stack pop", "[pop]"){
	bool mark=false;
	stack<int> st;
	st.push(123);
	st.pop();
	if (st.count()==0)
	{
		mark=true;
	}
	REQUIRE(mark);
}

SCENARIO("Stack top", "[top]"){
	bool mark=false;
	stack<int> st;
	st.push(11);
	st.push(22);
	int v=st.top();
	if (v==22)
	{
		mark=true;
	}
	REQUIRE(mark);
}

SCENARIO("Assign", "[assign]"){
	bool mark=false;
	stack<int> st;
	st.push(10);
	stack<int> st_;
	st_=st;
	std::cout << "st_.count_=" << st_.count() << std::endl;
	std::cout << "st_.top=" << st_.top() << std::endl;
	if ((st_.top()==st.top())
	{
		mark=true;
	}
	REQUIRE(mark);
}

SCENARIO("Copy","[copy]"){
	bool mark=false;
	stack<int> st;
	st.push(10);
	stack<int> st_=st;
	std::cout << "st_.count_=" << st_.count() << std::endl;
	std::cout << "st_.top=" << st_.top() << std::endl;
	if ((st_.top()==st.top())
	{
		mark=true;
	}
	REQUIRE(mark);
}

SCENARIO("Empty","[empty]"){
	bool mark=false;
	bool mark_empty,mark_full;
	stack<int> st;
	mark_empty=st.empty();
	st.push(10);
	mark_full=st.empty();
	if ((mark_empty==true) && (mark_full==false))
	{
		mark=true;
	}
	REQUIRE(mark);
}
