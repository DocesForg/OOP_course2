class SnowFlake:
    def __init__(self, size):
        """Инициализация снежинки с заданной стороной квадрата (нечетное число)."""
        if size % 2 == 0:  # Проверяем, что размер нечетный
            raise ValueError("Размер должен быть нечетным числом")
        self.size = size  # Сохраняем размер снежинки
        self.grid = self._create_initial_snowflake(size)  # Создаем начальную матрицу снежинки

    def _create_initial_snowflake(self, size):
        """Создает начальную снежинку в виде квадратной матрицы."""
        grid = [[' ' for _ in range(size)] for _ in range(size)]  # Создаем пустую матрицу
        mid = size // 2  # Определяем центральный индекс
        for i in range(size):
            grid[i][mid] = '*'  # Заполняем вертикальную линию звездочками
            grid[mid][i] = '*'  # Заполняем горизонтальную линию звездочками
        return grid  # Возвращаем готовую снежинку

    def thaw(self, steps=1):
        """Растапливает снежинку, удаляя крайние звездочки со всех сторон."""
        for _ in range(steps):  # Выполняем указанное количество шагов таяния
            if self.size <= 1:  # Если снежинка слишком мала, прекращаем процесс
                break
            self.size -= 2  # Уменьшаем размер снежинки на 2 (по 1 с каждой стороны)
            self.grid = [row[1:-1] for row in self.grid[1:-1]]  # Удаляем крайние ряды и столбцы

    def freeze(self, n=1):
        """Замораживает снежинку, увеличивая размер квадрата и добавляя звездочки."""
        for _ in range(n):  # Выполняем увеличение указанное количество раз
            self.size += 2  # Увеличиваем размер снежинки на 2 (по 1 с каждой стороны)
            new_grid = [[' ' for _ in range(self.size)] for _ in range(self.size)]  # Создаем новую пустую матрицу
            mid = self.size // 2  # Определяем новый центральный индекс
            for i in range(self.size):
                new_grid[i][mid] = '*'  # Восстанавливаем вертикальную линию
                new_grid[mid][i] = '*'  # Восстанавливаем горизонтальную линию
            self.grid = new_grid  # Обновляем снежинку

    def thicken(self):
        """Утолщает снежинку, добавляя параллельные линии звездочек."""
        new_grid = [[' ' for _ in range(self.size)] for _ in range(self.size)]  # Создаем пустую матрицу
        for i in range(self.size):
            for j in range(self.size):
                if self.grid[i][j] == '*':  # Если текущая ячейка содержит '*'
                    new_grid[i][j] = '*'  # Копируем звездочку
                    if i > 0:
                        new_grid[i - 1][j] = '*'  # Добавляем звездочку сверху
                    if i < self.size - 1:
                        new_grid[i + 1][j] = '*'  # Добавляем звездочку снизу
                    if j > 0:
                        new_grid[i][j - 1] = '*'  # Добавляем звездочку слева
                    if j < self.size - 1:
                        new_grid[i][j + 1] = '*'  # Добавляем звездочку справа
        self.grid = new_grid  # Обновляем снежинку

    def show(self):
        """Отображает снежинку в консоли."""
        for row in self.grid:  # Перебираем строки матрицы
            print(' '.join(row))  # Выводим строку с пробелами между символами


# Пример использования
flake = SnowFlake(5)  # Создаем снежинку размером 5x5
flake.show()  # Отображаем начальную снежинку
print("\nПосле утолщения:")
flake.thicken()  # Утолщаем снежинку
flake.show()
print("\nПосле заморозки (увеличения):")
flake.freeze(1)  # Увеличиваем снежинку
flake.show()
print("\nПосле таяния:")
flake.thaw(1)  # Уменьшаем снежинку
flake.show()