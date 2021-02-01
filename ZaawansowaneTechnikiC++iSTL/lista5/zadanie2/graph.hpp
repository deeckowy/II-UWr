#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>

#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

class graph
{
    private:
        std::unordered_map<int,std::string> vertexi2s;
        std::unordered_map<std::string,int> vertexs2i;
        std::unordered_map<int,std::vector<std::pair<int,int>>> edges;
    public:
        graph(){};
        void add_vertex(int id,const std::string& name);
        std::string get_name(int id);
        int get_id(const std::string& name);
        void add_edge(int from,int to,int val);
        void add_edge(const std::string& from,const std::string& to,int val);
        void reval_edge(int from,int to,int new_val);
        void reval_edge(const std::string& from,const std::string& to,int new_val);
        void remove_edge(int from,int to);
        void remove_edge(const std::string& from,const std::string& to);
        void show_path(const std::string& from,const std::string& to);
        void show_path(int from,int to);
        ~graph();
};

#endif