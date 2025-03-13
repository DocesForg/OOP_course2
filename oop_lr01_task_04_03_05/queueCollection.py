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