package pl.edu.pg.mygame;

import pl.edu.pg.mygame.organisms.Species;

import javax.swing.*;
import java.awt.*;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import static java.lang.Math.round;
import static pl.edu.pg.mygame.utils.Constants.ComponentSizes.SCALE;

public class Icons implements Serializable {
    final List<ImageIcon> icons;

    public Icons() {
        icons = new ArrayList<>(Species.length);

        for (int i = 0; i < Species.length; ++i) {
            icons.add(null);
        }

        icons.set(Species.HUMAN.ordinal(), createIcon("img/human.png", 50));
        icons.set(Species.WOLF.ordinal(), createIcon("img/wolf.png", 80));
        icons.set(Species.SHEEP.ordinal(), createIcon("img/sheep.png", 12));
        icons.set(Species.FOX.ordinal(), createIcon("img/fox.png", 25));
        icons.set(Species.TURTLE.ordinal(), createIcon("img/turtle.png", 13));
        icons.set(Species.ANTELOPE.ordinal(), createIcon("img/antelope.png", 25));
        icons.set(Species.GRASS.ordinal(), createIcon("img/grass.png", 8));
        icons.set(Species.SOW_THISTLE.ordinal(), createIcon("img/sow_thistle.png", 15));
        icons.set(Species.GUARANA.ordinal(), createIcon("img/guarana.png", 11));
        icons.set(Species.BELLADONNA.ordinal(), createIcon("img/belladonna.png", 13));
        icons.set(Species.SOSNOWSKYS_HOGWEED.ordinal(), createIcon("img/sosnowskys_hogweed.png", 8));

    }

    private ImageIcon createIcon(String path, int scale) {
        ImageIcon tmp_image = new ImageIcon(path);
        int newWidth = round(SCALE * tmp_image.getIconWidth() / scale);
        return new ImageIcon(tmp_image.getImage().getScaledInstance(newWidth, -1, Image.SCALE_SMOOTH));
    }

    public ImageIcon getIcon(Species species) {
        return icons.get(species.ordinal());
    }
}
