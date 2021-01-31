#include <stdio.h>
#include <stdlib.h>

////////1
// A=9
// b=5

////////2

// R=5
// S=13
// T=56



//////////3
typedef struct A
{
    long idx;
    long x[4];
}A;

typedef struct B
{
    int first;
    A a[7];
    int last;
}B;

////////4

typedef union elem
{
    struct 
    {
        long* p;
        long y;
    }e1;
    
    struct 
    {
        long x;
        union elem* next;
    }e2;

}elem;

//Rozmiar unii jest zawsze rowny jej najwiekszemu polu w tym wypadku e1 i e2 sa rowne 
//poniewaz wskaznik jest zawsze 8 bajtowy a long ma rowniez 8B wiec rozmiar unii to 16


void proc(elem* in)
{
    elem* t1=in->e2.next;
    long* t2=t1->e1.p;
    long t3=*t2;
    t3-=in->e2.x;
    in->e2.x=t3;
}

////////////5

typedef struct A
{
    long u[2];
    long *v;
}SA;

typedef struct B
{
    long p[2];
    long q;
}SB;

SB eval(SA s)
{
    SB temp;
    temp.p[0]=s.u[1]*(*s.v);
    temp.p[1]=s.u[0]-(*s.v);
    temp.q=s.u[0]-s.u[1];
    return temp;
}


long wrap(long x,long y,long z)
{
    SA sample;
    sample.u[0]=x;
    sample.u[1]=y;
    sample.v=&z;
    SB sample2=eval(sample);
    long t1=sample2.p[1];
    long t2=sample2.p[0];
    long t3=sample2.q;
    t1+=t2;
    t1*=t3;
    return t1;
}

//     -----------------
// 0
//     -----------------
// 8
//     -----------------
// 16
//     -----------------
// 24
//     -----------------
// 32
//     -----------------
// 40
//     -----------------
// 48
//     -----------------
// 56
//     -----------------
// 64
//     -----------------
// 72          z
//     -----------------
// 80      *ptr->$72
//     -----------------
// 88         y
//     -----------------
// 96         x
//     -----------------
// 104 adres powrotu do wrap


int main()
{
    printf("%li",sizeof(elem));
    return 0;
}