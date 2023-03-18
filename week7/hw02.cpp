#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct order
{
    int id, revenue, cost, resource, labor;
};

bool cmp(struct order l, struct order r)
{
    return l.revenue * r.cost > r.revenue * l.cost;
}

int main()
{
    int n, laborConst, resourceConst, laborLimit, resourceLimit;
    std::cin >> n >> laborConst >> resourceConst >> laborLimit >> resourceLimit;
    int totalLabor = 0, totalResource = 0, totalRevenue = 0;
    std::vector<struct order> data(n);
    for (int i = 0; i < data.size(); i++)
    {
        std::cin >> data.at(i).revenue;
        totalRevenue += data.at(i).revenue;
    }
    for (int i = 0; i < data.size(); i++)
    {
        std::cin >> data.at(i).labor;
        totalLabor += data.at(i).labor;
    }
    for (int i = 0; i < data.size(); i++)
    {
        std::cin >> data.at(i).resource;
        totalResource += data.at(i).resource;
    }
    for (int i = 0; i < data.size(); i++)
    {
        data.at(i).id = i;
        data.at(i).cost = data.at(i).resource * resourceConst + data.at(i).labor * laborConst;
    }
    std::sort(data.begin(), data.end(), cmp);
    while (totalResource > resourceLimit || totalLabor > laborLimit)
    {
        totalResource -= data.back().resource;
        totalLabor -= data.back().labor;
        totalRevenue -= data.back().revenue;
        data.pop_back();
    }
    std::set<int> acceptOrder;
    for (int i = 0; i < data.size(); i++)
    {
        acceptOrder.insert(data.at(i).id);
    }
    for (int i = 0; i < n; i++)
    {
        if (acceptOrder.count(i))
        {
            std::cout << 1;
        }
        else
        {
            std::cout << 0;
        }
        if (i == n - 1)
        {
            std::cout << ';';
        }
        else
        {
            std::cout << ',';
        }
    }
    std::cout << totalRevenue << std::endl;
}