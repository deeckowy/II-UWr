package Vehicles;

import javax.swing.*;
import java.awt.GridLayout;

public class VehiclePanel extends JPanel
{
    private static final long serialVersionUID = 1L;

    private JTextField n;
    private JTextField y;
    private JTextField h;
    private JLabel nn;
    private JLabel yy;
    private JLabel hh;
    private JButton butt;
    private VehicleListener vl;
    private Vehicle veh;


    public VehiclePanel(VehicleListener v,Vehicle o)
    {
        this.vl=v;
        this.veh=o;
        this.vl.SetPanel(this);
        this.SetComponents();
    }

    private void SetComponents()
    {
        this.setLayout(new GridLayout(4,2));
        this.n=new JTextField(this.veh.getName());
        this.y=new JTextField(this.veh.getYOP().toString());
        this.h=new JTextField(this.veh.getHP().toString());
        this.nn=new JLabel("NAME");
        this.yy=new JLabel("YEAR OF PRODUCTION ");
        this.hh=new JLabel("HORSE POWER");
        this.butt=new JButton("SAVE");
        this.butt.addActionListener(this.vl);
        

        this.add(this.nn);
        this.add(this.n);
        this.add(this.yy);
        this.add(this.y);
        this.add(this.hh);
        this.add(this.h);
        this.add(this.butt);
    }

    public String GetName(){return this.n.getText();}

    public String GetYOP(){return this.y.getText();}

    public String GetHP(){return this.h.getText();}

}