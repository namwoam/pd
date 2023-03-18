#include <iostream>
#include <cstring>

#define MEMBER_LIMIT 100
#define NAME_LIMIT 200
#define PHONE_NUMBER_LIMIT 20

struct Member
{
    char firstName[NAME_LIMIT], lastName[NAME_LIMIT], phoneNumber[PHONE_NUMBER_LIMIT];
    int year, month, day;
    bool isValid = false;
    unsigned long long getTime()
    {
        return day + month * 100 + year * 10000;
    }
    bool operator>(struct Member &other)
    {
        unsigned long long selfTime = getTime(), otherTime = other.getTime();
        if (selfTime == otherTime)
        {
            return !strcmp(lastName, other.lastName);
        }
        return selfTime < otherTime;
    }
};

void sort(struct Member *data, int n)
{
    for (int i = 0; i < n; i++)
    {
        int biggestPos = i;
        for (int k = i + 1; k < n; k++)
        {
            if (data[k] > data[biggestPos])
            {
                biggestPos = k;
            }
        }
        struct Member tmp;
        tmp = data[biggestPos];
        data[biggestPos] = data[i];
        data[i] = tmp;
    }
}

bool fistFourEqual(char *l, char *r)
{
    for (int i = 0; i < 4; i++)
    {
        if (l[i] != r[i])
        {
            return false;
        }
    }
    return true;
}

int check(struct Member *data, int n, int ageLimit, int algorNum, char *searchNumber)
{
    int result = 0;
    struct Member ageCheck;
    ageCheck.year = 2021 - (ageLimit - 1);
    ageCheck.month = 11;
    ageCheck.day = 3;
    for (int i = 0; i < n; i++)
    {
        bool flag = false;
        if (algorNum == 1)
        {
            // std::cout << data[i].getTime() << ' ' << ageCheck.getTime() << std::endl;
            if (data[i] > ageCheck)
            {
                flag = true;
            }
        }
        else if (algorNum == 2)
        {
            if (fistFourEqual(searchNumber, data[i].phoneNumber))
            {
                flag = true;
            }
        }
        else if (algorNum == 3)
        {
            if (data[i] > ageCheck || fistFourEqual(searchNumber, data[i].phoneNumber))
            {
                flag = true;
            }
        }
        else if (algorNum == 4)
        {
            if (data[i] > ageCheck && fistFourEqual(searchNumber, data[i].phoneNumber))
            {
                flag = true;
            }
        }
        if (flag == true)
        {
            data[i].isValid = true;
            result += 1;
        }
    }
    return result;
}

int main()
{
    int n, algorNum, ageLimit;
    std::cin >> n >> algorNum >> ageLimit;
    char searchNumber[PHONE_NUMBER_LIMIT];
    std::cin >> searchNumber;
    struct Member data[MEMBER_LIMIT];
    char firstName[NAME_LIMIT], lastName[NAME_LIMIT];
    char ch;
    for (int i = 0; i < n; i++)
    {
        std::cin >> data[i].firstName;
        int ptr = 0;
        while (std::cin >> ch)
        {
            if (ch == ',')
            {
                data[i].lastName[ptr] = '\0';
                break;
            }
            else
            {
                data[i].lastName[ptr] = ch;
                ptr += 1;
            }
        }
        // seperate member lastname and birthday
        std::cin >> data[i].year >> ch >> data[i].month >> ch >> data[i].day >> ch >> data[i].phoneNumber;
    }
    sort(data, n);
    // sort member by age;
    int validCnt = check(data, n, ageLimit, algorNum, searchNumber);
    // validate member
    for (int i = 0; i < n; i++)
    {
        if (data[i].isValid == true)
        {
            std::cout << data[i].firstName << ' ' << data[i].lastName << ',';
            // output first valid member
            break;
        }
    }
    std::cout << validCnt << std::endl;
    return 0;
}