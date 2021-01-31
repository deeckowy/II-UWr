using System;

namespace Zadanie1
{
    class PrimeStream:IntStream
    {
        override public bool eos(int x)
        {
            for(int i=2;i*i<=x;i++)
            {
                if(x%i==0)return false;
            }
            return true;
        }
        override public int next()
        {
            while(!eos(this.liczba))
            {
                this.liczba++;
            }
            if(this.liczba<0)
            {
                throw new Exception("End of Stream Reached.");
            }            
            return this.liczba++;
        }
        public PrimeStream()
        {
            this.liczba=2;
        }
        override public void reset()
        {
            this.liczba=2;
        }
    }
}