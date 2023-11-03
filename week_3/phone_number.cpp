#include "phone_number.h"

#include <sstream>
#include <exception>

PhoneNumber::PhoneNumber(const std::string &international_number)
{
    std::stringstream ss;
    ss << international_number;

    std::invalid_argument error("Wrong number format!");

    char plus = ss.get();

    if (plus != '+')
        throw error;

    std::getline(ss, country_code_, '-');

    if (country_code_ == "")
        throw error;

    std::getline(ss, city_code_, '-');

    if (city_code_ == "")
        throw error;

    std::getline(ss, local_number_);

    if (local_number_ == "")
        throw error;
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
    std::stringstream ss;

    ss << "+";
    ss << country_code_;
    ss << "-";
    ss << city_code_;
    ss << "-";
    ss << local_number_;

    return ss.str();
}

// #include <iostream>

// int main() 
// {
//     try {
//         PhoneNumber pn("+7-495-1112233");
    
//         std::cout << pn.GetCountryCode() << ' ' 
//                   << pn.GetCityCode() << ' ' 
//                   << pn.GetLocalNumber() << ' ' 
//                   << pn.GetInternationalNumber() << '\n';
//     } catch (std::invalid_argument &e) {
//         std::cout << e.what() << '\n';
//     }

//     try {
//         PhoneNumber pn("+323-22-460002");
    
//         std::cout << pn.GetCountryCode() << ' ' 
//                   << pn.GetCityCode() << ' ' 
//                   << pn.GetLocalNumber() << ' ' 
//                   << pn.GetInternationalNumber() << '\n';
//     } catch (std::invalid_argument &e) {
//         std::cout << e.what() << '\n';
//     }

//     try {
//         PhoneNumber pn("+1-2-coursera-cpp");
    
//         std::cout << pn.GetCountryCode() << ' ' 
//                   << pn.GetCityCode() << ' ' 
//                   << pn.GetLocalNumber() << ' ' 
//                   << pn.GetInternationalNumber() << '\n';
//     } catch (std::invalid_argument &e) {
//         std::cout << e.what() << '\n';
//     }

//     try {
//         PhoneNumber pn("1-2-333");
    
//         std::cout << pn.GetCountryCode() << ' ' 
//                   << pn.GetCityCode() << ' ' 
//                   << pn.GetLocalNumber() << ' ' 
//                   << pn.GetInternationalNumber() << '\n';
//     } catch (std::invalid_argument &e) {
//         std::cout << e.what() << '\n';
//     }

//     try {
//         PhoneNumber pn("+7-1233");
    
//         std::cout << pn.GetCountryCode() << ' ' 
//                   << pn.GetCityCode() << ' ' 
//                   << pn.GetLocalNumber() << ' ' 
//                   << pn.GetInternationalNumber() << '\n';
//     } catch (std::invalid_argument &e) {
//         std::cout << e.what() << '\n';
//     }

//     try {
//         PhoneNumber pn("+7---");
    
//         std::cout << pn.GetCountryCode() << ' ' 
//                   << pn.GetCityCode() << ' ' 
//                   << pn.GetLocalNumber() << ' ' 
//                   << pn.GetInternationalNumber() << '\n';
//     } catch (std::invalid_argument &e) {
//         std::cout << e.what() << '\n';
//     }

//     return 0;
// }