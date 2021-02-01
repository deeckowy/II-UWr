#include "nifs3.hpp"

nifs3::nifs3(const std::vector<double>& x,const std::vector<double>& y):xs(x),ys(y)
{
    size=xs.size();
    double *a=new double[size];
    double *b=new double[size];
    double *d=new double[size];
    a[0]=0;
    b[0]=0;
    //h i lambda zawsze sa takie same wiec wystarczy policzyc raz 
    h=xs[1]-xs[0];
    double lam=1/2;
    auto fun=[&](const auto& i)
    {
        auto t=(ys[i]-ys[i-1])/h;
        auto t1=(ys[i+1]-ys[i])/h;
        return (t1-t)/(2*h);

    };
    for(auto i=1;i<size;i++)
    {
        double t=lam*b[i-1]+2;
        d[i]=fun(i);
        a[i]=(d[i]-lam*a[i-1])/t;
        b[i]=(lam-1)/t;

    }
    M.push_back(0);
    for(auto i=1;i<size-1;i++)
        M.push_back((d[i]-lam*a[i-1])/((lam*b[i-1])+2));
    M.push_back(0);

}

double nifs3::get_val(const double& x)
{
    int i=0;
    while(x>xs[i]&&i<size)i++;
    auto la=[&](const double& x){return ((std::pow((x-xs[i]),3)*M[i+1])/(6*h))+
    ((std::pow((xs[i+1]-x),3)*M[i])/(6*h))+
    ((ys[i+1]-(M[i+1]*h*h)/6)*(x-xs[i])/h)+
    ((ys[i]-(M[i]*h*h)/6)*(xs[i+1]-x)/h);};
    return la(x);
}