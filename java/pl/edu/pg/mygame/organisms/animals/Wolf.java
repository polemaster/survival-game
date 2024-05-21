package pl.edu.pg.mygame.organisms.animals;

import pl.edu.pg.mygame.organisms.Species;

import java.awt.Point;

public class Wolf extends Animal {
    public Wolf(Point p) {
        super(p);
        this.species = Species.WOLF;
        this.initiative = 5;
        this.strength = 9;
    }
}
