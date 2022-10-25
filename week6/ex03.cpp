#include <iostream>
#include <string>

int main()
{
    std::string input, target;
    std::getline(std::cin, input);
    std::cin >> target;
    for (int i = 0; i < target.size(); i++)
    {
        target.at(i) = tolower(target.at(i));
    }
    for (int i = 0; i < input.size(); i++)
    {
        input.at(i) = tolower(input.at(i));
    }
    if (input.find(target) == std::string::npos)
    {
        std::cout << 0 << std::endl;
    }
    else
    {
        std::cout << 1 << std::endl;
    }
    return 0;
}