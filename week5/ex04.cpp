#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (int i = 0; i < data.size(); i++)
    {
        std::cin >> data.at(i);
    }
    std::sort(data.begin(), data.end());
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data.at(i);
        if (i == data.size() - 1)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << ',';
        }
    }
}