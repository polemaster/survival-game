package pl.edu.pg.mygame;


import java.awt.Point;
import java.util.ArrayList;

import static pl.edu.pg.mygame.utils.Constants.HumanActions.*;

public class SquareGrid extends Grid {
    public SquareGrid(int width, int height) {
        super(width, height);

        neighbour_directions = new ArrayList<>() {
            {add(new Point(-1 , 0)); add(new Point(1, 0));
                add(new Point(0, -1)); add(new Point(0, 1));}
        };

        depth_two_neighbour_directions = new ArrayList<>(neighbour_directions.size());
        for (Point p : neighbour_directions) {
            depth_two_neighbour_directions.add(new Point(p.x * 2, p.y * 2));
        }
    }

    @Override
    public Point getHumanPoint(Point human_point, int action) {
        Point new_point = new Point(human_point);
        switch (action) {
            case LEFT -> new_point.translate(-1, 0);
            case RIGHT -> new_point.translate(1, 0);
            case UP -> new_point.translate(0, -1);
            case DOWN -> new_point.translate(0, 1);
        }
        if (isValid(new_point) && new_point != human_point)
            return new_point;
        return null;
    }
}
