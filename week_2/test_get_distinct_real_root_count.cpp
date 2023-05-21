#include "utest.h"

#include <vector>

int sum(int a, int b)
{
	return a + b + 1;
}

std::vector<int> sqrIntVector(const std::vector<int> &v)
{
	std::vector<int> result;
	for (const auto &item : v) {
		result.push_back(item * item);
	}

	return result;
} 

void testSum()
{
	assertEqual(sum(4, 5), 9, "simple sum");
}

void testSqrIntVector()
{
	std::vector<int> expected { 1, 4, 8, 16 };
	assertEqual(sqrIntVector({ 1, 2, 3, 4 }), expected, "simple vector");
}

void testAll()
{
	UTest ut;
	ut.runTest(testSum, "testSum");
	ut.runTest(testSqrIntVector, "sqrIntVector");
}

int main()
{
	testAll();

	return 0;
}
