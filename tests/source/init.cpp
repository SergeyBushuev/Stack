#include <Stack.cpp>
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("Stack: init", "[init]") {
	stack<size_t> a;
	REQUIRE(sizeof(a) != 0);
} 


SCENARIO("push", "[push]"){ 
  stack<int> stack;
  stack.push(1);
  REQUIRE(stack.count()==1);
  REQUIRE(stack.top()==1);
}
