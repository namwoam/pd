#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int upperLimit, price, cost;
    std::cin >> upperLimit >> price >> cost;
    std::vector<int> demand(upperLimit + 1), result(upperLimit + 1);
    for (int i = 0; i < demand.size(); i++)
    {
        std::cin >> demand.at(i);
    }
    for (int i = 0; i < result.size(); i++)
    {
        for (int k = 0; k < demand.size(); k++)
        {
            result.at(i) += (price / 100) * std::min(k, i) * demand.at(k);
        }
        result.at(i) -= cost * i;
    }
    int maxPosition = 0;
    for (int i = 0; i < result.size(); i++)
    {
        if (result.at(maxPosition) < result.at(i))
        {
            maxPosition = i;
        }
    }
    std::cout << maxPosition << ',' << result.at(maxPosition) << std::endl;
    return 0;
}