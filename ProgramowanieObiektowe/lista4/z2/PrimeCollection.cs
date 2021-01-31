using System.Collections;
using System;

namespace Prime
{
    public class PrimeCollection:IEnumerable
    {
        int curr;
        public int GetNextP()
        {
            for(int i=this.curr+1;i<Int32.MaxValue;i++)
            {
                if(this.IsPrime(i))
                {
                    int t=this.curr;
                    this.curr=i;
                    return t;
                }
            }
            this.curr=-1;
            return this.curr;
        }
        public PrimeCollection()
        {
            this.curr=2;
        }
        private bool IsPrime(int x)
        {
            for(int i=2;i*i<=x;i++)
            {
                if(x%i==0)return false;
            }
            return true;
        }
        public bool IsEnd(){if(this.curr<0)return true; else return false;}
        public IEnumerator GetEnumerator()
        {
            return new PrimeEnum(this);
        }
    }
}