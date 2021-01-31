#include <iostream>
#include "stos.hpp"
using namespace std;

    void stos::wloz(const string &in)
    {
        if(ile<pojemnosc)
        {
            stoss[ile]=in;
            ile++;
        }
        else
            cerr<<"Stos jest pelny!"<<endl;        
    }
    string stos::zdejmij()
    {
        string x=stoss[ile-1];
        stoss[ile-1]="";
        ile--;
        return x;
    }
    string stos::sprawdz()
    {
        return stoss[ile-1];
    }
    int stos::rozmiar()
    {
        return ile;
    }
    stos stos::odwroc()
    {
        stos out(pojemnosc);
        for(int i=0;i<ile;i++)
        {
            out.wloz(stoss[ile-i-1]);
        }
        return out;
    }
    ostream& operator<<(ostream &wyj,const stos &from)
    {
        for(int i=0;i<from.ile;i++) 
            wyj<<from.stoss[i]<<endl;
        return wyj;
    }
    stos::stos()
    {
        pojemnosc=1;
        ile=0;
        stoss=new string[pojemnosc];
    }
    stos::stos(const int& size):pojemnosc(size)
    {
        ile=0;
        stoss=new string[pojemnosc];
    }
    stos::stos(initializer_list<string> from):pojemnosc(from.size()),stoss(new string[from.size()]),ile(from.size())
    {
        int i=0;
        for(string x:from) {
            stoss[i] = x;
            i++;
        }
    }
    stos::stos(const stos& from):pojemnosc(from.pojemnosc), stoss(new string[from.pojemnosc]),ile(from.ile)
    {
        for(int i=0;i<ile;i++)
        {
            stoss[i]=from.stoss[i];
        }
    }
    stos::stos(stos &&from):pojemnosc(from.pojemnosc),stoss(from.stoss),ile(from.ile)
    {
        from.stoss=nullptr;
    }
    stos::~stos()
    {
        delete[] stoss;
    }

