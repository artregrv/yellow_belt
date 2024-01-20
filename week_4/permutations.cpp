#include <algorithm>
#include <iostream>
#include <vector>

/*size_t factorial(int n)
{
	size_t result = 1;
	while (n > 0) {
		result *= n;
		--n;
	}

	return result;
}*/

void print_vector(const std::vector<int> &v)
{
	for (const int item : v) {
		std::cout << item << ' ';
	}
}

void print_permutations(std::vector<int> v)
{
//	size_t size = v.size();
//	size_t number_of_permutations = factorial(size);
	do {
		print_vector(v);
		std::cout << '\n';
	} while (std::next_permutation(v.begin(), v.end(), 
								   [](int lhs, int rhs) {
			  return lhs > rhs;	
		  }));
}

int main()
{
	int n;
	std::cin >> n;

	std::vector<int> v;
	for (int i = n; i > 0; --i) {
		v.push_back(i);
	}

	print_permutations(v);

	return 0;
}
