#include <iostream>
#include <complex>

auto dzeta(const auto& c,const auto& n)
{
    auto output=std::complex<double>(1.0);
    for(auto i=1;i<=n;i++)
        output+=std::pow(double(i),-c);
    return output;
}
// for c.real()>=0&&c.real()<1
auto dzeta2(const auto& c,const auto& n)
{
    auto output=std::complex<double>(1.0);
    for (auto i=1;i<=n;i+=2)
    {
        auto h=std::pow(double(i),c);
        output+=1.0/h;
        output+=-1.0/h;
    }
    return output/(1.0-2.0/std::pow(2.0,c));
}

int main()
{
    auto step=1.0/100;
    auto start=-10.0;
    while(start<=10.0)
    {
        auto t=dzeta2(std::complex<double>{0.5,start},1000);
        std::cout<<start<<", "<<t.real()<<", "<<t.imag()<<std::endl;
        start+=step;
    }
    return 0;
}