#include <iostream>

void nxt(int n)
{
    int result;
    if (n % 2 == 0)
    {
        result = n / 2;
    }
    else
    {
        result = n * 3 + 1;
    }
    std::cout << result << ' ';
    if (result != 1)
    {
        return nxt(result);
    }
    else
    {
        return;
    }
}

int main()
{
    int n;
    std::cin >> n;
    nxt(n);
    return 0;
}