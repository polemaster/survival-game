from abc import abstractmethod

from gui.logger import Logger
from organisms.organism import Organism
from utils.helpers import Helpers
import world


class Plant(Organism):
    @abstractmethod
    def __init__(self, pos):
        super().__init__(pos)

    def make_action(self, grid):
        if Helpers.is_lucky(3):
            points = grid.get_free_neighbor_cells(self.position)
            if len(points) == 0:
                return
            new_point = Helpers.get_random_point(points)
            world.World.create_organism(self.species, new_point, grid)
            Logger.log(self.species.name + ' spread to: ' + str(new_point))
