/**
 * Klasa reprezentująca przeciwnika, dzidziczy po klasie Entity.
 * Metoda attack odpowiada za atak na graczu i wypisanie komunikatu na 
 * liscie zdarzen w gui.
 * Metoda isdead zwraca wartość prawda/fałsz w zależności od zdrowia przeciwnika. 
 */
package Entity;

import java.io.IOException;
import java.nio.file.Path;

import org.jsfml.graphics.Sprite;
import org.jsfml.graphics.Texture;

import Gui.Gui;
import Consts.Consts;

public class Enemy extends Entity 
{
    private static Texture look;
    static 
    {
        look = new Texture();
        try {
            look.loadFromFile(Path.of("src/enemy.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }   
    private Hero player;
    private Gui ge;

    public Enemy(Hero p,Gui g)
    {
        this.player=p;
        this.lvl=rng.nextInt(this.player.getlvl()*2)+1;
        this.strength=rng.nextInt(this.lvl)*100/50;
        this.hp=1+rng.nextInt(this.lvl)*100/50;
        this.dexterity=1+rng.nextInt(this.lvl)*100/50;
        this.defence=rng.nextInt(this.lvl)*100/50;
        this.ge=g;
        this.slook=new Sprite(look);
        this.slook.setScale(Consts.graphicscale,Consts.graphicscale);
    }

    public void attack(){this.ge.addmsg("Enemy deals you " +this.player.hit(this.strength)+" dmg");}

    public boolean isdead(){return !(this.hp>0);}

}