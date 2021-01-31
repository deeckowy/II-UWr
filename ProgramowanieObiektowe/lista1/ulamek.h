#ifndef _ULAMEK_H
#define _ULAMEK_H
#include <stdio.h>
#include <stdlib.h>
typedef struct ulamek
{
    int licznik, mianownik;
}Ulamek;
int nwd(int a,int b);
void skracanie(Ulamek *in);
Ulamek* nowy(int l,int m);
Ulamek* dodaj(Ulamek* u1,Ulamek* u2);
Ulamek* odejmij(Ulamek* u1,Ulamek* u2);
Ulamek* mnoz(Ulamek* u1,Ulamek* u2);
Ulamek* podziel(Ulamek* u1,Ulamek* u2);
void dodajj(Ulamek* u1,Ulamek* u2);
void odejmijj(Ulamek* u1,Ulamek* u2);
void mnozz(Ulamek* u1,Ulamek* u2);
void podziell(Ulamek* u1,Ulamek* u2);
#endif