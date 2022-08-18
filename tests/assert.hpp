#pragma once
#include <iostream>
#define EXPECT(x, y) { if ((x) != (y)) {std::cout << __FUNCTION__ << " failed on line " << __LINE__ << ": expected: " << x << ", found: " << y << std::endl; } }
#define VERIFY(x) { if (!(x)) {std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; } }
