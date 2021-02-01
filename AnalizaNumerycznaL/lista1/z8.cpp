#include <iostream>
#include <cmath>

double sigmoid(double x)
{
    return 1/(1+exp(-x));
}

double sigmoid_deriv(double x)
{
    return sigmoid(x)*(1-sigmoid(x));
}

double fun(double x)
{
    return exp(2*x);
}

double fun_deriv(double x)
{
    return 2*exp(2*x);
}

int main()
{
    for(int i=1;i<16;i++)
    {
        std::cout<<"\n\n\n\n\n"<<std::endl;
        double x=(double)rand()/RAND_MAX;
        std::cout<<"Random x is "<<x<<std::endl;
        double h=pow(10,-10);
        double trued=sigmoid_deriv(x);
        double wderiv=(sigmoid(x+h)-sigmoid_deriv(x))/h;
        double bderiv=(sigmoid(x+h)-sigmoid_deriv(x-h))/2*h;
        if(fabs(trued-wderiv)>fabs(trued-bderiv))
            std::cout<<"Wderiv is better in sigmoid in h= "<<pow(10,-i)<<std::endl<<"!!!!!!!"<<std::endl;
        else 
            std::cout<<"Bderiv is better in sigmoid in h= "<<pow(10,-i)<<std::endl;

        trued=1/pow(cos(x),2);
        wderiv=(tan(x+h)-tan(x))/h;
        bderiv=(tan(x+h)-tan(x-h))/2*h;
        if(fabs(trued-wderiv)>fabs(trued-bderiv))
            std::cout<<"Wderiv is better in tan in h= "<<pow(10,-i)<<std::endl<<"!!!!!!!"<<std::endl;
        else 
            std::cout<<"Bderiv is better in tan in h= "<<pow(10,-i)<<std::endl;

        trued=cos(x);
        wderiv=(sin(x+h)-sin(x))/h;
        bderiv=(sin(x+h)-sin(x-h))/2*h;
        if(fabs(trued-wderiv)>fabs(trued-bderiv))
            std::cout<<"Wderiv is better in sin in h= "<<pow(10,-i)<<std::endl<<"!!!!!!!"<<std::endl;
        else 
            std::cout<<"Bderiv is better in sin in h= "<<pow(10,-i)<<std::endl;

        ///fun
        trued=fun_deriv(x);
        wderiv=(fun(x+h)-fun(x))/h;
        bderiv=(fun(x+h)-fun(x-h))/2*h;
        if(fabs(trued-wderiv)>fabs(trued-bderiv))
            std::cout<<"Wderiv is better in fun in h= "<<pow(10,-i)<<std::endl<<"!!!!!!!"<<std::endl;
        else 
            std::cout<<"Bderiv is better in fun in h= "<<pow(10,-i)<<std::endl;

    }
    return 0;
}