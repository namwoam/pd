#include <iostream>
#include <vector>
#include <algorithm>

int calculate(int unmovePosition, std::vector<int> data)
{
    int result = 0;
    for (int i = unmovePosition + 1; i < data.size(); i++)
    {
        if (data.at(i) < data.at(i - 1))
        {
            data.at(i) = data.at(i - 1);
            result += 1;
        }
    }
    for (int i = unmovePosition - 1; i > -1; i--)
    {
        if (data.at(i) > data.at(i + 1))
        {
            data.at(i) = data.at(i + 1);
            result += 1;
        }
    }
    return result;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (int i = 0; i < data.size(); i++)
    {
        std::cin >> data.at(i);
    }
    int minResult = data.size() - 1;
    for (int i = 0; i < data.size(); i++)
    {
        int cache = calculate(i, data);
        minResult = (cache < minResult ? cache : minResult);
    }
    std::cout << minResult << std::endl;
    return 0;
}