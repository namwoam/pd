#include <iostream>
#include <vector>
#include <algorithm>
struct node
{
    int num = 0, height;
};

bool cmp(struct node l, struct node r)
{
    if (l.height == r.height)
    {
        return l.num < r.num;
    }
    else
    {
        return l.height > r.height;
    }
}

int main()
{
    std::vector<std::vector<struct node>> data(3);
    int a, b, height, position;
    std::cin >> a >> b;
    for (int i = 0; i < a; i++)
    {
        std::cin >> height >> position;
        struct node n;
        n.height = height;
        n.num = i + 1;
        data.at(position - 1).push_back(n);
    }
    for (int i = 0; i < data.size(); i++)
    {
        std::sort(data.at(i).begin(), data.at(i).end(), cmp);
        if (data.at(i).size() == 0)
        {
            struct node blank;
            blank.num = 0;
            data.at(i).push_back(blank);
        }
    }
    std::cout << data.at(0).at(0).num << ',' << data.at(1).at(0).num << ',' << data.at(2).at(0).num << std::endl;
    return 0;
}