package Vehicles;

import java.awt.Dimension;
import javax.swing.JFrame;

public class VehicleFrame extends JFrame
{
    private static final long serialVersionUID = 1L;

    public VehicleFrame(VehiclePanel vp)
    {
        this.add(vp);
        this.setPreferredSize(new Dimension(600,400));    
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.pack();
        this.setVisible(true);
    }
}