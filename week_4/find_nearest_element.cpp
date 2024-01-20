#include <iostream>
#include <set>

std::set<int>::const_iterator FindNearestElement(const std::set<int> &nums, 
                                                 int border)
{
    auto minIter = nums.lower_bound(border);

    if (minIter != nums.begin())
        --minIter;

    auto maxIter = nums.upper_bound(border);

    if (minIter == nums.end() && minIter == nums.end())
        return nums.end();

    if (maxIter == nums.end())
        --maxIter; 

    int difMin = abs(*minIter - border);
    int difMax = abs(*maxIter - border);

    if (difMin == difMax) {
        return minIter;
    } else if (difMin < difMax) {
        return minIter;
    } else {
        return maxIter;
    }
}

int main()
{
    std::set<int> numbers = {1, 4, 6};
    std::cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << '\n';
      
    std::set<int> empty_set;
  
    std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << '\n';
    
    return 0;
}