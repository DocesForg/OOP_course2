import random

# Абстракция: Абстрактный базовый класс для форм снежинок
class SnowflakeShape:
    """
    Абстрактный базовый класс для определения формы снежинки.
    """
    def __init__(self, size):
        """
        Инициализирует форму снежинки с заданным размером.

        :param size: int - Размер формы снежинки.
        """
        self.size = size

    def create_grid(self):
        """
        Абстрактный метод для создания матрицы, представляющей форму снежинки.
        Должен быть реализован в подклассах.

        :raises NotImplementedError: Если метод не реализован в подклассе.
        """
        raise NotImplementedError("Метод create_grid должен быть реализован в подклассе")

    def __call__(self):
        """
        Вызываемый метод для получения матрицы формы снежинки.

        :return: list[list[str]] - Матрица, представляющая форму снежинки.
        """
        return self.create_grid()


# Наследование: Конкретные классы форм снежинок, наследующие от SnowflakeShape
class SquareSnowflake(SnowflakeShape):
    """
    Реализует квадратную форму снежинки.
    """
    def create_grid(self):
        """
        Создает квадратную матрицу с '*' в центре по горизонтали и вертикали.

        :return: list[list[str]] - Квадратная матрица, представляющая снежинку.
        """
        grid = [[' ' for _ in range(self.size)] for _ in range(self.size)]
        mid = self.size // 2
        for i in range(self.size):
            grid[i][mid] = '*'
            grid[mid][i] = '*'
        return grid


class DiamondSnowflake(SnowflakeShape):
    """
    Реализует ромбовидную форму снежинки.
    """
    def create_grid(self):
        """
        Создает ромбовидную форму снежинки в матрице.

        :return: list[list[str]] - Матрица, представляющая ромбовидную снежинку.
        """
        grid = [[' ' for _ in range(self.size)] for _ in range(self.size)]
        mid = self.size // 2
        for i in range(self.size):
            for j in range(self.size):
                if abs(i - mid) + abs(j - mid) <= mid:
                    grid[i][j] = '*'
        return grid


# Композиция: Класс SnowFlake использует SnowflakeShape
class SnowFlake:
    """
    Представляет снежинку, используя композицию для определения формы.
    """
    def __init__(self, size, shape: SnowflakeShape):
        """
        Инициализирует снежинку с заданным размером и формой.

        :param size: int - Размер снежинки.
        :param shape: SnowflakeShape - Объект, определяющий форму снежинки.
        """
        if size % 2 == 0:
            raise ValueError("Размер должен быть нечетным числом")
        self.size = size
        self.__shape = shape  # Инкапсуляция: Защищенный атрибут
        self.grid = self.__shape()  # Используем вызываемый метод

    def show(self):
        """
        Отображает снежинку в консоли.
        """
        for row in self.grid:
            print(' '.join(row))

    #Полиморфизм, перегрузка метода __len__
    def __len__(self):
        """
        Перегрузка метода len() для возвращения размера снежинки.
        """
        return self.size

# Пример использования
size = 7
square_shape = SquareSnowflake(size)
diamond_shape = DiamondSnowflake(size)

# Создаем снежинки с разными формами
flake1 = SnowFlake(size, square_shape)
flake2 = SnowFlake(size, diamond_shape)

print("Квадратная снежинка:")
flake1.show()
print(f"Размер снежинки flake1: {len(flake1)}")

print("\nРомбовидная снежинка:")
flake2.show()
print(f"Размер снежинки flake2: {len(flake2)}")

# Пример использования вызываемого метода напрямую
print("\nВызываемый объект формы:")
SquareSnowflake(5).show()  #необходимо вызвать .show(), чтобы отобразить результат, тк create_grid возвращает список
#Результат вывода:
# Квадратная снежинка:
#   *   *   *
# * * * * * * *
#   *   *   *
#   *   *   *
# * * * * * * *
#   *   *   *
#   *   *   *
# Размер снежинки flake1: 7

# Ромбовидная снежинка:
#     *
#   * * *
# * * * * *
# * * * * *
# * * * * *
#   * * *
#     *
# Размер снежинки flake2: 7

# Вызываемый объект формы:
#   *   *   *
# * * * * *
#   *   *   *
#   *   *   *
# * * * * *
