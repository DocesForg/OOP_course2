# main.py
# Программирование на языке высокого уровня (Python).
# Задание № 04.03.06. Вариант 8
#
# Выполнил: Мальцев Виталий Игоревич
# Группа: ПИЖ-б-о-23-2(2)


from transport import WaterTransport, WheeledTransport, Car  # Импортируем классы WaterTransport, WheeledTransport и Car из файла transport.py

if __name__ == "__main__":  # Проверяем, является ли данный файл точкой входа в программу

    boat = WaterTransport(speed=30, capacity=10, water_type="река")  # Создаем экземпляр класса WaterTransport с указанными параметрами
    bike = WheeledTransport(speed=20, capacity=1, wheels=2)  # Создаем экземпляр класса WheeledTransport с указанными параметрами
    car = Car(speed=120, capacity=5, fuel_type="бензин")  # Создаем экземпляр класса Car с указанными параметрами

    print(boat)  # Выводим информацию об объекте boat (будет вызван метод __str__)
    boat.move()  # Вызываем метод move для объекта boat
    boat.stop()  # Вызываем метод stop для объекта boat

    print("\n" + str(bike))  # Выводим информацию об объекте bike (будет вызван метод __str__)
    bike.move()  # Вызываем метод move для объекта bike
    bike.stop()  # Вызываем метод stop для объекта bike

    print("\n" + str(car))  # Выводим информацию об объекте car (будет вызван метод __str__)
    car.move()  # Вызываем метод move для объекта car
    car.honk()  # Вызываем метод honk для объекта car
    car.stop()  # Вызываем метод stop для объекта car