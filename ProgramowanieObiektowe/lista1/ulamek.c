#include <stdio.h>
#include <stdlib.h>

typedef struct ulamek
{
    int licznik, mianownik;
}Ulamek;

int nwd(int a,int b){return b==0?a:nwd(b,a%b);}

void skracanie(Ulamek *in)
{
    int dziel=nwd(in->licznik,in->mianownik);
    in->licznik/=dziel;
    in->mianownik/=dziel;
}

Ulamek* nowy(int l,int m)
{
    Ulamek* new=malloc(sizeof(Ulamek));
    if(m<0)
    {
        l*=-1;
        m*=-1;
    }
    new->licznik=l;
    new->mianownik=m;
    return new;
}

Ulamek* dodaj(Ulamek* u1,Ulamek* u2)
{
    Ulamek* out=malloc(sizeof(Ulamek));
    u1->licznik*=u2->mianownik;
    u2->licznik*=u1->mianownik;
    u1->mianownik*=u2->mianownik;
    u2->mianownik=u1->mianownik;
    out->licznik=u1->licznik+u2->licznik;
    out->mianownik=u1->mianownik;
    skracanie(u1);
    skracanie(u2);
    skracanie(out);
    return out;    
}

Ulamek* odejmij(Ulamek* u1,Ulamek* u2)
{
    Ulamek* out=malloc(sizeof(Ulamek));
    u1->licznik*=u2->mianownik;
    u2->licznik*=u1->mianownik;
    u1->mianownik*=u2->mianownik;
    u2->mianownik=u1->mianownik;
    out->licznik=u1->licznik-u2->licznik;
    out->mianownik=u1->mianownik;
    skracanie(u1);
    skracanie(u2);
    skracanie(out);
    return out;    
}

Ulamek* mnoz(Ulamek* u1,Ulamek* u2)
{
    Ulamek* out=malloc(sizeof(Ulamek));
    out->licznik=u1->licznik*u2->licznik;
    out->mianownik=u1->mianownik*u2->mianownik;
    skracanie(out);
    return out;
}

Ulamek* podziel(Ulamek* u1,Ulamek* u2)
{
    int temp=u2->licznik;
    u2->licznik=u2->mianownik;
    u2->mianownik=temp;
    return mnoz(u1,u2);
}

void dodajj(Ulamek* u1,Ulamek* u2)
{
    Ulamek* out=malloc(sizeof(Ulamek));
    u1->licznik*=u2->mianownik;
    u2->licznik*=u1->mianownik;
    u1->mianownik*=u2->mianownik;
    u2->mianownik=u1->mianownik;
    out->licznik=u1->licznik+u2->licznik;
    out->mianownik=u1->mianownik;
    skracanie(u1);
    skracanie(u2);
    skracanie(out);
    u2->licznik=out->licznik;
    u2->mianownik=out->mianownik;    
}

void odejmijj(Ulamek* u1,Ulamek* u2)
{
    Ulamek* out=malloc(sizeof(Ulamek));
    u1->licznik*=u2->mianownik;
    u2->licznik*=u1->mianownik;
    u1->mianownik*=u2->mianownik;
    u2->mianownik=u1->mianownik;
    out->licznik=u1->licznik-u2->licznik;
    out->mianownik=u1->mianownik;
    skracanie(u1);
    skracanie(u2);
    skracanie(out);
    u2->licznik=out->licznik;
    u2->mianownik=out->mianownik;
}

void mnozz(Ulamek* u1,Ulamek* u2)
{
    Ulamek* out=malloc(sizeof(Ulamek));
    out->licznik=u1->licznik*u2->licznik;
    out->mianownik=u1->mianownik*u2->mianownik;
    skracanie(out);
    u2->licznik=out->licznik;
    u2->mianownik=out->mianownik;
}

void podziell(Ulamek* u1,Ulamek* u2)
{
    int temp=u2->licznik;
    u2->licznik=u2->mianownik;
    u2->mianownik=temp;
    Ulamek* out;
    out=mnoz(u1,u2);
    u2->licznik=out->licznik;
    u2->mianownik=out->mianownik;
    if(u2->mianownik<0)
    {
        u2->mianownik*=-1;
        u2->licznik*=-1;
    }
}