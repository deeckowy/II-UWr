package SCollection;

public class Kolo extends Figura
{
    private Double r;
    private Double Pi;

    public Kolo(Double t)
    {
        this.r=t;
        this.Pi=3.1415; 
        this.name="Kolo";
    }

    @Override
    public Double Pole()
    {
        return this.Pi*this.r*this.r;
    }

    public Double Obwod()
    {
        return this.Pi*2.0*this.r;
    }
}