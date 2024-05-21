package pl.edu.pg.mygame.organisms.animals;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.organisms.Species;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;

import static pl.edu.pg.mygame.utils.HelperFunctions.getRandomPoint;

public class Fox extends Animal {

    public Fox(Point p) {
        super(p);
        this.species = Species.FOX;
        this.initiative = 7;
        this.strength = 3;
    }

    @Override
    protected Point getNewPoint(Grid grid) {
        List<Point> neighbours = grid.getNeighbourCells(position);
        List<Point> final_neighbours = new ArrayList<>();
        for (Point neighbour : neighbours) {
            if ((grid.getOrganism(neighbour) != null && grid.getOrganism(neighbour).getStrength() <= this.strength) ||
                     (grid.getOrganism(neighbour) == null))
                final_neighbours.add(neighbour);
        }
        if (final_neighbours.size() > 0)
            return getRandomPoint(final_neighbours);
        return null;
    }
}
