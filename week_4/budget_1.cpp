#include <iostream>
#include <map>
#include <ctime>

class Date;

enum class QueryType
{
    ComputeIncome,
    Earn
};

class Budget
{
public:
    double computeIncome()
    {
        
    }
    void earn()
    {

    }

private:
    std::map<Date, int> calendar;
};

int main()
{
    Budget budget;

    int queryCount;
    std::cin >> queryCount;

    std::string query;
    for (int i = 0; i < queryCount; ++i) {
        std::cin >> query;

        if (query == "ComputeIncome") {
            std::cout << budget.computeIncome() << '\n';
        } else if (query == "Earn") {
            budget.earn();
        }
    }


    return 0;
}