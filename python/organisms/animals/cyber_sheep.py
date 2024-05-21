from organisms.animals.animal import Animal
from organisms.species import Species


class CyberSheep(Animal):
    def __init__(self, pos):
        super().__init__(pos)
        self.strength = 11
        self.initiative = 4
        self.species = Species.CYBER_SHEEP

    def get_new_point(self, grid):
        new_point = grid.get_closest_hogweed(self.position)
        if new_point is None:
            return super().get_new_point(grid)
        return new_point
