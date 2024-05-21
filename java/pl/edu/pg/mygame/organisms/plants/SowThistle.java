package pl.edu.pg.mygame.organisms.plants;

import pl.edu.pg.mygame.Grid;
import pl.edu.pg.mygame.organisms.Species;

import java.awt.*;

public class SowThistle extends Plant {

    public SowThistle(Point p) {
        super(p);
        this.species = Species.SOW_THISTLE;
    }

    @Override
    public void makeAction(Grid grid) {
        for (int i = 0; i < 3; ++i)
            super.makeAction(grid);
    }
}
