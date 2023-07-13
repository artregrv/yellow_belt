#include <iostream>
#include <map>
#include <utility>
#include <vector>

template<typename T>
T Sqr(const T &t);

template<typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second> &p);

template<typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second> &p);

template<typename T>
std::vector<T> Sqr(const std::vector<T> &v);

template<typename T>
T Sqr(const T &t)
{
	return t * t;
}

template<typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second> &p)
{
	return std::make_pair(Sqr(p.first), Sqr(p.second));
}

template<typename First, typename Second>
std::map<First, Second> Sqr(const std::map<First, Second> &m)
{
	std::map<First, Second> result;

	for (const auto &item : m) {
		result[item.first] = Sqr(item.second);
	}
	
	return result;
}

template<typename T>
std::vector<T> Sqr(const std::vector<T> &v)
{
	std::vector<T> result;

	for (const auto &item : v) {
		result.push_back(Sqr(item));
	}

	return result;
}

int main()
{
	std::map<int, int> m1 { {1, 2}, {3, 4} };
	for (const auto &item : m1) {
		std::cout << item.first << ' ' << item.second << '\n';
	}
	std::map<int, int> result1 = Sqr(m1);
	for (const auto &item : result1) {
		std::cout << item.first << ' ' << item.second << '\n';
	}

	std::vector<double> v1 { 1, 2, 5, 2.1 };
	for (const auto &item : v1) {
		std::cout << item << ' ';
	}
	std::cout << '\n';
	std::vector<double> result2 = Sqr(v1);
	for (const auto &item : result2) {
		std::cout << item << ' ';
	}
	std::cout << '\n';

	std::pair<int, int> p1 { 1, 2 };
	std::cout << p1.first << ' ' << p1.second << '\n';
	std::pair<int, int> result3 = Sqr(p1);
	std::cout << result3.first << ' ' << result3.second << '\n';

	std::pair<double, double> p2 = { 0.5, 1.1 };
	std::pair<int, int> p3 = { 3, 4 };
	std::map<std::pair<int, int>, std::pair<double, double>> m2;
	m2[p3] = p2;
	std::vector<std::map<std::pair<int, int>, std::pair<double, double>>> vmp
		{ m2, m2 };

	auto result = Sqr(vmp);
	for (const auto &item : result) {
		for (const auto &m : item) {
			std::cout << m.first.first << m.first.second << '\n';
			std::cout << m.second.first << m.second.second << '\n';
		}
	}

	return 0;
}
