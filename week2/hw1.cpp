#include <iostream>

int main()
{
    int n, t, cache;
    std::cin >> n >> t;
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        std::cin >> cache;
        if (t * 12 <= cache)
        {
            result += 1;
        }
    }
    std::cout << result << std::endl;
}