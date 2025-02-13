# Урок 10. Документирование кода.
## Практическая работа

Выполните полное документирование модуля, созданного в практической работе прошлого урока.


```PYTHON
#main.py
import room

r1 = room.Room(float(input("Введите ширину комнаты: ")),
               float(input("Введите длину комнаты: ")),
               float(input("Введите высоту комнаты: ")))
for i in range(int(input("Введите сумму окон и дверей в комнате: "))):
    r1.add_wd(float(input("Введите ширину окна или двери: ")),
              float(input("Ввдетие длину окна или двери: ")))
print(f"Площадь оклеиваемой поверхности: {r1.work_surface()}")
rolls = r1.roll_count(float(input("Введите ширину рулона обоев: ")),
                      float(input("Введите длину рулона обоев: ")))
print(f"Необходимое количество рулонов: {rolls}")
```
---
```PYTHON
#room.py
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
```