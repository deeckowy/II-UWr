#include <iostream>
#include <unordered_map>


#ifndef _CALC_HPP_
#define _CALC_HPP_

namespace calc
{
    class symbol
    {
        public:
            virtual double eval();
            virtual double eval(double x);
            virtual double eval(double x,double y);
    };

    class number:public symbol
    {
        private:
            double val;
        public:
            number(double val):val(val){};
            double eval();
    };

    class var:public symbol
    {
        static std::unordered_map<std::string,double> var_map;
        public:
            var();
            var(std::string name,double val);
            double eval(std::string name);
            bool is_var(std::string name);
            void clean();
    };

    class constt:public symbol
    {
        private:
            double val;
        public: 
            constt(std::string name);
            double eval();
    };

    class funbin:public symbol
    {
        public:
            virtual double eval(double x,double y); 
    };

    class add:public funbin
    {
        public:
            double eval(double x,double y);
    };

    class sub:public funbin
    {
        public:
            double eval(double x,double y);
    };

    class mult:public funbin
    {
        public:
            double eval(double x,double y);
    };

    class div:public funbin
    {
        public:
            double eval(double x,double y);
    };

    class mod:public funbin
    {
        public:
            double eval(double x,double y);
    };

    class min:public funbin
    {
        public:
            double eval(double x,double y);
    };

    class max:public funbin
    {
        public:
            double eval(double x,double y);
    };

    class pow:public funbin
    {
        public:
            double eval(double x,double y);
    };

    class funun:public symbol
    {
        public:
            virtual double eval(double x);
    };

    class abs:public funun
    {
        public:
            double eval(double x);
    };

    class sgn:public funun
    {
        public:
            double eval(double x);
    };

    class floor:public funun
    {
        public:
            double eval(double x);
    };

    class ceil:public funun
    {
        public:
            double eval(double x);
    };

    class sin:public funun
    {
        public:
            double eval(double x);
    };

    class cos:public funun
    {
        public:
            double eval(double x);
    };

    class atan:public funun
    {
        public:
            double eval(double x);
    };

    class acot:public funun
    {
        public:
            double eval(double x);
    };

    class ln:public funun
    {
        public:
            double eval(double x);
    };

    class exp:public funun
    {
        public:
            double eval(double x);
    };
}




#endif