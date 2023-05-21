#include <iostrea>

class UTest
{
public:
	template<class TestFunction>
	void runTest(TestFunction function)
	{
	}
	~UTest()
	{
		if (_failedTestsCount > 0) {
			cerr << _failedTestsCount << " tests failed. Terminate.\n";
			exit(1);
		}
	}

private:
	size_t _failedTestsCount { 0 };
};
