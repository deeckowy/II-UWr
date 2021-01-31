#include <iostream>
#include "obliczenia.hpp"

#ifndef _WYM_WYJ_HPP_
#define _WYM_WYJ_HPP_

using namespace std;

class wyjatek_wymierny
{
    public:
        void poka_blad()const{cerr<<blad<<endl;}
    protected:
        string blad;
};

class dzielenie_przez_0:public wyjatek_wymierny
{
    public:
        dzielenie_przez_0(const int &a,const int &b);
};

class przekroczenie_zakresu:public wyjatek_wymierny
{
    public:
        przekroczenie_zakresu(const obliczenia::wymierna &a,const obliczenia::wymierna &b,char typ);
};

#endif