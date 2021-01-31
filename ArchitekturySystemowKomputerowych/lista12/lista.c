#include <stdio.h>

#define data_t int

typedef struct 
{
    size_t len;
    data_t* data;
}vec;

#define vec_ptr vec*

data_t* get_vec_start(vec_ptr v)
{
    return v->data;
}
//////6x1
void inner4(vec_ptr u,vec_ptr v,data_t *dest)
{
    long i=0;
    long length=vec_length(u);
    long limit=length-6;
    data_t* udata=get_vec_start(u);
    data_t* vdata=get_vec_start(v);
    data_t sum=(data_t)0;
    for(i=0;i<limit;i+=6)
    {
        sum+=udata[i]+vdata[i];
        sum+=udata[i+1]+vdata[i+1];
        sum+=udata[i+2]+vdata[i+2];
        sum+=udata[i+3]+vdata[i+3];
        sum+=udata[i+4]+vdata[i+4];
        sum+=udata[i+5]+vdata[i+4];
    }
    for(;i<length;i++)
    {
        sum+=udata[i]+vdata[i];
    }
    *dest=sum;
}


//////6x6
void inner4(vec_ptr u,vec_ptr v,data_t *dest)
{
    long i=0;
    long length=vec_length(u);
    long limit=length-6;
    data_t* udata=get_vec_start(u);
    data_t* vdata=get_vec_start(v);
    data_t sum=(data_t)0;
    data_t sum1=(data_t)0;
    data_t sum2=(data_t)0;
    data_t sum3=(data_t)0;
    data_t sum4=(data_t)0;
    data_t sum5=(data_t)0;
    for(i=0;i<limit;i+=6)
    {
        sum+=udata[i]+vdata[i];
        sum1+=udata[i+1]+vdata[i+1];
        sum2+=udata[i+2]+vdata[i+2];
        sum3+=udata[i+3]+vdata[i+3];
        sum4+=udata[i+4]+vdata[i+4];
        sum5+=udata[i+5]+vdata[i+4];
    }
    for(;i<length;i++)
    {
        sum+=udata[i]+vdata[i];
    }
    *dest=sum+sum1+sum2+sum3+sum4+sum5;
}

//////6x1a
void inner4(vec_ptr u,vec_ptr v,data_t *dest)
{
    long i=0;
    long length=vec_length(u);
    long limit=length-6;
    data_t* udata=get_vec_start(u);
    data_t* vdata=get_vec_start(v);
    data_t sum=(data_t)0;
    for(i=0;i<limit;i+=6)
    {
        sum+=((udata[i]+vdata[i])+(udata[i+1]+vdata[i+1]))+((udata[i+2]+vdata[i+2]));
    }
    for(;i<length;i++)
    {
        sum+=udata[i]+vdata[i];
    }
    *dest=sum;
}