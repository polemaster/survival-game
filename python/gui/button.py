from utils.constants import BUTTON_COLOR, BUTTON_HOVER_COLOR, BUTTON_TEXT_COLOR
import pygame
import tkinter as tk
from tkinter import filedialog


class Button:
    def __init__(self, rect, txt, font):
        self.rect = rect
        self.txt = txt
        self.clicked = False
        self.font = font

    def draw(self, win):
        color = BUTTON_HOVER_COLOR if self.rect.collidepoint(pygame.mouse.get_pos()) else BUTTON_COLOR
        pygame.draw.rect(win, color, self.rect)
        txt_surf = self.font.render(self.txt, True, BUTTON_TEXT_COLOR)
        txt_rect = txt_surf.get_rect(center=(self.rect.x + self.rect.width // 2, self.rect.y + self.rect.height // 2))
        win.blit(txt_surf, txt_rect)

    def get_filename(self):
        root = tk.Tk()
        root.withdraw()
        if self.txt == 'Save game':
            file_name = filedialog.asksaveasfilename(defaultextension='.bin', parent=root)
        else:
            file_name = filedialog.askopenfilename(filetypes=[('Save Files', '*.bin')], parent=root)
        root.destroy()
        return file_name
