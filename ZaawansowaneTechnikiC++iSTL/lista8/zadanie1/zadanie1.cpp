#include <iostream>
#include <complex>

constexpr double elrmsch=0.5772156649;

auto gamma(const auto& c,const auto& n)
{
    auto output=std::complex<double>(1.0);
    for(auto i=1;i<=n;i++)
    {
        auto h=1.0/double(i);
        output*=std::pow((1.0+h),c)/(1.0+c*h);
    }
    return output/c;
}

auto ggamma(const auto& c,const auto& n)
{
    auto output=c*std::exp(elrmsch*c);
    auto mlt=std::complex<double>(1.0);
    for(auto i=1;i<=n;i++)
    {
        auto h=c/double(i);
        mlt*=(1.0+h)*std::exp(-h);
    }
    return mlt*output;
}

int main()
{
    auto c=std::complex<double>(1.0,1.0);
    std::cout<<"Gamma ="<<gamma(c,900)<<std::endl;
    std::cout<<"1/Gamma ="<<ggamma(c,900)<<std::endl;
    return 0;
}
