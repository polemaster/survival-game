package pl.edu.pg.mygame.gui;

import javax.swing.*;
import java.awt.*;
import java.io.File;

import static pl.edu.pg.mygame.utils.Constants.PanelActions.NO_ACTION;
import static pl.edu.pg.mygame.utils.Constants.DisplayLayout.*;

public class MainPanel extends JPanel {
    private int action;
    File file;
    public MainPanel(GridMap game_panel) {
        action = NO_ACTION;
        file = null;

        setLayout(null);
        setPreferredSize(new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT));
        setBackground(Color.white);

        add(game_panel);

        SaveGameButton save_game_button = new SaveGameButton(this);
        LoadGameButton load_game_button = new LoadGameButton(this);
        add(save_game_button);
        add(load_game_button);
    }

    public int getAction() {
        return action;
    }

    public void setAction(int action) {
        this.action = action;
    }

    public File getFile() {
        return file;
    }

    public void setFile(File file) {
        this.file = file;
    }
    public void showEnd() {
        JOptionPane.showMessageDialog(null, "You died", "THE END", JOptionPane.ERROR_MESSAGE);
    }
}
