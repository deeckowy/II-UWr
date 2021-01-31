#include <stdio.h>
#include <stdlib.h>
///////////1

// x=%rsi
// y=%rdi

// CMPQ %rdi, %rsi y-x
// CMOVAQ $-1,%rax
// CMOVEQ $0,%rax
// CMOVBQ $1,%rax


//////////2

long puzzle2(char* s,char* d)
{
    long res=0;
    do
    {
        if(*s==*d)
        {
            res++;
            d++;
        }

        s++;

    } while (*d!='\0');
    return res;
}

__uint32_t puzzle3(__uint32_t n,__uint32_t d)
{
    __uint32_t x=32;
    __uint32_t s=0x80000000;
    __uint32_t res=0;
    L3:
    n=n*2;
    __uint32_t f=n;
    f=f-d;
    if(f<0)goto L2;
    res|=x;
    n=f;
    L2:
    s=s>>1;
    x--;
    if(x!=0)goto L3;
    return res;

}

int main()
{   
    char* s1=malloc(6*sizeof(char));
    char* s2=malloc(6*sizeof(char));

    for(int i=0;i<5;i++)
    {
        s1[i]='x';
        s2[i]='x';
    }
    s1[5]='\0';
    s2[5]='\0';
    printf("%li",puzzle2(s1,s2));
    printf("\n%u",puzzle3(32321,1));

    return 0;
}