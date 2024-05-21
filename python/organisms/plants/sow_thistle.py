from organisms.plants.plant import Plant
from organisms.species import Species


class SowThistle(Plant):
    def __init__(self, pos):
        super().__init__(pos)
        self.species = Species.SOW_THISTLE

    def make_action(self, grid):
        for _ in range(3):
            super().make_action(grid)
