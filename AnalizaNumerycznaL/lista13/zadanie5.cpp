#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>

class romberg_approx
{
    private:
        std::function<double(double)> f;
        double a;
        double b;
    public:
        romberg_approx(const auto& ff,const auto& af,const auto& bf):f(ff),a(af),b(bf){}
        double get_val(const auto& n_prec)
        {
            double r[n_prec+1][n_prec+1];
            //R(0,0) first
            r[0][0]=(b-a)*(f(a)/2+f(b)/2);
            for(int i=1;i<=n_prec;i++)
            {
                double m=0;
                double h=(b-a)/std::pow(2,i-1);
                for(int k=1;k<=(int)std::pow(2,i-1);k++)
                    m+=f(a+((2*k-1)/2.0)*h);
                m*=h;
                r[0][i]=(r[0][i-1]+m)/2;
            }
            for(int i=1;i<=n_prec;i++)
                for(int k=0;k<=n_prec-i;k++)
                    r[i][k]=(std::pow(4.0,i)*r[i-1][k+1]-r[i-1][k])/(std::pow(4.0,i)-1);
            return r[n_prec][0];
        }
};

int main() 
{
    auto funa=[](double x){return 2021*std::pow(x,5)-2020*std::pow(x,4)+2019*std::pow(x,2);};
    romberg_approx r_uno=romberg_approx(funa,-1,2);
    std::cout<<"Aproksymacja dla funkcji a):\n";
    std::cout<<"T(2,0)=";
    std::cout<<r_uno.get_val(2)<<std::endl;
    std::cout<<"T(16,0)=";
    std::cout<<r_uno.get_val(16)<<std::endl;

    auto funb=[](double x){return 1/(1+25*x*x);};
    romberg_approx r_dos=romberg_approx(funb,-2,2);
    std::cout<<"Aproksymacja dla funkcji b):\n";
    std::cout<<"T(2,0)=";
    std::cout<<r_dos.get_val(2)<<std::endl;
    std::cout<<"T(16,0)=";
    std::cout<<r_dos.get_val(16)<<std::endl;

    auto func=[](double x){return std::sin(7*x-2)/x;};
    romberg_approx r_tres=romberg_approx(func,2,3*M_PI);
    std::cout<<"Aproksymacja dla funkcji c):\n";
    std::cout<<"T(2,0)=";
    std::cout<<r_tres.get_val(2)<<std::endl;
    std::cout<<"T(16,0)=";
    std::cout<<r_tres.get_val(16)<<std::endl;


    return 0;
}