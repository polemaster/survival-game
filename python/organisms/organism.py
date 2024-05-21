from abc import ABC, abstractmethod


class Organism(ABC):
    def __init__(self, pos):
        self.strength = 0
        self.initiative = 0
        self.age = 0
        self.position = pos
        self.species = None

    @abstractmethod
    def make_action(self, grid):
        pass

    def collision(self, other_organism, is_attacking, grid):
        return False
