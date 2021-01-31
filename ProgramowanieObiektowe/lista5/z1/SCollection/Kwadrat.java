package SCollection;

public class Kwadrat extends Figura
{
    private Double a;
    public Kwadrat(Double t)
    {
        this.a=t;
        this.name="Kwadrat";
    }

    @Override
    public Double Pole()
    {
        return this.a*this.a;    
    }

    public Double Obwod()
    {
        return this.a*4;
    }
}