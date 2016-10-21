#include <stack.hpp>
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("Stack: init", "[init]") {
	stack<size_t> a;
	REQUIRE(sizeof(a) != 0);
} 
