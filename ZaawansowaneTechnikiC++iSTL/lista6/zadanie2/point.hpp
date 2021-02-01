#include <iostream>
#include <random>

#ifndef _POINT_HPP_
#define _POINT_HPP_

class point
{
    private:
        int x;
        int y;
        int rgb[3];
        std::string name;
    public:
        point();
        auto getx()const{return x;}
        auto gety()const{return y;}
        auto getrgb()const{return rgb;}
        auto getname()const{return name;}
        friend std::ostream& operator<<(std::ostream& out,const point& p)
        {
            out<<p.name<<" "<<p.x<<" "<<p.y<<" r = "<<p.rgb[0]<<" g = "<<p.rgb[1]<<" b = "<<p.rgb[2]<<std::endl;
            return out;
        }
};

point::point()
{
    std::random_device r;
    std::mt19937 g(r());
    std::uniform_int_distribution<> distxy(-1000,1000);
    x=distxy(g);
    y=distxy(g);
    std::uniform_int_distribution<> distrgb(0,255);
    for(int i=0;i<3;i++)
        rgb[i]=distrgb(g);
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int len=distrgb(g);
    while(len>16||len==0)len=distrgb(g);
    std::uniform_int_distribution<> chdist(0,63);
    for(auto i=0;i<len;i++)
        name+=alphanum[chdist(g)];
}


#endif