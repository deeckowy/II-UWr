#include <iostream>
#include <cmath>
#include <functional>

auto po_kolei(auto f,auto g)
{
    return [&](auto x){f(x);g(x);};
}



auto fun1(int x){std::cout<<"x = "<<x<<std::endl;}
auto fun2(int x){std::cout<<"x * x = "<<x*x<<std::endl;}
auto fun3(int x){std::cout<<"x/2 = "<<x/2<<std::endl;}


int main()
{
    po_kolei(po_kolei(fun1,fun2),fun3)(2);
    return 0;
}