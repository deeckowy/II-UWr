#include <iostream>
#include <cstdlib>
#include "game.hpp"
#include <cmath>

using namespace std;

float rand_y()
{
    float random_y;
    random_y=rand()%450;
    if(random_y<40)
    {
        random_y=rand()%450;
    }
    return random_y;
}

float rand_x()
{
    float random_x;
    random_x=rand()%1200;
    while(random_x<230)
    {
        random_x=rand()%1100;
    }
    return random_x;
}

bool is_move(float x,float y,float dx,float dy,float R)
{
    if(dx!=0.0)
    {
        if((x<(1200-R)||dx<0)&&(x>(200+R)||dx>0))return true;
        else return false;
    }
    else 
    {
        if(y<900||y>0)return true;
        else return false;
    }
}
