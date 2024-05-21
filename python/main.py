import pygame
from world import World


def main():
    pygame.init()
    world = World()

    world.init()
    world.play()

    pygame.quit()


if __name__ == '__main__':
    main()
