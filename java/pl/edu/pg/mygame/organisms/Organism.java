package pl.edu.pg.mygame.organisms;

import pl.edu.pg.mygame.Grid;

import java.awt.Point;
import java.io.Serializable;

public abstract class Organism implements Serializable {
    protected Point position;
    protected Species species;
    protected int strength;
    protected int initiative;
    protected final int age;

    public Organism(Point p) {
        this.position = p;
        this.strength = 0;
        this.initiative = 0;
        this.age = 0;
    }

    public Point getPosition() {
        return position;
    }

    public abstract void makeAction(Grid grid);


    public int getInitiative() {
        return initiative;
    }

    public int getStrength() {
        return strength;
    }

    public int getAge() {
        return age;
    }

    public Species getSpecies() {
        return species;
    }

    public void setPosition(Point position) {
        this.position = position;
    }

    public boolean collision(Organism other, boolean attacking, Grid grid) {
        return false;
    }

    public void setStrength(int strength) {
        this.strength = strength;
    }
}
