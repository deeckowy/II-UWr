using System;
using System.Collections.Generic;

namespace Graph
{
    class ListR:Graphh
    {
        List<Vertex> conn;
        Random x;
        int size;
        List<string> BPath;
        public ListR()
        {
            this.conn=new List<Vertex>();
            this.x=new Random();
            this.size=0;
        }
        public ListR(int vertex,int con)
        {
            this.conn=new List<Vertex>();
            this.x=new Random();
            this.size=0;
            for(int i=0;i<vertex;i++)
            {
                this.Add();
            }
            for(int i=0;i<con;i++)
            {
                this.AddConn();
            }
        }
        public void Add(string name)
        {
            this.conn.Add(new Vertex(name));
            this.size++;
        }
        public void Add()
        {
            string name="";
            for(int i=0;i<this.x.Next(1,10);i++)
            {
                char s=(char)this.x.Next(65,90);
                name+=s;
            }
            this.conn.Add(new Vertex(name));
            this.size++;
        }
        public void Print()
        {
            foreach(Vertex p in this.conn)
            {
                Console.Write(p.name + " -> ");
                p.PrintConn();
                Console.Write("\n");
            }
        }
        public void AddConn(string from,string to)
        {
            int i=this.GetIndex(from);
            int k=this.GetIndex(to);
            if(i>=0&&k>=0)
            {
                if(i==k)
                    this.conn[i].AddConn(this.conn[k]);
                else
                {
                    this.conn[i].AddConn(this.conn[k]);
                    this.conn[k].AddConn(this.conn[i]);
                }
            }
        }
        public void AddConn(int from,int to)
        {
            if(from<this.size&&to<this.size)
            {
                if(from==to)
                    this.conn[from].AddConn(this.conn[to]);
                else
                {
                    this.conn[from].AddConn(this.conn[to]);
                    this.conn[to].AddConn(this.conn[from]);
                }
            }
        }
        public void AddConn()
        {
            this.AddConn(this.x.Next(0,this.size),this.x.Next(0,this.size));
        }
        public void RemVer(string name)
        {
            int i=this.GetIndex(name);
            if(i>0)
            {
                this.conn.RemoveAt(i);
                this.size--;
            }
        }
        public void RemVer(int z)
        {
            if(z<this.size)
            {
                this.conn.RemoveAt(z);
                this.size--;
            }
        }
        private int GetIndex(string n)
        {
            for(int i=0;i<this.size;i++)
            {
                if(this.conn[i].name==n)return i;
            }
            return -1;
        }
        public List<string> QuickPath(int start,int destination)
        {
            if(start<this.size&&destination<this.size)
            {
                this.BPath=new List<string>();
                this.SearchPath(new List<string>(),start,destination);
                return this.BPath;
            }
            else
                return new List<string>();
        }
        public List<string> QuickPath(string start,string destination)
        {
            int i=this.GetIndex(start);
            int k=this.GetIndex(destination);
            if(i>=0&&k>=0)
            {
                this.BPath=new List<string>();
                this.SearchPath(new List<string>(),i,k);
                return this.BPath;
            }
            else
                return new List<string>();
        }
        private void SearchPath(List<string> Path,int sin,int din)
        {
            Path.Add(this.conn[sin].name);
            if(sin==din)
            {
                if((Path.Count<this.BPath.Count||this.BPath.Count==0))
                {    
                    BPath.Clear();
                    foreach(string x in Path)
                        this.BPath.Add(x);
                }
            }
            foreach(Vertex p in this.conn[sin].conn)
            {
                if(!IsVisited(Path,this.GetIndex(p.name)))
                {
                    this.SearchPath(Path,this.GetIndex(p.name),din);
                }
            }
            Path.Remove(this.conn[sin].name);
        }      
        private bool IsVisited(List<string> Path,int index)
        {
            if(index>=0)
            {
                foreach(string p in Path)
                {
                    if(p==this.conn[index].name)return true;
                }
            }
            return false;
        }
    }
}