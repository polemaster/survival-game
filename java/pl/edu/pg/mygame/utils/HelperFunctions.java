package pl.edu.pg.mygame.utils;

import java.awt.*;
import java.util.List;
import java.util.Random;

public class HelperFunctions {
    private static Random random;
    public static void setRandom(Random random) {
        HelperFunctions.random = random;
    }
    public static Point getRandomPoint(List<Point> points) {
        int index = random.nextInt(points.size());
        return points.get(index);
    }

    public static Point addPoints(Point p1, Point p2) {
        return new Point(p1.x + p2.x, p1.y + p2.y);
    }

    public static boolean isLucky(double percentage) {
        double randomNum = random.nextDouble() * 100; // generates a random number between 0 and 100
        return randomNum < percentage;
    }
}
