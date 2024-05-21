package pl.edu.pg.mygame.gui;

import javax.swing.*;
import java.awt.*;

public class MyFrame extends JFrame {

    public MyFrame(MainPanel main_panel) {
        this.add(main_panel);

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.pack();
        this.setLocationRelativeTo(null); // after setLayout() or pack() and before setVisible()
        this.setResizable(false);
        this.getContentPane().setBackground(Color.white);
        this.setVisible(true); // at the end
    }
}
