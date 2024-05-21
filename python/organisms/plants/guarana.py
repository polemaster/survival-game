from gui.logger import Logger
from organisms.plants.plant import Plant
from organisms.species import Species


class Guarana(Plant):
    def __init__(self, pos):
        super().__init__(pos)
        self.species = Species.GUARANA

    def collision(self, other, attacking, grid):
        other.strength += 3
        Logger.log(other.species.name + ' gained 3 strength and ')
        return False
