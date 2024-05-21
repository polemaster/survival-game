package pl.edu.pg.mygame.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import static pl.edu.pg.mygame.utils.Constants.PanelActions.LOADED_FILE;
import static pl.edu.pg.mygame.utils.Constants.DisplayLayout.*;

public class LoadGameButton extends JButton implements ActionListener {
    private final MainPanel main_panel;
    public LoadGameButton(MainPanel panel) {
        main_panel = panel;
        setBounds(LOAD_BUTTON_X, LOAD_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
        setText("Load Game");
        setFont(new Font("Impact", Font.BOLD, 20));

        setFocusable(false);
        addActionListener(this);
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        JFileChooser file_chooser = new JFileChooser();

        file_chooser.setCurrentDirectory(new File("."));

        int response = file_chooser.showOpenDialog(null);

        if (response == JFileChooser.APPROVE_OPTION) {
            File file = file_chooser.getSelectedFile();

            main_panel.setAction(LOADED_FILE);
            main_panel.setFile(file);
        }
    }
}
