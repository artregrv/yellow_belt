#include <iostream>
#include <limits>

int main()
{
	int n;
	int density;

	std::cin >> n;
	std::cin >> density;

	int64_t w;
	int64_t h;
	int64_t d;

	uint64_t sum = 0;

	for (int i = 0; i < n; ++i) {
		std::cin >> w >> h >> d;
		
		sum += w * h * d * density;
	}

	std::cout << sum << '\n';
		
	return 0;
}
