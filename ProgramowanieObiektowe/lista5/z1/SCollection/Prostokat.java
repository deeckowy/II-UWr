package SCollection;

public class Prostokat extends Figura
{
    private Double a;
    private Double b;

    public Prostokat(Double x,Double y)
    {
        this.a=x;
        this.b=y;
        this.name="Prostokat";
    }

    @Override
    public Double Pole()
    {
        return this.a*this.b;
    }

    public Double Obwod()
    {
        return this.a*2.0+this.b*2.0;
    }

}