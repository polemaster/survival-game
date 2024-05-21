package pl.edu.pg.mygame.organisms.animals;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.World;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;

import java.awt.*;
import java.util.List;

import static pl.edu.pg.mygame.utils.HelperFunctions.getRandomPoint;
import static pl.edu.pg.mygame.utils.HelperFunctions.isLucky;

public class Antelope extends Animal {
    public Antelope(Point p) {
        super(p);
        this.species = Species.ANTELOPE;
        this.initiative = 4;
        this.strength = 4;
    }

    @Override
    protected Point getNewPoint(Grid grid) {
        List<Point> far_neighbours = grid.getDeepNeighbourCells(position);
        // when there are no cells at range 2, get the cells at range 1
        // this can for example happen when square grid is 3x3 and antelope is in the middle
        if (far_neighbours.size() == 0)
            far_neighbours = grid.getNeighbourCells(position);
        return getRandomPoint(far_neighbours);
    }

    @Override
    public boolean collision(Organism other, boolean attacking, Grid grid) {
        if (isLucky(50)) {
            List<Point> points = grid.getFreeNeighbourCells(position);
            if (points.size() == 0)
                return false;
            Point p = getRandomPoint(points);
            Point old_position = position;
            grid.setOrganism(position, null);
            position = p;
            grid.setOrganism(position, this);
            World.message_panel.showMessage("Antelope escaped from the fight to:" +
                    String.format("(%d, %d)\n", position.x, position.y));

            if (!attacking) {
                grid.setOrganism(other.getPosition(), null);
                other.setPosition(old_position);
                grid.setOrganism(old_position, other);
            }
            return true;
        }
        return false;
    }
}
