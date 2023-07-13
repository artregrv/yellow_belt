#include <exception>
#include <iostream>
#include <map>
#include <string>

template<typename Key, typename Value>
Value &GetRefStrict(std::map<Key, Value> &m, const Key k)
{
	if (m.count(k) == 0) {
		throw std::runtime_error("There is no such element!");
	}

	return m[k];
}

int main()
{
	std::map<int, std::string> m = {{0, "value"}};
	std::string& item = GetRefStrict(m, 0);
	item = "newvalue";
	std::cout << m[0] << std::endl; // выведет newvalue
	return 0;
}
