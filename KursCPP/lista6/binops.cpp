#include "binops.hpp"

add::add(expre* e,expre* b):fst(e),sec(b){priority=1;}

string add::print(int prior){return prior>priority?"("+fst->print(priority)+"+"+sec->print(priority)+")":fst->print(priority)+"+"+sec->print(priority);}

double add::eval(){return fst->eval()+sec->eval();} 

sub::sub(expre* e,expre* b):fst(e),sec(b){priority=1;}

string sub::print(int prior){return prior>priority?"("+fst->print(priority)+"-"+sec->print(priority)+")":fst->print(priority)+"-"+sec->print(priority);}

double sub::eval(){return fst->eval()-sec->eval();}

mult::mult(expre* e,expre* b):fst(e),sec(b){priority=2;}

string mult::print(int prior){return prior>priority?"("+fst->print(priority)+"*"+sec->print(priority)+")":fst->print(priority)+"*"+sec->print(priority);}

double mult::eval(){return fst->eval()*sec->eval();}

divv::divv(expre* e,expre* b):fst(e),sec(b){priority=2;}

string divv::print(int prior){return prior>priority?"("+fst->print(priority)+"/"+sec->print(priority)+")":fst->print(priority)+"/"+sec->print(priority);}

double divv::eval(){return fst->eval()/sec->eval();}

poww::poww(expre* e,expre* b):fst(e),sec(b){priority=3;}

string poww::print(int prior){return fst->print(priority)+"^"+sec->print(priority);}

double poww::eval(){return pow(fst->eval(),sec->eval());}

logg::logg(expre* e,expre* b):fst(e),sec(b){priority=3;}

string logg::print(int prior){return "log("+fst->print(priority)+","+sec->print(priority)+")";}

double logg::eval(){return log(fst->eval())/log(sec->eval());}