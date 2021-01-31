#include "wektor.hpp"
#include "punkt.hpp"

punkt::punkt(const double &a,const double &b) : x(a),y(b) {}

punkt::punkt(const punkt &in,const wektor &vec): x(in.x+vec.dx),y(in.y+vec.dy){}

