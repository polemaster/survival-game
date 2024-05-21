package pl.edu.pg.mygame.organisms.animals;

import pl.edu.pg.mygame.organisms.Species;

import java.awt.Point;

public class Sheep extends Animal {
    public Sheep(Point p) {
        super(p);
        this.species = Species.SHEEP;
        this.initiative = 4;
        this.strength = 4;
    }
}
