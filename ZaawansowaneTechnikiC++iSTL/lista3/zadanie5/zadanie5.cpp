#include <iostream>
#include <chrono>
#include <random>


int main(int argc,char** argv)
{
    if(argc<2)
    {
        std::cout<<"Usage: ./zadanie5 n ~ n is matrix size\n";
        return 0;
    }
       
    int n=std::atoi(argv[1]);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.5,2.0);
    double* mtx=new double[n*n];
    for(int i=0;i<n*n;i++)
        mtx[i]=dist(gen);
    double* dest=new double[n*n];    
    auto start=std::chrono::high_resolution_clock::now();
    //poprawnie mnozenia macierzy
    for (int i=0;i<n;i++) 
    {
        for (int j=0;j<n;j++) 
        {
            dest[i*n+j]=0.0;
            for (int k=0;k<n;k++) 
            {
                dest[i*n+j]+=mtx[i*n+k]*mtx[k*n+j];
            }
        }
    }    
    //poprawione zwolnienie pamieci 
    delete mtx;
    delete dest;
    auto end=std::chrono::high_resolution_clock::now();
    auto time_elapsed=end-start;
    std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(time_elapsed).count()<<" microseconds"<<std::endl;
    std::cout<<std::chrono::duration_cast<std::chrono::milliseconds>(time_elapsed).count()<<" milliseconds"<<std::endl;

    return 0;
}