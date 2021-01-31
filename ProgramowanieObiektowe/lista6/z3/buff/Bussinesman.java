package buff;

import java.util.Random;

public class Bussinesman implements Runnable
{
    buff<String> to;

    public Bussinesman(buff<String> x)
    {
        this.to=x;
    }

    public void run()
    {
        for(int i=0;i<12;i++)
        {
            try 
            {
                this.Produce();
            }
            catch (InterruptedException ex) 
            {
                System.out.println("Something bad happend! "+"\n");
            }
        }
    }

    private void Produce() throws InterruptedException
    {
        synchronized(to)
        {
            while(!to.IsSpace())
            {
                to.notifyAll();
                to.wait();
            }                    
            String s="";
            Random x=new Random();
            for(int i=0;i<10;i++)
            {
                int j=x.nextInt(25)+97;
                s+=(char)j;                
            }
            to.Add(s);
        }
    }

}