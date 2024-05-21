from organisms.animals.animal import Animal
from organisms.species import Species


class Sheep(Animal):
    def __init__(self, pos):
        super().__init__(pos)
        self.strength = 4
        self.initiative = 4
        self.species = Species.SHEEP
