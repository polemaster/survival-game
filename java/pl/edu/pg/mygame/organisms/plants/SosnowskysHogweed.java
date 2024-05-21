package pl.edu.pg.mygame.organisms.plants;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.World;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;
import pl.edu.pg.mygame.organisms.animals.Animal;

import java.awt.*;
import java.util.List;

public class SosnowskysHogweed extends Plant {
    public SosnowskysHogweed(Point p) {
        super(p);
        this.species = Species.SOSNOWSKYS_HOGWEED;
        this.strength = 10;
    }

    @Override
    public boolean collision(Organism other, boolean attacking, Grid grid) {
        grid.setOrganism(other.getPosition(), null);
        World.message_panel.showMessage("Sosnowsky's hogweed killed " + other.getSpecies() + "\n");
        return true;
    }

    @Override
    public void makeAction(Grid grid) {
        // kill all adjacent organisms
        List<Point> neighbours = grid.getNeighbourCells(position);
        for (Point neighbour : neighbours) {
            if (neighbour != null && grid.getOrganism(neighbour) instanceof Animal) {
                World.message_panel.showMessage("Belladonna killed " + grid.getOrganism(neighbour).getSpecies() + "\n");
                grid.setOrganism(neighbour, null);
            }
        }
        super.makeAction(grid);
    }
}
