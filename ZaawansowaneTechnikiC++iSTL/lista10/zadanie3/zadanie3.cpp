#include <iostream>
#include <filesystem>
#include <chrono>
#include <algorithm>
#include <iterator>

namespace fs=std::filesystem;

//from https://en.cppreference.com/w/cpp/filesystem/perms
void demo_perms(fs::perms p)
{
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-");
}


auto get_ftype(const auto& info)
{
    switch (info)
    {
        case fs::file_type::regular:
            return "file";
        case fs::file_type::directory:
            return "dir";
        case fs::file_type::symlink:
            return "symlink";
        case fs::file_type::block:
        case fs::file_type::character:
            return "device";
        case fs::file_type::fifo:
            return "fifo";
        case fs::file_type::socket:
            return "socket";
        default:
            return "unknown";
    }
}

int main(int argc,char **argv)
{
    if(argc==1)
    {
        std::cout<<"Usage: "<<argv[0]<<" <filenames>"<<std::endl;
        exit(EXIT_FAILURE);
    }
    auto i=1;
    while(i!=argc)
    {
        if(fs::exists(argv[i]))
        {
            auto path=fs::path(argv[i]);
            std::cout<<fs::canonical(path)<<" | ";
            auto fstat=fs::status(path);
            std::cout<<get_ftype(fstat.type())<<" | ";
            if(fs::is_directory(path))
                std::cout<<"d";
            else 
                std::cout<<"-";
            demo_perms(fstat.permissions());
            if(fs::is_regular_file(path))
            {
                std::cout<<" | size = "<<fs::file_size(path)<<" bytes";
                auto ftime = fs::last_write_time(path);

                std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
                std::cout << "File write time is " << std::asctime(std::localtime(&cftime)) << '\n';
            
                fs::last_write_time(path, ftime + 1h); // move file write time 1 hour to the future
                ftime = fs::last_write_time(path); // read back from the filesystem
            
                cftime = decltype(ftime)::clock::to_time_t(ftime);
                std::cout << "File write time is " << std::asctime(std::localtime(&cftime)) << '\n';
            }
            
            std::cout<<std::endl;
        }
        i++;
    }
    return 0;
}