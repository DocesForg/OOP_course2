# Класс-контейнер

Создайте класс-контейнер, который будет содержать набор объектов из предыдущей задачи.

№8 - Queue - Очередь -> QueueCollection - Коллекция очередей

Для класса-контейнера предусмотрите:
- специальные методы:
  - `__init__(self, ...)` - инициализация с необходимыми параметрами;
  - `__str__(self)` - представление объекта удобным для человека виде;
  - `__getitem__()` - индексация и срез для класса-контейнера
- поля, методы, свойства:
  - поле `_data` - содержит набор данных;
  - метод `add(self, value)` - добавляет элемент value в контейнер;
  - метод `remove(self, index)` - удаляет элемент из контейнера по индексу index;
  - метод `save(self, filename)` - сохраняет объект в JSON-файл filename;
  - метод `load(self, filename)` - загружает объект из JSON-файл filename;

```PYTHON
# main.py
# Программирование на языке высокого уровня (Python).
# Задание № 04.03.05. Вариант 8
#
# Выполнил: Мальцев Виталий Игоревич
# Группа: ПИЖ-б-о-23-2(2)

from queueCollection import QueueCollection  # Импортируем класс QueueCollection из файла queueCollection.py
from my_queue import Queue  # Импортируем класс Queue из файла my_queue.py

if __name__ == "__main__":  # Проверяем, является ли данный файл точкой входа в программу

    collection = QueueCollection()  # Создаем экземпляр класса QueueCollection

    queue1 = Queue()  # Создаем экземпляр класса Queue
    queue1.enqueue(1)  # Добавляем элемент 1 в очередь queue1
    queue1.enqueue(2)  # Добавляем элемент 2 в очередь queue1
    queue1.enqueue(3)  # Добавляем элемент 3 в очередь queue1
    collection.add(queue1)  # Добавляем очередь queue1 в коллекцию collection

    queue2 = Queue()  # Создаем экземпляр класса Queue
    queue2.enqueue(4)  # Добавляем элемент 4 в очередь queue2
    queue2.enqueue(5)  # Добавляем элемент 5 в очередь queue2
    collection.add(queue2)  # Добавляем очередь queue2 в коллекцию collection

    print(collection)  # Выводим содержимое коллекции collection (будет вызван метод __str__ класса QueueCollection)

    print("Queue at index 0:", collection[0])  # Выводим очередь, находящуюся по индексу 0 в коллекции (будет вызван метод __getitem__ класса QueueCollection)

    collection.remove(0)  # Удаляем элемент (очередь) по индексу 0 из коллекции collection
    print("After removing index 0:", collection)  # Выводим содержимое коллекции collection после удаления элемента

    collection.save("queues.json")  # Сохраняем коллекцию в файл queues.json (будет вызван метод save класса QueueCollection)

    new_collection = QueueCollection()  # Создаем новый экземпляр класса QueueCollection
    new_collection.load("queues.json")  # Загружаем коллекцию из файла queues.json (будет вызван метод load класса QueueCollection)
    print("Loaded collection:", new_collection)  # Выводим содержимое загруженной коллекции
```

```PYTHON
# queue.py
# Программирование на языке высокого уровня (Python).
# Задание № 04.03.05. Вариант 8
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

```PYTHON
#queueCollection.py
import json  # Импортируем модуль json для работы с JSON-форматом данных
from typing import List  # Импортируем List из модуля typing для аннотации типов
from my_queue import Queue  # Импортируем класс Queue из файла my_queue.py

class QueueCollection:
    """
    A container class for storing multiple Queue objects.
    """

    def __init__(self) -> None:
        """
        Initialize the QueueCollection object
        with an empty list of Queue objects.
        """
        self._data: List[Queue] = []  # Инициализируем приватный атрибут _data как пустой список для хранения объектов Queue

    def __str__(self) -> str:
        """
        Return the string representation of the queue collection.
        """
        return "QueueCollection: " + str([str(queue) for queue in self._data])  # Возвращаем строковое представление коллекции, отображая строковое представление каждой очереди

    def __getitem__(self, index: int) -> Queue:
        """
        Get the queue at the specified index.
        """
        return self._data[index]  # Возвращаем объект Queue по указанному индексу

    def add(self, value: Queue) -> None:
        """
        Add a Queue object to the collection.
        """
        self._data.append(value)  # Добавляем объект Queue в конец списка _data

    def remove(self, index: int) -> None:
        """
        Remove a Queue object from the collection by index.
        """
        if 0 <= index < len(self._data):  # Проверяем, находится ли индекс в пределах допустимого диапазона
            del self._data[index]  # Удаляем элемент (очередь) по указанному индексу

    def save(self, filename: str) -> None:
        """
        Save the collection to a JSON file.
        """
        with open(filename, 'w') as f:  # Открываем файл для записи
            json.dump([queue.items for queue in self._data], f)  # Записываем в файл JSON список, содержащий items каждой очереди

    def load(self, filename: str) -> None:
        """
        Load the collection from a JSON file.
        """
        with open(filename, 'r') as f:  # Открываем файл для чтения
            data = json.load(f)  # Загружаем данные из файла JSON
            self._data = [Queue.from_string(json.dumps(queue_items))
                          for queue_items in data]  # Создаем объекты Queue из загруженных данных и сохраняем их в _data
            # Используем Queue.from_string для создания объектов Queue из JSON-представления списка элементов queue_items
            # Предварительно преобразуя queue_items в строку JSON с помощью json.dumps

```
При выполнении задания необходимо построить UML-диаграмма классов приложения
<image src="image.png">