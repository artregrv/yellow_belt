#include <algorithm>
#include <iostream>
#include <vector>

/*enum class Gender
{
	FEMALE,
	MALE
};

struct Person
{
	int age;
	Gender gender;
	bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end)
{
  	if (range_begin == range_end) {
    	return 0;
  	}
  	std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  	auto middle = begin(range_copy) + range_copy.size() / 2;
  	nth_element(
      	begin(range_copy), middle, end(range_copy),
      	[](const Person& lhs, const Person& rhs) {
        	return lhs.age < rhs.age;
      	}
  	);

  	return middle->age;
}*/

void PrintMessage(int value, const std::string &s = "")
{
	if (s.empty()) {
		std::cout << "Median age = " << value << '\n';
	} else {
		std::cout << "Median age for " << s << " = " << value << '\n';
	}
}

void PrintStats(std::vector<Person> persons)
{
	auto p_begin = persons.begin();
	auto p_end = persons.end();

	PrintMessage(ComputeMedianAge(persons.begin(), persons.end()));

	std::vector<Person>::iterator it;

	it = std::partition(p_begin, p_end, [](const Person &p) {
		return p.gender == Gender::FEMALE;
	});

	PrintMessage(ComputeMedianAge(p_begin, it), "females");

	it = std::partition(p_begin, p_end, [](const Person &p) {
		return p.gender == Gender::MALE;
	});

	PrintMessage(ComputeMedianAge(p_begin, it), "males");

	it = std::partition(p_begin, p_end, [](const Person &p) {
		return ((p.gender == Gender::FEMALE) 
				&& p.is_employed);
	});

	PrintMessage(ComputeMedianAge(p_begin, it), "employed females");

	it = std::partition(p_begin, p_end, [](const Person &p) {
		return ((p.gender == Gender::FEMALE) 
				&& !p.is_employed);
	});

	PrintMessage(ComputeMedianAge(p_begin, it), "unemployed females");

	it = std::partition(p_begin, p_end, [](const Person &p) {
		return ((p.gender == Gender::MALE)
				&& p.is_employed);
	});

	PrintMessage(ComputeMedianAge(p_begin, it), "employed males");

	it = std::partition(p_begin, p_end, [](const Person &p) {
		return ((p.gender == Gender::MALE)
				&& !p.is_employed);
	});

	PrintMessage(ComputeMedianAge(p_begin, it), "unemployed males");
}

int main()
{
	std::vector<Person> persons = {
		{31, Gender::MALE, false},
		{40, Gender::FEMALE, true},
		{24, Gender::MALE, true},
		{20, Gender::FEMALE, true},
		{80, Gender::FEMALE, false},
		{78, Gender::MALE, false},
		{10, Gender::FEMALE, false},
		{55, Gender::MALE, true},
	};

  	PrintStats(persons);
	
	return 0;
}

