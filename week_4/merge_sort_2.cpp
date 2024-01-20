#include <algorithm>
#include <vector>
#include <iostream>

template<typename RandomIt>
void MergeSort(RandomIt rangeBegin, RandomIt rangeEnd)
{
    size_t length = rangeEnd - rangeBegin;
    
    if ((length) < 3)
        return;

    std::vector<typename RandomIt::value_type> elements(rangeBegin, rangeEnd);

    MergeSort(elements.begin(), elements.begin() + length / 3);
    MergeSort(elements.begin() + length / 3, elements.end() - length / 3);
    MergeSort(elements.end() - length / 3, elements.end());

    std::vector<typename RandomIt::value_type> tmp;

    std::merge(elements.begin(), elements.begin() + length / 3,
               elements.begin() + length / 3, elements.end() - length / 3,
               std::back_inserter(tmp));

    std::merge(tmp.begin(), tmp.end(),
               elements.end() - length / 3, elements.end(),
               rangeBegin);
}

int main()
{
    std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
    MergeSort(begin(v), end(v));
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << '\n';
    return 0;
}