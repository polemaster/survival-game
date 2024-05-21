from gui.logger import Logger
from organisms.animals import CyberSheep
from organisms.animals.animal import Animal
from organisms.plants.plant import Plant
from organisms.species import Species


class SosnowskysHogweed(Plant):
    def __init__(self, pos):
        super().__init__(pos)
        self.strength = 10
        self.species = Species.SOSNOWSKYS_HOGWEED

    def collision(self, other, attacking, grid):
        if other.species != Species.CYBER_SHEEP:
            grid.set_organism(other.position, None)
            Logger.log("Sosnowsky's hogweed killed " + other.species.name)
            return True
        return False

    def make_action(self, grid):
        # kill all adjacent organisms
        neighbors = grid.get_neighbor_cells(self.position)
        for neighbor in neighbors:
            if neighbor is not None and isinstance(grid.get_organism(neighbor), Animal) and not isinstance(grid.get_organism(neighbor), CyberSheep):
                Logger.log("Sosnowsky's hogweed killed " + grid.get_organism(neighbor).species.name)
                grid.set_organism(neighbor, None)
        super().make_action(grid)
