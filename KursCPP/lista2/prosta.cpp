#include <iostream>
#include "punkt.hpp"
#include "prosta.hpp"
#include <cmath>
#include <stdexcept>

void prosta::norm(const double &a,const double &b,const double &c)
{
    double nan=(sqrt(a*a+b*b));
    if(c<0.0)nan*=(-1.0);
    A=a/nan;
    B=b/nan;
    C=c/nan;
}

prosta::prosta(const punkt &a,const punkt &b)
{
    if(a.x==b.x&&a.y==b.y){throw std::invalid_argument("Punkty sa takie same.");}
    double temp=(b.y-a.y)/(b.x-a.x);
    norm(temp,(-1.0),a.y-temp*a.x);
}

prosta::prosta(const wektor &vec)
{
    double temp=(-1.0)/(vec.dy/vec.dx);
    norm(temp,1.0,vec.dy-vec.dx*temp);
}
prosta::prosta(const double &a,const double &b,const double &c)
{
    if(a==b){throw std::invalid_argument("a i b nie moga byc zerowe");}
    norm(a,b,c);
}
prosta::prosta(const prosta &pros,const wektor &vec)
{
    norm(pros.A,pros.B-vec.dx,pros.C+vec.dy);
}

double prosta::getter_A(){return A;}

double prosta::getter_B(){return B;}

double prosta::getter_C(){return C;}

bool prosta::is_prosto(const wektor &vec){return (A/B)*(vec.dy/vec.dy)==(-1);}   

bool prosta::is_rowno(const wektor &vec){return (A/B)==(vec.dy/vec.dx);}

bool prosta::is_on(const punkt &pun){return B*pun.y+A*pun.x+C<0.01||B*pun.y+A*pun.x+C>-0.01;}

bool is_prostoo(const prosta &lajn1,const prosta &lajn2){return lajn1.A*lajn1.B==(-1)*lajn2.A*lajn2.B;}

bool is_rownoo(const prosta &lajn1,const prosta &lajn2){return lajn1.A*lajn2.B==lajn2.A*lajn1.B;}

punkt wheree(const prosta &lajn1,const prosta &lajn2)
{
    if(is_rownoo(lajn1,lajn2)){throw std::invalid_argument("Funkcje sa rownolegle !");}
    double D=lajn1.A*lajn2.B-lajn2.A*lajn1.B;
    std::cout<<D<<std::endl;
    double x=(lajn1.B*lajn2.C-lajn2.B*lajn1.C)/D;
    std::cout<<x<<std::endl;
    double y=(-1)*(lajn1.A*lajn2.C-lajn2.A*lajn1.C)/D;
    punkt out(x,y);
    return out;
}