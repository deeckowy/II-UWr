#include "list.hpp"
#include <iostream>
using namespace std;

template<class T>
list<T>::list()
{
    head=nullptr;
    length=0;
}
template<class T>
list<T>::list(initializer_list<T> from)
{
    for(auto i:from)
        this->add(i);
    cout<<"init length:"<<this->length;
}

template<class T>
void list<T>::add(T v)
{
    if(head==nullptr)
    {
        head=new node<T>(v,head);
        length=1;
    }
    else
    {
        node<T>* x=head;
        while(x->gonext()!=nullptr)
        {
            x=x->gonext();
        }
        node<T>* nnode=new node<T>(v,x);
        length++;
    }
}

template<class T>
void list<T>::add(T v,int id)
{
    if(id>=length)
        add(v);
    else 
    {
        int i=0;
        node<T>* x=head; 
        node<T>* p=nullptr;
        while(i!=id)
        {
            p=x;
            x=x->gonext();
            i++;
        }
        node<T>* t=new node<T>(v,p);
        t->setnext(x);
        length++;
    }
}



template<class T>
T list<T>::getval(int id)const
{
    node<T>* x=head;
    int i=0;
    while(i!=id)
    {
        x=x->gonext();
        i++;
    }
    return x->getval();
}

template<class T>
void list<T>::rem(T v)
{
    node<T>* x=head;
    if(x->getval()==v)
    {
        head=x->gonext();
        delete x;
        length--;
        return;
    }
    node<T>* p=nullptr;
    while(x->getval()!=v&&x!=nullptr)
    {
        p=x;
        x=x->gonext();
    }
    if(x!=nullptr)
    {
        p->setnext(x->gonext());
        delete x;
        length--;
    }
}
template<class T>
list<T>::~list()
{
    node<T>* x= head;
    while(x->gonext()!=nullptr)
    {
        node<T>* p=x;
        x=x->gonext();
        delete p;
    }
    delete x;
}


template class list<int>;
template class list<double>;
template class list<char>;
template class list<float>;
template class list<long>;