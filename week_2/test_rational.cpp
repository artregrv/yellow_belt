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

// class Rational
// {
// public:
// 	Rational() :
// 		_numerator(0),
// 		_denominator(1)
// 	{}

// 	Rational(int numerator, int denominator)
// 	{
// 		if (numerator == 0) {
// 			_numerator = 0;
// 			_denominator = 1;
// 		} else {
// 			int sign = (numerator / abs(numerator)) * (denominator / abs(denominator));

// 			numerator = abs(numerator);
// 			denominator = abs(denominator);

// 			int tmp_gcd = gcd(numerator, denominator);

// 			_numerator = numerator / tmp_gcd;
// 			_denominator = denominator / tmp_gcd;	
			
// 			_numerator *= sign;
// 		}
// 	}

// 	int Numerator() const
// 	{
// 		return _numerator;
// 	}

// 	int Denominator() const
// 	{
// 		return _denominator;
// 	}

// private:
// 	int gcd(int lhs, int rhs)
// 	{
// 		while ((lhs != rhs)) {
// 			if (lhs > rhs) {
// 				lhs -= rhs;
// 			} else {
// 				rhs -= lhs;
// 			}
// 		}

// 		return lhs;
// 	}
	
// 	int _numerator;
// 	int _denominator;
// };

void test_DefaultConstructorNumerator()
{
    Rational r;

    assertEqual(r.Numerator(), 0, "numerator is 0"); 
}

void test_DefaultConstructorDenominator()
{
    Rational r;

    assertEqual(r.Denominator(), 1, "denominator is 1"); 
}

void test_SimpleRationalNumerator()
{
    Rational r(1, 2);

    assertEqual(r.Numerator(), 1, "denominator is 1"); 
}

void test_SimpleRationalDenominator()
{
    Rational r(1, 2);

    assertEqual(r.Denominator(), 2, "denominator is 1"); 
}

void test_ComplexRationalNumerator()
{
    Rational r(8, 16);

    assertEqual(r.Numerator(), 1, "denominator is 1"); 
}

void test_ComplexRationalDenominator()
{
    Rational r(8, 16);

    assertEqual(r.Denominator(), 2, "denominator is 1"); 
}

void test_NegativeNumeratorNumerator()
{
    Rational r(-3, 4);

    assertEqual(r.Numerator(), -3, "denominator is 1"); 
}

void test_NegativeNumeratorDenominator()
{
    Rational r(-3, 4);

    assertEqual(r.Denominator(), 4, "denominator is 1"); 
}

void test_NegativeDenominatorNumerator()
{
    Rational r(3, -4);

    assertEqual(r.Numerator(), -3, "denominator is 1"); 
}

void test_NegativeDenominatorDenominator()
{
    Rational r(3, -4);

    assertEqual(r.Numerator(), -3, "denominator is 1"); 
}

void test_SimplePositiveRationalNumerator()
{
    Rational r(-3, -4);

    assertEqual(r.Numerator(), 3, "denominator is 1"); 
}

void test_SimplePositiveRationalDenominator()
{
    Rational r(-3, -4);

    assertEqual(r.Denominator(), 4, "denominator is 1"); 
}

void test_ComplexPositiveRationalNumerator()
{
    Rational r(-3, -12);

    assertEqual(r.Numerator(), 1, "denominator is 1"); 
}

void test_ComplexPositiveRationalDenominator()
{
    Rational r(-3, -12);

    assertEqual(r.Denominator(), 4, "denominator is 1"); 
}

void test_ComplexNegativeRationalNumerator1()
{
    Rational r(3, -12);

    assertEqual(r.Numerator(), -1, "denominator is 1"); 
}

void test_ComplexNegativeRationalDenominator1()
{
    Rational r(3, -12);

    assertEqual(r.Denominator(), 4, "denominator is 1"); 
}

void test_ComplexNegativeRationalNumerator2()
{
    Rational r(-3, 12);

    assertEqual(r.Numerator(), -1, "denominator is 1"); 
}

void test_ComplexNegativeRationalDenominator2()
{
    Rational r(-3, 12);

    assertEqual(r.Denominator(), 4, "denominator is 1"); 
}

void test_ZeroNumeratorNumerator()
{
    Rational r(0, 100);

    assertEqual(r.Numerator(), 0, "numerator is 0");
}

void test_ZeroNumeratorDenominator()
{
    Rational r(0, 100);

    assertEqual(r.Denominator(), 1, "numerator is 0");
}


int main()
{
    TestRunner testRunner;

    testRunner.runTest(test_DefaultConstructorNumerator, "test_DefaultConstructorNumerator");
    testRunner.runTest(test_DefaultConstructorDenominator, "test_DefaultConstructorDenominator");
    testRunner.runTest(test_SimpleRationalNumerator, "test_SimpleRationalNumerator");
    testRunner.runTest(test_SimpleRationalDenominator, "test_SimpleRationalDenominator");
    testRunner.runTest(test_ComplexRationalNumerator, "test_ComplexRationalNumerator");
    testRunner.runTest(test_ComplexRationalDenominator, "test_ComplexRationalDenominator");
    testRunner.runTest(test_NegativeNumeratorNumerator, "test_NegativeNumeratorNumerator");
    testRunner.runTest(test_NegativeNumeratorDenominator, "test_NegativeNumeratorDenominator");
    testRunner.runTest(test_NegativeDenominatorNumerator, "test_NegativeDenominatorNumerator");
    testRunner.runTest(test_NegativeDenominatorDenominator, "test_NegativeDenominatorDenominator");
    testRunner.runTest(test_SimplePositiveRationalNumerator, "test_SimplePositiveRationalNumerator");
    testRunner.runTest(test_SimplePositiveRationalNumerator, "test_SimplePositiveRationalNumerator");
    testRunner.runTest(test_ComplexPositiveRationalNumerator, "test_ComplexPositiveRationalNumerator");
    testRunner.runTest(test_ComplexPositiveRationalDenominator, "test_ComplexPositiveRationalDenominator");
    testRunner.runTest(test_ComplexNegativeRationalNumerator1, "test_ComplexNegativeRationalNumerator1");
    testRunner.runTest(test_ComplexNegativeRationalDenominator1, "test_ComplexNegativeRationalDenominator1");
    testRunner.runTest(test_ComplexNegativeRationalNumerator2, "test_ComplexNegativeRationalNumerator2");
    testRunner.runTest(test_ComplexNegativeRationalDenominator2, "test_ComplexNegativeRationalDenominator2");
    testRunner.runTest(test_ZeroNumeratorNumerator, "test_ZeroNumeratorNumerator");
    testRunner.runTest(test_ZeroNumeratorDenominator, "test_ZeroNumeratorDenominator");

    return 0;
}