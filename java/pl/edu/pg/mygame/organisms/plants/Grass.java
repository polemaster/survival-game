package pl.edu.pg.mygame.organisms.plants;

import pl.edu.pg.mygame.organisms.Species;

import java.awt.*;

public class Grass extends Plant {
    public Grass(Point p) {
        super(p);
        this.species = Species.GRASS;
    }
}
