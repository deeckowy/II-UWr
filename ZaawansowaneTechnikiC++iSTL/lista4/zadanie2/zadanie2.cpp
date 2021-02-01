#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template<typename F,typename G,typename H>
class compose
{
    
    private:
        std::function<F(G,H)> f;
        std::function<G(G)> g;
        std::function<H(H)> h;
    public:
        compose(std::function<F(G,H)> fg,std::function<G(G)> gf,std::function<H(H)> hf):f(fg),g(gf),h(hf){};
        F operator()(G x,H y){return f(g(x),h(y));}
};

auto mult2(int x){return 2*x;}
auto add1(int x){return x+1;}
auto multxy(int x,int y){return x*y;}

int main()
{
    std::vector<int> vec{1,2,3,4,5,6};
    auto ff=compose<int,int,int>(multxy,mult2,add1);
    std::transform(vec.begin(),vec.end(),vec.begin(),[&](int x){return ff(x,x);});
    for(auto x:vec)
        std::cout<<x<<std::endl;
    return 0;
}