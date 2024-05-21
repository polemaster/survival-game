package pl.edu.pg.mygame;

import java.awt.Point;
import java.util.ArrayList;

import static java.lang.Math.abs;
import static pl.edu.pg.mygame.utils.Constants.HumanActions.*;

public class HexGrid extends Grid {
    public HexGrid(int width, int height) {
        super(width, height);
        if (width % 2 == 0 || height % 2 == 0)
            throw new RuntimeException("Width and height of the HexGrid need to be odd");


        neighbour_directions = new ArrayList<>() {
            {add(new Point(-1, 0)); add(new Point(0, -1));
                add(new Point(1, 0)); add(new Point(0, 1));
                add(new Point(1, -1)); add(new Point(-1, 1));}
        };


        depth_two_neighbour_directions = new ArrayList<>() {
            {add(new Point(-1, -1)); add(new Point(1, 1));
                add(new Point(0, -2)); add(new Point(0, 2));
                add(new Point(1, -2)); add(new Point(-1, 2));
                add(new Point(2, -2)); add(new Point(-2, 2));
                add(new Point(2, -1)); add(new Point(-2, 1));
                add(new Point(2, 0)); add(new Point(-2, 0));}
        };
    }

    @Override
    public boolean isValid(Point p) {
        boolean is_valid = super.isValid(p);
        if (!is_valid)
            return false;
        if (abs(p.x) + abs(p.y) < width/2 || abs(p.x) + abs(p.y) > width/2 + width - 1)
            return false;
        return true;
    }

    @Override
    public Point getHumanPoint(Point human_point, int action) {
        Point new_point = new Point(human_point);
        switch (action) {
            case UP -> new_point.translate(0, -1);
            case RIGHT_UP -> new_point.translate(1, -1);
            case RIGHT_DOWN -> new_point.translate(1, 0);
            case DOWN -> new_point.translate(0, 1);
            case LEFT_DOWN -> new_point.translate(-1, 1);
            case LEFT_UP -> new_point.translate(-1, 0);
        }
        if (isValid(new_point) && new_point != human_point)
            return new_point;
        return null;
    }
}
