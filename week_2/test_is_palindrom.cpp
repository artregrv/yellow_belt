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

bool IsPalindrom(std::string s)
{
	size_t size = s.size();

	if (size == 0) {
		return true;
	}
	
	for (size_t i = 0; i < size / 2; ++i) {
		if (s.at(i) != s.at(size - i - 1)) {
			return false;
		}
	}

	return true;
}

void test_EmptyString()
{
    std::string s { "" };

    assert(IsPalindrom(s), "empty string");
}

void test_OneSymbol()
{
    std::string s { "a" };

    assert(IsPalindrom(s), "one simbol");
}

void test_OddPalindrom()
{
    std::string s { "aaabbbaaa" };

    assert(IsPalindrom(s), "odd palindrom");
}

void test_EvenPalindrom()
{
    std::string s { "aaabbaaa" };

    assert(IsPalindrom(s), "odd palindrom");
}

void test_SkipFirtSymbol()
{
    std::string s { "saaabbaaa" };

    assert(!IsPalindrom(s), "skip firt symbol");
}

void test_SkipLastSymbol()
{
    std::string s { "aaabbaaas" };

    assert(!IsPalindrom(s), "skip last symbol");
}

void test_SkipCenter1()
{
    std::string s { "aaabxzbaaa" };

    assert(!IsPalindrom(s), "skip center");
}

void test_SkipCenter2()
{
    std::string s { "aaab-!baaa" };

    assert(!IsPalindrom(s), "skip center");
}

void test_SkipCenter3()
{
    std::string s { "adjahkjdhfklahfdkhasfha" };

    assert(!IsPalindrom(s), "skip center");
}

void test_SkipSpaces1()
{
    std::string s { "aaab baaa" };

    assert(IsPalindrom(s), "skip center");
}

void test_SkipSpaces2()
{
    std::string s { "   aaabbaaa" };

    assert(!IsPalindrom(s), "skip center");
}

void test_SkipSpaces3()
{
    std::string s { "aaabbaaa    " };

    assert(!IsPalindrom(s), "skip center");
}

void test_TwoSymbos()
{
    std::string s { "ab" };

    assert(!IsPalindrom(s), "one simbol");
}

void test_LongValidPalindrom()
{
    std::string s { "qwertyuiop!@#$%^&*(+(*&^%$#@!poiuytrewq" };

    assert(IsPalindrom(s), "long valid");
}

void test_LongInvalidPalindrom()
{
    std::string s { "qwertyuiop!@#$%^&*)boo)*&^%$#@!poiuytrewq" };

    assert(!IsPalindrom(s), "long valid");
}

int main()
{
    TestRunner testRunner;

    testRunner.runTest(test_EmptyString, "test_EmptyString");
    testRunner.runTest(test_OneSymbol, "test_OneSymbol");
    testRunner.runTest(test_OddPalindrom, "test_OddPalindrom");
    testRunner.runTest(test_EvenPalindrom, "test_EvenPalindrom");
    testRunner.runTest(test_SkipFirtSymbol, "test_SkipFirtSymbol");
    testRunner.runTest(test_SkipLastSymbol, "test_SkipLastSymbol");
    testRunner.runTest(test_SkipCenter1, "test_SkipCenter1");
    testRunner.runTest(test_SkipCenter2, "test_SkipCenter2");
    testRunner.runTest(test_SkipCenter3, "test_SkipCenter3");
    testRunner.runTest(test_SkipSpaces1, "test_SkipSpaces1");
    testRunner.runTest(test_SkipSpaces2, "test_SkipSpaces2");
    testRunner.runTest(test_SkipSpaces3, "test_SkipSpaces3");
    testRunner.runTest(test_TwoSymbos, "test_TwoSymbos");
    testRunner.runTest(test_LongValidPalindrom, "test_LongValidPalindrom");
    testRunner.runTest(test_LongInvalidPalindrom, "test_LongInvalidPalindrom");


    return 0;
}