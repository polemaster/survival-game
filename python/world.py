import pickle
import random

import pygame
from pygame.locals import *

from utils.constants import GRID_HEIGHT, GRID_WIDTH
from gui.display import Display
from grid import Grid
from gui.grid_map import GridMap
from gui.logger import Logger
from organisms.species import Species

from organisms.animals import Human, Wolf, Sheep, Fox, Turtle, Antelope, CyberSheep
from organisms.plants import Grass, SowThistle, Guarana, Belladonna, SosnowskysHogweed
from utils.point import Point


class World:
    VALID_KEYS = (K_a, K_w, K_s, K_d)

    @staticmethod
    def create_organism(species, position, grid):
        organism = None
        match species:
            case Species.HUMAN:
                organism = Human(position)
            case Species.WOLF:
                organism = Wolf(position)
            case Species.SHEEP:
                organism = Sheep(position)
            case Species.FOX:
                organism = Fox(position)
            case Species.TURTLE:
                organism = Turtle(position)
            case Species.ANTELOPE:
                organism = Antelope(position)
            case Species.CYBER_SHEEP:
                organism = CyberSheep(position)
            case Species.GRASS:
                organism = Grass(position)
            case Species.SOW_THISTLE:
                organism = SowThistle(position)
            case Species.GUARANA:
                organism = Guarana(position)
            case Species.BELLADONNA:
                organism = Belladonna(position)
            case Species.SOSNOWSKYS_HOGWEED:
                organism = SosnowskysHogweed(position)

        grid.add_organism(organism)

    def __init__(self):
        self.turn = 1
        self.grid = Grid(GRID_WIDTH, GRID_HEIGHT)
        self.grid_map = GridMap(self.grid)
        self.screen = Display(self.grid_map)
        self.unoccupied_points = self.grid.get_all_points()
        self.player = Human(self.pop_random_point())

    def init(self):
        self.grid.add_organism(self.player)

        self.add_organism(Species.SOSNOWSKYS_HOGWEED)
        self.add_organism(Species.SOSNOWSKYS_HOGWEED)
        self.add_organism(Species.SOSNOWSKYS_HOGWEED)
        self.add_organism(Species.SOSNOWSKYS_HOGWEED)
        self.add_organism(Species.SOSNOWSKYS_HOGWEED)
        self.add_organism(Species.CYBER_SHEEP)
        self.add_organism(Species.CYBER_SHEEP)
        # self.add_each_organism()

    def add_each_organism(self):
        [self.add_organism(species) for species in Species if species != Species.HUMAN]

    def add_organism(self, species):
        self.create_organism(species, self.pop_random_point(), self.grid)

    def pop_random_point(self):
        if len(self.unoccupied_points) == 0:
            return None
        index = random.randrange(len(self.unoccupied_points))
        return self.unoccupied_points.pop(index)

    def save_file(self, filename):
        data = [self.grid, self.turn]
        with open(filename, 'wb') as file:
            pickle.dump(data, file)

            self.screen.clear()
            Logger.log('Saved successfully to: ' + filename)
            Logger.display_logs()

    def load_file(self, filename):
        with open(filename, 'rb') as file:
            game_state = pickle.load(file)
            self.grid = game_state[0]
            self.turn = game_state[1]
            self.player = self.grid.get_human()
            self.grid_map = GridMap(self.grid)
            self.screen = Display(self.grid_map)

            Logger.clear()
            self.screen.clear()

            Logger.log('Loaded successfully from: ' + filename)
            Logger.display_logs()

    def play(self):
        clock = pygame.time.Clock()

        running = True
        reading_new_org = False
        new_org_keys = {K_1: 1, K_2: 2, K_3: 3, K_4: 4, K_5: 5, K_6: 6, K_7: 7, K_8: 8, K_9: 9, K_u: 10, K_i: 11}
        cell = None

        while running:
            # for making action with human
            key = None
            filename_load = ''
            filename_save = ''
            # for clicking buttons and cells
            mouse_pos = pygame.mouse.get_pos()
            for event in pygame.event.get():
                if event.type == KEYDOWN and event.key == K_ESCAPE:
                    running = False
                elif event.type == QUIT:
                    running = False
                elif event.type == KEYUP:
                    key = event.key
                    if reading_new_org and key in new_org_keys.keys():
                        if self.grid.get_organism(Point(*cell)) is not None:
                            Logger.log('Cell already occupied')
                        else:
                            self.create_organism(Species(new_org_keys[key]), Point(*cell), self.grid)
                            Logger.log('Added new organism: ' + Species(new_org_keys[key]).name)
                        self.screen.clear()
                        Logger.display_logs()
                        reading_new_org = False
                elif event.type == MOUSEBUTTONDOWN and event.button == 1:
                    for button in (self.screen.load_button, self.screen.save_button):
                        if button.rect.collidepoint(mouse_pos):
                            button.clicked = True
                        else:
                            button.clicked = False
                elif event.type == MOUSEBUTTONUP and event.button == 1:
                    if self.screen.save_button.clicked:
                        filename_save = self.screen.save_button.get_filename()
                    elif self.screen.load_button.clicked:
                        filename_load = self.screen.load_button.get_filename()
                    cell = self.grid_map.get_clicked_cell(mouse_pos, self.grid)
                    if cell:
                        self.screen.display_choose_surf()
                        reading_new_org = True

            if len(filename_load) > 0:
                self.load_file(filename_load)
            elif len(filename_save) > 0:
                self.save_file(filename_save)
            # Make move for all organisms if the valid key was pressed
            elif key in type(self).VALID_KEYS:
                reading_new_org = False
                self.screen.clear()
                Logger.log('turn: ' + str(self.turn))
                organisms = sorted(self.grid.get_all_organisms(), key=lambda x: (x.initiative, x.age), reverse=True)
                self.player.update(key, self.grid, self.turn)
                for organism in organisms:
                    if organism is not None and self.grid.get_organism(organism.position) == organism:
                        organism.make_action(self.grid)

                Logger.display_logs()
                self.turn += 1

                if self.grid.get_organism(self.player.position) is not self.player:
                    running = False
            elif key == K_r:
                self.screen.clear()
                self.player.activate_ability(self.turn)
                Logger.display_logs()

            self.screen.update(self.grid)

            clock.tick(60)
