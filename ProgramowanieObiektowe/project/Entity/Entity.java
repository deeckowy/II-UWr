/**
 * Klasa Entity reprezentuje byt w grze taki jak gracz lub przeciwnik.
 * Implementuje metody:
 * hit ~ odpowiada za otrzymanie obrazeń,
 *  przy odpowiedniej przewadze obiekt może uniknąć obrażeń, 
 *  co jest reprezentowane jako otrzymanie 0 punktów obrażeń 
 * draw ~ rysuje graficzny wygląd obiektu w oknie
 * move ~ przemieszcza obiekt po planszy, 
 *  poniewaz plansza sklada sie z pol, 
 *  przesuwanie graczy i przeciwnków wygląda tak samo 
 */
package Entity;

import java.util.Random;

import org.jsfml.graphics.RenderWindow;
import org.jsfml.graphics.Sprite;
import org.jsfml.system.Vector2f;
import Consts.Consts;

public abstract class Entity 
{
    protected static Random rng;
    static 
    {
        rng=new Random();
    }
    protected Sprite slook;
    protected Integer hp;
    protected Integer strength;
    protected Integer defence;
    protected Integer dexterity;
    protected Integer lvl;

    public Integer getlvl(){return this.lvl;}    
    public Integer hit(Integer amount)
    {
        Integer hitval=0;
        if(!(rng.nextInt()/this.dexterity<5))
            hitval=(amount-this.defence);
        if(hitval<0)
            hitval=0;
        this.hp-=hitval;
        return hitval;
    }    
    public void draw(RenderWindow g){g.draw(slook);}
    public void move(Vector2f pos)
    {
        slook.setPosition(new Vector2f(pos.x*Consts.tilesize*Consts.graphicscale+Consts.startx
        ,pos.y*Consts.tilesize*Consts.graphicscale+Consts.starty));
    }
}