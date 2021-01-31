package mergesort;

import java.util.Vector;

public class Merge implements Runnable
{
    private Vector<Integer>marr;
    private Vector<Integer>rarr;
    private Vector<Integer>larr;


    public Merge(Vector<Integer> x)
    {
        this.marr=x;
        this.rarr=new Vector<Integer>();
        this.larr=new Vector<Integer>();
    }

    public synchronized void run()
    {
        synchronized(this.marr)
        {
            if(this.marr.size()>1)
            {
                for(int i=0;i<this.marr.size();i++)
                {
                    if(i<this.marr.size()/2)
                        this.larr.add(this.marr.get(i));
                    else 
                        this.rarr.add(this.marr.get(i));
                }
                Thread left=new Thread(new Merge(this.larr));
                Thread right=new Thread(new Merge(this.rarr));
                try 
                {
                    left.start();
                    right.start();
                    left.join();
                    right.join();
            
                } 
                catch (Exception e) 
                {
                    System.out.println("Something bad happend\n");
                }
                this.marr.clear();
                while(!this.rarr.isEmpty()&&!this.larr.isEmpty())
                {
                    if(this.rarr.get(0)<this.larr.get(0))
                    {
                        this.marr.add(this.rarr.get(0));
                        this.rarr.remove(0);
                    }
                    else
                    {
                        this.marr.add(this.larr.get(0));
                        this.larr.remove(0);
                    }
                }
                this.marr.addAll(this.rarr);
                this.marr.addAll(this.larr);
            }
        }
    }
}