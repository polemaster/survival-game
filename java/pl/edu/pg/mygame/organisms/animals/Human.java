package pl.edu.pg.mygame.organisms.animals;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.World;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;

import java.awt.*;
import java.io.Serializable;
import java.util.List;

import static pl.edu.pg.mygame.utils.Constants.HumanActions.NO_MOVEMENT;
import static pl.edu.pg.mygame.utils.HelperFunctions.getRandomPoint;

public class Human extends Animal implements Serializable {
    private int action;
    private int last_ability;
    private boolean ability_on;
    public Human(Point p) {
        super(p);
        this.species = Species.HUMAN;
        this.strength = 5;
        this.initiative = 4;
        this.last_ability = -10;
        action = NO_MOVEMENT;
    }

    @Override
    protected Point getNewPoint(Grid grid) {
        return grid.getHumanPoint(position, action);
    }


    // here is only Alzur's shield implemented
    @Override
    public boolean collision(Organism other, boolean attacking, Grid grid) {
        if (!attacking && ability_on) {
            List<Point> neighbours = grid.getFreeNeighbourCells(other.getPosition());
            if (neighbours.size() > 0) {
                Point new_point = getRandomPoint(neighbours);
                World.message_panel.showMessage("Human deterred " + other.getSpecies() + " and it moved to: " +
                        String.format("(%d, %d)", new_point.x, new_point.y));
                grid.setOrganism(other.getPosition(), null);
                other.setPosition(new_point);
                grid.setOrganism(new_point, other);
            }
            else
                World.message_panel.showMessage("Human deterred " + other.getSpecies() + " and it didn't move (no free space)\n");
            return true;
        }
        return false;
    }


    public void setAction(int action, int curr_turn) {
        this.action = action;
        if (ability_on && curr_turn > last_ability + 5)
            ability_on = false;
    }

    public void activateAbility(int curr_turn) {
        if (last_ability + 10 <= curr_turn) {
            ability_on = true;
            last_ability = curr_turn;
            World.message_panel.showMessage("Human used ability Alzur's shield\n");
        }
    }
}
