#include <iostream>

int profit(int demand, int priceSensitivity, int price, int cost)
{
    return (demand - priceSensitivity * price) * (price - cost);
}

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    int setPrice = (a / b) + 1, bestProfit = 0, bestPrice;
    while (setPrice >= c)
    {
        if (profit(a, b, setPrice, c) >= bestProfit)
        {
            bestProfit = profit(a, b, setPrice, c);
            bestPrice = setPrice;
        }
        setPrice--;
    }
    std::cout << bestPrice << ' ' << bestProfit << std::endl;
    return 0;
}