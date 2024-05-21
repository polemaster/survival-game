from organisms.animals.animal import Animal
from organisms.species import Species
from utils.helpers import Helpers


class Fox(Animal):
    def __init__(self, pos):
        super().__init__(pos)
        self.strength = 3
        self.initiative = 7
        self.species = Species.FOX

    def get_new_point(self, grid):
        neighbors = grid.get_neighbor_cells(self.position)
        final_neighbors = []
        for neighbor in neighbors:
            if (grid.get_organism(neighbor) is not None and grid.get_organism(neighbor).strength <= self.strength) or (grid.get_organism(neighbor) is None):
                final_neighbors.append(neighbor)
        if len(final_neighbors) > 0:
            return Helpers.get_random_point(final_neighbors)
        return None
