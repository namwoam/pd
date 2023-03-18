#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Customer
{
public:
    std::string name;
    int lastVisit, averageSpend;
    Customer() = default;
    bool operator<(const Customer &c) const
    {
        if (lastVisit == c.lastVisit)
        {
            return averageSpend > c.averageSpend;
        }
        return lastVisit > c.lastVisit;
    }
    bool updateStatus()
    {
        if (lastVisit > 12)
        {
            lastVisit = -1;
            return false;
        }
        return true;
    }
};

int main()
{
    int customerCount, couponCount;
    std::cin >> customerCount >> couponCount;
    std::vector<Customer> customers(customerCount);
    std::string names;
    std::cin.ignore();
    std::getline(std::cin, names);
    int customerPtr = 0, stringPtr = 0;
    while (customerPtr < customers.size() && stringPtr < names.size())
    {
        char chr = names.at(stringPtr);
        if (chr == ',')
        {
            customerPtr += 1;
        }
        else
        {
            customers.at(customerPtr).name.push_back(chr);
        }
        stringPtr += 1;
    }
    int validCount = 0;
    for (int i = 0; i < customers.size(); i++)
    {
        std::cin >> customers.at(i).lastVisit;
        if (customers.at(i).updateStatus() == true)
        {
            validCount += 1;
        }
    }
    for (int i = 0; i < customers.size(); i++)
    {
        std::cin >> customers.at(i).averageSpend;
    }
    std::stable_sort(customers.begin(), customers.end());
    int outputCount = std::min(validCount, couponCount);
    for (int i = 0; i < outputCount; i++)
    {
        std::cout << customers.at(i).name;
        if (i == outputCount - 1)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << ',';
        }
    }
}