#include <iostream>
#include <vector>

int main()
{
    int n, limit;
    std::cin >> n >> limit;
    std::vector<int> height(n), team(n), result(3);
    for (int i = 0; i < height.size(); i++)
    {
        std::cin >> height.at(i);
    }
    for (int i = 0; i < team.size(); i++)
    {
        std::cin >> team.at(i);
    }
    for (int i = 0; i < n; i++)
    {
        if (limit * 12 <= height.at(i))
        {
            result.at(team.at(i) - 1) += 1;
        }
    }
    std::cout << result.at(0) << ',' << result.at(1) << ',' << result.at(2) << std::endl;
    return 0;
}