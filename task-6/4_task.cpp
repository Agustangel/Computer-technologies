
#include <iostream>
#include <vector>


//=========================================================================
void inputData(std::vector<int>& vect, int* given_number)
{
    int n = 0;
    int elem = 0;

    std::cout << "Input some number: " << std::endl;
    std::cin >> *given_number;

    std::cout << "Input number of elements: " << std::endl;
    std::cin >> n;

    std::cout << "Input elements of vector: " << std::endl;
    for(int idx = 0; idx < n; ++idx)
    {
        std::cin >> elem;
        vect.push_back(elem);
    }   
}

//=========================================================================

int getMax(std::vector<int>& vect)
{
    int max = vect[0];
    for(int idx = 1; idx < vect.size(); ++idx)
    {
        if(vect[idx] > max)
        {
            max = vect[idx];
        }
    }

    return max;
}

//=========================================================================

void printIndex(std::vector<int>& vect, int given_number)
{
    int min = getMax(vect);
    int idx_min = 0;

    for(int idx = 0; idx < vect.size(); ++idx)
    {
        if((vect[idx] > given_number) && (vect[idx] < min))
        {
            min = vect[idx];
            idx_min = idx;
        }
    }

    std::cout << "min = " <<  min << std::endl;
    std::cout << "idx_min = " <<  idx_min << std::endl;
}

//=========================================================================

int main()
{
    int given_number = 0;
    std::vector<int> vect;

    inputData(vect, &given_number);
    printIndex(vect, given_number);

    return 0;
}
