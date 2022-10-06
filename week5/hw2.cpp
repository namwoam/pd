#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    int kidCount, toyCount;
    std::cin >> toyCount >> kidCount;
    std::vector<std::vector<int>> data(kidCount, std::vector<int>(toyCount));
    for (int i = 0; i < data.size(); i++)
    {
        for (int k = 0; k < data.at(i).size(); k++)
        {
            std::cin >> data.at(i).at(k);
        }
    }
    std::vector<int> remainKid(kidCount), remainToy(toyCount);
    std::iota(remainKid.begin(), remainKid.end(), 0);
    std::iota(remainToy.begin(), remainToy.end(), 0);
    int joySum = 0;
    while (remainKid.empty() != true)
    {
        int selectedToyLocation = 0, selectedKidLocation = 0;
        for (int i = 0; i < remainToy.size(); i++)
        {
            for (int k = 0; k < remainKid.size(); k++)
            {
                if (data.at(remainKid.at(k)).at(remainToy.at(i)) > data.at(remainKid.at(selectedKidLocation)).at(remainToy.at(selectedToyLocation)))
                {
                    selectedToyLocation = i;
                    selectedKidLocation = k;
                }
            }
        }
        //std::cout << remainKid.at(selectedKidLocation) + 1 << ' ' << remainToy.at(selectedToyLocation) + 1 << std::endl;
        //std::cout << "Added " << data.at(remainKid.at(selectedKidLocation)).at(remainToy.at(selectedToyLocation)) << std::endl;
        joySum += data.at(remainKid.at(selectedKidLocation)).at(remainToy.at(selectedToyLocation));
        remainKid.erase(remainKid.begin() + selectedKidLocation);
        remainToy.erase(remainToy.begin() + selectedToyLocation);
    }
    std::cout << joySum << std::endl;
    return 0;
}