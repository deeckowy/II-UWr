#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include "graph.hpp"

int main()
{
    auto* g=new graph();
    g->add_vertex(0,"pierwszy");
    g->add_vertex(1,"drugi");
    g->add_vertex(2,"trzeci");
    g->add_vertex(3,"czwarty");
    g->add_edge(0,3,1);
    g->show_path("pierwszy","czwarty");
    g->add_edge(0,1,9);
    g->add_edge(1,2,9);
    g->show_path("pierwszy","trzeci");
    return 0;
}