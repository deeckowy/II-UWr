using System;
using dict;

namespace z2
{
    class Program
    {
        static void Main()
        {      
            Dictionary<string,int> sample=new Dictionary<string,int>();
            sample.Add("jedynka",1);
            Console.WriteLine(sample.Find("jedynka"));
            sample.Add("XD",213);
            Console.WriteLine(sample.Find("XD"));
            sample.Remove("XD");
            sample.Add("PO",3211111);
            Console.WriteLine(sample.Find("PO"));
        }
    }
}