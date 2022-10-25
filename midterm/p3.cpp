#include <iostream>
#include <vector>

struct time
{
    int minute, hour;
    bool operator<(struct time t)
    {
        if (hour == t.hour)
        {
            return minute < t.minute;
        }
        return hour < t.hour;
    }
    bool operator==(struct time t)
    {
        return (hour == t.hour) && (minute == t.minute);
    }
    friend std::istream &operator>>(std::istream &in, struct time &t)
    {
        in >> t.hour >> t.minute;
        return in;
    }
};

struct period
{
    struct time start, end;
    bool overlap(struct period p)
    {
        return (singleOverlap(p) || p.singleOverlap(*this));
    }
    bool singleOverlap(struct period p)
    {
        return (start < p.start && p.start < end) || ((start < p.end && p.end < end)) || (start == p.start || end == p.end);
    }
    friend std::istream &operator>>(std::istream &in, struct period &p)
    {
        in >> p.start >> p.end;
        return in;
    }
};

int main()
{
    int n;
    std::cin >> n;
    std::vector<struct period> data(n);
    for (int i = 0; i < data.size(); i++)
    {
        std::cin >> data.at(i);
    }
    int overlapCnt = 0;
    for (int l = 0; l < data.size(); l++)
    {
        for (int r = l + 1; r < data.size(); r++)
        {
            if (data.at(l).overlap(data.at(r)))
            {
                overlapCnt += 1;
            }
        }
    }
    std::cout << overlapCnt << std::endl;
    return 0;
}