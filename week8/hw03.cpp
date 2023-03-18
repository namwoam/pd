#include <iostream>
#include <cstring>

#define maxProductCount 30
#define maxNameLength 200
#define maxRecordCount 30
#define traceRecord 3
#define maxCustomerCount 120
class Customer
{
public:
    char name[maxNameLength];
    int purchaseRecord[maxProductCount] = {0};
    int purchaseHistory[traceRecord] = {0};
    int historyCount = 0;
    int lastVisit, averageSpend, targetProductNumber;
    Customer() = default;
    void updateRecord(int productNumber, int count)
    {
        purchaseRecord[productNumber] += count;
        for (int i = traceRecord - 1; i > 0; i--)
        {
            purchaseHistory[i] = purchaseHistory[i - 1];
        }
        purchaseHistory[0] = productNumber;
        historyCount += 1;
    }
    bool checkStatus()
    {
        if (lastVisit > 12)
        {
            lastVisit = -1;
            return false;
        }
        if (purchaseRecord[targetProductNumber] == 0)
        {
            return false;
        }
        return true;
    }
    bool operator<(const Customer &c) const
    {
        if (purchaseRecord[targetProductNumber] == c.purchaseRecord[targetProductNumber])
        {
            if (lastVisit == c.lastVisit)
            {
                return averageSpend < c.averageSpend;
            }
            return lastVisit < c.lastVisit;
        }
        return purchaseRecord[targetProductNumber] < c.purchaseRecord[targetProductNumber];
    }
};

class Record
{
public:
    int buyer = 0, count = 0, productNum = 0;
};

std::ostream &operator<<(std::ostream &os, const Customer &c)
{
    os << c.name << ',';
    int outputCount = (c.historyCount > traceRecord) ? traceRecord : c.historyCount;
    for (int i = outputCount - 1; i >= 0; i--)
    {

        
        os << c.purchaseHistory[i];
        if (i != 0)
        {
            os << ',';
        }
    }
    return os;
}

char bigString[maxCustomerCount * maxNameLength];

int main()
{
    int customerCount, couponCount, recordCount, productCount, targetProduct;
    std::cin >> customerCount >> couponCount >> recordCount >> productCount >> targetProduct;
    std::cin.ignore();
    Customer customers[maxCustomerCount];
    std::cin.getline(bigString, maxCustomerCount * maxNameLength);
    int stringPtr = 0, customerPtr = 0, insertPos = 0;
    while (stringPtr < strlen(bigString) && customerPtr < customerCount)
    {
        char chr = bigString[stringPtr];
        stringPtr += 1;
        if (chr == ',')
        {
            customers[customerPtr].name[insertPos] = '\0';
            customerPtr += 1;
            insertPos = 0;
            continue;
        }
        customers[customerPtr].name[insertPos] = chr;
        insertPos += 1;
    }
    for (int i = 0; i < customerCount; i++)
    {
        std::cin >> customers[i].lastVisit;
    }
    for (int i = 0; i < customerCount; i++)
    {
        std::cin >> customers[i].averageSpend;
    }
    for (int i = 0; i < customerCount; i++)
    {
        customers[i].targetProductNumber = targetProduct;
    }
    Record records[maxRecordCount];
    for (int i = 0; i < recordCount; i++)
    {
        std::cin >> records[i].productNum;
    }
    for (int i = 0; i < recordCount; i++)
    {
        std::cin >> records[i].count;
    }
    for (int i = 0; i < recordCount; i++)
    {
        std::cin >> records[i].buyer;
    }
    for (int i = 0; i < recordCount; i++)
    {
        int buyerPos = records[i].buyer - 1;
        customers[buyerPos].updateRecord(records[i].productNum, records[i].count);
    }
    int validCount = 0;
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].checkStatus() == true)
        {
            validCount += 1;
        }
    }
    int outputCount = validCount > couponCount ? couponCount : validCount;
    for (int i = 0; i < customerCount; i++)
    {
        int biggestPos = i;
        for (int k = i + 1; k < customerCount; k++)
        {
            if (customers[biggestPos] < customers[k])
            {
                biggestPos = k;
            }
        }
        Customer tmp = customers[i];
        customers[i] = customers[biggestPos];
        customers[biggestPos] = tmp;
    }
    for (int i = 0; i < outputCount; i++)
    {
        std::cout << customers[i] << std::endl;
    }
    return 0;
}