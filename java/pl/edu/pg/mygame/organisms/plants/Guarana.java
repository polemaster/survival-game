package pl.edu.pg.mygame.organisms.plants;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.World;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;

import java.awt.*;

public class Guarana extends Plant {
    public Guarana(Point p) {
        super(p);
        this.species = Species.GUARANA;
    }

    @Override
    public boolean collision(Organism other, boolean attacking, Grid grid) {
        other.setStrength(other.getStrength() + 3);
        World.message_panel.showMessage(other.getSpecies() + " gained 3 strength and ");
        return false;
    }
}
