#include "extout.h"

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
