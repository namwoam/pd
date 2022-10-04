#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct people
{
    int a, b, c, d;
    std::string name;
};

bool cmp(struct people l, struct people r)
{
    if (l.a == r.a)
    {
        if (l.b == r.b)
        {
            if (l.c == l.c)
            {
                return l.d > r.d;
            }
            return l.c > r.c;
        }
        return l.b > r.b;
    }
    return l.a > r.a;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::vector<struct people>> data(4);
    std::vector<std::string> pattern(4);
    for (int i = 0; i < pattern.size(); i++)
    {
        std::cin >> pattern.at(i);
    }
    
    
}