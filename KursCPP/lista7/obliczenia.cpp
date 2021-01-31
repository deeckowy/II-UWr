#include <iostream>
#include "obliczenia.hpp"
#include "wym_wyj.hpp"
#include <climits>

using namespace std;
typedef long long int lli;
#define MAX INT_MAX
#define MIN INT_MIN

int nwd(int a,int b)
{
    if(a!=b)
        return nwd(a>b?a-b:a,b>a?b-a:b);
    return a;
}

void obliczenia::wymierna::skroc()
{
    while(nwd(licz,mian)!=1)
    {
        licz/=nwd(licz,mian);
        mian/=nwd(licz,mian);
        if(mian==0)throw new dzielenie_przez_0(licz,mian);
    }
    minus();
}

void obliczenia::wymierna::minus()
{
    if((licz<0&&mian<0)||mian<0)
    {   
        licz*=-1;
        mian*=-1;
    }
}

obliczenia::wymierna::wymierna(const int &a,const int &b=1)
{
    try
    {
        if(b==0)throw new dzielenie_przez_0(a,b);

        licz=a;
        mian=b;
        this->skroc();
    }
    catch(const wyjatek_wymierny *x)
    {
        x->poka_blad();
    }
}


int obliczenia::wymierna::getLiczn()const{return licz;}
int obliczenia::wymierna::getMian()const{return mian;}

obliczenia::wymierna& obliczenia::wymierna::operator+(const wymierna &d)
{
    try
    {
        lli c1=this->mian;
        lli c2=d.mian;
        lli c3=this->licz;
        lli c4=d.licz;
        c3*=c2;
        c1*=c2;
        c4*=c2;
        c3+=c4;
        if(c3>MAX||c3<MIN||c1>MAX||c1<MIN)throw new przekroczenie_zakresu(*this,d,'+');
        this->licz=(int)c3;
        this->mian=(int)c1;
        this->skroc();
    }
    catch(const wyjatek_wymierny *x)
    {
        x->poka_blad();
    }
    return *this;    
}

obliczenia::wymierna& obliczenia::wymierna::operator-(const wymierna &d)
{
    try
    {
        lli c1=this->mian;
        lli c2=d.mian;
        lli c3=this->licz;
        lli c4=d.licz;
        c3*=c2;
        c1*=c2;
        c4*=c2;
        c3-=c4;
        if(c3>MAX||c3<MIN||c1>MAX||c1<MIN)throw new przekroczenie_zakresu(*this,d,'-');
        this->licz=(int)c3;
        this->mian=(int)c1;
        this->skroc();
    }
    catch(const wyjatek_wymierny *x)
    {
        x->poka_blad();
    }
    return *this;    
}

obliczenia::wymierna& obliczenia::wymierna::operator-()
{
    this->licz*=-1;
    return *this;
}

obliczenia::wymierna& obliczenia::wymierna::operator*(const wymierna &d)
{
    try
    {
        lli c1=this->mian;
        lli c2=d.mian;
        lli c3=this->licz;
        lli c4=d.licz;
        c3*=c4;
        c1*=c2;
        if(c3>MAX||c3<MIN||c1>MAX||c1<MIN)throw new przekroczenie_zakresu(*this,d,'*');
        this->licz=(int)c3;
        this->mian=(int)c1;
        this->skroc();
    }
    catch(const wyjatek_wymierny *x)
    {
        x->poka_blad();
    }
    return *this;    
}
obliczenia::wymierna& obliczenia::wymierna::operator!()
{
    try
    {
        int help_me=this->getMian();
        if(help_me==0)throw new dzielenie_przez_0(help_me,this->getLiczn());
        this->mian=this->getLiczn();
        this->licz=help_me;
    }
    catch(const wyjatek_wymierny *x)
    {
        x->poka_blad();
    }
    return *this;
}

obliczenia::wymierna& obliczenia::wymierna::operator/(const wymierna &d)
{
    try
    {
        lli c1=this->mian;
        lli c2=d.mian;
        lli c3=this->licz;
        lli c4=d.licz;
        c3*=c2;
        c1*=c4;
        if(c3>MAX||c3<MIN||c1>MAX||c1<MIN)throw new przekroczenie_zakresu(*this,d,'/');
        this->licz=(int)c3;
        this->mian=(int)c1;
        this->skroc();
    }
    catch(const wyjatek_wymierny *x)
    {
        x->poka_blad();
    }
    return *this;    
}


obliczenia::wymierna::operator int()const
{
    return (int)this->licz/this->mian;
}

obliczenia::wymierna::operator double()const
{
    return (double)this->licz/this->mian;
}
