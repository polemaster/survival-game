from gui.logger import Logger
from organisms.animals.animal import Animal
from organisms.species import Species
from utils.helpers import Helpers


class Antelope(Animal):
    def __init__(self, pos):
        super().__init__(pos)
        self.strength = 4
        self.initiative = 4
        self.species = Species.ANTELOPE

    def get_new_point(self, grid):
        far_neighbors = grid.get_deep_neighbor_cells(self.position)
        # when there are no cells at range 2, get the cells at range 1
        # this can for example happen when square grid is 3x3 and antelope is in the middle
        if len(far_neighbors) == 0:
            far_neighbors = grid.get_neighbor_cells(self.position)
        return Helpers.get_random_point(far_neighbors)

    def collision(self, other, attacking, grid):
        if Helpers.is_lucky(50):
            points = grid.get_free_neighbor_cells(self.position)
            if len(points) == 0:
                return False
            p = Helpers.get_random_point(points)
            old_position = self.position
            grid.set_organism(self.position, None)
            self.position = p
            grid.set_organism(self.position, self)
            Logger.log(f'Antelope escaped from the fight to: {self.position}')

            if not attacking:
                grid.set_organism(other.position, None)
                other.position = old_position
                grid.set_organism(old_position, other)
            return True
        return False
