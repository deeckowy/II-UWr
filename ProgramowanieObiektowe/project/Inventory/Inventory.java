/**
 * Klasa odpowiadająca za ekwipunek gracza przechowuje maksymalnie 21 obiektów klasy Item. 
 * Metoda lookatitems przejmuje sterowanie od mainloop, 
 *  rysuje ekwipunek i pozwala graczowi założyć lub usunąć zebrane wcześniej przedmioty.
 * add przyjmuje podniesiony przedmiot i dodaje go do ekwipunku.
 * Metody getit*** zwracają statystki aktualnie noszonych przez gracza przedmiotów
 * Metoda delit usuwa przedmiot z ekwipunku. 
 * Metoda equip dodaje do aktualnie noszonych przez gracza przedmiotów, przedmiot wybrany z ekwipunku  
 */
package Inventory;

import java.util.*;

import org.jsfml.graphics.RenderWindow;
import org.jsfml.graphics.Sprite;
import org.jsfml.graphics.Texture;
import org.jsfml.system.Vector2f;
import org.jsfml.window.Keyboard.Key;
import org.jsfml.window.event.Event;
import org.jsfml.window.event.KeyEvent;

import java.io.IOException;
import java.nio.file.Path;

import Entity.Hero;
import Item.*;

public class Inventory 
{
    private static final Integer limit=21;
    private static Texture invframe;
    private static Sprite invf;
    private static Integer pos=0;
    static 
    {
        invframe = new Texture();
        try {
            invframe.loadFromFile(Path.of("src/inv2.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        invf=new Sprite(invframe);
    }
    private ArrayList<Item> inv;
    private ArrayList<Item> eqitems;
    private Hero player;
    public Inventory(Hero p)
    {
        this.player=p;
        this.inv=new ArrayList<>();
        this.eqitems=new ArrayList<>();
        invf.setPosition(new Vector2f(400,140));
        this.inv.add(new Item(997));
    }    
    public void lookatitems(RenderWindow g)
    {
        int b=0;
        while(g.isOpen())
        {
            for(Event ev:g.pollEvents())
            {
                switch (ev.type) 
                {
                    case CLOSED:
                        g.close();
                        break;
                
                    case KEY_PRESSED:
                        KeyEvent k=ev.asKeyEvent();
                        if(k.key==Key.ESCAPE)
                            b=1;
                        else if(!this.inv.isEmpty())
                        {
                            if(k.key==Key.DOWN&&pos<this.inv.size()-1)
                                pos++;
                            else if(k.key==Key.UP&&pos>0)
                                pos--;
                            else if(k.key==Key.D)
                            {delit();pos=0;}
                            else if(k.key==Key.RETURN&&this.player.getlvl()>=this.inv.get(pos).getlvn())
                                equip();
                        }
                        break;
                    default:
                        break;
                }
            }
            g.clear();
            g.draw(invf);
            int x=0;
            for(Item i:this.eqitems)
            {
                i.draw(x,g);
                x++;
            }
            for(x=-1;x<2;x++)
            {
                if(pos+x<this.inv.size()&&pos+x>=0)
                    this.inv.get(pos+x).draw(x+4,g);
            }
            g.display();
            if(b==1)
                break;
        }
    }    
    public void add(Item i)
    {if(this.inv.size()!=limit)
            this.inv.add(i);}

    
            public boolean isfreespace(){return !(this.inv.size()==limit);}    
            public Integer getithp()
            {
        Integer score=0;
        for(Item i:this.eqitems)
        score+=i.gethp();
        return score;
    }    
    public Integer getitstr()
    {
        Integer score=0;
        for(Item i:this.eqitems)
        score+=i.getstr();
        return score;
    }    
    public Integer getitdex()
    {
        Integer score=0;
        for(Item i:this.eqitems)
        score+=i.getdex();
        return score;
    }    
    public Integer getitdef()
    {
        Integer score=0;
        for(Item i:this.eqitems)
        score+=i.getdef();
        return score;        
    }
    private void delit(){this.inv.remove(this.inv.get(pos));}
    private void equip()
    {
        Integer type=this.inv.get(pos).type();
        boolean x=true;
        int p=0;
        for(Item i:this.eqitems)
        {
            if(i.type()==type)
            {
                this.eqitems.set(p,this.inv.get(pos));
                this.inv.set(pos,i);
                x=false;
            }
            p++;
        }
        if(x)
        {
            this.eqitems.add(this.inv.get(pos));
            this.delit();
        }
    }    
}