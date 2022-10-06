#include <iostream>
#include <vector>

int getDirection(int ptr, std::vector<int> &data)
{
    if (data.at(ptr) < data.at(ptr + 1))
    {
        return 1;
    }
    else if (data.at(ptr) > data.at(ptr + 1))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int getPattern(std::vector<int> &data)
{
    int prevDirection = getDirection(0, data), currentDirection = getDirection(0, data);
    bool changeQuota = true;
    for (int i = 1; i < data.size() - 1; i++)
    {
        prevDirection = currentDirection;
        currentDirection = getDirection(i, data);
        if (currentDirection == 0 || prevDirection == 0)
        {
            return 4;
        }
        if (prevDirection != currentDirection)
        {
            if (changeQuota == true && prevDirection == 1)
            {
                changeQuota = false;
            }
            else
            {
                return 4;
            }
        }
    }
    if (changeQuota == false)
    {
        return 3;
    }
    if (currentDirection == 1)
    {
        return 1;
    }
    else if (currentDirection == -1)
    {
        return 2;
    }
    else
    {
        return -1;
    }
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
    std::cout << getPattern(data) << std::endl;
    return 0;
}