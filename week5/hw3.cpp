#include <iostream>
#define maxCustomer 200

int main()
{
    int customerCount, couponCount;
    std::cin >> customerCount >> couponCount;
    int lastVisit[maxCustomer];
    int averageMoney[maxCustomer];
    int custumerNumber[maxCustomer];
    for (int i = 0; i < customerCount; i++)
    {
        std::cin >> lastVisit[i];
        if (lastVisit[i] > 12)
        {
            lastVisit[i] = -1;
        }
    }
    for (int i = 0; i < customerCount; i++)
    {
        std::cin >> averageMoney[i];
        custumerNumber[i] = i + 1;
    }
    int cache;                                  // for swaping numbers
    for (int i = customerCount - 1; i > 0; i--) // bubble sort
    {
        for (int k = 0; k < i; k++)
        {
            if (lastVisit[k] < lastVisit[k + 1] || (lastVisit[k] == lastVisit[k + 1] && averageMoney[k] < averageMoney[k + 1]))
            {
                // since bubble sort is a stable sorting algorithm, hence there is no need to consider customer number.
                cache = custumerNumber[k];
                custumerNumber[k] = custumerNumber[k + 1];
                custumerNumber[k + 1] = cache;
                cache = lastVisit[k];
                lastVisit[k] = lastVisit[k + 1];
                lastVisit[k + 1] = cache;
                cache = averageMoney[k];
                averageMoney[k] = averageMoney[k + 1];
                averageMoney[k + 1] = cache;
            }
        }
    }
    /*
    for (int i = 0; i < customerCount; i++)
    {
        std::cout << custumerNumber[i] << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < customerCount; i++)
    {
        std::cout << lastVisit[i] << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < customerCount; i++)
    {
        std::cout << averageMoney[i] << ' ';
    }
    std::cout << std::endl;
    */
    int result[maxCustomer];
    int resultPtr = 0;
    for (int i = 0; i < customerCount; i++)
    {
        if (lastVisit[i] > 0 && couponCount > 0)
        {
            result[resultPtr] = custumerNumber[i];
            resultPtr += 1;
            couponCount -= 1;
        }
    }
    for (int i = 0; i < resultPtr; i++)
    {
        std::cout << result[i];
        if (i == resultPtr - 1)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << ',';
        }
    }
}