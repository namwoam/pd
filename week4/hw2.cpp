#include <iostream>
#include <vector>

struct order
{
    int laborCost, resourceCost, revenue;
    double cp;
    bool takeOrder;
};

int main()
{
    int n, wh, ws, h, s;
    std::cin >> n >> wh >> ws >> h >> s;
    std::vector<struct order> data(n);
    int totalRevenue = 0, totalLaborCost = 0, totalResourceCost = 0;
    for (int i = 0; i < n; i++)
    {
        std::cin >> data.at(i).revenue;
        totalRevenue += data.at(i).revenue;
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> data.at(i).laborCost;
        totalLaborCost += data.at(i).laborCost;
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> data.at(i).resourceCost;
        totalResourceCost += data.at(i).resourceCost;
    }
    for (int i = 0; i < n; i++)
    {
        data.at(i).cp = (double)data.at(i).revenue / (data.at(i).laborCost * wh + data.at(i).resourceCost * ws);
        data.at(i).takeOrder = true;
        // std::cout << data.at(i).cp << ' ';
    }
    // std::cout << std::endl;
    while (totalLaborCost > h || totalResourceCost > s)
    {
        int dropOrderPosition = -1;
        for (int i = 0; i < data.size(); i++)
        {
            if (data.at(i).takeOrder == true)
            {
                if (dropOrderPosition == -1)
                {
                    dropOrderPosition = i;
                    continue;
                }
                if ((data.at(dropOrderPosition).cp > data.at(i).cp) || (data.at(dropOrderPosition).cp == data.at(i).cp && data.at(dropOrderPosition).revenue > data.at(i).revenue))
                {
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
            data.at(dropOrderPosition).takeOrder = false;
            totalRevenue -= data.at(dropOrderPosition).revenue;
            totalLaborCost -= data.at(dropOrderPosition).laborCost;
            totalResourceCost -= data.at(dropOrderPosition).resourceCost;
        }
    }
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << (data.at(i).takeOrder == true ? 1 : 0);
        if (i == data.size() - 1)
        {
            std::cout << ';';
        }
        else
        {
            std::cout << ',';
        }
    }
    std::cout << totalRevenue << std::endl;
    return 0;
}