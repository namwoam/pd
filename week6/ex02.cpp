#include <iostream>
#include <string>

int main()
{
    std::string input;
    int result = 0;
    std::getline(std::cin, input);
    for (int i = 1; i < input.size(); i++)
    {
        if (isspace(input.at(i - 1)))
        {
            input.at(i) = toupper(input.at(i));
        }
        else
        {
            input.at(i) = tolower(input.at(i));
        }
    }
    std::cout << input << std::endl;
    return 0;
}