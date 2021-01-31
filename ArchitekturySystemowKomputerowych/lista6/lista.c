#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>

// //////1111111111111111
// long puzzle(long n,long* p)
// {
//     long t1=n;//%rbx
//     long* t2=p;//%rbp
//     long res=0;//%rax
//     if(n>0)
//     {
//         long* t3=malloc(sizeof(long));
//         n+=n;
//         res=puzzle(n,t3);
//         res+=*t3;
//         t1+=res;
//     }
//     *p=t1;
//     return res;
// }

long puzzle(long n,long* p)
{
    long res=0;//%rax
    if(n>0)
    {
        res=puzzle(n*2,p);
        res+=*p;
        n+=res;
    }
    *p=n;
    return res;
}

////////////222222222
long aframe(long n, long idx, long *q) 
{
    long i;
    long **p = alloca(n * sizeof(long *));
    p[n-1] = &i;
    for (i = 0; i < n; i++)
        p[i] = q;
        
    return *p[idx];
}

///////////3333333333
void readlong(long* p)
{
    scanf("%li",p);
}

long puzzle5(void)
{
    long* t1=malloc(sizeof(long));
    long* t2=malloc(sizeof(long));
    readlong(t1);
    readlong(t2);
    if(*t1%*t2==0)
        return 1;
    else
        return 0;
}




int main()
{
    long *p=malloc(sizeof(long));
    printf("%lu\n",puzzle(1,p));
    printf("%lu",*p);
    long n=2;
    long idx=1;
    long* q=malloc(sizeof(long)*2);
    q[0]=1;
    q[1]=2;
    printf("%li\n",aframe(n,idx,q));
    printf("%li",puzzle5());
    return 0;
}


// 000000000000071a <aframe>:
//  71a:	55                   	push   %rbp
//  71b:	48 89 e5             	mov    %rsp,%rbp
//  71e:	48 83 ec 10          	sub    $0x10,%rsp
//  722:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
//  729:	00 00 
//  72b:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
//  72f:	31 c0                	xor    %eax,%eax
//  731:	4c 8d 0c fd 00 00 00 	lea    0x0(,%rdi,8),%r9
//  738:	00 
//  739:	49 8d 41 1e          	lea    0x1e(%r9),%rax
//  73d:	48 83 e0 f0          	and    $0xfffffffffffffff0,%rax
//  741:	48 29 c4             	sub    %rax,%rsp
//  744:	4c 8d 44 24 0f       	lea    0xf(%rsp),%r8
//  749:	49 83 e0 f0          	and    $0xfffffffffffffff0,%r8
//  74d:	4c 89 c1             	mov    %r8,%rcx
//  750:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
//  754:	4b 89 44 08 f8       	mov    %rax,-0x8(%r8,%r9,1)
//  759:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
//  760:	00 
//  761:	eb 09                	jmp    76c <aframe+0x52>
//  763:	48 89 14 c1          	mov    %rdx,(%rcx,%rax,8)
//  767:	48 83 45 f0 01       	addq   $0x1,-0x10(%rbp)
//  76c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
//  770:	48 39 f8             	cmp    %rdi,%rax
//  773:	7c ee                	jl     763 <aframe+0x49>
//  775:	49 8b 04 f0          	mov    (%r8,%rsi,8),%rax
//  779:	48 8b 00             	mov    (%rax),%rax
//  77c:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
//  780:	64 48 33 34 25 28 00 	xor    %fs:0x28,%rsi
//  787:	00 00 
//  789:	75 02                	jne    78d <aframe+0x73>
//  78b:	c9                   	leaveq 
//  78c:	c3                   	retq   
//  78d:	e8 3e fe ff ff       	callq  5d0 <__stack_chk_fail@plt>