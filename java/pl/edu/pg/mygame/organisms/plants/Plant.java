package pl.edu.pg.mygame.organisms.plants;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.World;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.utils.OrganismFactory;

import java.awt.Point;
import java.util.List;

import static pl.edu.pg.mygame.utils.HelperFunctions.getRandomPoint;
import static pl.edu.pg.mygame.utils.HelperFunctions.isLucky;

public abstract class Plant extends Organism {
    public Plant(Point p) {
        super(p);
    }

    @Override
    public void makeAction(Grid grid) {
        if (isLucky(3)) {
            List<Point> points = grid.getFreeNeighbourCells(position);
            if (points.size() == 0)
                return;
            Point new_point = getRandomPoint(points);
            Organism new_plant = OrganismFactory.create(species, new_point);
            grid.addOrganism(new_plant);
            World.message_panel.showMessage(species + " spread to: " +
                    String.format("(%d, %d)\n", new_point.x, new_point.y));
        }
    }

}
