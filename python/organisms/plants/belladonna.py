from gui.logger import Logger
from organisms.plants.plant import Plant
from organisms.species import Species


class Belladonna(Plant):
    def __init__(self, pos):
        super().__init__(pos)
        self.strength = 99
        self.species = Species.BELLADONNA

    def collision(self, other, attacking, grid):
        Logger.log('Belladonna killed ' + other.species.name + ' at: ' + str(other.position))
        grid.set_organism(other.position, None)
        return True
