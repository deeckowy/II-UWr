import java.util.Vector;

import mergesort.Merge;

public class z5
{
    public static void main(String[] args) 
    {
        Vector<Integer> s= new Vector<>();
        s.add(12);
        s.add(1);
        s.add(32);
        s.add(32111);
        s.add(-12);
        Thread sam=new Thread(new Merge(s));
        try
        {
            sam.start();
        }
        catch(Exception ex)
        {
            System.out.println(ex);
        }
        System.out.println(s);
    }
}