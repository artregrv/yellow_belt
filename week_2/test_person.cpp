#include <exception>
#include <iostream>
#include <map>
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

class Person
{
public:
	void ChangeFirstName(int year, const std::string &first_name)
	{
		_first_names[year] = first_name;
	};

	void ChangeLastName(int year, const std::string &last_name)
	{
		_last_names[year] = last_name;
	};

	std::string GetFullName(int year)
	{
		std::string first_name_result = "";
		std::string last_name_result = "";

		for (const auto &first_name : _first_names) {
			if (first_name.first <= year) {
				first_name_result = first_name.second;
				break;
			}	
		}
		
		for (const auto &last_name : _last_names) {
			if (last_name.first <= year) {
				last_name_result = last_name.second;
				break;
			}
		} 

		if ((first_name_result == "") && (last_name_result == "")) {
			return "Incognito";
		} else if (first_name_result == "") {
			return last_name_result + " with unknown first name";
		} else if (last_name_result == "") {
			return first_name_result + " with unknown last name";
		} else {
			return first_name_result + ' ' +  last_name_result;
		}
	};

private:
	std::map<int, std::string, std::greater<int>> _first_names;
	std::map<int, std::string, std::greater<int>> _last_names;
};

void testGetFullName()
{
	{
		Person p;
		assertEqual(p.GetFullName(2000), "Incognito", "no name added");
	}
	{
		Person p;
		p.ChangeFirstName(2005, "FName2005");
		assertEqual(p.GetFullName(2005), "FName2005 with unknown last name", "fname 2005 2005");
	}
	{
		Person p;
		p.ChangeFirstName(2005, "FName2005");
		assertEqual(p.GetFullName(2004), "Incognito", "fname 2005 2004");
	}
	{
		Person p;
		p.ChangeFirstName(2005, "FName2005");
		assertEqual(p.GetFullName(2006), "FName2005 with unknown last name", "fname 2005 2006");
	}

}

void testAll()
{
	UTest ut;
	ut.runTest(testGetFullName, "testGetFullName");
}

int main()
{
	testAll();

	return 0;
}
