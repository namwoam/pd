#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string str;
    std::getline(std::cin, str);
    for (int i = 0; i < str.size() - 1; i++)
    {
        if (isspace(str.at(i)) && isspace(str.at(i + 1)))
        {
            str.erase(i, 1);
            i -= 1;
        }
    }
    // std::cout << str << std::endl;
    for (int i = 0; i < str.size(); i++)
    {
        bool frontSpace = (i == 0 ? false : str.at(i - 1) == ' ');
        bool backSpace = (i == str.size() - 1 ? false : str.at(i + 1) == ' ');
        // std::cout << str.at(i) << ' ' << frontSpace << ' ' << backSpace << std::endl;
        char ch = str.at(i);
        if (ch == '.' || ch == ',' || ch == ':' || ch == '!' || ch == '?' || ch == ';' || ch == ')')
        {
            if (frontSpace)
            {
                // std::cout << "Delete front space" << std::endl;
                str.erase(i - 1, 1);
                i -= 1;
            }
            if (!backSpace && i != str.size() - 1)
            {

                str.insert(i + 1, 1, ' ');
            }
        }
        else if (ch == '(')
        {
            if (!frontSpace)
            {
                str.insert(i, 1, ' ');
                i += 1;
            }
            if (backSpace)
            {
                str.erase(i + 1, 1);
            }
        }
        else if (ch == '-')
        {
            if (frontSpace)
            {
                str.erase(i - 1, 1);
                i -= 1;
            }
            if (backSpace)
            {
                str.erase(i + 1, 1);
            }
        }
    }
    std::cout << str << std::endl;
    return 0;
}