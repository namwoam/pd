#include <iostream>
#include <string>

int main()
{
    char ch;
    std::string punctuation = ",.:;!?";
    int result = 0;
    while (std::cin >> ch)
    {
        if (punctuation.find(ch) != std::string::npos)
        {
            result += 1;
        }
    }
    std::cout << result << std::endl;
    return 0;
}