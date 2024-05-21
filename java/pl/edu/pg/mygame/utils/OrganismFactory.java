package pl.edu.pg.mygame.utils;

import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;
import pl.edu.pg.mygame.organisms.animals.*;
import pl.edu.pg.mygame.organisms.plants.*;

import java.awt.Point;

public class OrganismFactory {
    public static Organism create(Species name, Point p) {
        return switch (name) {
            case HUMAN -> new Human(p);
            case WOLF -> new Wolf(p);
            case SHEEP -> new Sheep(p);
            case FOX -> new Fox(p);
            case TURTLE -> new Turtle(p);
            case ANTELOPE -> new Antelope(p);
            case GRASS -> new Grass(p);
            case SOW_THISTLE -> new SowThistle(p);
            case GUARANA -> new Guarana(p);
            case BELLADONNA -> new Belladonna(p);
            case SOSNOWSKYS_HOGWEED -> new SosnowskysHogweed(p);
        };
    }
}
