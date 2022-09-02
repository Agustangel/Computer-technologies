
#include <iostream>
#include <vector>
#include <cmath>



bool is_even(int element)
{
    if (fmod(element, 2) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void variation_elements(std::vector<int>& vect)
{
    for(int idx = 0; idx < vect.size(); ++idx)
    {
        if(is_even(vect[idx]))
        {
            vect[idx] *= 2;
            std::cout << idx + 1 << " element of vector is " << vect[idx] << std::endl;
        }
        else
        {
            vect[idx] += 2;
            std::cout << idx + 1 << " element of vector is " << vect[idx] << std::endl;
        }
        
    }
}

void input_dates(std::vector<int>& vect)
{
    int n = 0;
    int num = 0;
    
    std::cout << "Input numbers of elements." << std::endl;
    std::cin >> n;

    for(int idx = 0; idx < n; ++idx)
    {
        std::cout << "Input element of " << idx + 1 << " cell." << std::endl;
        std::cin >> num;

        vect.push_back(num);
    }    
}

int main()
{
    std::vector<int> numbers;
    input_dates(numbers);

    variation_elements(numbers);

    return 0;
}
