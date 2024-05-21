package pl.edu.pg.mygame.gui;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.gui.input.SquareKeyboardInput;

import java.awt.*;

import static pl.edu.pg.mygame.utils.Constants.ComponentSizes.*;

public class SquareGridMap extends GridMap {
    public SquareGridMap(Grid grid) {
        this.setLayout(new GridLayout(grid.getHeight(), grid.getWidth()));
        this.setSize(grid.getWidth() * SQUARE_SIZE, grid.getHeight() * SQUARE_SIZE);
        this.addKeyListener(new SquareKeyboardInput(this));

        for (int i = 0; i < grid.getHeight(); ++i) {
            for (int j = 0; j < grid.getWidth(); ++j) {
                Cell new_cell = new SquareCell(grid);
                grid.setCell(new Point(j, i), new_cell);
                this.add(new_cell);
            }
        }
    }
}
