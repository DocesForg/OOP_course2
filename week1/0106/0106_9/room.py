from math import ceil


class WinDoor:
    def __init__(self, x, y):
        self.square = x * y


class Room:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        self.wd = []

    def add_wd(self, w, h):
        self.wd.append(WinDoor(w, h))

    def work_surface(self):
        new_square = self.square()
        for i in self.wd:
            new_square = new_square - i.square
        return new_square

    def square(self):
        return 2 * self.z * (self.x + self.y)

    def roll_count(self, x, y):
        return ceil(self.work_surface() / (x*y))
