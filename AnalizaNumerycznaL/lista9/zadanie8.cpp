#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>

auto bincoeff(const auto& n,const auto& k) 
{
   if (k==0||k==n)
       return 1;
   return bincoeff(n-1,k-1)+bincoeff(n-1,k);
}

class point
{
    private:
        double px;
        double py;
    public:
        point(const double& x,const double& y):px(x),py(y){}
        auto get_val(){return std::pair<double,double>(px,py);}
        auto operator*(const auto& c)
        {
            point p(px*c,py*c);
            return p;
        }
        auto operator/(const auto& c){return operator*(std::pow(c,-1));}
        auto operator+(const point& p)
        {
            point pp(px+p.px,py+p.py);
            return pp;
        }
};

class bcurve
{
    private:
        std::vector<point> points;
        std::vector<double> weights;
        std::vector<int> bncff;
        std::function<double(double,int)> bfun;
        int size;
    public:
        bcurve(auto& p,auto& w):points(p),weights(w),size(p.size())
        {
            for(auto i=0;i<size;i++)
                bncff.push_back(bincoeff(size-1,i));
            bfun=[&](const double& t,const int& i)
            {
                auto q=(1.0-t);
                return bncff[i]*std::pow(t,i)*std::pow(q,size-1-i);
            };
        }
        auto get_val(const auto& t)
        {
            point p(0,0);
            auto sum=0.0;
            for(auto i=0;i<size;i++)
            {
                p=p+points[i]*weights[i]*bfun(t,i);
                sum+=weights[i]*bfun(t,i);
            }
            p=p/sum;
            return p;
        }
        auto get_standard_val(const auto& t)
        {
            point p(0,0);
            for(auto i=0;i<size;i++)
                p=p+points[i]*bfun(t,i);
            return p;
        }
};


int main()
{
    std::vector<double> weights={1,2,3,2.5,6,1.5,5,1,2,1,3,5,1};
    std::vector<point> points={
    point(39.5,10.5),
    point(30,20),
    point(6,6),
    point(13,-12),
    point(63,-12.5),
    point(18.5,17.5),
    point(48,63),
    point(7,25.5),
    point(48.5,49.5),
    point(9,19.5),
    point(48.5,35.5),
    point(59,32.5),
    point(56,20.5)};


    bcurve b(points,weights);
    auto t=0.01;
    auto step=0.01;
    while(t<=1)
    {
        auto p=b.get_standard_val(t).get_val();
        std::cout<<p.first<<" , "<<p.second<<std::endl;
        t+=step;
    }
    return 0;
}   