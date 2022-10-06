#include <iostream>

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    if (a == b && b == c && c == a)
    {
        std::cout << 1 << std::endl;
    }
    else if (a == b || b == c || c == a)
    {
        std::cout << 3 << std::endl;
    }
    else
    {
        std::cout << 2 << std::endl;
    }
    return 0;
}