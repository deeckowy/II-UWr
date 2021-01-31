using System;
using Graph;
using System.Collections.Generic;

namespace z1
{
    class Program
    {
        static void Main()
        {

            Console.WriteLine();
            Console.WriteLine("///////   Matrix Representation:\n");
            Graphh mx=new Matrix(20,40);
            mx.Print();
            Console.WriteLine();
            Console.WriteLine("Quickest Path from last vertex to first one is: \n");
            foreach(string p in mx.QuickPath(19,0))
                Console.WriteLine(p+"\n|\nv\n");
        
            Console.WriteLine();
            Console.WriteLine("///////   List Representation:\n");
            Graphh lx=new ListR(20,40);
            lx.Print();
            Console.WriteLine();
            Console.WriteLine("Quickest Path from last vertex to first one is: \n");
            foreach(string p in lx.QuickPath(19,0))
                Console.WriteLine(p+"\n|\nv\n");

        }
    }
}