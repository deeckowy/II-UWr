/**
 * Klasa gracza, dziedziczy po Entity pola ze statystykami oraz metody draw i move.
 * Hero nadpisuje metode hit ponieważ gracz oprócz własnych statystyk 
 * posiada również dodatkowe punkty za przedmioty które nosi.
 * Metoda addexp odpowiada za przyjmowanie punktow doswiadczenia i podnoszenie poziomu gracza.
 * upgradehero to metoda, która przejmuje sterowanie od klasy mainloop i rysuje menu gracza 
 *   w którym użytkownik może rozdzielić punkty statystyk 
 *   pryznawane za zdobycie kolejnego poziomu doświadczenia.   
 */
package Entity;

import org.jsfml.graphics.Color;
import org.jsfml.graphics.Font;
import org.jsfml.graphics.RenderWindow;
import org.jsfml.graphics.Sprite;
import org.jsfml.graphics.Text;
import org.jsfml.graphics.Texture;
import org.jsfml.system.Vector2f;
import org.jsfml.window.Keyboard.Key;
import org.jsfml.window.event.Event;
import org.jsfml.window.event.KeyEvent;

import java.io.IOException;
import java.nio.file.*;

import Consts.Consts;
import Gui.Gui;
import Inventory.Inventory;

public class Hero extends Entity
{
    private static Texture look;
    private static Texture hstats;
    private static Font statsfont;
    private static Sprite stsmenu;
    static 
    {
        look = new Texture();
        hstats=new Texture();
        statsfont=new Font();
        try {
            look.loadFromFile(Path.of("src/hero.png"));
            hstats.loadFromFile(Path.of("src/herostats.png"));
            statsfont.loadFromFile(Path.of("src/Pixeled.ttf"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        stsmenu=new Sprite(hstats);
        stsmenu.setPosition(760,240);
    }
    
    private Integer exp;
    private Integer hpmax;
    private Integer expmax;
    private Inventory hinv;
    private Gui pg;
    private Integer points;
    private Text stat;

    public Hero()
    {
        this.hp=100;
        this.lvl=1;
        this.expmax=this.lvl*10;
        this.exp=0;
        this.hpmax=100;
        this.strength=3;
        this.dexterity=3;
        this.defence=3;
        this.points=3;
        this.slook=new Sprite(look);
        this.slook.setScale(Consts.graphicscale,Consts.graphicscale);
        this.move(new Vector2f(0,0));
        this.stat=new Text();
        this.stat.setFont(statsfont);
        this.stat.setCharacterSize(15);
    }    
    public void setgui(Gui g){this.pg=g;}
    public void setinv(Inventory i){this.hinv=i;}    
    public Integer getsrt(){return this.strength+this.hinv.getitstr();}    
    public float getfullhp(){return (float)this.hp/(float)(this.hpmax+this.hinv.getithp());}    
    public float getexp(){return (float)this.exp/(float)this.expmax;}    
    @Override
    public Integer hit(Integer amount)
    {
        Integer hitval=0;
        if(!(rng.nextInt()/(this.dexterity+this.hinv.getitdex())<5))
            hitval=(amount-(this.defence+this.hinv.getitdef()));
        if(hitval<0)
            hitval=0;
        this.hp-=hitval;
        return hitval;
    }    
    public void addexp(Integer amount)
    {
        this.exp+=amount;
        if(this.exp>this.expmax)
        {
            this.lvl++;
            this.points+=3+this.lvl/10;
            this.exp-=this.expmax;
            this.expmax=this.lvl*10;
            this.pg.addmsg("Level up!");
        }
    }    
    public void upgradehero(RenderWindow g)
    {
        Integer hp=this.hinv.getithp();
        Integer str=this.hinv.getitstr();
        Integer dex=this.hinv.getitdex();
        Integer def=this.hinv.getitdef();
        Text hpp=new Text();
        hpp.setFont(statsfont);
        hpp.setCharacterSize(15);
        Text strr=new Text();
        strr.setFont(statsfont);
        strr.setCharacterSize(15);
        Text dexx=new Text();
        dexx.setFont(statsfont);
        dexx.setCharacterSize(15);
        Text deff=new Text();
        deff.setFont(statsfont);
        deff.setCharacterSize(15);
        strr.setPosition(990,215+245);
        deff.setPosition(990,298+245);
        dexx.setPosition(990,382+245);
        hpp.setPosition(990,465+245);
        this.stat.setPosition(260+760,131+270);

        
        int b=0;
        int pos=0;
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
                        else if(k.key==Key.UP&&pos>0)
                            pos--;
                        else if(k.key==Key.DOWN&&pos<3)
                            pos++;
                        else if(k.key==Key.RETURN&&this.points!=0)
                        {
                            switch (pos) 
                            {
                                case 0:
                                    this.strength++;
                                    break;
                                case 1:
                                    this.defence++;
                                    break;
                                case 2:
                                    this.dexterity++;
                                    break;
                                case 3:
                                    this.hpmax++;
                                    break;                            
                                default:
                                    break;
                            }
                            this.points--;
                        }
                        break;
                    default:
                        break;
                }
            }
            g.clear();
            g.draw(stsmenu);
            this.stat.setString(this.points.toString());
            hpp.setColor(Color.WHITE);
            strr.setColor(Color.WHITE);
            deff.setColor(Color.WHITE);
            dexx.setColor(Color.WHITE);
            switch (pos)
            {
                case 0:
                    strr.setColor(Color.YELLOW);
                    break;
                case 1:
                    deff.setColor(Color.YELLOW);
                    break;
                case 2:
                    dexx.setColor(Color.YELLOW);
                    break;
                case 3:
                    hpp.setColor(Color.YELLOW);
                    break;

                default:
                    break;
            }
            hpp.setString(this.hp.toString()+" + "+hp.toString());
            strr.setString(this.strength.toString()+" + "+str.toString());
            deff.setString(this.defence.toString()+" + "+def.toString());
            dexx.setString(this.dexterity.toString()+" + "+dex.toString());
            g.draw(this.stat);
            g.draw(hpp);
            g.draw(strr);
            g.draw(deff);
            g.draw(dexx);

            g.display();
            if(b==1)
                break;
        }
    }
}