"""The module contains a room class"""
from math import ceil


class WinDoor:
    """The class of windows and doors. The constructor
    takes width and length"""
    def __init__(self, x, y):
        self.square = x * y


class Room:
    """Room class. The constructor accepts width, length, and height."""
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        self.wd = []

    def add_wd(self, w, h):
        """A method for adding a window or door to a room"""
        self.wd.append(WinDoor(w, h))

    def work_surface(self):
        """A method for calculating the surface to be painted"""
        new_square = self.square()
        for i in self.wd:
            new_square = new_square - i.square
        return new_square

    def square(self):
        """A method for calculating the area of a room"""
        return 2 * self.z * (self.x + self.y)

    def roll_count(self, x, y):
        """The method that determines the number
        of rolls for wallpapering a room"""
        return ceil(self.work_surface() / (x*y))
