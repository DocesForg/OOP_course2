# Простой класс

Выберите класс под номером № (Таблица 1), где № Ваш порядковый номер в журнале. При превышении порядка номера отчет ведется сначала по циклу.

№8 - Queue - Очередь

Прежде чем перейти к написанию кода:
- Изучите предметную область объекта и доступные операции;
- для каждого поля и метода придумайте его области видимости, а также необходимость использования свойств.

При реализации класс должен содержать:
- специальные методы:
    - `__init__(self, ...)` - инициализация с необходимыми параметрами;
    - `__str__(self)` - представление объекта в удобном для человека виде; 
    - специальные методы для возможности сложения, разности и прочих операций, которые класс должен поддерживать;
- методы класса:
    - `from_string(cls, str_value)` - создает объект на основании строки str_value;
- поля, методы, свойства:
    - поля, необходимые для выбранного класса;
    - метод `save(self, filename)` - сохраняет объект в JSON-файл filename
    - метод `load(self, filename)` - загружает объект из JSON-файла filename;
    - прочие методы (не менее 3-х) и свойства, выявленные на этапе изучения класса.

Реализуйте класс в отдельном модуле, а также создайте main.py, который бы тестировал все его возможности

```PYTHON
# main.py
# Программирование на языке высокого уровня (Python).
# Задание № 04.03.03. Вариант 21
#
# Выполнил: Мальцев Виталий Игоревич
# Группа: ПИЖ-б-о-23-2(2)


from queue import Queue


if __name__ == "__main__":
    q1: Queue = Queue()
    print("Создание очереди q1:")
    q1.enqueue(1)
    q1.enqueue(2)
    q1.enqueue(3)
    print(q1)

    print("Размер очереди q1:", q1.size())

    q1.dequeue()
    print("Очередь q1 после удаления первого элемента:")
    print(q1)

    q1.save("queue.json")
    print("Очередь q1 сохранена в файл.")

    q2: Queue = Queue()
    q2.load("queue.json")
    print("Очередь q2 после загрузки из файла:")
    print(q2)

    q2.reverse()
    print("Очередь q2 после переворота:")
    print(q2)

    q3: Queue = Queue()
    q3.enqueue(4)
    q3.enqueue(5)
    print("Очередь q3:")
    print(q3)

    q4: Queue = q2 + q3
    print("Очередь q4 (результат сложения q2 и q3):")
    print(q4)

    str_value: str = '[10, 20, 30]'
    q5: Queue = Queue.from_string(str_value)
    print("Очередь q5 создана из строки:")
    print(q5)
```

```PYTHON
# queue.py
# Программирование на языке высокого уровня (Python).
# Задание № 04.03.03. Вариант 21
#
# Выполнил: Мальцев Виталий Игоревич
# Группа: ПИЖ-б-о-23-2(2)

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
```
При выполнении задания необходимо построить UML-диаграмма классов приложения
<image src="image.png">