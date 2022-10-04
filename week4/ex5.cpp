#include <iostream>

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    int result = 0, limit = 0, input, tmp;
    for (int i = 0; i < a; i++)
    {
        tmp = 0;
        for (int k = 0; k < b; k++)
        {
            std::cin >> input;
            if (input >= c)
            {
                tmp += 1;
            }
        }
        if (tmp > limit)
        {
            result = i + 1;
            limit = tmp;
        }
    }
    std::cout << result << std::endl;
    return 0;
}