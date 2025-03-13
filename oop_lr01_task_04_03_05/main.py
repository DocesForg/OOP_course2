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