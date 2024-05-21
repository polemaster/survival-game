package pl.edu.pg.mygame;

import pl.edu.pg.mygame.gui.*;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;
import pl.edu.pg.mygame.organisms.animals.Human;
import pl.edu.pg.mygame.utils.HelperFunctions;
import pl.edu.pg.mygame.utils.OrganismFactory;

import javax.swing.*;
import java.awt.Point;
import java.io.*;
import java.util.*;

import static pl.edu.pg.mygame.utils.Constants.GridDimension.*;
import static pl.edu.pg.mygame.utils.Constants.HumanActions.*;
import static pl.edu.pg.mygame.utils.Constants.PanelActions.*;


public class World implements Serializable {

    private Human human;
    Grid grid;
    final MyFrame my_frame;
    GridMap game_panel;
    MainPanel main_panel;
    private boolean is_end;
    private int turn;
    List<Point> unoccupied_points;
    private Random random;
    File file;

    public static MessagePanel message_panel;

    public World() {
        random = new Random();
        HelperFunctions.setRandom(random);

        is_end = false;
        turn = 1;

        message_panel = new MessagePanel();

        grid = new HexGrid(GRID_WIDTH, GRID_HEIGHT);
        game_panel = new HexGridMap(grid);
//        grid = new SquareGrid(GRID_WIDTH, GRID_HEIGHT);
//        game_panel = new SquareGridMap(grid);

        main_panel = new MainPanel(game_panel);
        main_panel.add(message_panel);
        my_frame = new MyFrame(main_panel);
        game_panel.requestFocus();
    }

    public void initGame() {
        unoccupied_points = grid.getAllPoints();

        addHuman();
        addEachOrganism();
        addEachOrganism();
        addEachOrganism();
//        addOrganism(Species.ANTELOPE);
//        addOrganism(Species.ANTELOPE);
    }


    private void addEachOrganism() {
        for (Species species : Species.values()) {
            if (species != Species.HUMAN)
                addOrganism(species);
        }
    }

    private void addHuman() {
        Point p = popRandomPoint();
        human = (Human) OrganismFactory.create(Species.HUMAN, p);
        grid.addOrganism(human);
    }

    private void addOrganism(Species species) {
        Point p = popRandomPoint();
        grid.addOrganism(OrganismFactory.create(species, p));
    }

    private Point popRandomPoint() {
        if (unoccupied_points.size() == 0)
            return null;
        int index = random.nextInt(unoccupied_points.size());
        return unoccupied_points.remove(index);
    }


    public void sortOrganisms(List<Organism> organisms) {
        Comparator<Organism> comparator = Comparator
                .comparingInt(Organism::getInitiative)
                .thenComparingInt(Organism::getAge)
                .reversed();
        organisms.sort(comparator);
    }


    public void saveWorldStateToFile(String fileName) {
        try {
            FileOutputStream file_out = new FileOutputStream(fileName);
            ObjectOutputStream out = new ObjectOutputStream(file_out);
            out.writeObject(grid);
            out.writeObject(is_end);
            out.writeObject(turn);
            out.writeObject(random);
            out.close();
            file_out.close();
        } catch(IOException i) {
            i.printStackTrace();
        }
    }


    public void loadWorldStateFromFile(String fileName) {
        try {
            FileInputStream file_in = new FileInputStream(fileName);
            ObjectInputStream in = new ObjectInputStream(file_in);
            this.grid = (Grid) in.readObject();
            this.is_end = (boolean) in.readObject();
            this.turn = (int) in.readObject();
            this.random = (Random) in.readObject();
            in.close();
            file_in.close();

            // fix the rest of the game state
            this.human = grid.getHuman();

            if (grid instanceof HexGrid)
                game_panel = new HexGridMap(grid);
            else
                game_panel = new SquareGridMap(grid);

            message_panel = new MessagePanel();

            my_frame.remove(main_panel);
            main_panel = new MainPanel(game_panel);
            main_panel.add(message_panel);
            my_frame.add(main_panel);

            game_panel.requestFocus();

            grid.resetIcons();
        } catch(IOException i) {
            i.printStackTrace();
        } catch(ClassNotFoundException c) {
            System.out.println("Some class not found");
            c.printStackTrace();
        }
    }

    public void play() {
        while (!is_end) {
            // saving & loading game, switching modes
            if (main_panel.getAction() != NO_ACTION) {
                World.message_panel.clearPanel();
                switch (main_panel.getAction()) {
                    case SAVED_FILE -> {
                        file = main_panel.getFile();
                        saveWorldStateToFile(file.getName());
                        JOptionPane.showMessageDialog(null,
                                "Saved game state to a file: " + file, "FILE", JOptionPane.INFORMATION_MESSAGE);
                    }
                    case LOADED_FILE -> {
                        file = main_panel.getFile();
                        loadWorldStateFromFile(file.getName());
                        JOptionPane.showMessageDialog(null,
                                "Loaded game state from a file: " + file, "FILE", JOptionPane.INFORMATION_MESSAGE);
                    }
                }
                main_panel.setAction(NO_ACTION);
            }
            // moving with human, using ability
            else if (game_panel.getAction() != NO_MOVEMENT && game_panel.getAction() != ABILITY) {
                World.message_panel.clearPanel();
                World.message_panel.showMessage("turn: " + turn + "\n");
                human.setAction(game_panel.getAction(), turn);
                List<Organism> organisms = grid.getAllOrganisms();
                sortOrganisms(organisms);
                for (Organism organism : organisms) {
                    if (organism != null && grid.getOrganism(organism.getPosition()) == organism) {
                        organism.makeAction(grid);
                    }
                }
                ++turn;
                game_panel.setAction(NO_MOVEMENT);
                // if human was killed, end the game
                if (grid.getOrganism(human.getPosition()) != human)
                    is_end = true;
            }
            else if (game_panel.getAction() == ABILITY) {
                World.message_panel.clearPanel();
                human.activateAbility(turn);
                game_panel.setAction(NO_MOVEMENT);
            }

            try {
                Thread.sleep(10);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        // after the end of the game
        main_panel.showEnd();
    }
}
