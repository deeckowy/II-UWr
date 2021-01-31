#include<cmath>
#include<iostream>
#include "expre.hpp"

using namespace std;

#ifndef _UNOPS_HPP
#define _UNOPS_HPP

class sinus:public expre
{
    private:
        expre* val;
    public:
        sinus(expre* e);
        string print(int prior);
        double eval();
};

class cosinus:public expre
{
    private:
        expre* val;
    public:
        cosinus(expre* e);
        string print(int prior);
        double eval();
};

class absolute:public expre
{
    private:
        expre* val;
    public:
        absolute(expre* e);
        string print(int prior);
        double eval();    
};

class oppo:public expre
{
    private:
        expre* val;
    public:
        oppo(expre* e);
        string print(int prior);
        double eval();
};

class expot:public expre
{
    private:
        expre* val;
    public:
        expot(expre* e);
        string print(int prior);
        double eval();        
};

class rev:public expre
{
    private:
        expre* val;
    public:
        rev(expre* e);
        string print(int prior);
        double eval();
};

class ln:public expre
{
    private:
        expre* val;
    public:
        ln(expre* e);
        string print(int prior);
        double eval();
};

#endif