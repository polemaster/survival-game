package pl.edu.pg.mygame.gui;

import pl.edu.pg.mygame.Grid;

import java.awt.*;

import static pl.edu.pg.mygame.utils.Constants.ComponentSizes.*;

public class SquareCell extends Cell {
    public SquareCell(Grid grid) {
        super(grid);
        sides = 4;
        size = SQUARE_SIZE;
        width = size;
        height = size;

        addMouseListener(this);
        setPreferredSize(new Dimension(size, size));
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g.create();

        g2d.setColor(getForeground());
        g2d.drawRect(0, 0, size - 1, size - 1);

        g2d.dispose();
    }

}
