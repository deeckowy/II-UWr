/**
 * Klasa Item reprezentuje przedmiot w ekwipunku gracza. 
 * Posiada statystyki odpowiadająca tym u gracza 
 * oraz metodę draw, która rysuje graficzny wygląd przedmiotu 
 * wraz z statystykami.
 */
package Item;

import org.jsfml.graphics.Font;
import org.jsfml.graphics.RenderWindow;
import org.jsfml.graphics.Sprite;
import org.jsfml.graphics.Text;
import org.jsfml.graphics.Texture;
import org.jsfml.system.Vector2f;

import java.io.IOException;
import java.nio.file.Path;
import java.util.Random;

public class Item 
{
    private static Texture[] looks;
    private static Font ifont;
    private static Text stat;
    static
    {
        ifont=new Font();
        try {
            ifont.loadFromFile(Path.of("src/Pixeled.ttf"));
        } catch (IOException e1) {
            e1.printStackTrace();
        }
        stat=new Text();
        stat.setFont(ifont);
        stat.setCharacterSize(20);
        looks = new Texture[3];
        looks[0]=new Texture();
        looks[1]=new Texture();
        looks[2]=new Texture();
        try {
            looks[0].loadFromFile(Path.of("src/weapon.png"));
            looks[1].loadFromFile(Path.of("src/boots0.png"));
            looks[2].loadFromFile(Path.of("src/armor0.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    private Integer hp;
    private Integer dex;
    private Integer str;
    private Integer def;
    private Integer lvlneeded;
    private Sprite dlook;
    private Random rng;
    private Integer type;

    public Integer gethp(){return this.hp;}
    public Integer getdex(){return this.dex;}
    public Integer getstr(){return this.str;}
    public Integer getdef(){return this.def;}
    public Integer getlvn(){return this.lvlneeded;}
    public Integer type(){return this.type;}

    public Item(Integer seed)
    {
        this.rng=new Random(seed);
        this.lvlneeded=this.rng.nextInt(100)+1;
        this.str=this.rng.nextInt(this.lvlneeded)+3;
        this.def=this.rng.nextInt(this.lvlneeded)+3;
        this.hp=this.rng.nextInt(this.lvlneeded)+3;
        this.dex=this.rng.nextInt(this.lvlneeded)+3;
        this.type=this.rng.nextInt(3)+1;//1-dla sword 2-boots 3-armor//this.rng.nextInt(3);
        this.dlook=new Sprite(looks[this.type-1]);
    }

    public void draw(Integer pos, RenderWindow g)
    {
        this.dlook.setPosition(new Vector2f(500,pos*100+318));
        g.draw(this.dlook);
        stat.setString(this.str.toString());
        stat.setPosition(new Vector2f(720,pos*100+340));
        g.draw(stat);
        stat.setString(this.def.toString());
        stat.setPosition(new Vector2f(880,pos*100+340));
        g.draw(stat);
        stat.setString(this.dex.toString());
        stat.setPosition(new Vector2f(1050,pos*100+340));
        g.draw(stat);
        stat.setString(this.hp.toString());
        stat.setPosition(new Vector2f(1190,pos*100+340));
        g.draw(stat);
        stat.setString(this.lvlneeded.toString());
        stat.setPosition(new Vector2f(1370,pos*100+340));
        g.draw(stat);
    }
}