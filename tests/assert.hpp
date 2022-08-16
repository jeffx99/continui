#define EXPECT(x, y) { if (x != y) {std::cout << __FUNCTION__ << " failed on line " << __LINE__ << ": expected: " << x << ", found: " << y << std::endl; } }
