#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <list>
#include <set>

/// Zmiany zamiast obslugi typow obslugujemy kolekcje w template 



template<typename T,T lowbnd,T upbnd>
void crita(T& elem)
{
    if(elem>lowbnd&&elem<upbnd)
        std::cout<<elem<<std::endl;
}

template<typename col>
class critb
{
    private:
        long start;
        long next;
        long pos;
    public:
        critb(long s,long n):start(s),next(n),pos(0){}
        void operator() (auto& elem)
        {
            if(pos-start>0&&(pos-start)%next==0)
                std::cout<<elem<<std::endl;
            pos++;
        }
};

template<typename col>
auto critc(col& vec)
{
    typename col::value_type sum=0;
    std::for_each(vec.begin(),vec.end(),[&](auto& x){sum+=x;});
    return sum/vec.size();
}

template<typename col>
auto critd(col& vec)
{
    auto min=vec.begin();
    auto max=vec.begin();
    auto pos=vec.begin();
    std::for_each(vec.begin(),vec.end(),[&](auto& elem){
        if(*max<elem)  
            max=pos;
        if(elem<*min)
            min=pos;
        pos++;
    });
    return std::make_pair(min,max);
};

template<typename col>
auto crite(col& vec,typename col::value_type init)
{
    std::for_each(vec.begin(),vec.end(),[&](auto& elem){init+=elem;});
    return init;
}

int main()
{
    std::vector<int> int_v{8,32,12,3214,53};
    std::list<double> double_v{2.0,3.0,4.43,0.34,12.98};
    std::set<std::string> string_v{"xd","321","sample_string","SAASAS","again_string","podpunkt b"}; 

    std::cout<<"Zadanie a dla przedziału 20-300 :"<<std::endl;
    std::for_each(int_v.begin(),int_v.end(),crita<int,20,300>);

    std::cout<<"Zadanie b od 1 co 2 :"<<std::endl;
    std::for_each(string_v.begin(),string_v.end(),critb<std::set<std::string>>(1,2));

    std::cout<<"Zadanie c ~ średnia dla double :"<<critc<std::list<double>>(double_v)<<std::endl;

    auto pr=critd<std::list<double>>(double_v);
    std::cout<<"Zadanie d ~ najmniejsza i najwieksza wartosc z listy double max = "<<*(pr.second)<<" min = "<<*(pr.first)<<std::endl;
    
    std::cout<<"Zadanie e ~ sumy "<<std::endl;
    std::cout<<"Suma vectora int :"<<crite<std::vector<int>>(int_v,0.0)<<std::endl;
    std::cout<<"Suma vectora double :"<<crite<std::list<double>>(double_v,0.0)<<std::endl;
    std::cout<<"Konkatenacja vectora string :"<<crite<std::set<std::string>>(string_v,"")<<std::endl;
    
    return 0;
}