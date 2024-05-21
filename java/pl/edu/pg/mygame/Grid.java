package pl.edu.pg.mygame;

import pl.edu.pg.mygame.gui.Cell;
import pl.edu.pg.mygame.organisms.Organism;
import pl.edu.pg.mygame.organisms.Species;
import pl.edu.pg.mygame.organisms.animals.Human;

import java.awt.Point;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import static pl.edu.pg.mygame.utils.HelperFunctions.addPoints;


public abstract class Grid implements Serializable {
    protected final Organism[][] organisms;
    protected final Cell[][] cells;
    protected final Icons icons;
    protected final int width;
    protected final int height;

    public Grid(int width, int height) {
        this.organisms = new Organism[height][width];
        this.cells = new Cell[height][width];
        this.icons = new Icons();
        this.width = width;
        this.height = height;
    }
    public int getHeight() {
        return height;
    }

    public int getWidth() {
        return width;
    }

    public void setCell(Point p, Cell cell) {
        cells[p.y][p.x] = cell;
    }

    public void addOrganism(Organism organism) {
        Point p = organism.getPosition();
        setOrganism(p, organism);
    }
    public void setOrganism(Point p, Organism organism) {
        organisms[p.y][p.x] = organism;
        if (organism != null)
            cells[p.y][p.x].setIcon(icons.getIcon(organism.getSpecies()));
        else
            cells[p.y][p.x].setIcon(null);
    }

    public Organism getOrganism(Point p) {
        if (!isValid(p))
            return null;
        return organisms[p.y][p.x];
    }

    public List<Organism> getAllOrganisms() {
        List<Organism> list = new ArrayList<>();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (organisms[i][j] != null)
                    list.add(organisms[i][j]);
            }
        }
        return list;
    }

    public List<Point> getAllPoints() {
        List<Point> list = new ArrayList<>();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                Point p = new Point(j, i);
                if (isValid(p)) list.add(p);
            }
        }
        return list;
    }

    public boolean isValid(Point p) {
        if (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height)
            return false;
        return true;
    }

    protected List<Point> neighbour_directions;
    protected List<Point> depth_two_neighbour_directions;
    public List<Point> getNeighbourCells(Point p) {
        List<Point> list = new ArrayList<>();
        for (Point neighbourDirection : neighbour_directions) {
            Point neighbour_point = addPoints(neighbourDirection, p);
            if (isValid(neighbour_point)) {
                list.add(neighbour_point);
            }
        }
        return list;
    }

    public List<Point> getFreeNeighbourCells(Point p) {
        List<Point> list = new ArrayList<>();
        for (Point neighbourDirection : neighbour_directions) {
            Point neighbour_point = addPoints(neighbourDirection, p);
            if (isValid(neighbour_point) && getOrganism(neighbour_point) == null) {
                list.add(neighbour_point);
            }
        }
        return list;
    }

    // gets neighbour cells that are 2 cells away instead of 1
    public List<Point> getDeepNeighbourCells(Point p) {
        List<Point> list = new ArrayList<>();
        for (Point depthTwoNeighbourDirection : depth_two_neighbour_directions) {
            Point neighbour_point = addPoints(depthTwoNeighbourDirection, p);
            if (isValid(neighbour_point)) {
                list.add(neighbour_point);
            }
        }
        return list;
    }

    public Point findCell(Cell cell) {
        for (int i = 0; i < cells.length; ++i) {
            for (int j = 0; j < cells.length; ++j) {
                if (cells[i][j] == cell) {
                    return new Point(j, i);
                }
            }
        }

        return null;
    }

    public abstract Point getHumanPoint(Point human_point, int action);

    public Human getHuman() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (organisms[i][j] != null && organisms[i][j].getSpecies() == Species.HUMAN)
                    return (Human) organisms[i][j];
            }
        }
        return null;
    }

    public void resetIcons() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (isValid(new Point(j, i))) {
                    if (organisms[j][i] != null)
                        cells[j][i].setIcon(icons.getIcon(organisms[j][i].getSpecies()));
                    else
                        cells[j][i].setIcon(null);
                }
            }
        }
    }

}
