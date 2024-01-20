#include <string>
#include <iostream>

int main()
{
    std::string expression = "";
    std::string firstParanthesis = "";

    int base;
    std::cin >> base;

    expression += std::to_string(base);

    size_t operationsCount;
    std::cin >> operationsCount;

    std::string operation;
    int number;
    for (size_t i = 0; i < operationsCount; ++i) {
        std::cin >> operation;    
        std::cin >> number;

        firstParanthesis += "(";
        expression += ") " + operation + " " + std::to_string(number); 
    }

    std::cout << firstParanthesis + expression;

    return 0;
}