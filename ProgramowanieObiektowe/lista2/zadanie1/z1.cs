using System;

namespace Zadanie1
{
    class Program
    {
        static void Main(string[] args)
        {
            RandomWordStream rs=new RandomWordStream();            
            for(int i=0;i<10;i++)
                try
                {
                    Console.WriteLine(rs.next());                            
                }
                catch (Exception)
                {
                    Console.WriteLine("End of Stream Reached.");
                }
            
        }
    }     
}