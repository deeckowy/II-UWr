using System;

namespace Zadanie1
{
    class RandomStream:IntStream
    {
        Random x=new Random();
        override public int next()
        {
            return this.x.Next();
        }
    }
}