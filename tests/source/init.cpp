#include <Stack.cpp>
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("count", "[count]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("push", "[push]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
  REQUIRE(s.pop()==1);
}

SCENARIO("pop", "[pop]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
  REQUIRE(s.pop()==1);
}
