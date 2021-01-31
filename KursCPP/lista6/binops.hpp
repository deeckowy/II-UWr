#include <iostream>
#include "expre.hpp"
#include <cmath>

using namespace std;

#ifndef _BINOPS_HPP
#define _BINOPS_HPP

class add:public expre
{
    private:
        expre* fst;
        expre* sec;
    public:
        add(expre* e,expre* b);
        string print(int prior);
        double eval();
};

class sub:public expre
{
    private:
        expre* fst;
        expre* sec;
    public:
        sub(expre* e,expre* b);
        string print(int prior);
        double eval();
};

class mult:public expre
{
    private:
        expre* fst;
        expre* sec;
    public:
        mult(expre* e,expre* b);
        string print(int prior);
        double eval();
};

class divv:public expre
{
    private:
        expre* fst;
        expre* sec;
    public:
        divv(expre* e,expre* b);
        string print(int prior);
        double eval();
};

class logg:public expre
{
    private:
        expre* fst;
        expre* sec;
    public:
        logg(expre* e,expre* b);
        string print(int prior);
        double eval();
};

class poww:public expre
{
    private:
        expre* fst;
        expre* sec;
    public:
        poww(expre* e,expre* b);
        string print(int prior);
        double eval();
};

#endif