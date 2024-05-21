package pl.edu.pg.mygame.organisms.animals;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.World;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;

import java.awt.*;

import static pl.edu.pg.mygame.utils.HelperFunctions.isLucky;

public class Turtle extends Animal {

    public Turtle(Point p) {
        super(p);
        this.species = Species.TURTLE;
        this.initiative = 1;
        this.strength = 2;
    }

    @Override
    protected Point getNewPoint(Grid grid) {
        if (isLucky(75))
            return null;
        return super.getNewPoint(grid);
    }

    @Override
    public boolean collision(Organism other, boolean attacking, Grid grid) {
        if (other.getStrength() < 5 && !attacking) {
            World.message_panel.showMessage("Turtle reflected attack from: " + other.getSpecies() + "\n");
            return true;
        }
        return false;
    }

}
