
#include <iostream>
#include <vector>


void output_data(std::vector<int>& vect, int average_grade);
int get_average_grade(std::vector<int>& vect);
void input_data(std::vector<int>& vect);

//=========================================================================
void output_data(std::vector<int>& vect, int average_grade)
{
    std::cout << "Average grade is " << average_grade << std::endl;
    std::cout << "Numbers of students with a mark above the average: " << std::endl;

    for(int idx = 0; idx < vect.size(); ++idx)
    {
        if(vect[idx] > average_grade)
        {
            std::cout << idx + 1 << " ";
        }
    }
    std::cout << std::endl;
}

//=========================================================================

int get_average_grade(std::vector<int>& vect)
{
    int sum = 0;
    int average_grade = 0;

    for(int idx = 0; idx < vect.size(); ++idx)
    {
        sum += vect[idx];
    }
    average_grade = sum / vect.size();

    return average_grade;
}

//=========================================================================

void input_data(std::vector<int>& vect)
{
    int n = 0;
    int grade = 0;
    
    std::cout << "Input numbers of students." << std::endl;
    std::cin >> n;

    for(int idx = 0; idx < n; ++idx)
    {
        std::cout << "Input grade of " << idx + 1 << " student." << std::endl;
        std::cin >> grade;

        vect.push_back(grade);
    }    
}

//=========================================================================

int main()
{
    std::vector<int> grades;

    input_data(grades);
    int average_grade = get_average_grade(grades);

    output_data(grades, average_grade);

    return 0;
}
