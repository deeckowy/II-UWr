using System;
using Prime;

namespace z2
{
    class Program
    {
        static void Main()
        {
            PrimeCollection pc=new PrimeCollection();
            foreach(int p in pc)
                Console.WriteLine(p);
        }
    }
}