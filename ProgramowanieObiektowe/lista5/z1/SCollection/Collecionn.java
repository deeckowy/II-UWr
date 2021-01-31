package SCollection;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Collecionn<T extends Comparable<T>> 
{
    List<T> main_array;
    
    public Collecionn()
    {
        this.main_array=new ArrayList<T>();
    }
    public void Add(T elem)
        {this.main_array.add(elem);Collections.sort(this.main_array);}
    public void Remove(T elem)
        {this.main_array.remove(elem);}
    public T Get()
    { 
        T temp; 
        temp=this.main_array.get(0);
        this.Remove(temp); 
        return temp;
    }
    public void PrintCol()
    {
        for(T i :this.main_array)
            System.out.println(i);
    }
}