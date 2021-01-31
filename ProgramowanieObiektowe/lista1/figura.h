#ifndef _FIGURA_H
#define _FIGURA_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef enum type{KOLO,KWADRAT,TROJKAT}type;
typedef struct figura
{
    float x,y,r;
    type typfig;
}figura;
figura* nowy_kwadrat(float x,float y,float r);
figura* nowy_kolo(float x,float y,float r);
figura* nowy_trojkat(float x,float y,float r);
float pole(figura *f);
void przesun(figura *f,float x,float y);
float sumapol(figura** f,int size);
#endif