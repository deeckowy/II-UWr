#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

template<typename T>
class on_stack
{
    private:
        T data;
    public:
        on_stack(){}
        T &operator*(){return data;}
        T *operator->(){return &data;}
        on_stack(const on_stack&)=delete;
        on_stack& operator=(const on_stack&)=delete;
};

template<typename T>
class on_heap
{
    private:
        T *data;
    public:
    on_heap() : data(new T){} 
    ~on_heap() { delete data; } 
    T& operator*(){return *data;}
    T* operator->(){return data;}
    on_heap(const on_heap&)=delete; 
    on_heap& operator=(const on_heap&)=delete;

};

constexpr int stack_limit=sizeof(std::string);

template<typename T>
struct obj_holder
{
    using type=typename std::conditional<(sizeof(T)<=stack_limit),
    on_stack<T>,on_heap<T>>::type;
};


//64 KiB max on heap 
constexpr int heap_limit=UINT16_MAX; 
const std::string filnam="data";


template<typename T,size_t size>
class array_in_file
{
    private:
        T *data;
    public:
        //niestety mapowanie pliku w pamiec nie chce dzialac a dzisiaj juz nie mam czasu tego naprawic :(
        array_in_file()
        {
            auto fd=open(filnam.c_str(),O_CREAT||O_WRONLY||O_RDONLY,S_IRWXU);
            data=static_cast<T*>(mmap(NULL,sizeof(T)*size,PROT_READ||PROT_WRITE,MAP_PRIVATE,fd,0));
            std::cout<<data<<std::endl;
            close(fd);
        }
        ~array_in_file(){munmap(data,sizeof(T)*size);}
        T& operator*(){return *data;}
        T& operator[](int idx){return data[idx];}
        array_in_file(const array_in_file&)=delete; 
        array_in_file& operator=(const array_in_file&)=delete;
};

template<typename T,size_t size>
class array_on_heap
{
    private:
        T *data;
    public:
    array_on_heap() : data(new T[size]){} 
    ~array_on_heap() { delete data; } 
    T& operator*(){return *data;}
    T& operator[](int idx){return data[idx];}
    array_on_heap(const array_on_heap&)=delete; 
    array_on_heap& operator=(const array_on_heap&)=delete;

};


template<typename T,size_t size>
struct arr_holder
{
    using type=typename std::conditional<(sizeof(T)*size<=heap_limit),array_on_heap<T,size>,array_in_file<T,size>>::type;
};

template<typename T>
using Holder=typename obj_holder<T>::type;

template<typename T,size_t size>
using ArrHolder=typename arr_holder<T,size>::type;

int main()
{

    Holder<int> n;
    *n=9;
    std::cout<<*n<<std::endl;
    ArrHolder<long,400> tab;
    tab[300]=21;
    std::cout<<tab[300]<<std::endl;
    return 0;
}