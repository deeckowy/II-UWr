#include <iostream>
#include <type_traits>

template<typename T,typename T2>
    void foo(T arg1,T2& arg2,std::true_type,std::true_type)
    {
        arg2=arg1;
    }
template<typename T,typename T2>
    void foo(T arg1,T2& arg2,std::false_type,std::true_type)
    {
        arg2=arg1;
    }

template<typename T,typename T2>
    void foo(T arg1,T2& arg2,std::false_type,std::false_type)
    {
        std::cout<<"T1 is a not pointer and cannot be converted!"<<std::endl;        
    }
template<typename T,typename T2>
    void foo(T arg1,T2& arg2,std::true_type,std::false_type)
    {
        std::cout<<"T1 is a pointer and cannot be converted!"<<std::endl;
    }

template<typename T,typename T2>
    void foo_impl(T arg1,T2& arg2)
    {
        foo(arg1,arg2,std::is_pointer<T>(),std::is_convertible<T,T2>());
    }

int main()
{
    double* a;
    double* ptr=new double(4.0123);
    foo_impl(ptr,a);
    std::cout<<*a<<std::endl;
    double f=*ptr;
    double& x=f;
    double y;
    foo_impl(x,y);
    std::cout<<y<<std::endl;
    int s;
    foo_impl(y,s);
    std::cout<<s<<std::endl;

    return 0;
}