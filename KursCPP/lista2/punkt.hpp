#include "wektor.hpp"

#ifndef _PUNKT_HPP
#define _PUNKT_HPP

class punkt
{
    public:
    double x;
    double y;
    punkt()=default;
    punkt(const double &,const double &);
    punkt(const punkt &,const wektor &);
    punkt(const punkt &)=default;
    punkt &operator=(const punkt &)=delete;
};

#endif