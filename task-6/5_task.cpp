
#include <iostream>
#include <vector>
#include <bits/stdc++.h>


//=========================================================================
void inputData(std::vector<std::string>& vect)
{
    std::string str = "";
    std::cout << "Input 3 words: " << std::endl;

    for(int idx = 0; idx < 3; ++idx)
    {
        std::cin >> str;
        vect.push_back(str);
    }
}

//=========================================================================

void sortStrings(std::vector<std::string>& vect)
{
    for(int idx = 0; idx < vect.size(); ++idx)
    {
        sort(vect[idx].begin(), vect[idx].end());
        std::cout << vect[idx] << std::endl; 
    }
}

//=========================================================================

int countLetter(std::string str, char letter)
{
    int count = 0;
    std::string::iterator iter = str.begin();

    while(*iter != letter)
    {
        ++iter;
    }
    while(*iter == letter)
    {
        ++count;
        ++iter;
    }
    
    return count;
}

//=========================================================================

int main()
{
    std::vector<std::string> strs;

    inputData(strs);
    sortStrings(strs);

    std::cout << "Enter the letter which you would to count" << std::endl;
    char letter = 0;
    std::cin >> letter;

    int count = countLetter(strs[0], letter);
    std::cout << "count = " << count << std::endl;

    return 0;
}
