package pl.edu.pg.mygame.organisms.plants;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.World;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;

import java.awt.*;

public class Belladonna extends Plant {
    public Belladonna(Point p) {
        super(p);
        this.species = Species.BELLADONNA;
        this.strength = 99;
    }

    @Override
    public boolean collision(Organism other, boolean attacking, Grid grid) {
        World.message_panel.showMessage("Belladonna killed " + other.getSpecies() + " at: " +
                String.format("%d,%d)\n", other.getPosition().x, other.getPosition().y));
        grid.setOrganism(other.getPosition(), null);
        return true;
    }
}
