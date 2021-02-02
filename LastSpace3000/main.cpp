
//////g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include "game.hpp"
#include "screens.hpp"

using namespace std;
using namespace sf;

int main()
{
    //create window and set param 
    RenderWindow app(sf::VideoMode(1200,900),"Last Space 3000",Style::Default);
    int i=0;
    
    
    
    //loading textures for menu
    Texture b1,b2,b3,b4,ttitle,back;
    back.loadFromFile("src/back.png");
    ttitle.loadFromFile("src/title.png");
    b4.loadFromFile("src/exitbutton.png");
    b3.loadFromFile("src/creditsbutton.png");
    b2.loadFromFile("src/scoresbutton.png");
    b1.loadFromFile("src/playbutton.png");


    //making sprites
    Sprite bback(back);
    Sprite bb1(b1);//playbutton
    Sprite bb2(b2);//scores button
    Sprite bb3(b3);//credits button
    Sprite bb4(b4);//exit button
    Sprite title(ttitle);


    //seting positions and scales
    title.setPosition(150.f,50.f);
    bb1.setPosition(300.f,400.f);
    bb1.setScale(0.5,0.5);
    bb2.setPosition(300.f,500.f);
    bb2.setScale(0.5,0.5);
    bb3.setPosition(300.f,600.f); 
    bb3.setScale(0.5,0.5);
    bb4.setPosition(300.f,700.f);
    bb4.setScale(0.5,0.5);
    
    
    //menu loop - enter to confirm choosen option 
    while(app.isOpen())
    {
        app.setFramerateLimit(10);
        Event eve;
        while(app.pollEvent(eve))
        {
            if(eve.key.code==Keyboard::Up)
            {
                if(i!=0)
                {
                    i--;
                }
            }
            else if(eve.key.code==Keyboard::Down)
            {
                if(i!=6)
                {
                    i++;
                }
            }
            else if(eve.key.code==Keyboard::Return)
            {
                if(i==0)
                {levels(app,1);main_game(app,bback);i=-2;break;}
                if(i==2)
                {show_score(app);i=-2;break;}
                if(i==4)
                {credits(app);i=-2;break;}
                if(i==6)
                {app.close();}
            }
            else if(eve.type==Event::Closed)
            {app.close();}
        }

    
        //set all button's color to white
        bb1.setColor(Color::White);
        bb2.setColor(Color::White);
        bb3.setColor(Color::White);
        bb4.setColor(Color::White);
        
        //set random color title
        title.setColor(Color(rand()%255,rand()%255,rand()%255));
        
        //set choosen button color to yellow
        if(i==0)bb1.setColor(Color::Yellow);
        else if(i==2)bb2.setColor(Color::Yellow);
        else if(i==4)bb3.setColor(Color::Yellow);
        else if(i==6)bb4.setColor(Color::Yellow);

        //draw all graphics on background
        app.draw(bback);
        app.draw(title);
        app.draw(bb1);
        app.draw(bb2);
        app.draw(bb3);
        app.draw(bb4);
        app.display();
    }
    return 0;
}