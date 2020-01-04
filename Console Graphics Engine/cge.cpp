#include <iostream>
#include "cge.hpp"

int SET_UP(std::string mode)
{
    if(mode == "CLS" || mode == "cls")
    {
        system("CLS");
        return 1;
    }
    return 0;
}

void fill(int width, int height, char input)
{
    using namespace std;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cout << input;
        }
        cout << endl;
    }
}

void draw_square(int width, int height, unsigned char top, unsigned char sides)
{
    using namespace std;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(i == 0 || i == height - 1) cout << top;
            else {
                cout << sides;
                for(int k = 0; k < width - 2; k++)
                {
                    cout << ' ';
                }
                cout << sides;
                break;
            }
        }
        cout << endl;
    }
}

void draw_triangle(int width, int height, unsigned char chr)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < i; j++)
        {
            std::cout << chr;
        }
        std::cout << std::endl;
    }
}
