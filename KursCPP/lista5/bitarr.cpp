#include <iostream>
#include "bitarr.hpp"
#include <cmath>

using namespace std;

ref::ref():arr(new word()),bitn(0){}

void ref::set(word* x,int n)
{
    arr=x;
    bitn=n;
}

ref::operator bool()const{return *arr|(1<<bitn);}

ref& ref::operator=(bool h)
{
    __uint64_t i=1;
    if(h)
    {
        *arr|=(i<<bitn);
    }
    else
    {
        *arr&=~i;
    }
    return *this;
}

ostream& operator<<(ostream& out,const bitarr& ar)
{
    int i;
    for(i=0;i<ar.length-1;i++)
        out<<ar.read(i)<<", ";
    out<<ar.read(i)<<endl;
    return out;
}

bool bitarr::read(int i)const
{
    __uint64_t f=1;
    if(i<length)
    {
        return arr[(i/wordSize)]&(f<<(i%wordSize));
    }
    else 
        _Exit(EXIT_FAILURE);
}

bool bitarr::write(int i,bool b)
{
    if(b&&i<length)
    {
        arr[i/wordSize]|=(1<<(i%wordSize));
    }
    else if(!b&&i<length)
    {
        arr[i/wordSize]&=~(1<<(i%wordSize));
    } 
    _Exit(EXIT_FAILURE);
}

bitarr::bitarr(int size):length(size),arr(new word[size/wordSize]()),wordSize(sizeof(word)*8-1){x=new ref();}
bitarr::bitarr(word ar):length(sizeof(word)*8-1),arr(new word(ar)),wordSize(sizeof(word)*8-1){x=new ref();}
bitarr::bitarr(initializer_list<int> from):length(from.size())
{
    wordSize=(sizeof(word)*8-1);
    x=new ref();
    arr=new word[length/wordSize]();
    int i=0;
    for(int x:from)
    {
        arr[i/wordSize]|=(x<<(i%wordSize));
        i++;
    }        
}

bitarr::bitarr(const bitarr& ar):length(ar.length),wordSize(ar.wordSize),x(ar.x)
{
    arr=new word(*ar.arr);
}

bitarr::bitarr(bitarr&& ar):length(move(ar.length)),arr(move(ar.arr)),wordSize(move(ar.wordSize)),x(move(ar.x)){ar.arr=nullptr;}

bitarr& bitarr::operator=(const bitarr& ar)
{
    arr=ar.arr;
    x=ar.x;
    wordSize=ar.wordSize;
    length=ar.length;
    return *this;
}

bitarr& bitarr::operator=(bitarr&& ar)
{
    arr=move(ar.arr);
    wordSize=move(ar.wordSize);
    x=move(ar.x);
    length=move(ar.length);
    return *this;
}

bitarr::~bitarr(){delete[] arr;}

bool bitarr::operator[](int i)const{return read(i);}

ref bitarr::operator[](int i)
{
    x.set(&arr[i/wordSize],i%wordSize);
    return x;
}

bitarr& bitarr::operator&(const bitarr& ar)
{
    int min=length<ar.length?length:ar.length;
    for(int i=0;i<min;i+=wordSize)
        arr[i/wordSize]&=ar.arr[i/wordSize];
    return *this;
}

bitarr& bitarr::operator!()
{
    for(int i=0;i<length;i+=wordSize)
        arr[i/wordSize]=~arr[i/wordSize];
    return *this;
}

bitarr& bitarr::operator^(const bitarr& ar)
{
    int min=length<ar.length?length:ar.length;
    for(int i=0;i<min;i+=wordSize)
        arr[i/wordSize]^=ar.arr[i/wordSize];
    return *this;
}

bitarr& bitarr::operator|(const bitarr& ar)
{
    int min=length<ar.length?length:ar.length;
    for(int i=0;i<min;i+=wordSize)
        arr[i/wordSize]|=ar.arr[i/wordSize];
    return *this;
}

bitarr& bitarr::operator&=(const bitarr& ar){return *this&ar;}

bitarr& bitarr::operator^=(const bitarr& ar){return *this^ar;}

bitarr& bitarr::operator|=(const bitarr& ar){return *this|ar;}