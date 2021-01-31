using System;
using System.Collections.Generic;

namespace Zadanie4
{
    class LazyList
    {
        protected List<int> ll=new List<int>();
        Random x=new Random();
        virtual public int element(int wej)
        {
            if(wej>this.ll.Capacity)
            {
                for(int i=this.ll.Capacity;i<wej;i++)
                {
                    this.ll.Add(x.Next());
                }
                return 0;
            }
            else return this.ll[wej];   
        }
        public int size()
        {
            return this.ll.Capacity;
        }
    }
}