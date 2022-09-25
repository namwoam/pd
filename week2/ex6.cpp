#include <iostream>
#include <vector>
#include <cmath>

struct node
{
    int x;
    int y;
    char status;
};

int main()
{
    int mazeSize = 6;
    std::vector<struct node> data(mazeSize * mazeSize);
    for (int i = 0; i < data.size(); i++)
    {
        data[i].y = i % mazeSize;
        data[i].x = i / mazeSize;
        data[i].status = 'Y';
    }
    int sniperNumber = 3, x, y;
    for (int i = 0; i < sniperNumber; i++)
    {
        std::cin >> x >> y;
        data[y + x * mazeSize].status = 'S';
        for (int k = 0; k < mazeSize; k++)
        {
            data[k + x * mazeSize].status = 'N';
            data[y + k * mazeSize].status = 'N';
        }
        for (int k = 0; k < data.size(); k++)
        {
            if (std::abs(data[k].x - x) == std::abs(data[k].y - y))
            {
                data[k].status = 'N';
            }
        }
    }
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].status == 'Y')
        {
            std::cout << data[i].x << ' ' << data[i].y << std::endl;
        }
    }
}
