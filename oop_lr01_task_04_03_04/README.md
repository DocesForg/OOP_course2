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


from queue import Queue  # Импортируем класс Queue из файла queue.py.


if name == "__main__":  # Проверяем, является ли текущий файл точкой входа в программу.
    q1: Queue = Queue()  # Создаем экземпляр класса Queue и присваиваем его переменной q1.
    print("Создание очереди q1:")  # Выводим сообщение о создании очереди q1.
    q1.enqueue(1)  # Добавляем элемент 1 в очередь q1.
    q1.enqueue(2)  # Добавляем элемент 2 в очередь q1.
    q1.enqueue(3)  # Добавляем элемент 3 в очередь q1.
    print(q1)  # Выводим содержимое очереди q1.

    print("Размер очереди q1:", q1.size())  # Выводим размер очереди q1.

    q1.dequeue()  # Удаляем первый элемент из очереди q1.
    print("Очередь q1 после удаления первого элемента:")  # Выводим сообщение об удалении первого элемента.
    print(q1)  # Выводим содержимое очереди q1 после удаления элемента.

    q1.save("queue.json")  # Сохраняем содержимое очереди q1 в файл "queue.json".
    print("Очередь q1 сохранена в файл.")  # Выводим сообщение о сохранении очереди в файл.

    q2: Queue = Queue()  # Создаем экземпляр класса Queue и присваиваем его переменной q2.
    q2.load("queue.json")  # Загружаем содержимое очереди q2 из файла "queue.json".
    print("Очередь q2 после загрузки из файла:")  # Выводим сообщение о загрузке очереди из файла.
    print(q2)  # Выводим содержимое очереди q2 после загрузки из файла.

    q2.reverse()  # Переворачиваем очередь q2.
    print("Очередь q2 после переворота:")  # Выводим сообщение о перевороте очереди.
    print(q2)  # Выводим содержимое очереди q2 после переворота.

    q3: Queue = Queue()  # Создаем экземпляр класса Queue и присваиваем его переменной q3.
    q3.enqueue(4)  # Добавляем элемент 4 в очередь q3.
    q3.enqueue(5)  # Добавляем элемент 5 в очередь q3.
    print("Очередь q3:")  # Выводим сообщение об очереди q3.
    print(q3)  # Выводим содержимое очереди q3.

    q4: Queue = q2 + q3  # Складываем очереди q2 и q3 и присваиваем результат переменной q4.
    print("Очередь q4 (результат сложения q2 и q3):")  # Выводим сообщение о сложении очередей.
    print(q4)  # Выводим содержимое очереди q4 после сложения.

    str_value: str = '[10, 20, 30]'  # Определяем строковое представление очереди.
    q5: Queue = Queue.from_string(str_value)  # Создаем очередь q5 из строки str_value.
    print("Очередь q5 создана из строки:")  # Выводим сообщение о создании очереди из строки.
    print(q5)  # Выводим содержимое очереди q5.
```

```PYTHON
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
```
При выполнении задания необходимо построить UML-диаграмма классов приложения
<image src="image.png">
