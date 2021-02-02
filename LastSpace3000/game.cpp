#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "functions.hpp"
#include "screens.hpp"

using namespace std;
using namespace sf;

#define dell(IN)delete IN;\
IN=NULL;\

#define make_enemy(in)Enemy *e=new Enemy();\
e->lives=rand()%4+Level;\
e->val=e->lives*100;\
e->look=elooks[enemies_type];\
e->look.setOrigin(20,20);\
e->x=rand_x();\
e->y=rand_y();\
e->look.setPosition(e->x,e->y);\
e->dx=(rand()%200+100)/100;\
e->R=30;\
in=e;\


class object
{
    public:
    float x=0.0,y=0.0,dx=0.0,dy=0.0,R=0.0;
    Sprite look;
};

class Player:public object
{
    public:
    Player()
    {}
    int lives;
};

class Bullet:public object
{
    public:
    Bullet()
    {}
};

class Enemy:public object
{
    public:
    Enemy()
    {}
    int lives;
    int val;
};

class Weapon
{
    public:
    Sprite BLL;
    int BLLSPEED;
    int BLLPWR;
};


void main_game(RenderWindow &app,Sprite back)
{

    //font loading
    Font pixel;
    pixel.loadFromFile("src/8-bit-pusab.ttf");


    //set up window & counters
    app.setFramerateLimit(60);
    Clock clock;
    Clock time;
    int Level=1,max_pbullets=10,scores=0,max_enemies=rand()%100,max_ebullets=10;
    bool game_over=false,level_completed=false,shoot=false,bos=false;
    int enemies_type=rand()%5,enbull_type=rand()%5;
    
    //gui
    Texture border;
    border.loadFromFile("src/borders.png");
    Sprite bborder(border);

    //gui text
    Text score,times,level,lives;
    score.setFont(pixel);
    level.setFont(pixel);
    times.setFont(pixel);
    lives.setFont(pixel);
    score.setString(" SCORE ");
    level.setString(" LEVEL ");
    times.setString(" TIME ");
    lives.setString(" LIVES ");
    level.setCharacterSize(10);
    level.setPosition(20,10);
    score.setCharacterSize(10);
    score.setPosition(20,800);
    times.setCharacterSize(10);
    times.setPosition(20,700);
    lives.setCharacterSize(10);
    lives.setPosition(20,270);
    //unconst gui values 
    Text s1,t1,l1;
    string s2,t2,l2;
    s1.setFont(pixel);
    t1.setFont(pixel);
    l1.setFont(pixel);
    l1.setCharacterSize(20);
    l1.setPosition(60,40);
    s1.setCharacterSize(20);
    s1.setPosition(60,830);
    t1.setCharacterSize(20);
    t1.setPosition(60,730);


    //Player setup
    Player *p=new Player();
    Texture plook;
    Sprite lk;
    plook.loadFromFile("src/ship1.png");
    lk.setTexture(plook);
    lk.setScale(0.5,0.5);
    lk.setPosition(60,300);
    p->look.setTexture(plook);
    p->lives=3;
    p->look.setOrigin(30,30);
    p->x=770;
    p->y=870;
    p->R=30;
    

    //player's weapons 
    Texture w0,w1,w2,w3,w4,w5;
    w0.loadFromFile("src/bullet.png");
    w1.loadFromFile("src/bullet1.png");
    w2.loadFromFile("src/bullet2.png");
    w3.loadFromFile("src/bullet3.png");
    w4.loadFromFile("src/bullet4.png");
    Weapon *types[5];
    for(int i=0;i<5;i++)types[i]=new Weapon();
    types[0]->BLL.setTexture(w0);
    types[0]->BLL.setOrigin(4,4);
    types[1]->BLL.setTexture(w1);
    types[1]->BLL.setOrigin(5,10);
    types[2]->BLL.setTexture(w2);
    types[2]->BLL.setOrigin(10,5);
    types[3]->BLL.setTexture(w3);
    types[3]->BLL.setOrigin(12,17);
    types[4]->BLL.setTexture(w4);
    types[4]->BLL.setOrigin(5,5);
    types[0]->BLLSPEED=-3;
    types[1]->BLLSPEED=-5;
    types[2]->BLLSPEED=-2;
    types[3]->BLLSPEED=-7;
    types[4]->BLLSPEED=-7;
    types[0]->BLLPWR=1;
    types[1]->BLLPWR=4;
    types[2]->BLLPWR=10;
    types[3]->BLLPWR=7;
    types[4]->BLLPWR=20;
    Weapon *curr_wp=types[0];



    //bonuses
    bool shield=false;
    int shield_start;
    object *sh=new object();
    Texture shh;
    shh.loadFromFile("src/shield.png");
    sh->look.setTexture(shh);
    sh->look.setOrigin(32,32);
    object *Bonus=NULL;
    Texture bss;
    bss.loadFromFile("src/bonus.png");
    Text Bonus_MSG;
    Bonus_MSG.setFont(pixel);
    Bonus_MSG.setCharacterSize(10);
    Bonus_MSG.setPosition(600,600);
    int bonus_time;
    bool bonus_ms=false;


    //player bullets 
    Bullet *pbullets[100]={NULL};
    
    //enemies bullets 
    Bullet *ebullets[100]={NULL};
    Texture ell,ell1,ell2,ell3,ell4,bbll;
    ell.loadFromFile("src/enemy_bullet.png");
    ell1.loadFromFile("src/enemy_bullet1.png");
    ell2.loadFromFile("src/enemy_bullet2.png");
    ell3.loadFromFile("src/enemy_bullet3.png");
    ell4.loadFromFile("src/enemy_bullet4.png");
    bbll.loadFromFile("src/bossbll.png");
    Sprite enbull[6];
    enbull[0].setTexture(ell);
    enbull[1].setTexture(ell1);
    enbull[2].setTexture(ell2);
    enbull[3].setTexture(ell3);
    enbull[4].setTexture(ell4);
    enbull[5].setTexture(bbll);

    //enemies setup
    if(max_enemies<20)max_enemies+=20;
    Enemy *enemies[100]={NULL};
    Sprite elooks[5];
    Texture en,en1,en2,en3,en4,bsl;
    Texture BOSS;
    BOSS.loadFromFile("src/boss.png");
    en.loadFromFile("src/enemy.png");
    bsl.loadFromFile("src/boss_live.png");
    elooks[0].setTexture(en);
    en1.loadFromFile("src/enemy1.png");
    elooks[1].setTexture(en1);
    en2.loadFromFile("src/enemy2.png");
    elooks[2].setTexture(en2);
    en3.loadFromFile("src/enemy3.png");
    elooks[3].setTexture(en3);
    en4.loadFromFile("src/enemy4.png");
    elooks[4].setTexture(en4);

    //set enemies for first level
    for(int i=0;i<max_enemies;i++)
    {
        make_enemy(enemies[i])
    }
    int curr_enemies=max_enemies;

    while (!game_over&&!level_completed)
    {   
        //clock for smooth movin and time countin
        float dt=clock.restart().asSeconds();
        int timm=90-time.getElapsedTime().asSeconds();
        
        Event event;
        while(app.pollEvent(event))
        {if(event.type==Event::Closed)
        {game_over=true;app.close();exit(0);}}

        //setting gui unconst values 
        s2=to_string(scores);
        t2=to_string(timm);
        l2=to_string(Level);
        t1.setString(t2);
        l1.setString(l2);
        s1.setString(s2);
        app.clear();
        app.draw(back);

        //movin player
        if(Keyboard::isKeyPressed(Keyboard::Left))p->dx=-5.0;
        if(Keyboard::isKeyPressed(Keyboard::Right))p->dx=5.0;
        if(Keyboard::isKeyPressed(Keyboard::Z)&&!shoot)
        {
            for(int i=0;i<max_pbullets;i++)
            {
                shoot=true;
                if(pbullets[i]==NULL)
                {
                    Bullet *b=new Bullet();
                    b->look=curr_wp->BLL;
                    b->x=p->x;
                    b->y=p->y-30;
                    b->dy=curr_wp->BLLSPEED;
                    pbullets[i]=b;
                    break;
                }
            }
        } 
        else {shoot=false;}
        

        //enemies shooting
        for(int i=0;i<max_enemies;i++)
        {
            if(enemies[i]!=NULL&&rand()%100==0)
            {
                for(int k=0;k<max_ebullets;k++)
                {
                    if(ebullets[k]==NULL)
                    {
                        Bullet *ebll=new Bullet();
                        ebll->look=enbull[enbull_type];
                        ebll->dy=3.0;
                        ebll->y=enemies[i]->y+20;
                        ebll->x=enemies[i]->x;
                        ebullets[k]=ebll;
                        break;
                    }
                }
            }
        }
        
        //delete useless things
        for(int i=0;i<100;i++)
        {
            if(ebullets[i]!=NULL&&ebullets[i]->y>900){dell(ebullets[i]);}
            if(pbullets[i]!=NULL&&pbullets[i]->y<0){dell(pbullets[i]);}
        }
        //delete dead enemies && add points
        for(int i=0;i<max_enemies;i++)
        {
            if(enemies[i]!=NULL)
            {
                if(enemies[i]->lives<0)
                {
                    if(Bonus==NULL)
                    {
                        Bonus= new object();
                        Bonus->look.setTexture(bss);
                        Bonus->x=enemies[i]->x;
                        Bonus->y=enemies[i]->y;
                        Bonus->dy=rand()%5+2;
                    }
                    scores+=enemies[i]->val;
                    dell(enemies[i]);
                    curr_enemies--;
                }
            }
        }


        if(bonus_ms&&bonus_time<timm)
        {app.draw(Bonus_MSG);Bonus_MSG.setFillColor(Color(rand()%255,rand()%255,rand()%255));}
        else bonus_ms=false;

        //BONUS things
        if(Bonus!=NULL)
        {
            Bonus->look.setColor(Color(rand()%255,rand()%255,rand()%255));
            if(is_move(Bonus->x,Bonus->y,Bonus->dx,Bonus->dy,0))
            {
                Bonus->y+=Bonus->dy*dt*100;
                Bonus->look.setPosition(Bonus->x,Bonus->y);
                app.draw(Bonus->look);
            }
            if(p->look.getGlobalBounds().intersects(Bonus->look.getGlobalBounds()))
            {
                int z=rand()%80;
                if(z<20)
                {
                    if(max_pbullets<100)
                    {max_pbullets+=(rand()%10-3);}
                    else scores+=1000;
                    Bonus_MSG.setString(" BULLETS ");
                    bonus_ms=true;
                    bonus_time=timm-2;
                }
                else if(z<40)
                {
                    shield=true;
                    shield_start=timm-5;
                    Bonus_MSG.setString(" SHIELD ");
                    bonus_ms=true;
                    bonus_time=timm-2;
                }
                else if(z<70)
                {
                    scores+=rand()%100*100;
                    Bonus_MSG.setString(" EXTRA POINTS ");
                    bonus_ms=true;
                    bonus_time=timm-2;
                }
                else if(z<75)
                {
                    p->lives++;
                    Bonus_MSG.setString(" EXTRA LIFE ");
                    bonus_ms=true;
                    bonus_time=timm-2;
                }
                else if(z<80)
                {
                    curr_wp=types[rand()%4+1];
                    Bonus_MSG.setString(" WEAPON ");
                    bonus_ms=true;
                    bonus_time=timm-2;
                }
                dell(Bonus);    
            }
            else if(Bonus->y>900)
            {dell(Bonus);}
            
        }

        //movin player 
        if(is_move(p->x,p->y,p->dx,p->dy,p->R)){p->x+=p->dx*dt*100;p->look.setPosition(p->x,p->y);p->dx=p->dy=0;}


        //collision detect
        //for enemies
        for(int i=0;i<max_enemies;i++)
        {
            if(enemies[i]!=NULL)
            {
                for(int k=0;k<max_pbullets;k++)
                {
                    if(pbullets[k]!=NULL)
                    {    
                        if(enemies[i]->look.getGlobalBounds().intersects(pbullets[k]->look.getGlobalBounds()))
                        {
                            enemies[i]->lives-=curr_wp->BLLPWR;
                            dell(pbullets[k]);
                        }
                    }
                }
            }
        }
        //for player
        if(!shield)
        {
            for(int i=0;i<max_ebullets;i++)
            {
                if(ebullets[i]!=NULL)
                    if(p->look.getGlobalBounds().intersects(ebullets[i]->look.getGlobalBounds()))
                    {
                        p->lives--;
                        dell(ebullets[i]);
                        shield=true;
                        shield_start=timm-3;
                        p->x=700;
                        p->y=870;
                        curr_wp=types[0];
                    }
            }
        }
        else 
        {
            if(shield_start!=timm)
            {
                sh->look.setPosition(p->x,p->y);
                app.draw(sh->look);
            }
            else shield=false;
        }

        
        //movin things
        for(int i=0;i<100;i++)
        {
            //movin enemy bullets 
            if(ebullets[i]!=NULL&&is_move(ebullets[i]->x,ebullets[i]->y,ebullets[i]->dx,ebullets[i]->dy,0))
            {
                ebullets[i]->y+=ebullets[i]->dy*dt*100;
                ebullets[i]->look.setPosition(ebullets[i]->x,ebullets[i]->y);
            }
            //movin enemies 
            if(enemies[i]!=NULL)
            {
                if(is_move(enemies[i]->x,enemies[i]->y,enemies[i]->dx,enemies[i]->dy,enemies[i]->R))
                {
                    enemies[i]->x+=enemies[i]->dx*dt*100;
                    enemies[i]->look.setPosition(enemies[i]->x,enemies[i]->y);
                }
                else enemies[i]->dx=enemies[i]->dx*(-1);
            }
            //movin player's bullets
            if(pbullets[i]!=NULL&&is_move(pbullets[i]->x,pbullets[i]->y,pbullets[i]->dx,pbullets[i]->dy,0))
            {
                pbullets[i]->y+=pbullets[i]->dy*dt*100;
                pbullets[i]->look.setPosition(pbullets[i]->x,pbullets[i]->y);
            }
        }

        //draw and display
        
        app.draw(bborder);
        app.draw(score);
        app.draw(level);
        app.draw(times);
        app.draw(lives);
        app.draw(s1);
        app.draw(t1);
        app.draw(l1);
        app.draw(p->look);
        for(int i=0;i<100;i++)
        {
            if(ebullets[i]!=NULL)
            {
                app.draw(ebullets[i]->look);
            }
            if(enemies[i]!=NULL)
            {
                app.draw(enemies[i]->look);
            }
            if(pbullets[i]!=NULL)
            {
                app.draw(pbullets[i]->look);
            }
        }
        for(int i=0;i<p->lives;i++)
        {
            lk.setPosition(60,300+(i*35));
            app.draw(lk);
        }
        if(bos&&enemies[0]!=NULL)
        {
            Sprite bssl[500];
            Text bbssh;
            bbssh.setFont(pixel);
            bbssh.setPosition(760,55);
            bbssh.setCharacterSize(10);
            bbssh.setString(" BOSS HEALTH ");
            app.draw(bbssh);
            for(int i=0;i<enemies[0]->lives;i++)
            {
                bssl[i].setTexture(bsl);
                bssl[i].setPosition(250+i,50);
                app.draw(bssl[i]);
            }
        }
        app.display();
        
        //no enemies == level complete
        if(curr_enemies==0)
        {
            scores+=timm*1000;
            Level++;
            shield=false;
            if(Level<20)
            {
                levels(app,Level);
                if(max_enemies<95)max_enemies+=5;
                for(int i=0;i<max_enemies;i++)
                {
                    make_enemy(enemies[i]);
                }
                for(int i=0;i<100;i++)
                {
                    pbullets[i]=ebullets[i]=NULL;
                }
                max_ebullets++;
                time.restart();
                curr_enemies=max_enemies;
                enemies_type=rand()%5;
                enbull_type=rand()%5;
            }
            else if(Level==20)
            {
                for(int i=0;i<100;i++)
                {
                    pbullets[i]=ebullets[i]=NULL;
                }
                time.restart();
                levels(app,20);
                enbull_type=5;
                Enemy *Boss=new Enemy();
                Boss->look.setTexture(BOSS);
                Boss->look.setOrigin(65,65);
                Boss->dx=5;
                Boss->R=70;
                Boss->x=700;
                Boss->y=200;
                max_enemies=curr_enemies=1;
                Boss->lives=500;
                Boss->val=1000000;
                enemies[0]=Boss;
                bos=true;
                max_ebullets=20;
            }
        }   

        //time is up == game over
        if(timm<0)game_over=true;
        //player has no lives == game over 
        if(p->lives<=0)game_over=true;
        //player beat boss == game over
        if(Level>20)game_over=true;
    }
    gameoverr(app);
    scores+=p->lives*10000;
    for(int i=0;i<100;i++)
    {
        delete enemies[i];
        delete pbullets[i];
        delete ebullets[i];
    }
    delete sh;
    delete p;
    delete Bonus;
    for(int i=0;i<5;i++)delete types[i];
    save_score(app,scores,back);
}