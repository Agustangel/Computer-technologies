
#include <iostream>
#include <vector>
#include <algorithm>


class Point
{      
    public:
        int x;
        int y;

        Point(int x_, int y_) : x{x_}, y{y_} {}
};

class Token
{   
    public:
        Token(int x, int y, char col) : point{x, y}, color{col} {}
        Token(int x, int y) : point{x, y}, color{'N'} {};

        Point get_point(Token t);
        char get_color(Point p);
    private:
        Point point;
        char color;
};

std::vector<Token> vect_print;
std::vector<Token> vect_query;

static const char not_found = 'N';
static const char red = 'R';
static const char blue = 'B';
static const int get_token = 1;
static const int get_color = 2;

//===================================================================

char Token::get_color(Point p)
{
    for(int idx = 0; idx < vect_print.size(); ++idx)
    {
        if((vect_print[idx].point.x == p.x) && (vect_print[idx].point.y == p.y))
        {
            return vect_print[idx].color;
        }
    }

    return not_found;
}

Point Token::get_point(Token t)
{
    return t.point;
}

//===================================================================

void error (std::string s)
{
  throw std::runtime_error(s);
}


void clear_buffer() {
    char c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
}

//===================================================================

void get_input_token()
{
    int opcode = 0;
    int x = 0;
    int y = 0;
    char col = 0;

    std::cin >> opcode;
    if(opcode == get_token)
    {
        std::cin >> x >> y >> col;

        if((col != blue) && (col != red))
        {
            clear_buffer();
            error("Incorrect color");
        }

        Token t{x, y, col};
        vect_print.push_back(t);
    }
    else if(opcode == get_color)
    {
        std::cin >> x >> y;

        Token t{x, y};
        vect_query.push_back(t);
    }
    else
    {
        clear_buffer();
        error("Incorrect command");
    }
}

//===================================================================

void get_data()
{
    int n = 0;

    std::cout << "Input numbers of elements." << std::endl;
    std::cin >> n;

    while(n > 0)
    {
        try
        {
            get_input_token();
            --n;
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            
        }
    }
}

//===================================================================

void output_data()
{
    for(int idx = 0; idx < vect_query.size(); ++idx)
    {
        Point p = vect_query[idx].get_point(vect_query[idx]);
        char color = vect_query[idx].get_color(p);

        std::cout << color << std::endl;
    }
}

//===================================================================

int main()
{
    get_data();
    output_data();

    return 0;
}
