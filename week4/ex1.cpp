#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << (a > b ? b : a) << std::endl;
    return 0;
}