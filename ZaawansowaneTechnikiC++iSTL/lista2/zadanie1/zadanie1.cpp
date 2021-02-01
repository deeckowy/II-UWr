#include </usr/include/c++/7/memory>
#include <iostream>
#include <cstdint>
#include <cstdlib>

class sample_class{
    private:
        uint64_t counter;
    public:
        sample_class(){counter=1;}
        void add(int n){counter+=n;}
        virtual ~sample_class(){std::cout<<counter<<std::endl;}
};

void fun(std::unique_ptr<sample_class[]> &arr,int m,int size)
{
    if(!m)
        return;
    else 
    {
        arr[rand()%size].add(m);
        fun(arr,m-1,size);
    }
}



int main()
{
    int size=12;
    std::unique_ptr<sample_class[]> arr(new sample_class[size]);
    fun(arr,100,size);
    arr.~unique_ptr();
}