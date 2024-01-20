#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if ((range_end - range_begin) < 2) {
		return;
	}

	std::vector<typename RandomIt::value_type> v(range_begin, range_end);

	MergeSort(v.begin(), v.begin() + v.size() / 2);
	MergeSort(v.begin() + v.size() / 2, v.end());

	std::merge(v.begin(), v.begin() + v.size() / 2,
			   v.begin() + v.size() / 2, v.end(),
			   range_begin);
}

int main()
{
	std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
  	MergeSort(begin(v), end(v));

  	for (int x : v) {
    	std::cout << x << " ";
  	}
  	std::cout << std::endl;

	return 0;
}
