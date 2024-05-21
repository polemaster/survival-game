package pl.edu.pg.mygame.gui;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.gui.input.HexKeyboardInput;

import java.awt.*;
import java.util.List;

import static java.lang.Math.*;
import static pl.edu.pg.mygame.utils.Constants.ComponentSizes.*;

public class HexGridMap extends GridMap {
    public HexGridMap(Grid grid) {
        // we need to add 1 to height to display lower edge
        this.setLayout(null);
        this.setSize(((int) ceil(grid.getWidth() * 1.5)) * HEXAGON_SIZE, grid.getHeight() * HEXAGON_HEIGHT + 1);
        this.addKeyListener(new HexKeyboardInput(this));

        int shift_right = HEXAGON_WIDTH / 2;
        int shift_down = HEXAGON_HEIGHT / 2 + 1; // +1 is because for grid size = 13, the top edge doesn't show
        int shift_up = (int) round(HEXAGON_SIZE * sqrt(3) / 2) * (grid.getHeight() / 2);

        List<Point> list2 = grid.getAllPoints();
        for (Point p : list2) {
            int x = (int) round(HEXAGON_SIZE * 3. / 2 * p.x) + shift_right;
            int y = (int) round(HEXAGON_SIZE * (sqrt(3) / 2 * p.x + sqrt(3) * p.y)) + shift_down - shift_up;
            HexCell new_cell = new HexCell(new Point(x, y), grid);
            grid.setCell(p, new_cell);
            this.add(new_cell);
        }
    }

}
