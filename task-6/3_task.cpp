
#include <iostream>
#include <vector>


//=========================================================================
void inputData(std::vector<int>& vect)
{
    int elem = 0;

    while(std::cin.good())
    {
        std::cin >> elem;
        vect.push_back(elem);
    }
}

//=========================================================================

void sortVector(std::vector<int>& vect)
{
    for(int i = 0; i < vect.size(); ++i)
    {
        for(int j = i; j < (vect.size()); ++j)
        {
            if (vect[i] < vect[j])
            {
                std::swap(vect[i], vect[j]);
            }
        }
    }
}

//=========================================================================

void outputVector(std::vector<int>& vect)
{
    std::cout << std::endl;
    std::cout << "New vector: " << std::endl;

    for(int idx = 0; idx < vect.size(); ++idx)
    {
        std::cout << vect[idx] << ' ';
    }
    std::cout << std::endl;
}

//=========================================================================

int main()
{
    std::vector<int> vect;
    inputData(vect);

    sortVector(vect);
    outputVector(vect);

    return 0;
}
