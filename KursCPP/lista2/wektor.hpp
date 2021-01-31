#ifndef _WEKTOR_HPP
#define _WEKTOR_HPP

class wektor
{
    public:
    const double dx;
    const double dy;
    wektor()=default;
    wektor(const double &,const double &);
    wektor(const wektor &)=default;
    wektor &operator=(const wektor &)=delete;
};
wektor dodaj(const wektor &from,const wektor &from2);
#endif