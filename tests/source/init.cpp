#include <Stack.cpp>
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("count", "[count]"){
  stack<int> stack;
  stack.push(1);
  REQUIRE(stack.count()==1);
}

SCENARIO("push", "[push]"){
  stack<int> stack;
  stack.push(1);
  REQUIRE(stack.count()==1);
  REQUIRE(stack.pop()==1);
}

SCENARIO("pop", "[pop]"){
  stack<int> stack;
  stack.push(1);
  REQUIRE(stack.count()==1);
  REQUIRE(stack.pop()==1);
}
SCENARIO("copy", "[copy]"){
  stack<int> stack, stack2;
  stack.push(1);
  stack2=stack;
  REQUIRE(stack2.count()==1);
  REQUIRE(stack2.pop()==1);
}
SCENARIO("copy2", "[copy2]"){
  stack<int> stack1;
  stack.push(1);
  stack<int> stack2= stack1;
  REQUIRE(stack2.count()==1);
  REQUIRE(stack2.pop()==1);
}
