#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>

std::map<std::string, std::string> database;

std::vector<std::string> split(std::string data, std::string target = " ")
{
    std::string token;
    std::vector<std::string> result;
    for (int i = 0; i < data.size(); i++)
    {
        for (auto ch : target)
        {
            if (data.at(i) == ch)
            {
                data.at(i) = ' ';
            }
        }
    }
    std::stringstream ss;
    ss << data;
    while (ss >> token)
    {
        result.push_back(token);
    }
    return result;
}

auto accessIndex(std::string str)
{
    std::pair<int, std::string> result;
    auto cache = split(str, "[]");
    result.second = cache.at(0);
    result.first = std::stoi(cache.at(1));
    return result;
}

std::string parser(std::string str)
{
    if (str.find('"') != std::string::npos)
    {
        str.pop_back();
        str.erase(str.begin());
        return str;
    }
    else if (str.find('+') != std::string::npos)
    {
        std::vector<std::string> addition = split(str, "+");
        return database.at(addition.at(0)) + database.at(addition.at(1));
    }
    else if (str.find('*') != std::string::npos)
    {
        std::vector<std::string> multiplication = split(str, "*");
        int t = std::stoi(multiplication.at(1));
        std::string result;
        for (int i = 0; i < t; i++)
        {
            result += database.at(multiplication.at(0));
        }
        return result;
    }
    else if (str.find('[') != std::string::npos)
    {
        std::pair<int, std::string> cache = accessIndex(str);
        return std::string(1, database.at(cache.second).at(cache.first));
    }
    else
    {
        return database.at(str);
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::string rawInstruction;
    std::cin.ignore();
    for (int i = 0; i < n; i++)
    {
        // std::cout << "Start Instruction: " << std::endl;
        std::getline(std::cin, rawInstruction);
        std::vector<std::string> instruction = split(rawInstruction);
        if (instruction.at(0) == "declare" || instruction.at(0) == "assignObject")
        {
            database[instruction.at(1)] = parser(instruction.at(2));
        }
        else if (instruction.at(0) == "assignString")
        {
            if (instruction.at(1).find('[') != std::string::npos)
            {
                std::pair<int, std::string> cache = accessIndex(instruction.at(1));
                database[cache.second].at(cache.first) = parser(instruction.at(2)).at(0);
            }
            else
            {
                database[instruction.at(1)] = parser(instruction.at(2));
            }
        }
        else if (instruction.at(0) == "print")
        {
            std::cout << parser(instruction.at(1)) << std::endl;
        }
        // std::cout << "End instruction" << std::endl;
    }
    return 0;
}