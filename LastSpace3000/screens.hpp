#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;

#ifndef _SCREENS_HPP
#define _SCREENS_HPP

void levels(RenderWindow &app,int level);
void gameoverr(RenderWindow &app);
void save_score(RenderWindow &app,int sc,Sprite back);
void show_score(RenderWindow &app);
void credits(RenderWindow &app);
#endif