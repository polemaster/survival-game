import random


class Helpers:
    @staticmethod
    def is_lucky(percentage):
        return random.random() < percentage / 100

    # TO-DO:
    @staticmethod
    def get_random_point(points):
        return random.choice(points)
