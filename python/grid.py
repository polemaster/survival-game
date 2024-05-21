import copy
import random

from pygame.locals import (K_w, K_a, K_s, K_d)

from organisms.species import Species
from utils.point import Point


class Grid:
    neighbor_directions = [Point(-1, 0), Point(1, 0), Point(0, 1), Point(0, -1)]
    depth_two_neighbor_directions = [Point(-2, 0), Point(2, 0), Point(0, 2), Point(0, -2)]

    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.organisms = [[None] * width for _ in range(height)]

    def add_organism(self, organism):
        self.set_organism(organism.position, organism)

    def set_organism(self, pos, organism):
        self.organisms[pos.y][pos.x] = organism

    def get_organism(self, pos):
        if not self.is_valid(pos):
            return None
        return self.organisms[pos.y][pos.x]

    def is_valid(self, pos):
        if pos.x < 0 or pos.x >= self.width or pos.y < 0 or pos.y >= self.height:
            return False
        return True

    def get_new_human_position(self, human_point, key):
        new_point = copy.deepcopy(human_point)
        if key == K_a:
            new_point.translate(-1, 0)
        elif key == K_d:
            new_point.translate(1, 0)
        elif key == K_w:
            new_point.translate(0, -1)
        elif key == K_s:
            new_point.translate(0, 1)

        if self.is_valid(new_point) and new_point != human_point:
            return new_point
        return None

    def get_all_organisms(self):
        return [element for sublist in self.organisms for element in sublist if element is not None]

    def get_all_points(self):
        return [Point(j, i) for i in range(self.height) for j in range(self.width) if self.is_valid(Point(j, i))]

    def get_neighbor_cells(self, pos):
        return [neigh_dir + pos for neigh_dir in self.neighbor_directions if self.is_valid(neigh_dir + pos)]

    def get_deep_neighbor_cells(self, pos):
        return [neigh_dir + pos for neigh_dir in self.depth_two_neighbor_directions if self.is_valid(neigh_dir + pos)]

    def get_free_neighbor_cells(self, pos):
        return [neigh_dir + pos for neigh_dir in self.neighbor_directions if self.is_valid(neigh_dir + pos) and
                self.get_organism(neigh_dir + pos) is None]

    def get_human(self):
        for row in self.organisms:
            for organism in row:
                if organism and organism.species == Species.HUMAN:
                    return organism
        return None

    def get_closest_hogweed(self, position):
        min_dist = 10000000
        result_point = None

        def manhattan_distance(p1, p2):
            return abs(p1.x - p2.x) + abs(p1.y - p2.y)

        for i in range(self.height):
            for j in range(self.width):
                dist = manhattan_distance(Point(j, i), position)
                if dist < min_dist and self.get_organism(Point(j, i)) and self.get_organism(Point(j, i)).species == Species.SOSNOWSKYS_HOGWEED:
                    min_dist = dist
                    neighbors = self.get_neighbor_cells(position)
                    result_point = random.choice(list(filter(lambda x: manhattan_distance(x, Point(j, i)) < min_dist, neighbors)))
        return result_point
