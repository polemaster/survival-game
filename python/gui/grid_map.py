import pygame

from utils.constants import *
from organisms.species import Species
from utils.point import Point


class GridMap:
    def __init__(self, grid):
        self.height = grid.height * CELL_SIZE
        self.width = grid.width * CELL_SIZE
        self.icons = self.load_icons()
        self.cells = [[None] * GRID_WIDTH for _ in range(GRID_HEIGHT)]
        for row in range(grid.height):
            for col in range(grid.width):
                rect = pygame.Rect(BOARD_X + col * CELL_SIZE, BOARD_Y + row * CELL_SIZE, CELL_SIZE, CELL_SIZE)
                self.cells[row][col] = rect

    def get_clicked_cell(self, mouse_pos, grid):
        for i in range(grid.height):
            for j in range(grid.width):
                if self.cells[i][j].collidepoint(mouse_pos):
                    return j, i  # (x, y)
        return None

    def draw(self, screen, grid):
        # fill the board with white (to erase the previous one)
        pygame.draw.rect(screen, BOARD_COLOR, (BOARD_X, BOARD_Y, self.width, self.height))
        for i in range(grid.height):
            for j in range(grid.width):
                organism = grid.get_organism(Point(j, i))
                pygame.draw.rect(screen, CELL_BORDER_COLOR, self.cells[i][j], width=1)
                if organism:
                    new_x = self.cells[i][j].x + (self.cells[i][j].width - self.icons[organism.species].get_width()) / 2
                    new_y = self.cells[i][j].y + (self.cells[i][j].height - self.icons[organism.species].get_height()) / 2
                    screen.blit(self.icons[organism.species], (new_x, new_y))

    def load_icons(self):
        icons = dict()
        icons[Species.HUMAN] = self.load_icon('img/human.png', 0.02)
        icons[Species.WOLF] = self.load_icon('img/wolf.png', 0.035)
        icons[Species.SHEEP] = self.load_icon('img/sheep.png', 0.09)
        icons[Species.FOX] = self.load_icon('img/fox.png', 0.045)
        icons[Species.TURTLE] = self.load_icon('img/turtle.png', 0.08)
        icons[Species.ANTELOPE] = self.load_icon('img/antelope.png', 0.044)
        icons[Species.CYBER_SHEEP] = self.load_icon('img/cyber_sheep.png', 0.043)
        icons[Species.GRASS] = self.load_icon('img/grass.png', 0.16)
        icons[Species.SOW_THISTLE] = self.load_icon('img/sow_thistle.png', 0.07)
        icons[Species.GUARANA] = self.load_icon('img/guarana.png', 0.11)
        icons[Species.BELLADONNA] = self.load_icon('img/belladonna.png', 0.07)
        icons[Species.SOSNOWSKYS_HOGWEED] = self.load_icon('img/sosnowskys_hogweed.png', 0.13)
        return icons

    def load_icon(self, path, scale):
        image = pygame.image.load(path)
        scaled_image = pygame.transform.scale(image, (image.get_width() * scale * SCALE, image.get_height() * scale * SCALE))
        return scaled_image
