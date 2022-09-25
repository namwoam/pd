#include <iostream>
#include <vector>

int main()
{
    int a, b, height, position;
    std::vector<int> data(3);
    std::cin >> a >> b;
    for (int i = 0; i < a; i++)
    {
        std::cin >> height >> position;
        if (height >= b * 12)
        {
            data.at(position - 1) += 1;
        }
    }
    std::cout << data[0] << ',' << data[1] << ',' << data[2] << std::endl;
    return 0;
}