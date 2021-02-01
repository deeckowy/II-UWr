#include <iostream>
#include <algorithm>
#include <string>

auto fun(const auto& s)
{
    auto perm=s;
    std::next_permutation(perm.begin(),perm.end());
    std::cout<<"Permutacje "<<s<<":\n"<<perm<<std::endl;
    while(perm!=s)
    {
        std::next_permutation(perm.begin(),perm.end());
        std::cout<<perm<<std::endl;
    }
}


int main()
{
    std::string es;
    std::cout<<"Podaj napis:\n";
    std::cin>>es;
    fun(es);
    return 0;
}