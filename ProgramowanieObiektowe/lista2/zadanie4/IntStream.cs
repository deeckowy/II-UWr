using System;

namespace Zadanie4
{
    class IntStream
    {
        public int liczba;
        virtual public bool eos(int x)
        {
            if(x==int.MaxValue)return false;
            else return true;
        }
        virtual public int next()
        {
            if(eos(this.liczba))
            {
                this.liczba++;
                return liczba-1;
            }
            else
            {
                throw new Exception("End of Stream Reached");
            }
        }
        virtual public void reset()
        {
            this.liczba=0;
        }
    }
}