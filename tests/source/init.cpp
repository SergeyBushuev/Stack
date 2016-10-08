#include <Stack.cpp>
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("Stack: init", "[init]") {
	stack<size_t> a;
	REQUIRE(sizeof(a) != 0);
} 

SCENARIO("push", "[push]"){ 
  stack<size_t> stack;
  stack.push(1);
  REQUIRE(stack.count()==1);
  REQUIRE(stack.top()==1);
}

SCENARIO("pop", "[pop]"){
  stack<size_t> stack;
  stack.push(1);
  REQUIRE(stack.count()==1);
  REQUIRE(stack.top()==1);
}
SCENARIO("copy", "[copy]"){
  stack<size_t> stack, stack2;
  stack.push(1);
  stack2=stack;
  REQUIRE(stack2.count()==1);
  REQUIRE(stack2.top()==1);
}
SCENARIO("copy2", "[copy2]"){
  stack<size_t> stack1;
  stack1.push(1);
  stack<size_t> stack2= stack1;
  REQUIRE(stack2.count()==1);
  REQUIRE(stack2.top()==1);
}
