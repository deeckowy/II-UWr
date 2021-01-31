/**
 * Klasa Room odpowiada za poziomy po których porusza się gracz.
 * Metoda draw rysuje cały poziom w oknie 
 * isvalidmove sprawdza czy ruch gracza jest poprawny
 * genboard generuje plansze i dla każdego pola wybiera wartość od 0 do 2, gdzie
 *  0 - puste pole, po którym obiekty Entity nie mogą sie poruszać 
 *  1 - zwykłe pole, po którym wszytskie obiekty mogą sie poruszać 
 *  2 - pole z przedmiotem, na które wejść może tylko gracz
 * validemove - sprawdza czy ruch przeciwnika jest poprawny 
 * drawexits - pomocnicza metoda, która rysuje wyjścia z pomieszczenia
 */
package Room;
import Consts.Consts;
import Gui.Gui;
import Inventory.Inventory;
import Item.Item;

import java.io.IOException;
import java.nio.file.*;

import org.jsfml.graphics.RenderWindow;
import org.jsfml.graphics.Sprite;
import org.jsfml.graphics.Texture;
import org.jsfml.system.Vector2f;

import java.util.*;

public class Room 
{
    private static Texture tile;
    private static Texture chest;
    private static Sprite til;
    private static Sprite ches;
    static 
    {
        tile=new Texture();
        chest=new Texture();
        try {
            tile.loadFromFile(Path.of("src/tile.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            chest.loadFromFile(Path.of("src/chest.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        til=new Sprite();
        ches=new Sprite();
        til.setTexture(tile);
        til.scale(Consts.graphicscale,Consts.graphicscale);
        ches.setTexture(chest);
        ches.scale(Consts.graphicscale,Consts.graphicscale);        
    }
    private Inventory maininv;
    private Gui maingui;
    private Random rng;
    private LinkedList<Integer> board;

    public Room(Integer seed,Inventory inv,Gui g)
    {
        this.rng=new Random(seed);
        this.board=new LinkedList<>();
        this.genBoard();
        this.maininv=inv;
        this.maingui=g;
    }

    public void draw(RenderWindow g)
    {
        Integer t=0;
        for(Integer x:this.board)
        {
            Vector2f actpos=new Vector2f(t/Consts.len*Consts.tilesize*Consts.graphicscale+Consts.startx,
             t%Consts.len*Consts.tilesize*Consts.graphicscale+Consts.starty);
            switch (x) 
            {
                case 1:
                    til.setPosition(actpos);
                    g.draw(til);
                    break;
                case 2:
                    ches.setPosition(actpos);
                    g.draw(ches);
                    break;
                default:
                    break;
            }
            t++;
        }
        this.drawexits(g);
    }

    public boolean isvalidmove(float x,float y)
    {
        Integer pos=(int)(x*Consts.len+y);
        if(pos<Consts.size&&pos>=0)
        {
            if(this.board.get(pos)==0)
                return false;
            else if(this.board.get(pos)==2)
            {
                if(maininv.isfreespace())
                {
                    maininv.add(new Item(this.rng.nextInt()));
                    this.maingui.addmsg("You picked item!");
                    this.board.set(pos,1);
                }
                else 
                    this.maingui.addmsg("Inventory is full!");
                
                return true;
            }
            else 
                return true;
        }
        else return true;
    }

    private void genBoard()
    {
        for(int i=0;i<Consts.size;i++)
        {
            Integer x=this.rng.nextInt(90);
            if(x<80)
                this.board.add(1);
            else if(x<87)
                this.board.add(0);
            else
                this.board.add(2); 
        }
    }
    
    public boolean validemove(float x,float y)
    {
        if(x>=0.0&&x<=8.0&&y>=0.0&&y<=8.0)
        {
            Integer pos=(int)(x*Consts.len+y);
            if(pos<Consts.size&&pos>=0)
            {
                return this.board.get(pos)==1;
            }
            return false;
        }
        else return false;
    }

    private void drawexits(RenderWindow g)
    {
        til.setPosition(new Vector2f(36/Consts.len*Consts.tilesize*Consts.graphicscale+Consts.startx,
        -1%Consts.len*Consts.tilesize*Consts.graphicscale+Consts.starty));
        g.draw(til);
        til.setPosition(new Vector2f(36/Consts.len*Consts.tilesize*Consts.graphicscale+Consts.startx,
        9*Consts.tilesize*Consts.graphicscale+Consts.starty));
        g.draw(til);
        til.setPosition(new Vector2f(9*Consts.tilesize*Consts.graphicscale+Consts.startx,
        4%Consts.len*Consts.tilesize*Consts.graphicscale+Consts.starty));
        g.draw(til);
        til.setPosition(new Vector2f(-9/Consts.len*Consts.tilesize*Consts.graphicscale+Consts.startx,
        4*Consts.tilesize*Consts.graphicscale+Consts.starty));
        g.draw(til);
    }
}