package wyrazenie;
import java.util.Hashtable;

enum Typ{cons,operation,variable}

public class Wyrazenie
{
    private Wyrazenie left;
    private Wyrazenie right;
    private Object wart;
    private Typ type;
    private Hashtable <String,Integer> zmienne;

    public Wyrazenie(Integer x)//konstruktor zwraca nam jedna liczbe
    {
        this.type=Typ.cons;
        this.left=null;
        this.right=null;
        this.zmienne=new Hashtable<String,Integer>();
        this.wart=x;
    }
    private Wyrazenie(String op)
    {
        if(op=="+"||op=="-"||op=="*"||op=="/")
        {
            this.wart=op;
            this.left=null;
            this.right=null;
            this.type=Typ.operation;
        }
        else 
        {
            this.wart=op;
            this.left=null;
            this.right=null;
            this.type=Typ.variable;
        }
    }
    public Wyrazenie OP(String op, Object x)
    {
        if(x instanceof Integer)
        {
            Wyrazenie nTop=new Wyrazenie(op);
            Wyrazenie righ=new Wyrazenie((Integer)x);
            nTop.left=this;
            righ.zmienne=this.zmienne;
            nTop.right=righ;
            nTop.zmienne=this.zmienne;
            return nTop;
        }
        else if(x instanceof Wyrazenie)
        {
            Wyrazenie s=(Wyrazenie)x;
            Wyrazenie nTop=new Wyrazenie(op);
            nTop.left=this;
            nTop.right=s;
            s.zmienne=this.zmienne;
            this.zmienne.putAll(s.zmienne);
            nTop.zmienne=this.zmienne;
            return nTop;            
        }
        else if(x instanceof String&&this.zmienne.containsKey((String)x))
        {
            Wyrazenie s=new Wyrazenie((String)x);
            Wyrazenie nTop=new Wyrazenie(op);
            nTop.left=this;
            s.zmienne=this.zmienne;
            nTop.right=s;
            nTop.zmienne=this.zmienne;
            return nTop;
        }
        return this;
    }
    public void NEWVARIABLE(String x,Integer val)
    {
        this.zmienne.put(x,val);
    }
    public Integer Eval()
    {
        if(this.type==Typ.operation)
        {
            String ope=(String)this.wart;
            switch (ope)
            {
                case "+":
                {
                    return this.left.Eval()+this.right.Eval();
                }
                case "-":
                {
                    return this.left.Eval()-this.right.Eval();
                }
                case "*":
                {
                    return this.left.Eval()*this.right.Eval();
                }
                case "/":
                {
                    return this.left.Eval()/this.right.Eval();
                }
            }
        }
        else if(this.type==Typ.variable)
        {
            return this.zmienne.get(this.wart);
        }
        return (Integer)this.wart;
    }
    @Override
    public String toString()
    {
        if(this.type==Typ.operation)
        {
            return "("+this.left.toString()+this.wart.toString()+this.right.toString()+")";
        }
        return this.wart.toString();
    }
    public Hashtable<String,Integer> GetHashVal()
    {
        return this.zmienne;
    }
}