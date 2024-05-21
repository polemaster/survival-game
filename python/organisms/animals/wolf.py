from organisms.animals.animal import Animal
from organisms.species import Species


class Wolf(Animal):
    def __init__(self, pos):
        super().__init__(pos)
        self.strength = 9
        self.initiative = 5
        self.species = Species.WOLF
