#include <iostream>
#include <algorithm>
#include "point.hpp"
#include <list>

int main()
{
    std::list<point> points;
    for(int i=0;i<17;i++)
    {
        points.push_front(point());
    }
    ///a
    points.remove_if([](const point& p){return p.getname().length()<5;});
    std::cout<<"Lista punktow bez nazw o dlugosci mniejszej niz 5:\n";
    for(auto& x:points)
        std::cout<<x;
    std::cout<<"\n\n\n";
    ///b poprawione count if na for each
    int q[4]={0};
    std::for_each(points.begin(),points.end(),[&](const point& p)
    {
        if(p.getx()>=0)
            if(p.gety()>=0)
                q[0]++;
            else
                q[1]++;
        else 
            if(p.gety()>=0)
                q[3]++;
            else 
                q[2]++;
    });
    for(int i=0;i<4;i++)
        std::cout<<"Punkty w "<<i+1<<" cwiartce : "<<q[i]<<std::endl;
    std::cout<<"\n\n\n";

    ///c
    std::cout<<"Punkty posortowane wg luminacji :\n";
    points.sort([](const point& p1,const point& p2)
    {
        auto rgb1=p1.getrgb();
        auto rgb2=p2.getrgb();
        double lum1=0.3*rgb1[0]+0.59*rgb1[1]+0.11*rgb1[2];
        double lum2=0.3*rgb2[0]+0.59*rgb2[1]+0.11*rgb2[2];
        return lum1<lum2;
    });

    for(auto& x:points)
        std::cout<<x;
    std::cout<<"\n\n\n";

    ///d
    int dp=std::count_if(points.begin(),points.end(),[](const point& p)
    {
        auto rgb1=p.getrgb();
        double lum=0.3*rgb1[0]+0.59*rgb1[1]+0.11*rgb1[2];
        return lum<64;
    });
    auto darkp=std::partition(points.begin(),points.end(),[](const point& p)
    {
        auto rgb1=p.getrgb();
        double lum=0.3*rgb1[0]+0.59*rgb1[1]+0.11*rgb1[2];
        return lum<64;
    });

    std::cout<<"Liczba ciemnych puntkow : "<<dp<<std::endl;
    std::cout<<"Ciemne puntky :\n";
    std::list<point> dpoints;
    std::move(points.begin(),darkp,std::inserter(dpoints,dpoints.begin()));
    for(auto& x:dpoints)
        std::cout<<x;
    return 0;
}
