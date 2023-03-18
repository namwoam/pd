#include <iostream>
#include <vector>
#include <algorithm>

#define NUMBER_OF_SHIFT 24

auto standardSchedule(int days)
{
    std::vector<int> result(days, 1);
    for (int i = 0; i < result.size(); i++)
    {
        if (i % 7 == 0 || i % 7 == 1)
        {
            result.at(i) = 0;
        }
    }
    return result;
}

auto genRestSchedule(int days, int limit)
{
    std::vector<std::vector<int>> result;
    for (int i = 0; i < 7; i++)
    {
        int restDay = ((days - i) / 7) * 2 + std::min((days - i) % 7, 2) + (i == 6 ? 1 : 0);
        if (restDay == limit)
        {
            std::vector<int> validSchedule = standardSchedule(days);
            for (int k = 0; k < i; k++)
            {
                validSchedule.pop_back();
                validSchedule.insert(validSchedule.begin(), (k == 5 ? 0 : 1));
            }
            result.push_back(validSchedule);
        }
    }
    return result;
}

int main()
{
    int numberOfEmployee, numberOfSchedule, days, restConst, overtimeConst, numberOfRequest, restLimit;
    std::cin >> numberOfEmployee >> days >> numberOfSchedule >> restLimit >> restConst >> overtimeConst >> numberOfRequest;
    std::vector<std::vector<int>> scheduleTemplate(numberOfSchedule + 1, std::vector<int>(NUMBER_OF_SHIFT));
    std::vector<std::vector<int>> demand(days, std::vector<int>(NUMBER_OF_SHIFT));
    std::vector<std::vector<int>> workerSchedule(numberOfEmployee, std::vector<int>(days));
    for (int i = 0; i < scheduleTemplate.size(); i++)
    {
        for (int k = 0; k < scheduleTemplate.at(i).size(); k++)
        {
            std::cin >> scheduleTemplate.at(i).at(k);
        }
    }
    scheduleTemplate.insert(scheduleTemplate.begin(), scheduleTemplate.back());
    scheduleTemplate.pop_back();
    for (int i = 0; i < demand.size(); i++)
    {
        for (int k = 0; k < demand.at(i).size(); k++)
        {
            std::cin >> demand.at(i).at(k);
        }
    }
    std::vector<std::vector<int>> possibleRestSchedule = genRestSchedule(days, restLimit);
    for (int i = 0; i < workerSchedule.size(); i++)
    {
        workerSchedule.at(i) = possibleRestSchedule.at(i % possibleRestSchedule.size());
    }
    int workingScheduleCnt = 0;
    for (int i = 0; i < days; i++)
    {
        for (int k = 0; k < workerSchedule.size(); k++)
        {
            if (workerSchedule.at(k).at(i) != 0)
            {
                workerSchedule.at(k).at(i) = 1 + (workingScheduleCnt % numberOfSchedule);
                workingScheduleCnt += 1;
            }
        }
    }
    int result = 0;
    for (int i = 0; i < demand.size(); i++)
    {
        // std::cout << "Day: " << i << std::endl;
        for (int k = 0; k < demand.at(i).size(); k++)
        {
            int workerSupply = 0;
            for (int r = 0; r < workerSchedule.size(); r++)
            {
                workerSupply += scheduleTemplate.at(workerSchedule.at(r).at(i)).at(k);
            }
            result += std::max(0, demand.at(i).at(k) - workerSupply);
        }
    }
    std::cout << result << std::endl;
    return 0;
}