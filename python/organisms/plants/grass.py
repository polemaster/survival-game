from organisms.plants.plant import Plant
from organisms.species import Species


class Grass(Plant):
    def __init__(self, pos):
        super().__init__(pos)
        self.species = Species.GRASS
