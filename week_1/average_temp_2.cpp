#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int64_t calculateAverageTemp(std::vector<int64_t> &v)
{
	int64_t sum = std::accumulate(v.begin(), v.end(), static_cast<int64_t>(0));

	return 	sum / static_cast<int64_t>(v.size());	
}

int main()
{
	int n;
	std::cin >> n;

	std::vector<int64_t> v(n);

	for (auto &item : v) {
		std::cin >> item;
	}
		
	int64_t average_temp = calculateAverageTemp(v);

	int result_days_count = std::count_if(v.begin(), v.end(),
										  [average_temp](int64_t value) {
										  	  return value > average_temp;
										  });

	std::cout << result_days_count << '\n';

	for (int i = 0; i < n; ++i) {
		if (v.at(i) > average_temp) {
			std::cout << i << ' ';	
		}
	}

	if (result_days_count > 0) {
		std::cout << '\n';
	}

	return 0;
}
