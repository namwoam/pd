#include <iostream>
#include <vector>

struct node
{
    int val, pos;
};

std::ostream &operator<<(std::ostream &os, struct node const &m)
{
    return os << m.pos << ',' << m.val;
}

int main()
{
    int n, target;
    std::cin >> n >> target;
    std::vector<int> data(n);
    std::vector<struct node> negativeData;
    for (int i = 0; i < data.size(); i++)
    {
        std::cin >> data.at(i);
    }
    for (int i = 0; i < data.size(); i++)
    {
        if (data.at(i) < 0)
        {
            struct node tmp;
            tmp.val = data.at(i);
            tmp.pos = i + 1;
            negativeData.push_back(tmp);
            // std::cout << tmp << std::endl;
        }
    }
    if (target >= negativeData.size())
    {
        if (negativeData.size() == 0)
        {
            std::cout << 0 << std::endl;
        }
        else
        {
            std::cout << negativeData.back() << std::endl;
        }
    }
    else
    {
        std::cout << negativeData.at(target - 1) << std::endl;
    }
    return 0;
}