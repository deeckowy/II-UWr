/**
 * Klasa game to klasa obsługująca główne menu, stąd można przejść do rozgrywki, 
 * sprawdzić instrukcje lub autorów oraz zakończyć grę.  
 */
import java.io.IOException;
import java.nio.file.Path;

import org.jsfml.graphics.Color;
import org.jsfml.graphics.Font;
import org.jsfml.graphics.RenderWindow;
import org.jsfml.graphics.Text;
import org.jsfml.window.VideoMode;
import org.jsfml.window.Keyboard.Key;
import org.jsfml.window.event.Event;
import org.jsfml.window.event.KeyEvent;

import MainLoop.MainLoop;

public class Game 
{    
    public static void main(String[] args) 
    {
        Font menfont = new Font();
        try {
            menfont.loadFromFile(Path.of("src/font.otf"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        Text m1=new Text("PLAY",menfont,40);
        Text m2=new Text("HELP",menfont,40);
        Text m3=new Text("CREDITS",menfont,40);
        Text m4=new Text("EXIT",menfont,40);
        m1.setPosition(100, 600);
        m2.setPosition(100, 700);
        m3.setPosition(100, 800);
        m4.setPosition(100, 900);

        RenderWindow app=new RenderWindow(new VideoMode(1920, 1080), "Test Game!");
        Integer pos=0;
        while(app.isOpen())
        {
            for(Event ev:app.pollEvents())
            {
                switch (ev.type) 
                {
                    case CLOSED:
                        app.close();
                        break;
                    case KEY_PRESSED:
                        KeyEvent k=ev.asKeyEvent();
                        if(k.key==Key.DOWN&&pos<3)
                            pos++;
                        else if(k.key==Key.UP&&pos>0)
                            pos--;
                        else if(k.key==Key.RETURN)
                        {
                            switch (pos) 
                            {
                                case 0:
                                    MainLoop game=new MainLoop();
                                    game.Play(app);
                                    break;
                                case 1:
                                    //TODO: HELP
                                    break;
                                case 2:
                                    //TODO: credits
                                case 3:
                                    app.close();
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
            
            m1.setColor(Color.WHITE);
            m2.setColor(Color.WHITE);
            m3.setColor(Color.WHITE);
            m4.setColor(Color.WHITE);
            switch (pos) 
            {
                case 0:
                    m1.setColor(Color.YELLOW);
                    break;
                case 1:
                    m2.setColor(Color.YELLOW);
                    break;
                case 2:
                    m3.setColor(Color.YELLOW);
                    break;
                case 3:
                    m4.setColor(Color.YELLOW);
                    break;
                default:
                    break;
            }
            app.clear();
            app.draw(m1);
            app.draw(m2);
            app.draw(m3);
            app.draw(m4);
            app.display();
        }       
    }
}