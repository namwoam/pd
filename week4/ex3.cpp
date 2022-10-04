#include <iostream>

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    std::cout << gcd(gcd(a, b), c) << std::endl;
    return 0;
}