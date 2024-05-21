package pl.edu.pg.mygame.utils;

import static java.lang.Math.round;
import static java.lang.Math.sqrt;

public class Constants {
    public static class GridDimension {
        // max values for:
        // HexGrid -> 13
        // SquareGrid -> 14
        public static final int GRID_HEIGHT = 13;
        public static final int GRID_WIDTH = GRID_HEIGHT;

    }
    public static class HumanActions {
        public static final int NO_MOVEMENT = -1;
        // for normal grid
        public static final int UP = 0;
        public static final int RIGHT = 1;
        public static final int DOWN = 2;
        public static final int LEFT = 3;

        // for hexagonal grid
        public static final int LEFT_UP = 4;
        public static final int LEFT_DOWN = 5;
        public static final int RIGHT_UP = 6;
        public static final int RIGHT_DOWN = 7;

        public static final int ABILITY = 8;
    }

    public static class ComponentSizes {
        public static final float SCALE = 1;
        public static final int HEXAGON_SIZE = round(38 * SCALE);
        public static final int HEXAGON_WIDTH = 2 * HEXAGON_SIZE;
        public static final int HEXAGON_HEIGHT = (int) round(sqrt(3) * HEXAGON_SIZE);
        public static final int SQUARE_SIZE = round(60 * SCALE);
    }

    public static class DisplayLayout {
        public static final int WINDOW_HEIGHT = 900;
        public static final int WINDOW_WIDTH = 1600;

        public static final int GAME_PANEL_X = 650;
        public static final int GAME_PANEL_Y = 20;



        public static final int LOAD_BUTTON_X = 10;
        public static final int LOAD_BUTTON_Y = 650;

        public static final int SAVE_BUTTON_X = 10;
        public static final int SAVE_BUTTON_Y = 730;


        public static final int BUTTON_HEIGHT = 50;
        public static final int BUTTON_WIDTH = 200;

        public static final int MESSAGE_PANEL_X = 0;
        public static final int MESSAGE_PANEL_Y = 0;
        public static final int MESSAGE_PANEL_HEIGHT = 500;
        public static final int MESSAGE_PANEL_WIDTH = 550;
    }

    public static class PanelActions {
        public static final int NO_ACTION = -1;
        public static final int SAVED_FILE = 0;
        public static final int LOADED_FILE = 1;
    }
}
