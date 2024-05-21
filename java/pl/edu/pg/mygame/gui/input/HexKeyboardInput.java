package pl.edu.pg.mygame.gui.input;

import pl.edu.pg.mygame.gui.GridMap;

import java.awt.event.KeyEvent;

import static pl.edu.pg.mygame.utils.Constants.HumanActions.*;

public class HexKeyboardInput extends KeyboardInput {
    public HexKeyboardInput(GridMap game_panel) {
        super(game_panel);
    }

    @Override
    public void keyTyped(KeyEvent e) {

        switch (e.getKeyChar()) {
            case 'q' -> game_panel.setAction(LEFT_UP);
            case 'w' -> game_panel.setAction(UP);
            case 'e' -> game_panel.setAction(RIGHT_UP);
            case 'a' -> game_panel.setAction(LEFT_DOWN);
            case 's' -> game_panel.setAction(DOWN);
            case 'd' -> game_panel.setAction(RIGHT_DOWN);
            case 'r' -> game_panel.setAction(ABILITY);
        }
    }
}
