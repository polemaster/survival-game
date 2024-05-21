from gui.logger import Logger
from organisms.animals.animal import Animal
from organisms.species import Species
from utils.helpers import Helpers


class Human(Animal):
    def __init__(self, pos):
        super().__init__(pos)
        self.strength = 5
        self.initiative = 4
        self.species = Species.HUMAN
        self.last_ability = -10
        self.action = 0
        self.new_position = self.position
        self.ability_on = False

    def update(self, key, grid, turn):
        self.new_position = grid.get_new_human_position(self.position, key)
        if self.ability_on and turn > self.last_ability + 5:
            self.ability_on = False

    def activate_ability(self, turn):
        if self.last_ability + 10 <= turn:
            self.ability_on = True
            self.last_ability = turn
            Logger.log("Human used ability Alzur's shield")

    def get_new_point(self, grid):
        return self.new_position

    def collision(self, other, attacking, grid):
        if not attacking and self.ability_on:
            neighbors = grid.get_free_neighbor_cells(other.position)
            if len(neighbors) > 0:
                new_point = Helpers.get_random_point(neighbors)
                Logger.log('Human deterred ' + other.species.name + ' and it moved to: ' + str(new_point))
                grid.set_organism(other.position, None)
                other.position = new_point
                grid.set_organism(new_point, other)
            else:
                Logger.log('Human deterred ' + other.species.name + " and it didn't move (no free space)")
            return True
        return False
