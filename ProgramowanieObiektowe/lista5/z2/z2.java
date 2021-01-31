import wyrazenie.Wyrazenie;


public class z2
{
    public static void main(String[] args) 
    {
        Wyrazenie x=new Wyrazenie(5);
        x=x.OP("*",5);
        System.out.println(x.Eval());
        x=x.OP("/",2);
        System.out.println(x.Eval());
        System.out.println(x.toString());
        x.NEWVARIABLE("xd", 120);
        System.out.println(x.GetHashVal());
        x=x.OP("-","xd");
        System.out.println(x.toString());
        System.out. println(x.Eval());
    }   
}