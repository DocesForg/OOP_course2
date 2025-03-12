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
