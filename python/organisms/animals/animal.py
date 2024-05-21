import copy
from abc import abstractmethod

import world
from gui.logger import Logger

from organisms.organism import Organism
from utils.helpers import Helpers


class Animal(Organism):
    @abstractmethod
    def __init__(self, pos):
        super().__init__(pos)

    def make_action(self, grid):
        new_point = copy.deepcopy(self.get_new_point(grid))
        if new_point is None:
            return

        Logger.log(self.species.name + f' tried to move to: {new_point}')
        if grid.get_organism(new_point) is None:
            Logger.log_add_to_prev(' and moved')
            grid.set_organism(self.position, None)
            self.position = new_point
            grid.set_organism(self.position, self)
        elif grid.get_organism(new_point).species == self.species:
            Logger.log_add_to_prev(' and reproduced at: ')
            self.reproduce(new_point, grid)
        else:
            Logger.log_add_to_prev(' and collided with: ' + grid.get_organism(new_point).species.name + ' ---> ')
            self.handle_collision(new_point, grid)

    def get_new_point(self, grid):
        neighbors = grid.get_neighbor_cells(self.position)
        return Helpers.get_random_point(neighbors)

    def reproduce(self, new_point, grid):
        dest = self.get_random_free_adjacent_point(self.position, new_point, grid)
        if dest is None:
            Logger.log_add_to_prev('None')
            return

        Logger.log_add_to_prev(str(dest))

        world.World.create_organism(self.species, dest, grid)

    def handle_collision(self, other_org_point, grid):
        other_org = grid.get_organism(other_org_point)
        # make the collision of current organism with the other
        collided = self.collision(other_org, True, grid)
        # if the other organism survived, make his collision
        if not collided:
            collided = other_org.collision(self, False, grid)

        # if nothing important happened, make the default collision
        if not collided:
            if self.strength >= other_org.strength:
                Logger.log_add_to_prev(self.species.name + ' killed ' + other_org.species.name)
                grid.set_organism(self.position, None)
                self.position = other_org_point
                grid.set_organism(self.position, self)
            else:
                Logger.log_add_to_prev(other_org.species.name + ' killed ' + self.species.name)
                grid.set_organism(self.position, None)

    @staticmethod
    def get_random_free_adjacent_point(point1, point2, grid):
        neighbors1 = set(grid.get_free_neighbor_cells(point1))
        neighbors2 = set(grid.get_free_neighbor_cells(point2))
        neighbors_union = neighbors1.union(neighbors2)

        if len(neighbors_union) == 0:
            return None

        return Helpers.get_random_point(list(neighbors_union))
