#include "expre.hpp"
#include <map>
#include <iostream>

using namespace std;

#ifndef _NUMCONVAR_HPP
#define _NUMCONVAR_HPP

class number:public expre
{
    private:
        double val;

    public:
        number(double x);
        string print(int prior);
        double eval();
};

class cons:public expre
{
    private:
        double val;
        string name;
    public :
        cons(string name);
        string print(int prior);
        double eval();
};

class var:public expre
{
    private:
        static map<string,double> variables;
        string variable;
    public :
        static void addval(string varia,double x);
        var(string name);
        string print(int prior);
        double eval();
};

#endif