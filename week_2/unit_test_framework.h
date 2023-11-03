#include <iostream>
#include <set>
#include <map>
#include <string>
#include <exception>
#include <sstream>


template <class T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s)
{
    os << "{ ";
    
    bool first = true;

    for (const auto &item : s) {
        if (!first) {
            os << ", ";
        }
        first = false;

        os << item;
    }

    os << " }";

    return os;
}

template <class K, class V>
std::ostream &operator<<(std::ostream &os, std::map<K, V> m)
{
    os << "{ ";

    bool first = true;

    for (const auto &item : m) {
        if (!first) {
            os << ", ";
        }
        first = false;

        os << item.first << ": " << item.second;
    }

    os << " }";

    return os;
}

template <class T, class U>
void assertEqual(const T &t, const U &u, const std::string &hint)
{
    if (t != u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " hint: " << hint;
        
        throw std::runtime_error(os.str());
    }
}

inline void assert(bool b, const std::string &hint)
{
    assertEqual(b, true, hint);
}

class TestRunner
{
public:
    template <class TestFunc>
    void runTest(TestFunc func, const std::string testName)
    {
        try {
            func();
            std::cerr << testName << " OK" << '\n';
        } catch (std::runtime_error &e) {
            ++_failCount;
            std::cerr << testName << " fail: " << e.what()  << '\n';
        }
    }

    ~TestRunner() 
    {
        if (_failCount > 0) {
            std::cerr << _failCount << " unit tests failed. Terminate" << '\n';
            exit(1);
        }
    }

private:
    size_t _failCount { 0 };
};