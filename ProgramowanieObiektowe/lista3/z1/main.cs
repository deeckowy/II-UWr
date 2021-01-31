using System;
using List;

namespace z1
{
    class Program
    {
        public static void Main()
        {
            List<int> tesst=new List<int>();

            try
            {
                tesst.AddElem(1);
                Console.WriteLine(tesst.GetFirst());
                tesst.AddElem(2);
                Console.WriteLine(tesst.GetFirst());
                tesst.RemFirst();
                Console.WriteLine(tesst.GetFirst());
                Console.WriteLine(tesst.GetLast());
                tesst.RemLast();
                Console.WriteLine(tesst.IsEmpty());
                tesst.AddElem(3);
                Console.WriteLine(tesst.GetLast());
                tesst.AddElem(4);
                tesst.AddElem(5);
                Console.WriteLine(tesst.GetFirst()+"x"+tesst.GetLast());
                tesst.RemFirst();
                Console.WriteLine(tesst.GetFirst() + "x" +tesst.GetLast());
                tesst.AddElem(6);
                Console.WriteLine(tesst.GetLast());
                tesst.RemLast();
                Console.WriteLine(tesst.GetLast());
            }
            catch (System.Exception e)
            {
                Console.WriteLine(e);
            }
        }
    }
}