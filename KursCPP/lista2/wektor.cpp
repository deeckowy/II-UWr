#include "wektor.hpp"

wektor::wektor(const double &x,const double &y) :dx(x), dy(y) {} 

wektor dodaj(const wektor &from,const wektor &from2)
{
    wektor out=wektor(from.dx+from2.dx,from.dy+from2.dy);
    return out;
}