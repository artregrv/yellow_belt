#include <iostream>
#include <vector>

void PrintVectorPart(const std::vector<int> &numbers)
{
	if (numbers.empty()) {
		return;
	}

	auto it = numbers.begin();

	while ((*it >= 0) && (it < numbers.end())) {
		++it;
	}

	while (it > numbers.begin()) {
		--it;
		std::cout << *it << ' ';
	}
}

int main()
{
 	PrintVectorPart({});
  	std::cout << std::endl;
  	PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  	std::cout << std::endl;
  	PrintVectorPart({6, 1, 8, 5, 4});
  	std::cout << std::endl;

	return 0;
}
