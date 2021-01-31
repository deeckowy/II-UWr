#include "manip.hpp"

istream& operator>>(istream& in,const ignore& ig)
{
    char c;
    int n=ig.length;
    while(n--&&c!=EOF&&c!='\n')
    {
        in.get(c);
    }
    return in;
}

ostream& operator<<(ostream& o,const index& idx)
{
    int x=idx.x;
    int w=idx.w;
    int c=x;
    while(c)
    {
        c/=10;
        w--;
    }
    o<<"[";
    while(w--)
    {
        o<<" ";
    }
    o<<x<<"]";
    return o;
} 