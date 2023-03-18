#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <algorithm>
#include <tuple>
#include <random>
#include <chrono>
#include <limits>

#define SHIFT_COUNT 24
#define FULL_BLOCK_SIZE 4
#define EPOCH_NUM 1
#define OPTIMIZE_CYCLE 40000

bool overtime(int time)
{
    if (time >= 18)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class dayData
{
public:
    std::array<int, SHIFT_COUNT> data;
};

class daySchedule : public dayData
{
public:
    bool isOvertime;
    bool isHoliday;
    void checkStatus();
};
class dayDemand : public dayData
{
public:
    std::array<int, SHIFT_COUNT> dynamicDemand;
    void resetDynamicDemand();
    dayDemand();
    std::vector<bool> applyWork(int);
    void unapplyWork(std::vector<bool>);
    int unsatisfiedDemand();
    int testWorkReward(int);
};

class workerSchedule
{
public:
    int holidayCount, id;
    bool prevOvertime;
    std::vector<int> workingSchedule;
    std::vector<int> rewardData;
    std::vector<std::vector<bool>> rewardInfo;
    std::set<int> requestHoliday;
    workerSchedule();
    workerSchedule(int);
    void updateSchedule(int, int, int);
    void processBlock(int, int, std::vector<dayDemand> &);
    void extraHoliday();
    void getEnoughHoliday();
    int unsatisfiedHoliday();
};

class scheduler
{
public:
    static std::vector<daySchedule> scheduleDatabese;
    static int day, holidayLimit, holidayPenalty, overtimePenalty;
    std::vector<dayDemand> demands;
    std::vector<workerSchedule> workers;
    int startDelta, result = 0;
    scheduler(std::vector<dayDemand>, std::vector<workerSchedule>, int);
    void eval();
    void print();
    void optimize();
};

std::istream &operator>>(std::istream &in, dayData &d)
{
    for (auto &i : d.data)
    {
        in >> i;
    }
    return in;
}

void daySchedule::checkStatus()
{
    for (auto i : data)
    {
        if (i != 0 && i != 1)
        {
            throw std::runtime_error("All number in a schedule must be 0 or 1");
        }
    }
    isHoliday = true;
    for (auto i : data)
    {
        if (i != 0)
        {
            isHoliday = false;
            break;
        }
    }
    isOvertime = false;
    for (int i = 0; i < data.size(); i++)
    {
        if (overtime(i) && data.at(i) == 1)
        {
            isOvertime = true;
            break;
        }
    }
}

void dayDemand::resetDynamicDemand()
{
    for (int i = 0; i < data.size(); i++)
    {
        dynamicDemand.at(i) = data.at(i);
    }
}
dayDemand::dayDemand() : dayData()
{
    resetDynamicDemand();
}
std::vector<bool> dayDemand::applyWork(int scheduleNumber)
{
    std::vector<bool> info(SHIFT_COUNT);
    auto schedule = scheduler::scheduleDatabese.at(scheduleNumber);
    for (int i = 0; i < dynamicDemand.size(); i++)
    {
        if (dynamicDemand.at(i) > 0 && schedule.data.at(i) == 1)
        {
            info.at(i) = true;
            dynamicDemand.at(i) -= schedule.data.at(i);
        }
        else
        {
            info.at(i) = false;
        }
    }
    return info;
}
int dayDemand::unsatisfiedDemand()
{
    int sum = 0;
    for (auto i : dynamicDemand)
    {
        sum += i;
    }
    return sum;
}
int dayDemand::testWorkReward(int scheduleNumber)
{
    int reward = 0;
    auto schedule = scheduler::scheduleDatabese.at(scheduleNumber);
    for (int i = 0; i < dynamicDemand.size(); i++)
    {
        if (dynamicDemand.at(i) > 0 && schedule.data.at(i) == 1)
        {
            reward += 1;
        }
    }
    return reward;
}

void dayDemand::unapplyWork(std::vector<bool> info)
{
    for (int i = 0; i < info.size(); i++)
    {
        if (info.at(i) == true)
        {
            dynamicDemand.at(i) += 1;
        }
    }
    return;
}

workerSchedule::workerSchedule(int workerId)
{
    id = workerId;
    holidayCount = 0;
    prevOvertime = false;
    workingSchedule = std::vector<int>(scheduler::day);
    rewardData = std::vector<int>(scheduler::day);
    rewardInfo = std::vector<std::vector<bool>>(scheduler::day, std::vector<bool>(SHIFT_COUNT));
}
void workerSchedule::updateSchedule(int pos, int scheduleNumber, int reward)
{
    if (scheduleNumber == 0)
    {
        holidayCount += 1;
        if (requestHoliday.count(pos) == 1)
        {
            requestHoliday.erase(pos);
        }
    }
    workingSchedule.at(pos) = scheduleNumber;
    rewardData.at(pos) = reward;
}
void workerSchedule::processBlock(int startPos, int blockSize, std::vector<dayDemand> &demandData)
{
    blockSize = std::min(int(demandData.size()), startPos + blockSize) - startPos;
    if (blockSize == 0)
    {
        return;
    }
    // std::cout << "Process Block" << std::endl;
    std::vector<std::tuple<int, int, int>> best; // day , schuduleNum , reward
    std::vector<std::tuple<int, int, int>> bestNoOvertime;
    std::vector<std::pair<int, int>> overtimeReward; // day , difference of best and bestNoOvertime
    for (int i = startPos; i < startPos + blockSize; i++)
    {
        // compute possible work;
        std::vector<std::pair<int, int>> possibleSchedule; // schuduleNum , reward
        for (int k = 0; k < scheduler::scheduleDatabese.size(); k++)
        {
            int reward = demandData.at(i).testWorkReward(k);
            if (requestHoliday.count(i) != 0 && k != 0)
            {
                reward -= scheduler::holidayPenalty;
            }
            possibleSchedule.push_back(std::pair<int, int>(k, reward));
        }
        std::sort(possibleSchedule.begin(), possibleSchedule.end(),
                  [](std::pair<int, int> l, std::pair<int, int> r)
                  {
                      return l.second > r.second;
                  });
        // sort in descending by reward
        std::pair<int, int> bestSchedule = possibleSchedule.front(), bestNoOvertimeSchedule;
        for (auto el : possibleSchedule)
        {
            if (scheduler::scheduleDatabese.at(el.first).isOvertime == false)
            {
                bestNoOvertimeSchedule = el;
                break;
            }
        }
        // std::cout << "best ScheduleNum: " << bestSchedule.first << " reward: " << bestSchedule.second << std::endl;
        // std::cout << "best no overtime ScheduleNum: " << bestNoOvertimeSchedule.first << " reward: " << bestNoOvertimeSchedule.second << std::endl;
        best.push_back(std::tuple<int, int, int>(i, bestSchedule.first, bestSchedule.second));
        bestNoOvertime.push_back(std::tuple<int, int, int>(i, bestNoOvertimeSchedule.first, bestNoOvertimeSchedule.second));
        overtimeReward.push_back(std::pair<int, int>(i, bestSchedule.second - bestNoOvertimeSchedule.second));
    }

    // choose which day to work overtime
    auto bestOvertimeReward = std::max_element(overtimeReward.begin(), overtimeReward.end(), [](auto l, auto r)
                                               { return l.second < r.second; });
    if (prevOvertime == false || (prevOvertime == true && bestOvertimeReward->second >= scheduler::overtimePenalty * 2))
    {
        if (bestOvertimeReward->second > 0)
        {
            int pos = std::distance(overtimeReward.begin(), bestOvertimeReward);
            bestNoOvertime.at(pos) = best.at(pos);
        }
    }
    bool haveHoliday = false;
    for (auto &el : bestNoOvertime)
    {
        if (scheduler::scheduleDatabese.at(std::get<1>(el)).isHoliday == true)
        {
            haveHoliday = true;
            break;
        }
    }
    std::sort(bestNoOvertime.begin(), bestNoOvertime.end(),
              [](std::tuple<int, int, int> l, std::tuple<int, int, int> r)
              {
                  return std::get<2>(l) < std::get<2>(r);
              });
    // sort bestNoOverTime by reward in ascending order
    if (haveHoliday == false && blockSize == FULL_BLOCK_SIZE)
    {
        // force to rest on the day with lowest reward
        std::get<1>(bestNoOvertime.at(0)) = 0;
        std::get<2>(bestNoOvertime.at(0)) = 0;
    }
    bool haveOvertime = false;
    prevOvertime = false;
    for (auto &el : bestNoOvertime)
    {
        if (scheduler::scheduleDatabese.at(std::get<1>(el)).isOvertime)
        {
            haveOvertime = true;
            break;
        }
        // check if this block contains overtime
    }
    if (prevOvertime && haveOvertime == true)
    {
        prevOvertime = true;
    }
    else
    {
        prevOvertime = haveOvertime;
    }
    // std::cout << "Check Point" << std::endl;
    for (auto &el : bestNoOvertime)
    {
        // update worker schedule
        updateSchedule(std::get<0>(el), std::get<1>(el), std::get<2>(el));
        // update demand
        auto info = demandData.at(std::get<0>(el)).applyWork(std::get<1>(el));
        rewardInfo.at(std::get<0>(el)) = info;
    }
    // std::cout << "Process Block End" << std::endl;
    return;
}
void workerSchedule::extraHoliday()
{
    // return the position of next holiday
    int minRewardPosition = -1;
    for (int i = 0; i < rewardData.size(); i++)
    {
        if (workingSchedule.at(i) != 0)
        {
            if (minRewardPosition == -1)
            {
                minRewardPosition = i;
            }
            else if (rewardData.at(i) < rewardData.at(minRewardPosition))
            {
                minRewardPosition = i;
            }
        }
    }
    if (minRewardPosition == -1)
    {
        throw std::runtime_error("Can't have more holiday");
    }
    updateSchedule(minRewardPosition, 0, 0);
}
void workerSchedule::getEnoughHoliday()
{
    while (holidayCount < scheduler::holidayLimit)
    {
        // std::cout << holidayCount << std::endl;
        extraHoliday();
    }
}
int workerSchedule::unsatisfiedHoliday()
{
    return requestHoliday.size();
}

scheduler::scheduler(std::vector<dayDemand> _demands, std::vector<workerSchedule> _workers, int _startDelta)
{
    result = 0;
    demands = _demands;
    workers = _workers;
    startDelta = _startDelta;
}
void scheduler::eval()
{
    for (auto &demand : demands)
    {
        demand.resetDynamicDemand();
    }
    for (auto &worker : workers)
    {
        worker.processBlock(0, startDelta, demands);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(workers.begin(), workers.end(), std::default_random_engine(seed));
    std::stable_sort(workers.begin(), workers.end(),
                     [](workerSchedule l, workerSchedule r)
                     {
                         return l.prevOvertime < r.prevOvertime;
                     });
    int pos = startDelta;
    while (pos < demands.size())
    {
        for (auto &worker : workers)
        {
            worker.processBlock(pos, FULL_BLOCK_SIZE, demands);
        }
        std::rotate(workers.rbegin(), workers.rbegin() + 5, workers.rend());
        pos += FULL_BLOCK_SIZE;
    }
    for (auto &worker : workers)
    {
        worker.getEnoughHoliday();
    }
    optimize();
    result = 0;
    for (auto demand : demands)
    {
        result += demand.unsatisfiedDemand();
    }
    for (auto worker : workers)
    {
        result += worker.unsatisfiedHoliday() * holidayPenalty;
    }
}

void scheduler::optimize()
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> randomDay(0, scheduler::day - 1), randomWorker(0, workers.size() - 1);
    for (int i = 0; i < OPTIMIZE_CYCLE; i++)
    {
        int targetDay = randomDay(gen), targetWorker = randomWorker(gen);
        int originalScheduleNum = workers.at(targetWorker).workingSchedule.at(targetDay);
        int originalReward = workers.at(targetWorker).rewardData.at(targetDay);
        if (scheduler::scheduleDatabese.at(originalScheduleNum).isHoliday)
        {
            continue;
        }
        std::pair<int, int> bestSchedule(originalScheduleNum, originalReward); // scheduleNum , reward
        demands.at(targetDay).unapplyWork(workers.at(targetWorker).rewardInfo.at(targetDay));
        for (int i = 1; i < scheduler::scheduleDatabese.size(); i++)
        {
            int reward = demands.at(targetDay).testWorkReward(i);
            if ((reward > bestSchedule.second) && (scheduler::scheduleDatabese.at(i).isOvertime == scheduler::scheduleDatabese.at(originalScheduleNum).isOvertime))
            {
                bestSchedule.first = i;
                bestSchedule.second = reward;
                // std::cout << "Optimization!" << std::endl;
            }
        }
        auto info = demands.at(targetDay).applyWork(bestSchedule.first);
        workers.at(targetWorker).updateSchedule(targetDay, bestSchedule.first, bestSchedule.second);
        workers.at(targetWorker).rewardInfo.at(targetDay) = std::move(info);
    }
}

void scheduler::print()
{
    std::sort(workers.begin(), workers.end(),
              [](workerSchedule l, workerSchedule r)
              {
                  return l.id > r.id;
              });
    // sort workers by theri id in ascending order
    for (auto worker : workers)
    {
        for (int i = 0; i < worker.workingSchedule.size(); i++)
        {
            std::cout << worker.workingSchedule.at(i);
            if (i == worker.workingSchedule.size() - 1)
            {
                std::cout << std::endl;
            }
            else
            {
                std::cout << ',';
            }
        }
    }
}

int scheduler::day, scheduler::holidayLimit, scheduler::holidayPenalty, scheduler::overtimePenalty;
std::vector<daySchedule> scheduler::scheduleDatabese;

int main()
{
    int numberOfWorker, numberOfSchedule, day, holidayPenalty, overtimePenalty, numberOfRequest, holidayLimit;
    std::cin >> numberOfWorker >> day >> numberOfSchedule >> holidayLimit >> holidayPenalty >> overtimePenalty >> numberOfRequest;
    scheduler::scheduleDatabese = std::vector<daySchedule>(numberOfSchedule + 1);
    scheduler::day = day;
    scheduler::holidayLimit = holidayLimit;
    scheduler::holidayPenalty = holidayPenalty;
    scheduler::overtimePenalty = overtimePenalty;
    for (int i = 0; i < scheduler::scheduleDatabese.size(); i++)
    {
        if (i == scheduler::scheduleDatabese.size() - 1)
        {
            std::cin >> scheduler::scheduleDatabese.at(0);
            scheduler::scheduleDatabese.at(0).checkStatus();
        }
        else
        {
            std::cin >> scheduler::scheduleDatabese.at(i + 1);
            scheduler::scheduleDatabese.at(i + 1).checkStatus();
        }
    }
    // std::cout << "schedule completed" << std::endl;
    std::vector<dayDemand> demandsInput(scheduler::day);
    for (auto &el : demandsInput)
    {
        std::cin >> el;
    }
    // std::cout << "demand completed" << std::endl;
    std::vector<workerSchedule> workersInput;
    for (int i = 0; i < numberOfWorker; i++)
    {
        workerSchedule worker(i);
        workersInput.push_back(worker);
    }
    // std::cout << "worker completed" << std::endl;
    std::vector<std::pair<int, int>> holidayRequest(numberOfRequest); // requester , day
    for (int i = 0; i < holidayRequest.size(); i++)
    {
        std::cin >> holidayRequest.at(i).first;
    }
    for (int i = 0; i < holidayRequest.size(); i++)
    {
        std::cin >> holidayRequest.at(i).second;
    }
    for (int i = 0; i < holidayRequest.size(); i++)
    {
        workersInput.at(holidayRequest.at(i).first - 1).requestHoliday.insert(holidayRequest.at(i).second - 1);
    }
    // std::cout << "holiday request" << std::endl;
    //  Input should not be modified by scheduler
    scheduler bestScheduler(demandsInput, workersInput, 0);
    bestScheduler.eval();
    // bestScheduler.print();
    for (int i = 0; i < EPOCH_NUM; i++)
    {
        for (int k = 0; k < FULL_BLOCK_SIZE; k++)
        {
            scheduler newScheduler(demandsInput, workersInput, k);
            newScheduler.eval();
            std::cout << newScheduler.result << std::endl;
            if (newScheduler.result < bestScheduler.result)
            {
                bestScheduler = newScheduler;
            }
        }
    }
    // bestScheduler.print();
    return 0;
}