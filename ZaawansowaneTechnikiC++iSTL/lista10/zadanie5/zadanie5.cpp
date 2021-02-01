#include <iostream>
#include <iterator>
#include <filesystem>

namespace fs=std::filesystem;

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        std::cout<<"Usage : "<<argv[0]<<" <directory_name>"<<std::endl;
        exit(EXIT_FAILURE);
    }
    if(!fs::exists(argv[1]))
    {
        std::cout<<argv[1]<<" does not exist !"<<std::endl;
        exit(EXIT_FAILURE);
    }
    if(!fs::is_directory(argv[1]))
    {
        std::cout<<argv[1]<<" is not a directory!"<<std::endl;
        exit(EXIT_FAILURE);
    }    

    long sum=0;
    for(auto &x :fs::recursive_directory_iterator(argv[1]))
    {
        std::cout<<x.path()<<std::endl;
        if(fs::is_regular_file(x))
            sum+=fs::file_size(x);
    }
    std::cout<<"Sum of all files size = "<<sum<<"bytes"<<std::endl;
    return 0;
}