#include <iostream>
#include <vector>

unsigned long long combination(unsigned long long n, unsigned long long k)
{
    if (k > n)
    {
        return 0;
    }
    else if (k == 0 || k == n)
    {
        return 1;
    }
    else if (k > n / 2)
    {
        return combination(n, n - k);
    }
    std::vector<unsigned long long> up;
    std::vector<unsigned long long> down;
    for (int i = 0; i < k; i++)
    {
        up.push_back(n - i);
        down.push_back(i + 1);
    }
    unsigned long long result = 1;
    while (up.empty() == false || down.empty() == false)
    {
        for (auto i = down.begin(); i != down.end(); i++)
        {
            if (result % *i == 0)
            {
                result /= *i;
                down.erase(i);
                break;
            }
        }
        if (up.empty() == false)
        {
            result *= up[0];
            up.erase(up.begin());
        }
    }
    return result;
}

int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << combination(a, b) << std::endl;
    return 0;
}