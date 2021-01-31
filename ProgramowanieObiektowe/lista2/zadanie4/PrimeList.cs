using System;
using System.Collections.Generic;

namespace Zadanie4
{
    class PrimeList:LazyList
    {
        PrimeStream ps=new PrimeStream(); 
        override public int element(int wej)
        {
            if(wej>this.ll.Capacity)
            {
                for(int i=this.ll.Capacity;i<wej;i++)
                {
                    this.ll.Add(ps.next());
                }
                return 0;
            }
            else return this.ll[wej];
        }
    }
}