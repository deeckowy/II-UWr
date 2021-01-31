using System;
using System.Collections.Generic;


namespace Graph
{
    interface Graphh
    {
        void Add(string name);//adding vertex
        void Add();//adding random vertex
        void Print();//print graph
        void AddConn(string from,string to);//adding connection between vertexs 
        void AddConn(int from,int to);//adding connection by index (only for pros !)
        void AddConn();//random connection
        void RemVer(string name);//removing vertex
        void RemVer(int z);//same as above (pro version !)
        List<string> QuickPath(string start,string destination);
        List<string> QuickPath(int start,int destination);
        
    }
}