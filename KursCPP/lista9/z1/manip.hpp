#include <iostream>
using namespace std;

#ifndef _MANIP_HPP
#define _MANIP_HPP


inline istream& clearline(istream& i)
{
    char c;
    while((c=i.get())!=EOF&&c!='\n');
    return i;
}

class ignore
{
        int length;
        friend istream& operator>>(istream& in,const ignore& ig);
    public:
        ignore(int x):length(x){}
};

inline ostream& comma(ostream& o)
{
    return o<<", ";
}

inline ostream& colon(ostream& o)
{
    return o<<": ";
}

class index
{
        int x;
        int w;
        friend ostream& operator<<(ostream& o,const index& idx);
    public:
        index(int x,int w):x(x),w(w){};
};


#endif