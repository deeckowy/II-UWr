#include <iostream>
#include "punkt.hpp"


#ifndef _PROSTA_HPP
#define _PROSTA_HPP


class prosta
{
    public:
    prosta()=default;
    prosta(const punkt &,const punkt &);
    prosta(const wektor &);
    prosta(const double &,const double &,const double &);
    prosta(const prosta &,const wektor &);
    prosta(const prosta &)=delete;
    prosta &operator=(prosta &)=delete;
    double getter_A();
    double getter_B();
    double getter_C();
    bool is_prosto(const wektor &);
    bool is_rowno(const wektor&);
    bool is_on(const punkt &);
    friend bool is_prostoo(const prosta &,const prosta &);
    friend bool is_rownoo(const prosta &,const prosta &);
    friend punkt wheree(const prosta &,const prosta &);

    private:
    double A=0.0;
    double B=0.0;
    double C=0.0;
    void norm(const double &,const double &,const double &);
};

bool is_prostoo(const prosta &,const prosta &);
bool is_rownoo(const prosta &,const prosta &);
punkt wheree(const prosta &,const prosta &);

#endif