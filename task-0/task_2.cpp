
#include <iostream>
#include <vector>



void get_distribution(std::vector<int>& vect, int middle)
{
    for(int idx = 0; idx < vect.size(); ++idx)
    {
        std::cout << "for " << idx + 1 << " ship: "<< middle - vect[idx] << std::endl;
    }
}

int get_middle(const std::vector<int>& vect)
{
    int sum = 0;
    int middle = 0;

    for(int idx = 0; idx < vect.size(); ++idx)
    {
        sum += vect[idx];
    }

    middle = sum / vect.size();

    return middle;
}

void input_dates(std::vector<int>& vect)
{
    int n = 0;
    int number_chestes = 0;
    
    std::cout << "Input numbers of ships." << std::endl;
    std::cin >> n;

    for(int idx = 0; idx < n; ++idx)
    {
        std::cout << "Input numbers of chestes in " << idx + 1 << " ship." << std::endl;
        std::cin >> number_chestes;

        vect.push_back(number_chestes);
    }    
}


int main()
{
    int middle = 0;

    std::vector<int> chestes;
    input_dates(chestes);
    
    middle = get_middle(chestes);

    get_distribution(chestes, middle);

    return 0;
}
