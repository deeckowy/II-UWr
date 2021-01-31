package buff;

public class Customer implements Runnable
{
    private buff<String> from;

    public Customer(buff<String> x)
    {
        this.from=x;
    }

    public void run()
    {
        for(int i=0;i<12;i++)
        {
            try 
            {
                this.Consume();
            } 
            catch (Exception e) 
            {
                System.out.println("Something bad happend! "+"\n");
            }
        }
    }

    private void Consume() throws InterruptedException
    {
        synchronized(from)
        {
            while(from.IsEmpty())
            {
                from.wait();
                from.notifyAll();
            }
            from.GetVal();
        }
    }

}