package Vehicles;

import java.io.Serializable;

public class Vehicle implements Serializable
{
    private static final long serialVersionUID = 1L;
    protected String name;
    protected Integer yop;
    protected Double hp;

    public String getName(){return this.name;}
    public Integer getYOP(){return this.yop;}
    public Double getHP(){return this.hp;}
    public void setName(String nam){this.name=nam;}
    public void setYOP(Integer yo){this.yop=yo;}
    public void setHP(Double HP){this.hp=HP;}

    public String toString()
    {
        return "Name : "+this.name +"\nYear of production : "+this.yop.toString()+"\nHorse Power : "+this.hp.toString(); 
    }

}