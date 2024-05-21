package pl.edu.pg.mygame.gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import static pl.edu.pg.mygame.utils.Constants.PanelActions.SAVED_FILE;
import static pl.edu.pg.mygame.utils.Constants.DisplayLayout.*;

public class SaveGameButton extends JButton implements ActionListener {
    private final MainPanel main_panel;
    public SaveGameButton(MainPanel panel) {
        main_panel = panel;
        setBounds(SAVE_BUTTON_X, SAVE_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
        setText("Save Game");
        setFont(new Font("Impact", Font.BOLD, 20));
        setFocusable(false);
        addActionListener(this);
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        JFileChooser file_chooser = new JFileChooser();

        file_chooser.setCurrentDirectory(new File("."));

        int response = file_chooser.showSaveDialog(null);

        if (response == JFileChooser.APPROVE_OPTION) {
            File file = file_chooser.getSelectedFile();

            main_panel.setAction(SAVED_FILE);
            main_panel.setFile(file);
        }
    }
}
