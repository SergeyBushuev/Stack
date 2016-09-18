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
  stack<int> stack;
  stack.push(1);
  stack<int> stackN;
  stackN=stack;
  REQUIRE(stack.count()==1);
  REQUIRE(stack.pop()==1);
}
