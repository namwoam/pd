#include <iostream>
#include <vector>
int main()
{
    int n;
    std::cin >> n;
    int sum = 0, largest = -200, cache;
    for (int i = 0; i < n; i++)
    {
        std::cin >> cache;
        sum += cache;
        if (cache > largest)
        {
            largest = cache;
        }
    }
    std::cout << largest << ',' << sum << std::endl;
    return 0;
}