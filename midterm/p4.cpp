#include <iostream>
#include <vector>
#include <set>

#define MAX_DISTANCE 2000

int main()
{
    int n, numberOfHospital, hospitalDistanceLimit;
    std::cin >> n >> numberOfHospital >> hospitalDistanceLimit;
    std::vector<std::vector<int>> data(n, std::vector<int>(n));
    for (int i = 0; i < data.size(); i++)
    {
        for (int k = 0; k < data.at(i).size(); k++)
        {
            std::cin >> data.at(i).at(k);
        }
    }
    std::set<int> hospital;
    for (int i = 0; i < numberOfHospital; i++)
    {
        int cache;
        std::cin >> cache;
        hospital.insert(cache - 1);
    }
    std::vector<int> distanceToClosestHospital(n, MAX_DISTANCE);
    for (int i = 0; i < data.size(); i++)
    {
        for (int k = 0; k < data.at(i).size(); k++)
        {
            if (hospital.count(k) == 1 && data.at(i).at(k) < distanceToClosestHospital.at(i))
            {
                distanceToClosestHospital.at(i) = data.at(i).at(k);
            }
        }
    }
    int sumDistance = 0, goodCityCount = 0;
    for (int i = 0; i < distanceToClosestHospital.size(); i++)
    {
        if (distanceToClosestHospital.at(i) <= hospitalDistanceLimit)
        {
            goodCityCount += 1;
        }
        // std::cout << distanceToClosestHospital.at(i) << std::endl;
        sumDistance += distanceToClosestHospital.at(i);
    }
    std::cout << sumDistance << ',' << goodCityCount << std::endl;
    return 0;
}