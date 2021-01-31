package Vehicles;

public class Plane extends Vehicle 
{
    private static final long serialVersionUID = 1L;
    public Plane() 
    {
        this.name="";
        this.hp=0.0;
        this.yop=1900;
    };
    public Plane(String x,Integer yo,Double hpp)
    {
        this.name=x;
        this.yop=yo;
        this.hp=hpp;
    }
}