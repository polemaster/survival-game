package pl.edu.pg.mygame.gui.input;

import pl.edu.pg.mygame.gui.GridMap;

import java.awt.event.KeyEvent;

import static pl.edu.pg.mygame.utils.Constants.HumanActions.*;

public class SquareKeyboardInput extends KeyboardInput {
    public SquareKeyboardInput(GridMap game_panel) {
        super(game_panel);
    }

    @Override
    public void keyTyped(KeyEvent e) {
        switch (e.getKeyChar()) {
            case 'w' -> game_panel.setAction(UP);
            case 'a' -> game_panel.setAction(LEFT);
            case 's' -> game_panel.setAction(DOWN);
            case 'd' -> game_panel.setAction(RIGHT);
            case 'r' -> game_panel.setAction(ABILITY);
        }
    }

}
