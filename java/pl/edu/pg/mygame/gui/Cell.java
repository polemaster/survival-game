package pl.edu.pg.mygame.gui;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.World;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;
import pl.edu.pg.mygame.utils.OrganismFactory;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Objects;


public abstract class Cell extends JLabel implements MouseListener {
    protected int sides;
    protected int size;
    protected int width;
    protected int height;
    protected boolean is_hovered;
    final Color normal_bg_color;
    final Color normal_fg_color;
    final Color highlighted_bg_color;
    final Color highlighted_fg_color;
    final Grid grid;

    public Cell(Grid grid) {
        this.grid = grid;

        is_hovered = false;

        normal_bg_color = Color.white;
        highlighted_bg_color = Color.lightGray;
        normal_fg_color = Color.black;
        highlighted_fg_color = Color.red;

        // set icons to appear in the center
        setVerticalAlignment(JLabel.CENTER);
        setHorizontalAlignment(JLabel.CENTER);

        setForeground(normal_fg_color);
        setBackground(normal_bg_color);

        // this is necessary in order for background color to work
        setOpaque(true);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        Point point = grid.findCell(this);
        // if the cell is already occupied, don't do anything
        if (grid.getOrganism(point) != null)
            return;

        // otherwise ask user for species and create organism
        Species[] arr = Species.values();
        Species[] new_arr = new Species[arr.length - 1];
        System.arraycopy(arr, 1, new_arr, 0, new_arr.length);
        JComboBox<Species> comboBox = new JComboBox<>(new_arr);
        int result = JOptionPane.showConfirmDialog(null, comboBox, "Select a new organism",
                JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
        if (result == JOptionPane.OK_OPTION) {
            Organism organism = OrganismFactory.create((Species) Objects.requireNonNull(comboBox.getSelectedItem()), point);
            grid.addOrganism(organism);

            if (point == null)
                World.message_panel.showMessage("Didn't find a cell in a grid and returned null point\n");
            else
                World.message_panel.showMessage("added new " + organism.getSpecies() +
                        String.format(" at: (%d, %d)\n", point.x, point.y) );
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {
        setForeground(highlighted_fg_color);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        setForeground(normal_fg_color);
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        is_hovered = true;
        setBackground(highlighted_bg_color);
        repaint();
    }

    @Override
    public void mouseExited(MouseEvent e) {
        is_hovered = false;
        setBackground(normal_bg_color);
        repaint();
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(width, height);
    }
}
