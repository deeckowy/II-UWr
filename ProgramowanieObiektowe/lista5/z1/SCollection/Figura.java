package SCollection;

public class Figura implements Comparable<Figura>
{
    String name;
    public Double Pole()
    {
        return 0.0;
    }
    public String nazwa()
    {
        return this.name;
    } 
    
    @Override
    public int compareTo(final Figura AnotherFig) 
    {
        return this.Pole().compareTo(AnotherFig.Pole());
    }
}