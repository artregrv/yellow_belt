#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

template<class Collection>
std::string join(const Collection &collection, const char d)
{
	std::stringstream stream;
	bool first = true;

	for (const auto &item : collection) {
		if (!first) {
			stream << d << ' ';
		}
		stream << item;

		first = false;
	}
	
	return stream.str();
}

template<class First, class Second>
std::ostream &operator<<(std::ostream &stream, const std::pair<First, Second> &p)
{
	stream << "{ " << p.first << ", " << p.second << " }";
	return stream;
}

template<class Key, class Value>
std::ostream &operator<<(std::ostream &stream, const std::map<Key, Value> &m)
{
	stream << "{ " << join(m, ',') << " }";	
	return stream;
}

template<class T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &v)
{
	stream << "{ " << join(v, ',') << " }";
	return stream;
}
