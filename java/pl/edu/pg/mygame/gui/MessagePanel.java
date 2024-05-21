package pl.edu.pg.mygame.gui;

import javax.swing.*;
import java.awt.*;

import static pl.edu.pg.mygame.utils.Constants.DisplayLayout.*;

public class MessagePanel extends JPanel {
    private final JTextArea message_area;
    public MessagePanel() {
        setBounds(MESSAGE_PANEL_X, MESSAGE_PANEL_Y, MESSAGE_PANEL_WIDTH, MESSAGE_PANEL_HEIGHT);
        setBackground(Color.white);
        setLayout(null);


        message_area = new JTextArea(10, 30);
        message_area.setEditable(false);
        message_area.setFocusable(false);
        message_area.setFont(new Font("Futura", Font.PLAIN, 15));
        JScrollPane scroll_pane = new JScrollPane(message_area);
        scroll_pane.setBounds(0, 0, getWidth(), getHeight());
        add(scroll_pane);
    }

    public void showMessage(String message) {
        message_area.append(message);
    }

    public void clearPanel() {
        message_area.setText("");
    }
}
