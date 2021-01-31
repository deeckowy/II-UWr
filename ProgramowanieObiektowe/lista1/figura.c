#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum type{KOLO,KWADRAT,TROJKAT}type;

typedef struct figura
{
    float x,y,r;
    type typfig;
}figura;

figura* nowy_kwadrat(float x,float y,float r)
{
    figura* new=malloc(sizeof(figura));
    if(r>0.0)
        new->r=r;
    else 
        {printf("UJEMNY PROMIEN\n");return NULL;}
    new->x=x;
    new->y=y;
    new->typfig=KWADRAT;
    return new;
}

figura* nowy_kolo(float x,float y,float r)
{
    figura* new=malloc(sizeof(figura));
    if(r>0.0)
        new->r=r;
    else 
        {printf("ZLY PROMIEN \n");return NULL;}
    new->x=x;
    new->y=y;
    new->typfig=KOLO;
    return new;
}

figura* nowy_trojkat(float x,float y,float r)
{
    figura* new=malloc(sizeof(figura));
    if(r>0.0)
        new->r=r;
    else 
        {printf("UJEMNY PROMIEN \n");return NULL;}
    new->x=x;
    new->y=y;
    new->typfig=TROJKAT;
    return new;
}

float pole(figura *f)
{
    float pole=0.0;
    if(f->typfig==KWADRAT)
    {
        pole=(f->r*f->r);
    }
    else if(f->typfig==KOLO)
    {
        pole=3.14*(f->r*f->r);
    }
    else if(f->typfig==TROJKAT)
    {
        pole=(f->r*3*sqrt(3))/4;
    }
    return pole;
}

void przesun(figura *f,float x,float y)
{
    f->x+=x;
    f->y+=y;
}

float sumapol(figura** f,int size)
{
    float wynik=0.0;
    for(int i=0;i<size;i++)
    {
        wynik+=pole(f[i]);
    }
    return wynik;
}
