
import Vehicles.*;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class z
{
    public static void main(String[] args) throws IOException,ClassNotFoundException
    {
        Vehicle te;
        File fii=new File(args[0]);
        if(!fii.exists()||fii.length()==0)
        {
            fii.createNewFile();
            te=new Car();
        }
        else
        {
            ObjectInputStream ni=new ObjectInputStream(new FileInputStream(fii));
            te=(Car) ni.readObject();
            ni.close();
        }
        VehicleListener vvl=new VehicleListener(te,fii);
        VehicleFrame fr=new VehicleFrame(new VehiclePanel(vvl, te));
    }
}