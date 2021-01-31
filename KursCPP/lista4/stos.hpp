#include <iostream>
#include <list>

using namespace std;

#ifndef _STOS_HPP
#define _STOS_HPP

class stos
{
    public:
    void wloz(const string &);
    string zdejmij();
    string sprawdz();
    int rozmiar();
    stos odwroc();
    friend ostream& operator<<(ostream &,const stos &);
    stos& operator=(stos &&from)
    {
        pojemnosc=move(from.pojemnosc);
        ile=move(ile);
        stoss=move(stoss);
        return *this;
    }
    stos& operator=(const stos &from)
    {
        pojemnosc=from.pojemnosc;
        ile=from.ile;
        stoss=from.stoss;
        return *this;
    }
    stos();
    stos(const int&);
    stos(initializer_list<string>);
    stos(const stos&);
    stos(stos&&);
    ~stos();

    private:
    int pojemnosc;
    int ile;
    string *stoss;
};


#endif