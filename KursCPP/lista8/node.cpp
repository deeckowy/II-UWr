#include "node.hpp"


template<class T>
void node<T>::setnext(node<T>* x){next=x;}

template<class T>
node<T>::node(T v,node<T>* p):val(v)
{
    next=nullptr;
    if(p!=nullptr)
        p->setnext(this);
}

template<class T>
T node<T>::getval(){return val;}

template<class T>
node<T>* node<T>::gonext(){return next;}

template class node<int>;
template class node<double>;
template class node<char>;
template class node<float>;
template class node<long>;
