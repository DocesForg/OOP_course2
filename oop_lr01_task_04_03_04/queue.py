# queue.py
# Программирование на языке высокого уровня (Python).
# Задание № 04.03.03. Вариант 21
#
# Выполнил: Мальцев Виталий Игоревич
# Группа: ПИЖ-б-о-23-2(2)

import json  # Импортируем модуль json для работы с JSON-форматом данных
from typing import List  # Импортируем List из модуля typing для аннотации типов

class Queue:
    """
    A class to represent a queue.
    """

    def __init__(self) -> None:
        """
        Initialize the Queue object with an empty list of items.
        """
        self.items: List[int] = []  # Инициализируем пустой список для хранения элементов очереди. Указываем, что элементы должны быть целыми числами.

    def __str__(self) -> str:
        """
        Return the string representation of the queue.

        :return: The string representation of the queue.
        """
        return "Queue: " + str(self.items)  # Возвращаем строковое представление очереди (Queue: [элементы])

    def enqueue(self, item: int) -> None:
        """
        Add an item to the end of the queue.

        :param item: The item to be added.
        """
        self.items.append(item)  # Добавляем элемент в конец списка (реализация enqueue - добавление в конец очереди)

    def dequeue(self):
        """
        Remove and return the first item from the queue.

        :return: The first item from the queue.
        """
        if not self.is_empty():  # Проверяем, не пуста ли очередь
            return self.items.pop(0)  # Удаляем и возвращаем первый элемент списка (реализация dequeue - удаление из начала очереди)
        return None  # Если очередь пуста, возвращаем None

    def is_empty(self) -> bool:
        """
        Check if the queue is empty.

        :return: True if the queue is empty, False otherwise.
        """
        return len(self.items) == 0  # Возвращаем True, если длина списка равна 0, иначе False (проверка на пустоту)

    def size(self) -> int:
        """
        Return the size of the queue.

        :return: The size of the queue.
        """
        return len(self.items)  # Возвращаем количество элементов в списке (размер очереди)

    @classmethod
    def from_string(cls, str_value: str) -> "Queue":
        """
        Create a queue from a string.

        :param str_value: The string representation of the queue.
        :return: The created queue.
        """
        items = json.loads(str_value)  # Преобразуем строку JSON в список элементов
        queue = cls()  # Создаем новый экземпляр класса Queue
        queue.items = items  # Присваиваем списку items нового экземпляра Queue полученный список items
        return queue  # Возвращаем созданную очередь

    def save(self, filename: str) -> None:
        """
        Save the queue to a file.

        :param filename: The name of the file to save the queue to.
        """
        with open(filename, 'w') as f:  # Открываем файл для записи ('w')
            json.dump(self.items, f)  # Записываем список элементов в файл в формате JSON

    def load(self, filename: str) -> None:
        """
        Load the queue from a file.

        :param filename: The name of the file to load the queue from.
        """
        with open(filename, 'r') as f:  # Открываем файл для чтения ('r')
            self.items = json.load(f)  # Загружаем список элементов из файла, интерпретируя содержимое как JSON

    def reverse(self) -> None:
        """
        Reverse the order of the items in the queue.
        """
        self.items.reverse()  # Изменяем порядок элементов в списке на обратный (изменяет исходный список)

    def __add__(self, other: 'Queue') -> 'Queue':
        """
        Add two queues together.

        :param other: The other queue to be added.
        :return: The new queue.
        """
        new_queue = Queue()  # Создаем новую очередь
        new_queue.items = self.items + other.items  # Объединяем списки items двух очередей и присваиваем их новому списку items
        return new_queue  # Возвращаем новую очередь, содержащую элементы обеих исходных очередей
