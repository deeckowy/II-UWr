#include <iostream>
#include <algorithm>
#include <vector>


template<typename T>
class LU_dcmp
{
    private:
        T** a;
        T** l;
        T** u;
        size_t bound;
    public:
        LU_dcmp(T** mat,const size_t size):bound(size)
        {
            a=new T*[bound]();
            l=new T*[bound]();
            u=new T*[bound]();
            for(size_t i=0;i<bound;i++)
            {
                a[i]=new T[bound]();
                l[i]=new T[bound]();
                u[i]=new T[bound]();
            }
            for(size_t i=0;i<bound;i++)
                for(size_t k=0;k<bound;k++)
                    a[i][k]=mat[i][k];
        }   
        void compute()
        {
            getchar();
            for(size_t i=0;i<bound;i++)
                l[i][i]=(T)1;
            for(int i=0;i<bound;i++)
            {
                for(int j=i;j<=bound;j++)
                {
                    T sum=(T)0;
                    for(int k=0;k<=i-1;k++)
                        sum+=l[i][k]*u[k][j];
                    u[i][j]=a[i][j]-sum;
                }
                for(int j=i+1;j<bound;j++)
                {
                    T sum=0;
                    for(int k=0;k<=i-1;k++)
                        sum+=l[j][k]*u[k][i];
                    l[j][i]=(a[j][i]-sum)/u[i][i];
                }
            }
        }
        T** get_L()
        {
            return l;
        }
        T** get_U()
        {
            return u;
        }
        void print_L()
        {
            std::cout<<std::endl<<"l="<<std::endl;
            for(size_t i=0;i<bound;i++)
            {
                // std::cout<<"|";
                for(size_t k=0;k<bound;k++)
                    std::cout<<" "<<l[i][k]<<" ";
                std::cout<<std::endl;
            }
        }
        void print_U()
        {
            std::cout<<std::endl<<"u="<<std::endl;
            for(size_t i=0;i<bound;i++)
            {
                // std::cout<<"|";
                for(size_t k=0;k<bound;k++)
                    std::cout<<" "<<u[i][k]<<" ";
                std::cout<<std::endl;
            }
        }
};

int main()
{
    size_t mat_size=0;
    std::cin>>mat_size;
    double **arr=new double*[mat_size]();
    for(size_t i=0;i<mat_size;i++)
        arr[i]=new double[mat_size]();
    for(size_t i=0;i<mat_size;i++)
        for(size_t k=0;k<mat_size;k++)
            std::cin>>arr[i][k];
    LU_dcmp<double> lu(arr,mat_size);
    lu.compute();
    lu.print_L();
    lu.print_U();
    return 0;
}

