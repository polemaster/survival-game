import pygame

from utils.constants import *
from gui.button import Button
from gui.logger import Logger
from organisms.species import Species


class Display:
    def __init__(self, grid_map):
        pygame.display.set_caption('Game simulator')
        self.screen = pygame.display.set_mode([SCREEN_WIDTH, SCREEN_HEIGHT])
        self.icons = []
        self.button_font = pygame.font.SysFont(BUTTON_FONT_TYPE, BUTTON_FONT_SIZE)
        self.load_button = Button(pygame.Rect(LOAD_BUTTON_X, LOAD_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT), 'Load game',
                                  self.button_font)
        self.save_button = Button(pygame.Rect(SAVE_BUTTON_X, SAVE_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT), 'Save game',
                                  self.button_font)
        self.grid_map = grid_map
        self.logger_font = pygame.font.SysFont(LOGGER_FONT_TYPE, LOGGER_FONT_SIZE)
        Logger.initialize(self.screen, self.logger_font, LOGGER_TEXT_COLOR)
        self.choose_menu_font = pygame.font.SysFont(CHOOSE_MENU_TYPE, CHOOSE_MENU_SIZE)
        self.screen.fill(BG_COLOR)

    def update(self, grid):
        # display board
        self.grid_map.draw(self.screen, grid)

        # display buttons
        self.load_button.draw(self.screen)
        self.save_button.draw(self.screen)

        pygame.display.flip()

    def clear(self):
        self.screen.fill(BG_COLOR)

    def display_choose_surf(self):
        texts = ['CHOOSE ONE OPTION:']
        for org_species in Species:
            if org_species.value == 0:
                continue
            elif org_species.value == 10:
                texts.append('U: ' + org_species.name)
            elif org_species.value == 11:
                texts.append('I: ' + org_species.name)
            else:
                texts.append(str(org_species.value) + ': ' + org_species.name)

        rect = pygame.Rect(CHOOSE_MENU_X, CHOOSE_MENU_Y, CHOOSE_MENU_WIDTH, CHOOSE_MENU_HEIGHT)
        pygame.draw.rect(self.screen, CHOOSE_MENU_COLOR, rect)

        line_height = self.choose_menu_font.get_height()
        y = rect.y + 10
        for txt in texts:
            text_surface = self.choose_menu_font.render(txt, True, CHOOSE_MENU_TEXT_COLOR)
            text_rect = text_surface.get_rect(topleft=(rect.x + 10, y))
            self.screen.blit(text_surface, text_rect)
            y += line_height + CHOOSE_MENU_SPACE
