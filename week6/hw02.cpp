#include <iostream>
#include <vector>
#include <algorithm>
#define NUMBER_OF_SHIFT 24

int main()
{
    int numberOfEmployee, numberOfSchedule, days, restConst, overtimeConst, numberOfRequest, L;
    std::cin >> numberOfEmployee >> days >> numberOfSchedule >> L >> restConst >> overtimeConst >> numberOfRequest;
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
    for (int i = 0; i < workerSchedule.size(); i++)
    {
        for (int k = 0; k < workerSchedule.at(i).size(); k++)
        {
            std::cin >> workerSchedule.at(i).at(k);
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