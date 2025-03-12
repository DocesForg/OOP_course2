# queue.py
# Программирование на языке высокого уровня (Python).
# Задание № 04.03.03. Вариант 8
#
# Выполнил: Черников Дмитрий Дмитриевич
# Группа: ПИЖ-б-о-23-2(1)
# E-mail: dima.chernikov.053@mail.ru
import json
from typing import List


class Queue:
    """
    A class to represent a queue.
    """

    def __init__(self) -> None:
        """
        Initialize the Queue object with an empty list of items.
        """
        self.items: List[int] = []

    def __str__(self) -> str:
        """
        Return the string representation of the queue.

        :return: The string representation of the queue.
        """
        return "Queue: " + str(self.items)

    def enqueue(self, item: int) -> None:
        """
        Add an item to the end of the queue.

        :param item: The item to be added.
        """
        self.items.append(item)

    def dequeue(self):
        """
        Remove and return the first item from the queue.

        :return: The first item from the queue.
        """
        if not self.is_empty():
            return self.items.pop(0)
        return None

    def is_empty(self) -> bool:
        """
        Check if the queue is empty.

        :return: True if the queue is empty, False otherwise.
        """
        return len(self.items) == 0

    def size(self) -> int:
        """
        Return the size of the queue.

        :return: The size of the queue.
        """
        return len(self.items)

    @classmethod
    def from_string(cls, str_value: str) -> "Queue":
        """
        Create a queue from a string.

        :param str_value: The string representation of the queue.
        :return: The created queue.
        """
        items = json.loads(str_value)
        queue = cls()
        queue.items = items
        return queue

    def save(self, filename: str) -> None:
        """
        Save the queue to a file.

        :param filename: The name of the file to save the queue to.
        """
        with open(filename, 'w') as f:
            json.dump(self.items, f)

    def load(self, filename: str) -> None:
        """
        Load the queue from a file.

        :param filename: The name of the file to load the queue from.
        """
        with open(filename, 'r') as f:
            self.items = json.load(f)

    def reverse(self) -> None:
        """
        Reverse the order of the items in the queue.
        """
        self.items.reverse()

    def __add__(self, other: 'Queue') -> 'Queue':
        """
        Add two queues together.

        :param other: The other queue to be added.
        :return: The new queue.
        """
        new_queue = Queue()
        new_queue.items = self.items + other.items
        return new_queue
