#ifndef _NODE_HPP
#define _NODE_HPP

template<class T>class node
{
    public: 
        node(T v,node<T>* p);
        void setnext(node<T>* x);
        T getval();
        node<T>* gonext();
    private:
        T val;
        node<T>* next;
    
};

#endif