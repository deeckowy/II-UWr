import buff.*;

public class z3
{
    public static void main(String[] args) 
    {
        buff<String> x=new buff<String>(12);
        Thread producer=new Thread(new Bussinesman(x));
        Thread customer=new Thread(new Customer(x));
        producer.start();
        customer.start();
    }
}