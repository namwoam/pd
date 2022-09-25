#include <iostream>
int main()
{
    int n, t, input, result = 0;
    std::cin >> n >> t;
    for (int i = 0; i < n; i++)
    {
        std::cin >> input;
        if (input == t)
        {
            break;
        }
        result += input;
    }
    std::cout << result << std::endl;
    return 0;
}