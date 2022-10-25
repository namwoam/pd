#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (int i = 0; i < data.size(); i++)
    {
        std::cin >> data.at(i);
    }
    int negativeCnt = 0;
    int result = -1;
    for (int i = 0; i < data.size(); i++)
    {
        if (data.at(i) < 0)
        {
            negativeCnt += 1;
            if (negativeCnt == 2)
            {
                result = i + 1;
            }
        }
    }
    std::cout << result << std::endl;
    return 0;
}