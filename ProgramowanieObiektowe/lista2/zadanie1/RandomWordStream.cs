using System;

namespace Zadanie1
{
    class RandomWordStream
    {
        RandomStream rs = new RandomStream();
        PrimeStream ps = new PrimeStream();

        public string next()
        {
            string xd="";
            int c;
            int word_size=ps.next();
            for(int i=0;i<word_size;i++)
            {
                c=(rs.next()%25+65);
                xd+=Convert.ToChar(c);
            }
            return xd;
        } 
    }
}