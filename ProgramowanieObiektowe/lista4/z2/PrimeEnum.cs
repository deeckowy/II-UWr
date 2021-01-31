using System;
using System.Collections;

namespace Prime
{
    class PrimeEnum:IEnumerator
    {
        private PrimeCollection pc;
        public PrimeEnum(PrimeCollection x)
        {
            this.pc=x;
        } 
        public bool MoveNext()
        {
            if(!this.pc.IsEnd())
            {

                return true;
            }
            else return false; 
        }
        object IEnumerator.Current
        {
            get{return Current;}
        }
        public int Current
        {
            get{return this.pc.GetNextP();}
        }
        public void Reset()
        {
            this.pc=new PrimeCollection();
        }
    }
}