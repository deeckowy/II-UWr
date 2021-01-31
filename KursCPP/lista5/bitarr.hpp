#ifndef _BITARR_HPP 
#define _BITARR_HPP

#include <iostream>

using namespace std;

typedef __uint64_t word;


class ref
{
    word* arr;
    int bitn;
    
    public:
        ref();
        ref& operator=(bool h);
        operator bool()const;
        void set(word* x,int n);
};

class bitarr
{
    class ref x;
    int wordSize;
    friend ostream& operator<<(ostream& out,const bitarr& ar);
    bool read(int i)const;
    bool write(int i, bool b);
    protected:
        int length;
        word* arr;
    public:
        explicit bitarr(int size);
        explicit bitarr(word ar);
        bitarr(initializer_list<int> from);
        bitarr(const bitarr &ar);
        bitarr(bitarr&& ar);
        ~bitarr();
        bitarr& operator=(const bitarr& ar);
        bitarr& operator=(bitarr&& ar);
        bool operator[](int i)const;
        ref operator[](int i);
        inline int size()const{return length;}
        bitarr& operator&(const bitarr& ar);
        bitarr& operator!();
        bitarr& operator^(const bitarr& ar);
        bitarr& operator|(const bitarr& ar);
        bitarr& operator&=(const bitarr& ar);
        bitarr& operator^=(const bitarr& ar);
        bitarr& operator|=(const bitarr& ar);
};

#endif