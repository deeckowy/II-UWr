using System;
using System.Collections.Generic;

namespace Zadanie4
{
    class Program
    {
        static public void Main(string[] args)
        {
            PrimeList xd=new PrimeList();
            xd.element(32);
            for(int i=0;i<32;i++)
            {
                Console.WriteLine(xd.element(i));
                Console.WriteLine(xd.size());
            }
        }
    }
}