#include "numconvar.hpp"
using namespace std;

number::number(double x):val(x){priority=0;}

double number::eval(){return val;}

string number::print(int prior)
{
    if(val>=0.0)
        return to_string(val);
    else
        return '-'+to_string(val);
}

cons::cons(string con):name(con)
{
    if(name=="pi"){val=3.1415926;}
    else if(name=="fi"){val=1.618033988;}
    else if(name=="e"){val=2.718281828459;}
    priority=0;
}

string cons::print(int prior){return name;}

double cons::eval(){return val;}

map<string,double> var::variables; 

var::var(string name):variable(name)
{
    if(variables.find(name)==variables.end())
    {
        variables[name]=0;
    }
    priority=0;
}

string var::print(int prior){return variable;}

double var::eval(){return variables.find(variable)->second;}

void var::addval(string varia,double x)
{
    variables[varia]=x;
}