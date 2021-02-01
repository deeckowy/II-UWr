#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> s1(new int(64));
    std::shared_ptr<int> s2(s1);
    std::shared_ptr<int> s3(s1);
    std::weak_ptr<int> w1(s1);
    std::cout<<w1.use_count()<<std::endl;
    s2.~__shared_ptr();
    std::cout<<w1.use_count()<<std::endl;
    s1.~__shared_ptr();
    std::cout<<w1.use_count()<<std::endl;
    std::cout<<*s3<<std::endl;
    s3.~__shared_ptr();
    w1.~__weak_ptr();
}