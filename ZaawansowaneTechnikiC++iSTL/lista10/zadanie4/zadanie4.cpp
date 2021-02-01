#include <filesystem>
#include <iostream>

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
    
    auto path=fs::canonical(argv[1]);
    auto it=fs::directory_iterator(path);
    for(auto &x:it)
        std::cout<<x.path()<<std::endl;
    return 0;
}