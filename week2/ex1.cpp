#include <iostream>

int main()
{
    int gender, age;
    std::cin >> gender >> age;
    if ((gender == 1 && age >= 18) || (gender == 0 && age >= 16))
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }
}