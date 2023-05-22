#include <exception>
#include <iostream>
#include <sstream>

template<class Lhs, class Rhs>
void assertEqual(const Lhs &lhs, const Rhs &rhs, const std::string &hint)
{
	if (lhs != rhs) {
		std::ostringstream stream;
		stream << "Assertion failed: " << lhs << " != " << rhs << " hint: " << hint;
		throw std::runtime_error(stream.str());
	}
}

void asset(bool value, const std::string &hint)
{
	assertEqual(value, true, hint);
}

class UTest
{
public:
	template<class TestFunction>
	void runTest(TestFunction function, const std::string &functionName)
	{
		try {
			function();
			std::cerr << functionName << " OK\n"; 
		} catch (std::runtime_error &error) {
			++_failedTestsCount;
			std::cerr << error.what() << '\n';
		}
	}

	~UTest()
	{
		if (_failedTestsCount > 0) {
			std::cerr << _failedTestsCount << " tests failed. Terminate.\n";
			exit(1);
		}
	}

private:
	size_t _failedTestsCount { 0 };
};

int GetDistinctRealRootCount(double a, double b, double c) 
{
	if (a == 0) {
		if (b == 0) {
			return 0;
		}
		return 1;
	} 
	
	int d = b * b - 4 * a * c;

	if (d == 0) {
		return 1;
	} else if (d > 0) {
		return 2;
	} 
	
	return 0;
}

void testGetDistinctRealRootCount()
{
	assertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "a = 0, b = 0, c = 1");
	assertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "a = 0, b = 1, c = 1");
	assertEqual(GetDistinctRealRootCount(1, 1, 1), 0, "a = 1, b = 1, c = 1");
	assertEqual(GetDistinctRealRootCount(1, 3, 1), 2, "a = 1, b = 3, c = 1");
	assertEqual(GetDistinctRealRootCount(1, 2, 1), 1, "a = 1, b = 2, c = 1");
}

void testAll()
{
	UTest ut;
	ut.runTest(testGetDistinctRealRootCount, "testGetDistinctRealRootCount");
}

int main()
{
	testAll();

	return 0;
}
