#include <iostream>
#include <tuple>

void printCoord(std::pair<double, double> c)
{
    int x = static_cast<int>(c.first * 100);
    int y = static_cast<int>(c.second * 100);
    std::cout << x << ',' << y << std::endl;
    return;
}

class randomCoordGenerator
{
public:
    int seed;
    const int constA = 75, constC = 74, constM = 32768;
    randomCoordGenerator(int _seed)
    {
        seed = _seed;
    }
    int nextNumber()
    {
        int result = (constA * seed + constC) % constM;
        seed = result;
        return result;
    }
    double normalize(int n)
    {
        return -1.0 + 2.0 * (static_cast<double>(n) / static_cast<double>(constM - 1));
    }
    std::pair<double, double> getNextCoord()
    {
        int x = nextNumber(), y = nextNumber();
        return std::pair<double, double>(normalize(x), normalize(y));
    }
};

int main()
{
    int seed, n;
    std::cin >> seed >> n;
    randomCoordGenerator r(seed);
    std::pair<double, double> coord;
    for (int i = 0; i < n; i++)
    {
        coord = r.getNextCoord();
        printCoord(coord);
    }
    return 0;
}