#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;

void levels(RenderWindow &app,int level)
{
    //load font
    Font pixel;
    pixel.loadFromFile("src/8-bit-pusab.ttf");


    //make signs
    string lv="LEVEL ";
    lv+=to_string(level);
    string pres="PRESS ENTER TO CONTINUE";
    
    //making texts
    Text leves,press;
    leves.setFont(pixel);
    press.setFont(pixel);
    leves.setString(lv);
    press.setString(pres);
    leves.setCharacterSize(40);
    press.setCharacterSize(20);
    leves.setPosition(450,450);
    press.setPosition(380,820);


    //draw everything
    app.clear(Color::Black);
    app.draw(leves);
    app.draw(press);
    app.display();
    Event event;
    while(app.pollEvent(event))
    {if(event.type==Event::Closed)
    {app.close();exit(0);}}


    //wait for enter 
    while(!Keyboard::isKeyPressed(Keyboard::Return));
}

void gameoverr(RenderWindow &app)
{
    //load font
    Font pixel;
    pixel.loadFromFile("src/8-bit-pusab.ttf");


    Text game,over;
    game.setFont(pixel);
    over.setFont(pixel);
    game.setString(" GAME ");
    over.setString(" OVER ");
    game.setCharacterSize(100);
    over.setCharacterSize(100);
    game.setPosition(300,300);
    over.setPosition(300,450);
    game.setFillColor(Color::Red);
    over.setFillColor(Color::Red);



    //draw everything
    app.clear(Color::Black);
    app.draw(game);
    app.draw(over);
    app.display();
    Event klik;
    while(app.pollEvent(klik));
    Time X=seconds(5);    
    sleep(X);
}


void save_score(RenderWindow &app,int sc,Sprite back)
{
    Font pixel;
    pixel.loadFromFile("src/8-bit-pusab.ttf");
    ifstream rank("src/ranking.txt");
    string names[10],points[10];
    int scores[10]={0};
    for(int i=0;i<10;i++)getline(rank,points[i]);
    for(int i=0;i<10;i++)getline(rank,names[i]);
    rank.close();   
    for(int i=0;i<10;i++)
    {
        stringstream temp(points[i]);
        temp>>scores[i];
    }
    int i=0;
    for(int k=0;k<10;k++)
    {
        if(sc>scores[k]){i=k+1;break;}
    }
    if(i!=0)
    {
        for(int k=9;k>i;k--)
        {
            points[k]=points[k-1];
            names[k]=names[k-1];
        }
        points[i-1]=to_string(sc);
        names[i-1]="";
        Text sco[10],nam[10],high;
        for(int k=0;k<10;k++)
        {
            sco[k].setFont(pixel);
            sco[k].setString(points[k]);
            sco[k].setPosition(900,100+k*70);
            nam[k].setFont(pixel);
            nam[k].setString(names[k]);
            nam[k].setPosition(100,100+k*70);
        }
        high.setFont(pixel);
        high.setCharacterSize(50);
        high.setPosition(250,20);
        high.setString(" HIGHSCORES ");
        Event event;
        app.pollEvent(event);
        string wname="";
        app.setFramerateLimit(10);
        while(!Keyboard::isKeyPressed(Keyboard::Return))
        {
            while(app.pollEvent(event))
            {
                if(event.type==Event::TextEntered)
                {
                    if(event.text.unicode<128&&wname.size()<20)
                    {
                        wname+=static_cast <char>(event.text.unicode);
                        nam[i-1].setString(wname);
                    }
                }
                if(event.key.code==Keyboard::BackSpace)
                {
                    if(wname.size())wname.pop_back();
                    nam[i-1].setString(wname);
                }
                if(event.type==Event::Closed)
                {app.close();exit(0);}

            }
            Color c;
            c.r=rand()%255;
            c.b=rand()%255;
            c.g=rand()%255;
            nam[i-1].setFillColor(c);
            sco[i-1].setFillColor(c);
            high.setFillColor(c);
            app.clear();
            app.draw(back);
            for(int k=0;k<10;k++)
            {
                app.draw(sco[k]);
                app.draw(nam[k]);
            }
            app.draw(high);
            app.display();
        }
        names[i-1]=wname;
        ofstream trank("src/ranking.txt",ofstream::trunc);
        for(int k=0;k<10;k++)
        {
            trank<<points[k]<<endl;
        }
        for(int k=0;k<10;k++)
        {
            trank<<names[k]<<endl;
        }
        trank.close();
    }
}

void show_score(RenderWindow &app)
{
    Event klik;
    app.pollEvent(klik);
    Font pixel;
    pixel.loadFromFile("src/8-bit-pusab.ttf");
    ifstream rank("src/ranking.txt");
    string names[10],points[10];
    int scores[10]={0};
    for(int i=0;i<10;i++)getline(rank,points[i]);
    for(int i=0;i<10;i++)getline(rank,names[i]);
    rank.close();   
    
    Text sco[10],nam[10],high,press;
    for(int k=0;k<10;k++)
    {
        sco[k].setFont(pixel);
        sco[k].setString(points[k]);
        sco[k].setPosition(900,100+k*70);
        nam[k].setFont(pixel);
        nam[k].setString(names[k]);
        nam[k].setPosition(100,100+k*70);
    }
    high.setFont(pixel);
    high.setCharacterSize(50);
    high.setPosition(250,20);
    high.setString(" HIGHSCORES ");
    press.setFont(pixel);
    press.setString(" PRESS ESC TO EXIT ");
    press.setPosition(300,850);
    Event event;
    app.pollEvent(event);
    app.setFramerateLimit(10);
    while(!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Event event;
        while(app.pollEvent(event))
        {if(event.type==Event::Closed)
        {app.close();exit(0);}}
        Color c;
        c.r=rand()%255;
        c.b=rand()%255;
        c.g=rand()%255;
        high.setFillColor(c);
        app.clear(Color::Black);
        for(int k=0;k<10;k++)
        {
            app.draw(sco[k]);
            app.draw(nam[k]);
        }
        app.draw(high);
        app.draw(press);
        app.display();
    }
}

void credits(RenderWindow &app)
{
    app.setFramerateLimit(10);
    Text author,version,supervisor,categories[3],place,press,credits;
    Font pixel;
    pixel.loadFromFile("src/8-bit-pusab.ttf");
    author.setFont(pixel);
    press.setFont(pixel);
    version.setFont(pixel);
    supervisor.setFont(pixel);
    place.setFont(pixel);
    credits.setFont(pixel);
    for(int i=0;i<3;i++)
    {
        categories[i].setFont(pixel);
        categories[i].setPosition(200,250+(i*100));
    }
    categories[0].setString("author:");
    categories[1].setString("supervisor:");
    categories[2].setString("version:");
    credits.setCharacterSize(50);
    credits.setPosition(350,20);
    credits.setString(" CREDITS ");
    press.setString(" PRESS ESC TO EXIT ");
    press.setPosition(300,850);
    author.setString("Mateusz Reis");
    supervisor.setString("Zuzanna Beltowska <3");
    version.setString("Alpha 0.1");
    author.setPosition(600,250);
    supervisor.setPosition(600,350);
    version.setPosition(600,450);
    place.setString("Wroclaw - Institute of Computer Science - 2020");
    place.setCharacterSize(20);
    place.setPosition(200,700);
    while(!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Event event;
        while(app.pollEvent(event))
        {if(event.type==Event::Closed)
        {app.close();exit(0);}}
        Color c;
        c.r=rand()%255;
        c.b=rand()%255;
        c.g=rand()%255;
        author.setFillColor(c);
        supervisor.setFillColor(c);
        version.setFillColor(c);
        place.setFillColor(c);
        app.clear(Color::Black);
        app.draw(author);
        app.draw(supervisor);
        app.draw(version);
        app.draw(credits);
        app.draw(press);
        app.draw(place);
        for(int i=0;i<3;i++)app.draw(categories[i]);
        app.display();
    }
}