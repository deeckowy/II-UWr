package buff;

import java.util.ArrayList;
import java.util.List;

public class buff <T>
{
    private List<T> arr;
    private int size;
    private int count;

    public buff(int sizzz)
    {
        this.size=sizzz;
        this.arr=new ArrayList<T>();
        this.count=0;
    }

    public synchronized Boolean IsSpace(){return this.size!=this.count;}

    public synchronized void Add(T val)
    {
        System.out.println("Adding elememnt to buffer :"+val);
        this.arr.add(val);
        this.count++;
    }

    public synchronized Boolean IsEmpty(){return this.count==0;}

    public synchronized T GetVal()
    {
        this.count--;
        T temp=this.arr.get(this.count);
        this.arr.remove(this.count);
        System.out.println("Getting element from buffer :"+temp);
        return temp;
    }
}