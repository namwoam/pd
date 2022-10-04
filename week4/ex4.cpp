#include <iostream>
#include <vector>

int main()
{
    int a, b, cache, result = 0;
    std::cin >> a >> b;
    for (int i = 0; i < a; i++)
    {
        std::cin >> cache;
        if (cache >= b)
        {
            result += 1;
        }
    }
    std::cout << result << std::endl;
    return 0;
}