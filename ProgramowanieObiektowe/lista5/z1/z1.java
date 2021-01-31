import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import SCollection.*;

public class z1
{
    public static void main(String[] args) 
    {
        Collecionn <Integer> smple=new Collecionn<>();
        smple.Add(21);
        for(int i=0;i<32;i++)
            smple.Add(i);
        smple.PrintCol();
        for(int i=0;i<12;i++)
            smple.Get();


        System.out.println();
        System.out.println("Collection after gettin 12 elements :");
        smple.PrintCol();

        List<Figura> figury= new ArrayList<Figura>();

        figury.add(new Kwadrat(4.0));
        figury.add(new Kolo(2.0));
        figury.add(new Prostokat(5.0, 6.0));
        figury.add(new Trojkat(1.0, 1.0));


        //pokazanie figur z listy
        for(Figura f:figury)
            System.out.println(f.nazwa() +"\n"+ f.Pole());

        //sortowanie figur
        System.out.println();
        Collections.sort(figury);
        System.out.println();
        //ponowny pokaz
        for(Figura f:figury)
            System.out.println(f.nazwa() +"\n"+ f.Pole());


    }
}