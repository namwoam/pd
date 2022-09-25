#include <iostream>
#include <cmath>

int main()
{
    int maxDemand, priceCount, cost;
    std::cin >> maxDemand >> priceCount >> cost;
    int price[priceCount];
    for (int i = 0; i < priceCount; i++)
    {
        std::cin >> price[i];
    }
    int demand[priceCount][maxDemand + 1];
    for (int i = 0; i < priceCount; i++)
    {
        for (int k = 0; k < maxDemand + 1; k++)
        {
            std::cin >> demand[i][k];
        }
    }
    int result[priceCount][maxDemand + 1];
    for (int i = 0; i < priceCount; i++)
    {
        for (int k = 0; k < maxDemand + 1; k++)
        {
            // k is the demand
            result[i][k] = 0;
            for (int j = 0; j < maxDemand + 1; j++)
            {
                result[i][k] += (price[i] / 100) * demand[i][j] * (j > k ? k : j);
            }
            result[i][k] -= k * cost;
            // std::cout << result[i][k] << ' ';
        }
        // std::cout << std ::endl; for debug
    }
    int bestPricePosition = 0, bestCount = 0;
    for (int i = 0; i < priceCount; i++)
    {
        for (int k = 0; k < maxDemand + 1; k++)
        {
            if (result[bestPricePosition][bestCount] < result[i][k] || (result[bestPricePosition][bestCount] == result[i][k] && price[bestPricePosition] > price[i]))
            {
                bestPricePosition = i;
                bestCount = k;
            }
        }
    }
    std::cout << price[bestPricePosition] << ',' << bestCount << ',' << result[bestPricePosition][bestCount] << std::endl;
}