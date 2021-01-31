#include "unops.hpp"

sinus::sinus(expre* e):val(e){priority=0;}

double sinus::eval(){return sin(val->eval());}

string sinus::print(int prior){return "sin("+val->print()+")";}

cosinus::cosinus(expre* e):val(e){priority=0;}

double cosinus::eval(){return cos(val->eval());}

string cosinus::print(int prior){return "cos("+val->print()+")";}

absolute::absolute(expre* e):val(e){priority=0;}

string absolute::print(int prior){return "|"+val->print()+"|";}

double absolute::eval(){return abs(val->eval());}

oppo::oppo(expre* e):val(e){priority=0;}

string oppo::print(int prior){return "oppo("+val->print()+")";}

double oppo::eval(){return val->eval()>=0?val->eval():(-1)*val->eval();}

expot::expot(expre* e):val(e){priority=0;}

string expot::print(int prior){return "exp("+val->print()+")";}

double expot::eval(){return exp(val->eval());}

rev::rev(expre* e):val(e){priority=0;}

string rev::print(int prior){return "rev("+val->print()+")";}

double rev::eval(){return 1/(val->eval());}

ln::ln(expre* e):val(e){priority=0;}

string ln::print(int prior){return "ln "+ val->print();}

double ln::eval(){return log(val->eval());}
