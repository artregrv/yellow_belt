#include <set>
#include <iostream>
#include <vector>
#include <string>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T> &elements, 
							 	   const T &border)
{
	std::vector<T> result;

	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (*it > border) {
			result.push_back(*it);
		}
	}

	return result;
}

int main()
{

	std::set<int> test_set = {1, 5, 7, 8}; 
  	for (int x : FindGreaterElements(test_set, 5)) {
    	std::cout << x << " ";
  	}
  	std::cout << std::endl;
  
 	std::string to_find = "Python";
  	std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;

	return 0;
}
