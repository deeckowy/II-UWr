package Vehicles;

public class Car extends Vehicle
{
    private static final long serialVersionUID = 1L;
    public Car()
    {
        this.name="";
        this.hp=0.0;
        this.yop=1900;
    }
    public Car(String x,Integer yo,Double hpp)
    {
        this.name=x;
        this.yop=yo;
        this.hp=hpp;
    }
}