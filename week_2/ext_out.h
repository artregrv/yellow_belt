#include <iostream>
#include <set>
#include <vector>

template <class T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s)
{
    os << "{ ";
    bool first = true;

    for (const auto &item : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        
        os << item;
    }

    return os << " }";
}

template<class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    os << "{ ";
    bool first = true;

    for (const auto &item : v) {
        if (!first) {
            os << ", ";
        }
        first = false;

        os << item;
    }

    return os << " }";
}