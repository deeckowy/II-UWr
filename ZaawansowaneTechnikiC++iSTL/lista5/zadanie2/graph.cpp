#include "graph.hpp"

void graph::add_vertex(int id,const std::string& name)
{
    vertexi2s[id]=name;
    vertexs2i[name]=id;
}

std::string graph::get_name(int id)
{
    return vertexi2s[id];
}

int graph::get_id(const std::string& name)
{
    return vertexs2i[name];
}

void graph::add_edge(int from,int to,int val)
{
    edges[from].push_back({to,val});
}

void graph::add_edge(const std::string& from,const std::string& to,int val)
{    
    add_edge(get_id(from),get_id(to),val);
}

void graph::reval_edge(int from,int to,int new_val)
{
    for(auto x:edges[from])
        if(x.first==to)x.second=new_val;
}

void graph::reval_edge(const std::string& from,const std::string& to,int new_val)
{
    reval_edge(get_id(from),get_id(to),new_val);
}

void graph::remove_edge(int from,int to)
{
    auto edg=edges[from];
    for(auto i=edg.begin();i<edg.end();i++)
    {
        if(i->first==to)
        {
            edg.erase(i);
            return;
        }
    }
}

void graph::remove_edge(const std::string& from,const std::string& to)
{
    remove_edge(get_id(from),get_id(to));
}

void graph::show_path(int from,int to)
{
    std::queue<int> que;
    std::set<int> visited;
    std::unordered_map<int,int> neighbours;
    que.push(from);
    visited.insert(from);
    
    while(!que.empty())
    {
        auto x=que.front();
        que.pop();
        if(x==to)
        {
            std::list<int> path;
            while(to!=from)
            {
                path.push_front(to);
                to=neighbours[to];
            }
            path.push_front(from);
            for(auto x:path)
            {
                if(x==path.back())
                    std::cout<<x<<std::endl;
                else 
                    std::cout<<x<<"->";
            }
            return;
        }
        for(auto v:edges[x])
        {
            if(!visited.count(v.first))
            {
                visited.insert(v.first);
                neighbours[v.first]=x;
                que.push(v.first);
            }            
        }
    }
}

void graph::show_path(const std::string& from,const std::string& to)
{
    return show_path(get_id(from),get_id(to));
}
