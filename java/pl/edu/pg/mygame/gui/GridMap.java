package pl.edu.pg.mygame.gui;


import javax.swing.*;
import java.awt.*;

import static pl.edu.pg.mygame.utils.Constants.HumanActions.*;
import static pl.edu.pg.mygame.utils.Constants.DisplayLayout.*;

public abstract class GridMap extends JPanel {
    protected int curr_action = NO_MOVEMENT;
    GridMap() {
        setLocation(GAME_PANEL_X, GAME_PANEL_Y);
        setBackground(Color.white);
    }

    public void setAction(int new_action) {
        curr_action = new_action;
    }

    public int getAction() {
        return curr_action;
    }
}
