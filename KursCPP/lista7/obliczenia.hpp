#include <iostream>

#ifndef _OBLICZENIA_HPP
#define _OBLICZENIA_HPP

using namespace std;

namespace obliczenia
{
    class wymierna
    {
        private:
            int licz;
            int mian;
            void skroc();//skraca licznik i mianownik tak aby ich NWD zawsze byl rowny 1
            void minus();//ustawia minus tak aby mianownik byl zawsze liczba dodatnia

        public:
            
            wymierna(const int &a,const int &b);//konstruktor dla 1 lub 2 intow
            
            //gettery
            int getMian()const;
            int getLiczn()const;
            //operatory 
            wymierna& operator+(const wymierna &d);
            wymierna& operator-(const wymierna &d);
            wymierna& operator-();
            wymierna& operator*(const wymierna &d);
            wymierna& operator/(const wymierna &d);
            wymierna& operator!();
            //operatory rzutowania
            operator int()const;
            operator double()const;
            friend ostream& operator<<(ostream &out,const wymierna &w)
            {
                double x=(double)w.licz/(double)w.mian;
                out<<x<<endl;
                return out;
            }
    };    
}


#endif