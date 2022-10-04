#include <iostream>
#define orderLimit 60

double calaulateCp(int weightH, int weightS, int labor, int resource, int revenue)
{
    //std::cout << "cp:" << ((double)revenue) / (weightH * labor + weightS * resource) << std::endl;
    return ((double)revenue) / (weightH * labor + weightS * resource);
}

int calculateTotalRevenue(int weightH, int weightS, int limitH, int limitS, int n, int revenue[], int labor[], int resource[])
{
    int totalRevenue = 0, totalLaborCost = 0, totalResourceCost = 0;
    double cp[orderLimit];
    bool takeOrder[orderLimit];
    for (int i = 0; i < n; i++)
    {
        cp[i] = calaulateCp(weightH, weightS, labor[i], resource[i], revenue[i]);
        takeOrder[i] = true;
        totalRevenue += revenue[i];
        totalLaborCost += labor[i];
        totalResourceCost += resource[i];
    }
    while (totalLaborCost > limitH || totalResourceCost > limitS)
    {
        int dropOrderPosition = -1;
        for (int i = 0; i < n; i++)
        {
            if (takeOrder[i] == true)
            {
                //std::cout << "Take this order" << std::endl;
                if (dropOrderPosition == -1)
                {
                    dropOrderPosition = i;
                    continue;
                }
                if ((cp[dropOrderPosition] > cp[i]) || (cp[dropOrderPosition] == cp[i] && revenue[dropOrderPosition] > revenue[i]))
                {
                    //std::cout << "dropping different order" << std::endl;
                    dropOrderPosition = i;
                }
            }
        }
        if (dropOrderPosition == -1)
        {
            break;
        }
        else
        {
            totalRevenue -= revenue[dropOrderPosition];
            totalLaborCost -= labor[dropOrderPosition];
            totalResourceCost -= resource[dropOrderPosition];
            takeOrder[dropOrderPosition] = false;
            //std::cout << "drop order:" << dropOrderPosition << std::endl;
        }
    }
    return totalRevenue;
}

int main()
{
    int n, limitH, limitS;
    std::cin >> n >> limitH >> limitS;
    int revenue[orderLimit], labor[orderLimit], resource[orderLimit];
    for (int i = 0; i < n; i++)
    {
        std::cin >> revenue[i];
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> labor[i];
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> resource[i];
    }
    int resultWeightH = 0, resultWeightS = 0, resultRevenue = -1;
    for (int weightH = 0; weightH < 6; weightH++)
    {
        for (int weightS = 0; weightS < 6; weightS++)
        {
            if (weightH + weightS == 0)
            {
                continue;
            }
            int cache = calculateTotalRevenue(weightH, weightS, limitH, limitS, n, revenue, labor, resource);
            //std::cout << weightH << ',' << weightS << ',' << cache << std::endl;
            if (cache > resultRevenue)
            {
                resultRevenue = cache;
                resultWeightH = weightH;
                resultWeightS = weightS;
            }
        }
    }
    std::cout << resultWeightH << ',' << resultWeightS << ',' << resultRevenue << std::endl;
}