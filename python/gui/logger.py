from utils.constants import LOGS_Y, LOGS_SPACE, LOGS_X


class Logger:
    screen = None
    font = None
    color = None
    text_list = []

    @staticmethod
    def initialize(screen, font, color):
        Logger.screen = screen
        Logger.font = font
        Logger.color = color

    @staticmethod
    def log(text):
        Logger.text_list.append(text)

    @staticmethod
    def log_add_to_prev(text):
        Logger.text_list[-1] = Logger.text_list[-1] + text

    @staticmethod
    def display_logs():
        y = LOGS_Y
        for text in Logger.text_list:
            text_surface = Logger.font.render(text, True, Logger.color)
            Logger.screen.blit(text_surface, (LOGS_X, y))
            y += Logger.font.get_height() + LOGS_SPACE
            Logger.clear()

    @staticmethod
    def clear():
        Logger.text_list = []
