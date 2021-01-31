using System;
using System.Collections.Generic;

namespace Graph
{
    class Vertex
    {
        public List<Vertex> conn;
        public string name;
        public Vertex(string val)
        {
            this.conn=new List<Vertex>();
            this.name=val;
        }
        public void AddConn(Vertex x)
        {
            foreach(Vertex p in this.conn)
            {
                if(p.name==x.name)return; 
            }            
            this.conn.Add(x);
        }
        public void RemConn(Vertex x)
        {
            this.conn.Remove(x);
        }
        public void PrintConn()
        {
            foreach(Vertex p in this.conn)
            {
                Console.Write("/" +p.name);
            }
        }
    }
}