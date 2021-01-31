/**
 * MainLoop to trzon rozgrywki, obsługuje ruchy gracza, 
 * steruje przeciwnikami, zmienia poziomy oraz 
 * przekazuje sterowanie do innych klas takich jak: Inventory czy Hero. 
 * Podczas jednego obrotu pętli w metodzie play, odczytuje ruch gracza, 
 * analizuje i wykonuje ruch przeciwnikow oraz przekazuje okno do wszytskich klas, 
 * które mają swój graficzny obiekt, aby mogły go narysować a następnie wyświetla 
 * pełne okno rozgrywki dla użytkownika.
 * Pozostałe metody:
 *  moveenemies - porusza przeciwnikami 
 *  isok - sprawdza czy ruch gracza spowoduje przejscie do kolejnego pomieszczenia 
 *  distance - sprawdza czy gracz i przeciwnik są obok siebie 
 *  isenemy - zwraca indeks przeciwnika którego gracz atakuje 
 *  makeenemies - tworzy nowych przeciwnikow podczas przejscia do nowego pomieszczenia 
 *  nextemove - generuje ruch przeciwnikow 
 */
package MainLoop;

import Room.Room;

import java.util.ArrayList;
import java.util.Random;

import org.jsfml.graphics.RenderWindow;
import org.jsfml.window.Keyboard.Key;
import org.jsfml.window.event.Event;
import org.jsfml.window.event.KeyEvent;
import org.jsfml.system.Vector2f;

import Entity.Enemy;
import Entity.Hero;
import Gui.Gui;
import Inventory.Inventory;

public class MainLoop 
{
    private RenderWindow game;
    private Random rng;
    private Room actroom;
    private Hero player;
    private Vector2f ppos;
    private Gui maingui;
    private Inventory inv;
    private ArrayList<Enemy> enemies;
    private ArrayList<Vector2f> epos;

    public MainLoop()
    {
        this.enemies=new ArrayList<>();
        this.epos=new ArrayList<>();
        this.rng=new Random();
        this.player=new Hero();
        this.ppos=new Vector2f(0,0);
        this.maingui=new Gui(this.player);
        this.player.setgui(this.maingui);
        this.inv=new Inventory(this.player);
        this.player.setinv(this.inv);
        this.actroom=new Room(this.rng.nextInt(),this.inv,this.maingui);
        this.makeenemies();
    }   
    
    
    public void Play(RenderWindow g)
    {
        Integer s=0;
        this.game=g;
        while(this.game.isOpen())
        {

            for(Event ev:game.pollEvents())
            {
                switch (ev.type) 
                {
                    case CLOSED:
                        game.close();
                        break;
                
                    case KEY_PRESSED:
                        KeyEvent k=ev.asKeyEvent();
                        float x=this.ppos.x;
                        float y=this.ppos.y;
                        if(k.key==Key.UP)
                            y-=1;
                        else if(k.key==Key.DOWN)
                            y+=1;
                        else if(k.key==Key.LEFT)
                            x-=1;
                        else if(k.key==Key.RIGHT)
                            x+=1;
                        else if(k.key==Key.ESCAPE)
                            s=1;
                        else if(k.key==Key.E)
                            inv.lookatitems(game);
                        else if(k.key==Key.C)
                            this.player.upgradehero(game);
                        else if(k.key==Key.A)
                        {
                            Integer e=isenemy();
                            if(e!=-1)
                                this.maingui.addmsg("You deal "+this.enemies.get(e).hit(this.player.getsrt())+"dmg to enemy!");
                        }

                        if(this.actroom.isvalidmove(x,y))
                        {
                            x=isok(x,y);
                            y=isok(y,x);
                            this.ppos=new Vector2f(x,y);
                            player.move(this.ppos);
                            this.moveenemies();
                        }
                        int f=0;
                        for(Enemy e:this.enemies)
                        {
                            e.move(this.epos.get(f));
                            f++;
                        }
                            break;
                    default:
                        break;
                }
            }
            this.game.clear();
            this.actroom.draw(game);
            this.player.draw(game);
            this.maingui.draw(game);
            for(Enemy e:enemies)
                e.draw(game);
            this.game.display();
            if(s==1)
                break;
        }
    }

    private void moveenemies()
    {
        int x=0;
        int dead=-1;
        for(Enemy e:this.enemies)
        {
            if(e.isdead())
            {
                this.player.addexp(e.getlvl());
                dead=x;
            }
            else
            {
                if(distance(ppos,this.epos.get(x)))
                    e.attack();
                else 
                    this.epos.set(x,nextemove(this.epos.get(x)));
            }
            x++;
        }
        if(dead!=-1)
        {
            this.enemies.remove(this.enemies.get(dead));
            this.epos.remove(dead);
        }
    }

    
    private float isok(float x,float y)
    {
        float out=x;
        boolean neww=false;
        if(x>8.0&&y==4)
        {
            out=(float)0.0;
            neww=true;
        }
        else if(x<0.0&&y==4)
        {
            out=(float)8.0;
            neww=true;
        }
        else if(x<0.0)
            out=(float)0.0;
        else if(x>8.0)
            out=(float)8.0;
        if(neww)
        {
            this.actroom=new Room(this.rng.nextInt(),this.inv,this.maingui);
            this.makeenemies();
        }
        return out;
    }

    
    private boolean distance(Vector2f p1,Vector2f p2)
    {
        float x=p1.x-p2.x;
        x*=x;
        float y=p1.y-p2.y;
        y*=y;
        y+=x;
        return Math.sqrt((double)y)==1.0;
    }

    
    private Integer isenemy()
    {
        Integer o=-1;
        Integer idx=0;
        for(Vector2f ep:this.epos)
        {
            if(this.distance(this.ppos,ep))
                o=idx;
            idx++;
        }
        return o;
    }

    private void makeenemies()
    {
        this.enemies.clear();
        this.epos.clear();
        Integer i=this.rng.nextInt(5);
        for(int x=0;x<i;x++)
        {
            this.enemies.add(new Enemy(this.player, this.maingui));
            this.epos.add(new Vector2f(this.rng.nextInt(9),this.rng.nextInt(9)));
            this.enemies.get(x).move(this.epos.get(x));
        }
    }

    
    private Vector2f nextemove(Vector2f actpos)
    {
        float x=actpos.x;
        float y=actpos.y;
        do 
        {
            x+=this.rng.nextInt(3)-1;
            y+=this.rng.nextInt(3)-1;    
        } while (!this.actroom.validemove(x,y));
        Vector2f o=new Vector2f(x,y);
        return o;    
    }
}