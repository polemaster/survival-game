package pl.edu.pg.mygame.gui.input;

import pl.edu.pg.mygame.gui.GridMap;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public abstract class KeyboardInput implements KeyListener {
    protected final GridMap game_panel;

    public KeyboardInput(GridMap game_panel) {
        this.game_panel = game_panel;
    }


    @Override
    public void keyPressed(KeyEvent e) {

    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}
