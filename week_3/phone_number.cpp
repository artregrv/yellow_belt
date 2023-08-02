#include "phone_number.h"

#include <sstream>
#include <stdexcept>
#include <cctype>

bool isNumber(const std::string &number)
{
	for (const auto sym : number) {
		if (!std::isdigit(sym) {
			return false;
		}
	}
	
	return true;
}

PhoneNumber::PhoneNumber(const std::string &number)
{
	std::stringstream ss(number);	
	if (ss.peek() != '+')
		throw std::invalid_argument(number);

	ss.ignore(1);

	std::string county_code;
	std::getline(ss, country_code, '-');
}

std::string PhoneNumber::GetCountryCode() const
{
	return country_code_;
}

std::string PhoneNumber::GetCityCode() const
{
	return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const
{
	return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const
{
	return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}
