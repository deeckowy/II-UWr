using System;
using System.Collections.Generic;

namespace Graph
{
    class Matrix:Graphh
    {
        int[,] connections_matrix;
        string[] vertex_names;
        int size;
        Random x=new Random();
        List<string> BPath;
        public Matrix()//normal constructor
        {
            this.connections_matrix=new int[5,5];
            this.vertex_names=new string[5];
            this.size=5;
        }
        public Matrix(int vertex,int conn)
        {
            this.connections_matrix=new int[vertex,vertex];
            this.vertex_names=new string[vertex];
            this.size=vertex;
            for(int i=0;i<this.size;i++)
            {
                this.Add();
            }
            for(int i=0;i<conn;i++)
            {
                this.AddConn();
            }

        }
        public void Add(string name)//adding vertex
        {
            this.Resize();
            for(int i=0;i<this.size;i++)
            {
                if(this.vertex_names[i]==null)
                    {this.vertex_names[i]=name;break;}
            }
        }
        public void Add()//random vertex 
        {
            string name="";
            for(int i=0;i<x.Next(1,20);i++)
            {
                char s=(char)x.Next(65,90);
                name+=s;
            }
            this.Add(name);
        }
        public void AddConn(string from,string to)//adding connection between two vertexs
        {
            int i=this.GetIndex(from);
            int k=this.GetIndex(to);
            if(!(i==-1||k==-1))
            {
                this.connections_matrix[i,k]=1;
                this.connections_matrix[k,i]=1;
            }
        }
        public void AddConn(int from,int to)//adding connections by index(only for pros !) 
        {
            if(from<this.size&&to<this.size)
            {
                this.connections_matrix[from,to]=1;
                this.connections_matrix[to,from]=1;
            }
        }
        public void AddConn()
        {
            int i=x.Next(0,this.size);
            int k=x.Next(0,this.size);
            while(this.vertex_names[i]==null&&this.vertex_names[k]==null)
            {
                k=x.Next(0,this.size);
                i=x.Next(0,this.size);
            }
            this.AddConn(i,k);
        }
        public void RemVer(string name)//rem vertex 
        {
            int k=this.GetIndex(name);
            this.vertex_names[k]=null;
            for(int i=0;i<this.size;i++)
            {
                this.connections_matrix[i,k]=0;
                this.connections_matrix[k,i]=0;
            }
        }
        public void RemVer(int z)//same as above (pro version !)
        {
            this.vertex_names[z]=null;
            for(int i=0;i<this.size;i++)
            {
                this.connections_matrix[i,z]=0;
                this.connections_matrix[z,i]=0;
            }
        }
        public void Print()//show graph
        {
            for(int i=0;i<this.size;i++)
            {
                if(this.vertex_names[i]!=null)
                {
                    Console.Write(this.vertex_names[i]+" -> ");
                    for(int k=0;k<this.size;k++)
                    {
                        if(this.connections_matrix[i,k]==1)
                            Console.Write(this.vertex_names[k]+" / ");
                    }
                    Console.Write("\n");
                }
            }
        }
        private bool isFree()//check for empty slots
        {
            for(int i=0;i<this.size;i++)
                if(this.vertex_names[i]==null)return true;
            return false;
        }
        private void Resize()//resizin if needed
        {            
            if(!this.isFree())
            {
                int[,] temp=new int[size*2,size*2];
                for(int i=0;i<this.size;i++)
                    for(int k=0;k<this.size;k++)
                        temp[i,k]=this.connections_matrix[i,k];

                this.connections_matrix=temp;

                string[] tt=new string[this.size*2];
                for(int i=0;i<this.size;i++)
                    tt[i]=this.vertex_names[i];

                this.vertex_names=tt;
                this.size*=2;                
            }
        }
        private int GetIndex(string name)//return index of vertex
        {
            for(int i=0;i<this.size;i++)
            {
                if(this.vertex_names[i]==name)
                    return i;
            }
            return -1;
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
        private void SearchPath(List<string> Path,int sin,int din)
        {
            Path.Add(this.vertex_names[sin]);
            if(sin==din)
            {
                if(Path.Count<this.BPath.Count||this.BPath.Count==0)
                {
                    BPath.Clear();
                    foreach(string x in Path)
                        this.BPath.Add(x);
                }
            }
            for(int i=0;i<this.size;i++)
            {
                if(this.connections_matrix[i,sin]==1&&!this.IsVisited(Path,i))
                this.SearchPath(Path,i,din);
            }
            Path.Remove(this.vertex_names[sin]);
        }
        private bool IsVisited(List<string> Path,int index)
        {
            if(index>=0)
            {
                foreach(string p in Path)
                {
                    if(p==this.vertex_names[index])return true;
                }
            }
            return false;
        }
    }
}