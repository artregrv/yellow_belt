#include <iostream>
#include <string>
#include <exception>

class TestRunner
{
public:

    /*!
     * \brief tries to run test, test function should 
     * throw exception if test failed 
     */
    template<class TestFunction>
    void RunTest(TestFunction function, const std::string &testName)
    {
        try {
            function();
            std::cerr << testName << " OK" << std::endl;
        } catch (std::runtime_error &error) {
            ++_failCount;
            std::cerr << testName << " fail: " << error.what() << std::endl;
        }
    }

    ~TestRunner()
    {
        if (_failCount > 0) {
            std::cerr << _failCount << " unit test failed. Terminate" << std::endl;
            exit(1);
        } else {
            std::cerr << "All tests passed" << std::endl;
        }
    }

private:
    size_t _failCount { 0 };
};