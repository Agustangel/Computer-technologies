
#include <iostream>
#include <vector>
#include <algorithm>


void inputData(std::vector<int>& vect);
void outputVector(std::vector<int>& vect);
void reverseVector(std::vector<int>& vect);

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

void outputVector(std::vector<int>& vect)
{
    std::cout << "New vector: " << std::endl;

    for(int idx = 0; idx < vect.size(); ++idx)
    {
        std::cout << vect[idx] << ' ';
    }
    std::cout << std::endl;
}

//=========================================================================
void reverseVector(std::vector<int>& vect)
{
    std::reverse(vect.begin(), vect.end());
}

//=========================================================================

int main()
{
    std::vector<int> vect;
    inputData(vect);

    reverseVector(vect);
    outputVector(vect);

    return 0;
}
