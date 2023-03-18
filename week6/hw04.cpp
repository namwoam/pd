#include <iostream>
#include <cstring>
#include <cctype>

#define CITY_LIMIT 30
#define NAME_LIMIT 200
#define INFINITE_DISTANCE 3000 // constants

int chooseNextHospital(int cityDistance[CITY_LIMIT][CITY_LIMIT], bool *isHospital, int cityNum, int algorNum, int happyDistance)
{
    if (algorNum == 0)
    {
        int closestHospital[CITY_LIMIT];
        int benefit[CITY_LIMIT] = {0};
        for (int i = 0; i < cityNum; i++)
        {
            closestHospital[i] = INFINITE_DISTANCE;
        }
        for (int i = 0; i < cityNum; i++)
        {
            for (int k = 0; k < cityNum; k++)
            {
                if (isHospital[k] == true && cityDistance[i][k] < closestHospital[i])
                {
                    closestHospital[i] = cityDistance[i][k];
                }
            }
        }
        for (int i = 0; i < cityNum; i++)
        {
            if (isHospital[i] == false)
            {
                for (int k = 0; k < cityNum; k++)
                {
                    if (closestHospital[k] > cityDistance[i][k])
                    {
                        // from city i to city k is closer than the cloest hospital to city k
                        // i.e. it is beneficial to setup a hospital in city i
                        // record the benefit
                        benefit[i] += (closestHospital[k] - cityDistance[i][k]);
                    }
                }
            }
        }
        int nextHospital = -1;
        for (int i = 0; i < cityNum; i++)
        {
            if (isHospital[i] == false)
            {
                if (nextHospital == -1)
                {
                    nextHospital = i;
                }
                else if (benefit[nextHospital] < benefit[i])
                {
                    nextHospital = i;
                }
            }
        }
        // std::cout << nextHospital << std::endl;
        if (nextHospital != -1)
        {
            isHospital[nextHospital] = true;
        }
        return nextHospital;
    }
    else if (algorNum == 1)
    {
        bool isHappy[CITY_LIMIT] = {false};
        for (int i = 0; i < cityNum; i++)
        {
            for (int k = 0; k < cityNum; k++)
            {
                if (cityDistance[i][k] <= happyDistance && isHospital[k] == true)
                {
                    isHappy[i] = true;
                }
            }
        }
        int benefit[CITY_LIMIT] = {0};
        for (int i = 0; i < cityNum; i++)
        {
            if (isHospital[i] == false)
            {
                for (int k = 0; k < cityNum; k++)
                {
                    if (isHappy[k] == false && cityDistance[i][k] <= happyDistance)
                    {
                        benefit[i] += 1;
                    }
                }
            }
        }
        int nextHospital = -1;
        for (int i = 0; i < cityNum; i++)
        {
            if (isHospital[i] == false)
            {
                if (nextHospital == -1)
                {
                    nextHospital = i;
                }
                else if (benefit[nextHospital] < benefit[i])
                {
                    nextHospital = i;
                }
            }
        }
        if (nextHospital != -1)
        {
            isHospital[nextHospital] = true;
        }
        return nextHospital;
    }
}

int main()
{
    int cityNum, hospitalNum, happyDistance, algorNum;
    std::cin >> cityNum >> hospitalNum >> happyDistance >> algorNum;
    int cityDistance[CITY_LIMIT][CITY_LIMIT];
    char cityName[CITY_LIMIT][NAME_LIMIT];
    bool isHospital[CITY_LIMIT] = {false};
    for (int i = 0; i < cityNum; i++)
    {
        for (int k = 0; k < cityNum; k++)
        {
            std::cin >> cityDistance[i][k];
        }
    }
    std::cin.ignore(); // switch from cin to getline
    for (int i = 0; i < cityNum; i++)
    {
        std::cin.getline(cityName[i], NAME_LIMIT);
        // std::cout << cityName[i] << std::endl;
    }
    for (int i = 0; i < hospitalNum; i++)
    {
        int result = chooseNextHospital(cityDistance, isHospital, cityNum, algorNum, happyDistance); // function for choosing next city to build hospital
        // std::cout << result << std::endl;
        if (result != -1)
        {
            int ptr = 0;
            char prevChar = '#';
            while (cityName[result][ptr] != '\0')
            {
                if (cityName[result][ptr] != ' ')
                {
                    std::cout << (char)tolower(cityName[result][ptr]);
                }
                else // is space
                {
                    if (prevChar != ' ') // only output one - character
                    {
                        std::cout << '-';
                    }
                }
                prevChar = cityName[result][ptr];
                ptr += 1;
            }
            std::cout << std::endl;
        }
    }
    int hospitalDistSum = 0;
    int happyCount = 0;
    for (int i = 0; i < cityNum; i++)
    {
        int closestDistance = INFINITE_DISTANCE;
        for (int k = 0; k < cityNum; k++)
        {
            if (isHospital[k] == true && cityDistance[i][k] < closestDistance)
            {
                closestDistance = cityDistance[i][k];
            }
        }
        hospitalDistSum += closestDistance;
        if (closestDistance <= happyDistance)
        {
            happyCount += 1;
        }
    }
    std::cout << hospitalDistSum << ';' << happyCount << std::endl;
    return 0;
}