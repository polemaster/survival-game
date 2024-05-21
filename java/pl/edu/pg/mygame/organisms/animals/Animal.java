package pl.edu.pg.mygame.organisms.animals;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.World;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.utils.OrganismFactory;

import java.awt.Point;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import static pl.edu.pg.mygame.utils.HelperFunctions.getRandomPoint;

public abstract class Animal extends Organism {
    Animal(Point p) {
        super(p);
    }


    @Override
    public void makeAction(Grid grid) {
        Point new_point = getNewPoint(grid); // this method should be overridden by some animals
        if (new_point == null)
            return;

        World.message_panel.showMessage(species + " tried to move to: " +
                String.format("(%d, %d)", new_point.x, new_point.y));
        if (grid.getOrganism(new_point) == null) {
            World.message_panel.showMessage(" and moved\n");
            grid.setOrganism(position, null);
            position = new_point;
            grid.setOrganism(position, this);
        }
        else if (grid.getOrganism(new_point).getSpecies() == this.species) {
            World.message_panel.showMessage(" and reproduced at: ");
            reproduce(new_point, grid);
        }
        else {
            World.message_panel.showMessage(" and collided with: " + grid.getOrganism(new_point).getSpecies() + " ---> ");
            handleCollision(new_point, grid);
        }
    }

    protected Point getNewPoint(Grid grid) {
        List<Point> neighbours = grid.getNeighbourCells(this.position);
        return getRandomPoint(neighbours);
    }

    private void reproduce(Point new_point, Grid grid) {
        Point dest = getRandomFreeAdjacentPoint(position, new_point, grid);
        if (dest == null) {
            World.message_panel.showMessage("null\n");
            return;
        }

        World.message_panel.showMessage(String.format("(%d, %d)", dest.x, dest.y) + "\n");

        Organism organism = OrganismFactory.create(this.species, dest);
        grid.addOrganism(organism);
    }

    public void handleCollision(Point other_org_point, Grid grid) {
        boolean collided;
        Organism other_org = grid.getOrganism(other_org_point);
        // make the collision of current organism with the other
        collided = collision(other_org, true, grid);
        // if the other organism survived, make his collision
        if (!collided)
            collided = other_org.collision(this, false, grid);


        // if nothing important happened, make the default collision
        if (!collided) {
            if (this.getStrength() >= other_org.getStrength()) {
                World.message_panel.showMessage(this.species + " killed " + other_org.getSpecies() + "\n");
                grid.setOrganism(position, null);
                position = other_org_point;
                grid.setOrganism(position, this);
            }
            else {
                World.message_panel.showMessage(other_org.getSpecies() + " killed " + this.species + "\n");
                grid.setOrganism(position, null);
            }
        }
    }


    private Point getRandomFreeAdjacentPoint(Point point1, Point point2, Grid grid) {
        Set<Point> neighbours1 = new HashSet<>(grid.getFreeNeighbourCells(point1));
        Set<Point> neighbours2 = new HashSet<>(grid.getFreeNeighbourCells(point2));
        Set<Point> neighbours_sum = new HashSet<>(neighbours1);
        neighbours_sum.addAll(neighbours2);

        if (neighbours_sum.size() == 0)
            return null;


        return getRandomPoint(new ArrayList<>(neighbours_sum));
    }
}
