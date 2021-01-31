/**
 * Klasa Gui reprezntuje interfejs, wyświetlany podczas rozgrywki, 
 * pokazuje aktualny stan zdrowia i doświadczenia gracza oraz 
 * obsługuje listę zdarzeń wypisując ostatnie 10 wiadomości wysłanych przez obiekty.  
 * Metoda draw rysuje interfejs w oknie podanych jako argument.
 * Metoda addmsg przyjmuje wiadomości od innych klas jako obiekt klas String i dodaje go do kolejki.
 *  W razie przepełnienia usuwa najstarsze wiadomości. 
 */
package Gui;

import Entity.Hero;
import java.util.*;
import java.io.IOException;
import java.nio.file.*;

import org.jsfml.graphics.Color;
import org.jsfml.graphics.Font;
import org.jsfml.graphics.RenderWindow;
import org.jsfml.graphics.Sprite;
import org.jsfml.graphics.Text;
import org.jsfml.graphics.Texture;

public class Gui 
{
    private static Texture hpbar;
    private static Texture hp;
    private static Texture exp;
    private static Sprite hpbarr;
    private static Sprite hpp;
    private static Sprite expp;
    private static float scale=(float)3.0;
    private static Font gfont;
    static 
    {
        hpbar = new Texture();
        hp=new Texture();
        exp=new Texture();
        try {
            hpbar.loadFromFile(Path.of("src/hpbar.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            hp.loadFromFile(Path.of("src/hp.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            exp.loadFromFile(Path.of("src/exp.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            gfont=new Font();
            gfont.loadFromFile(Path.of("src/Pixeled.ttf"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        hpbarr=new Sprite(hpbar);
        hpp=new Sprite(hp);
        expp=new Sprite(exp);
        hpbarr.setScale(scale,scale);
        hpp.setScale(scale,scale);
        expp.setScale(scale,scale);

    }
    private Hero player;
    private LinkedList<String> messages;
    private Text mess;

    public Gui(Hero p)
    {
        this.player=p;
        this.messages=new LinkedList<>();
        this.mess=new Text("",gfont,20);
        this.mess.setColor(Color.YELLOW);
    }

    public void addmsg(String msg)
    {
        if(this.messages.size()>10)
            this.messages.removeLast();
        this.messages.push(msg);
    }

    public void draw(RenderWindow g)
    {
        float t1=this.player.getfullhp()*306;
        Integer x=(int)t1;
        for(int i=0;i<x;i++)
        {
            hpp.setPosition(21+i,17);
            g.draw(hpp);
        }
        float t2=this.player.getexp()*189;
        Integer y=(int)t2;
        for(int i=0;i<y;i++)
        {
            expp.setPosition(i+93,63);
            g.draw(expp);
        }
        int p=0;
        for(String m:this.messages)
        {
            this.mess.setString(m);
            this.mess.setPosition(20,400+p*30);
            g.draw(this.mess);
            p++;
        }
        g.draw(hpbarr);
        Integer l=this.player.getlvl();
        this.mess.setString(l.toString());
        this.mess.setPosition(50,80);
        g.draw(this.mess);
    }
}