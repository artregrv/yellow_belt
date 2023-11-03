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

// class Person
// {
// public:
// 	void ChangeFirstName(int year, const std::string &first_name)
// 	{
// 		_first_names[year] = first_name;
// 	};

// 	void ChangeLastName(int year, const std::string &last_name)
// 	{
// 		_last_names[year] = last_name;
// 	};

// 	std::string GetFullName(int year)
// 	{
// 		std::string first_name_result = "";
// 		std::string last_name_result = "";

// 		for (const auto &first_name : _first_names) {
// 			if (first_name.first <= year) {
// 				first_name_result = first_name.second;
// 				break;
// 			}	
// 		}
		
// 		for (const auto &last_name : _last_names) {
// 			if (last_name.first <= year) {
// 				last_name_result = last_name.second;
// 				break;
// 			}
// 		} 

// 		if ((first_name_result == "") && (last_name_result == "")) {
// 			return "Incognito";
// 		} else if (first_name_result == "") {
// 			return last_name_result + " with unknown first name";
// 		} else if (last_name_result == "") {
// 			return first_name_result + " with unknown last name";
// 		} else {
// 			return first_name_result + ' ' +  last_name_result;
// 		}
// 	};

// private:
// 	std::map<int, std::string, std::greater<int>> _first_names;
// 	std::map<int, std::string, std::greater<int>> _last_names;
// };

void test_ChangeFirstName0()
{
	Person p;
	p.ChangeFirstName(0, "firstName0");

	assertEqual(p.GetFullName(0), "firstName0 with unknown last name", "only first name");
}

void test_ChangeFirstName1()
{
	Person p;
	p.ChangeFirstName(1, "firstName1");

	assertEqual(p.GetFullName(0), "Incognito", "should be incognito");
}

void test_ChangeLastName0()
{
	Person p;
	p.ChangeLastName(0, "lastName0");

	assertEqual(p.GetFullName(0), "lastName0 with unknown first name", "only last name");
}

void test_ChangeLastName1()
{
	Person p;
	p.ChangeLastName(1, "lastName0");

	assertEqual(p.GetFullName(0), "Incognito", "should be incognito");
}

void test_FullName0()
{
	Person p;
	p.ChangeFirstName(0, "firstName0");
	p.ChangeLastName(0, "lastName0");

	assertEqual(p.GetFullName(0), "firstName0 lastName0", "full name");
}

void test_FullName1()
{
	Person p;
	p.ChangeFirstName(1, "firstName1");
	p.ChangeLastName(1, "lastName1");

	assertEqual(p.GetFullName(0), "Incognito", "should be incognito");
}

void test_FullName2()
{
	Person p;
	p.ChangeFirstName(1, "firstName1");
	p.ChangeLastName(5, "lastName5");
	p.ChangeFirstName(10, "firstName10");

	assertEqual(p.GetFullName(20), "firstName10 lastName5", "first name changed twice");
}

void test_FullName3()
{
	Person p;
	p.ChangeLastName(1, "lastName1");
	p.ChangeFirstName(5, "firstName5");
	p.ChangeLastName(10, "lastName10");

	assertEqual(p.GetFullName(20), "firstName5 lastName10", "last name changed twice");
}


int main()
{
	TestRunner testRunner;
	testRunner.runTest(test_ChangeFirstName0, "test_ChangeFirstName0");
	testRunner.runTest(test_ChangeFirstName1, "test_ChangeFirstName1");
    testRunner.runTest(test_ChangeLastName0, "test_ChangeLastName0");
	testRunner.runTest(test_ChangeLastName1, "test_ChangeLastName1");
	testRunner.runTest(test_FullName0, "test_FullName0");
	testRunner.runTest(test_FullName1, "test_FullName1");
	testRunner.runTest(test_FullName2, "test_FullName2");
	testRunner.runTest(test_FullName3, "test_FullName3");
	return 0;
}