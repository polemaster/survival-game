package pl.edu.pg.mygame.gui;

import pl.edu.pg.mygame.Grid;

import java.awt.*;
import javax.swing.*;

import static java.lang.Math.*;
import static pl.edu.pg.mygame.utils.Constants.ComponentSizes.*;

public class HexCell extends Cell  {
    private final Point center;
    private final Point top_left_corner; // top left corner of the rectangle of the component
    private Polygon hexagon;

    public HexCell(Point p, Grid grid) {
        super(grid);
        sides = 6;
        size = HEXAGON_SIZE;
        width = HEXAGON_WIDTH;
        height = HEXAGON_HEIGHT;
        center = p;
        top_left_corner = new Point(p.x - width / 2, p.y - height / 2);

        addMouseListener(this);
        // we need to add 1 to height to display lower edge
        setBounds(top_left_corner.x, top_left_corner.y, width, height + 1);
        createHexagon();
    }

    @Override
    protected void paintComponent(Graphics g) {
        setBackground(normal_bg_color);
        super.paintComponent(g); // displays the icon


        Graphics2D g2d = (Graphics2D) g.create();
        if (is_hovered) {
            // We fill the hexagon with other color and the icon gets covered as well
            g2d.setColor(highlighted_bg_color);
            g2d.fill(hexagon);

            // so we need to repaint the icon
            ImageIcon icon = (ImageIcon) getIcon();
            if (icon != null) {
                Image img = icon.getImage();
                int x = (getWidth() - img.getWidth(null)) / 2;
                int y = (getHeight() - img.getHeight(null)) / 2;
                g2d.drawImage(img, x, y, null);
            }
        }

        g2d.setColor(getForeground());
        g2d.drawPolygon(hexagon);

        g2d.dispose();
    }

    private void createHexagon() {
        hexagon = new Polygon();

        for (int i = 0; i < sides; i++) {
            int angle_deg = 60 * i;
            double angle_rad = PI / 180 * angle_deg;

            // we need to subtract the top left corner in order for the paintComponent() method to work
            int x = center.x + (int) round(size * cos(angle_rad)) - top_left_corner.x;
            int y = center.y + (int) round(size * sin(angle_rad)) - top_left_corner.y;
            hexagon.addPoint(x, y);
        }
    }

    @Override
    public boolean contains(int x, int y) {
        return hexagon.contains(x, y);
    }

}
