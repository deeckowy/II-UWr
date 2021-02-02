#include <iostream>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace std;

#ifndef _FUNCTIONS_HPP
#define _FUNCTIONS_HPP
float rand_y();
float rand_x();
bool is_move(float x,float y,float dx,float dy,float R);
#endif 