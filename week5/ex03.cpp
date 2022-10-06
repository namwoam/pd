#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n, target;
    std::cin >> n >> target;
    std::vector<int> data(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> data.at(i);
    }
    if (std::binary_search(data.begin(), data.end(), target))
    {
        std::cout << 1 << std::endl;
    }
    else
    {
        std::cout << 0 << std::endl;
    }
    return 0;
}