#include <iostream>
#include <algorithm>
#include <deque>
#include <cmath>
#include <random>
#include "person.hpp"

int main()
{
    std::deque<person> dek{
        person("John","Doe",27,97.6,1.93),
        person("Stefan","W",93,88.2,1.60),
        person("Jack","Ripper",69,123.5,1.80),
        person("Wladysław","Kurczak",71,85.1,1.20),
        person("Janina","Kiel",75,68.6,1.67),
        person("Bartosz","Kozak",19,75.3,1.97),
        person("Grazyna","Andrzejewska",54,123.6,0.90),
        person("Koniec","Pomyslow",58,32.6,1.50),
        person("Andrzej","Stonoga",37,92.6,1.59),
        person("Kaja","Kleszcz",50,180.6,1.68),
        person("Robert","Bak",32,92.6,1.70),
        };

    //a  poprawa
    std::sort(dek.begin(),dek.end(),[](const person& p1,const person& p2)
    {
        double b1=p1.get_weight()/p1.get_height()*p1.get_height();
        double b2=p2.get_weight()/p2.get_height()*p2.get_height();
        return b1<b2;
    });
    std::cout<<"Osoby posortowane wg BMI: \n";
    for(auto& p:dek)
        std::cout<<p;
    std::cout<<"\n\n\n";
    //b
    std::cout<<"Osoby po obozie:\n";
    std::for_each(dek.begin(),dek.end(),[](person& p){p.set_weight()*=0.9;});
    for(auto& p:dek)
        std::cout<<p;
    std::cout<<"\n\n\n";
    //c 
    std::cout<<"Osoby podzielone na dwie grupy wagowe:\n";
    std::partition(dek.begin(),dek.end(),[](const person& p){return p.get_weight()>100;});
    for(auto& p:dek)
        std::cout<<p;
    std::cout<<"\n\n\n";    
    ///d  (zamiana sortowania na nth_element)
    std::nth_element(dek.begin(),dek.begin()+dek.size()/2,dek.end(),[](const person& p1,const person& p2){return p1.get_height()<p2.get_height();});
    std::cout<<"Ustawienie sredniej osoby na srodkowy miejscu: \n";
    for(auto& p:dek)
        std::cout<<p;
    std::cout<<"\n\n\n";
    ///e
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(dek.begin(),dek.begin()+4,g);
    std::shuffle(dek.end()-4,dek.end(),g);
    std::cout<<"Losowo pomieszane osoby od 0 do 4 oraz od 6 do 11:\n";
    for(auto& p:dek)
        std::cout<<p;
    std::cout<<"\n\n\n";

    ///f
    auto [min,max]=std::minmax_element(dek.begin(),dek.end(),[](const person& p1,const person& p2){return p1.get_age()<p2.get_age();});
    std::cout<<"Osoba najmlodsza i najstarsza:\n";
    std::cout<<*min<<*max;
    std::cout<<"\n";

    return 0;
}