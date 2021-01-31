package SCollection;

public class Trojkat extends Figura
{
    private Double a;
    private Double h;

    public Trojkat(Double t,Double x)
    {
        this.a=t;
        this.h=x;
        this.name="Trojkat";
    }

    @Override
    public Double Pole()
    {
        return this.a*this.h*0.5;
    }

    public Double Obwod()
    {
        return this.a*3.0;
    }
}