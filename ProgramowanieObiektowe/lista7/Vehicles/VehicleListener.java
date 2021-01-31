package Vehicles;

import java.awt.event.*;
import java.io.File;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;

public class VehicleListener implements ActionListener 
{
    Vehicle x;
    VehiclePanel myp;
    File ffff;

    public void actionPerformed(ActionEvent e) 
    {
        Vehicle te = new Car(this.myp.getName(), Integer.parseInt(this.myp.GetYOP()),
        Double.parseDouble(this.myp.GetHP()));
        te.setName(this.myp.GetName());
        try(ObjectOutputStream ou = new ObjectOutputStream(new FileOutputStream(this.ffff)))
        {
            ou.writeObject(te);
            ou.close();
        }
        catch(Exception et)
        {
            System.out.println("ERR!\n");
        }

    }
    
    public VehicleListener(Vehicle s,File fx)
    {
        this.x=s;
        this.ffff=fx;
    }
    public void SetPanel(VehiclePanel ix)
    {
        this.myp=ix;
    }
}