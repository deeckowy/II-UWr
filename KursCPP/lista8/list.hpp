#include "node.hpp"
#include <initializer_list>
#include <iostream>
#ifndef _LIST_HPP
#define _LIST_HPP

using namespace std;

template<class T>class list
{
    private: 
        node<T>* head;
        int length;

    public:
        list();
        list(initializer_list<T> from);
        //other constructors are default 
        void add(T v);
        void add(T v,int id);
        T getval(int id)const;
        void rem(T v);
        int size()const{return length;}
        ~list();
        friend ostream& operator<<(ostream& out,const list& li)
        {
             node<T>* x=li.head;
            while(x!=nullptr)
            {
                out<<x->getval()<<endl;
                x=x->gonext();
            }
            return out;
        }
};

template<class T>class checker
{
    public:
        static bool good(T a,T b){return a<=b;}
};

template<class T>class checker<T*>
{
    public:
        static bool good(T* a,T* b){return (*a)<=(*b);}
};

template<class T>class checker2
{
    public:
        static bool goodinanotherway(T a,T b){return a>=b;}
};

template<class T>class checker2<T*>
{
    public:
        static bool goodinanotherway(T* a,T* b){return (*a)>=(*b);}
};



template<class T,class C>
bool check(const list<T>& li)
{
    int len=li.size();
    for(int i=1;i<len;i++)
        if(!C::good(li.getval(i-1),li.getval(i)))
            return false;
    return true;
}
template<class T,class C>/// bubble sort
void sort(list<T>* li)
{
    int len=li->size();
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<len-i-1;j++)
        {
            if(C::goodinanotherway(li->getval(j),li->getval(j+1)))
            {
                T temp=li->getval(j);
                li->rem(temp);
                li->add(temp,j+1);
            }
        }
    }
}




#endif