from gui.logger import Logger
from organisms.animals.animal import Animal
from organisms.species import Species
from utils.helpers import Helpers


class Turtle(Animal):
    def __init__(self, pos):
        super().__init__(pos)
        self.strength = 2
        self.initiative = 1
        self.species = Species.TURTLE

    def get_new_point(self, grid):
        if Helpers.is_lucky(75):
            return None
        return super().get_new_point(grid)

    def collision(self, other, attacking, grid):
        if other.strength < 5 and not attacking:
            Logger.log('Turtle reflected attack from: ' + other.species.name)
            return True
        return False
