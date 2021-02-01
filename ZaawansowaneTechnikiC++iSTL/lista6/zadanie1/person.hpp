#include <deque>
#include <iostream>
#include <string>

#ifndef _PERSON_HPP_
#define _PERSON_HPP_


class person
{
    private:
        std::string name;
        std::string surname;
        int age;//years 
        double weight;//kgs
        double height;//m 
    public:
        person(const std::string& n,const std::string& s,const int& a,const double& w,const double& h):
            name(n),surname(s),age(a),weight(w),height(h){};
        auto get_name() const{return name;};
        auto get_surname() const{return surname;};
        auto get_age() const{return age;};
        auto get_weight() const{return weight;};
        auto get_height() const{return height;};
        auto& set_name(){return name;} 
        auto& set_surname(){return surname;};
        auto& set_age(){return age;};
        auto& set_weight(){return weight;};
        auto& set_height(){return height;};
        friend std::ostream& operator<<(std::ostream& out,const person& p)
        {
            out<<p.name<<" "<<p.surname<<" lat: "<<p.age<<" waga: "<<p.weight<<"kg wzrost: "
            <<p.height<<" m"<<std::endl;
            return out;
        };
};


#endif