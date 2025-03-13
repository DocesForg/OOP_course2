# Иерархия классов

Выберите класс под номером №, где № Ваш порядковый номер в журнале.

№8 = №3 - ТранспортноеСредство, ВодноеТС, КолесноеТС, Автомобиль

Методы базового класса - ехать()

Далее:

- выстройте классы в иерархию, продумайте их общие и отличительные характеристики и действия;
- добавьте собственную реализацию методов базового класса в каждый из классов. предусмотрев:
  - необходимые параметры для базовых методов
  - необходимые поля для функционирования базовых методов
  - вывод на экран работы метода
- по желанию добавьте собственные методы в классы иерархии



```PYTHON
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
```

```PYTHON
# transport.py
# Программирование на языке высокого уровня (Python).
# Задание № 04.03.06. Вариант 8
#
# Выполнил: Мальцев Виталий Игоревич
# Группа: ПИЖ-б-о-23-2(2)

from abc import ABC, abstractmethod  # Импортируем ABC (Abstract Base Class) и abstractmethod из модуля abc

class Transport(ABC):
    """
    An abstract base class to represent a transport.
    """

    def __init__(self, speed: float, capacity: int) -> None:
        """
        Initialize the Transport object with a speed and capacity.

        :param speed: The speed of the transport.
        :param capacity: The capacity of the transport.
        """
        self.speed: float = speed  # Инициализируем атрибут speed (скорость)
        self.capacity: int = capacity  # Инициализируем атрибут capacity (вместимость)

    @abstractmethod
    def move(self) -> None:
        """
        Move the transport.
        """
        pass  # Абстрактный метод move, который должен быть реализован в подклассах

    def stop(self) -> None:
        """
        Stop the transport.
        """
        print(f"{self.__class__.__name__}: Остановился.")  # Выводим сообщение об остановке транспорта (название класса)

    def __str__(self) -> str:
        """
        Return the string representation of the transport.

        :return: The string representation of the transport.
        """
        return (f"{self.__class__.__name__}:"  # Возвращаем строку с информацией о транспорте (название класса)
                f"скорость={self.speed}, вместимость={self.capacity}")  # Добавляем информацию о скорости и вместимости

class WaterTransport(Transport):
    """
    A class to represent a water transport.
    """

    def __init__(self, speed: float, capacity: int, water_type: str) -> None:
        """
        Initialize the WaterTransport object with a speed,
        capacity, and water type.

        :param speed: The speed of the water transport.
        :param capacity: The capacity of the water transport.
        :param water_type: The type of water the water transport is on.
        """
        super().__init__(speed, capacity)  # Вызываем конструктор базового класса Transport
        self.water_type: str = water_type  # Инициализируем атрибут water_type (тип воды)

    def move(self) -> None:
        """
        Move the water transport.
        """
        print(f"{self.__class__.__name__}: Плывет со скоростью"  # Выводим сообщение о движении водного транспорта (название класса)
              f"{self.speed} узлов по {self.water_type}.")  # Добавляем информацию о скорости и типе воды

class WheeledTransport(Transport):
    """"
    "    A class to represent a wheeled transport.
    """

    def __init__(self, speed: float, capacity: int, wheels: int) -> None:
        """
        Initialize the WheeledTransport object with a speed,
        capacity, and number of wheels.

        :param speed: The speed of the wheeled transport.
        :param capacity: The capacity of the wheeled transport.
        :param wheels: The number of wheels of the wheeled transport.
        """
        super().__init__(speed, capacity)  # Вызываем конструктор базового класса Transport
        self.wheels: int = wheels  # Инициализируем атрибут wheels (количество колес)

    def move(self) -> None:
        """
        Move the wheeled transport.
        """
        print(f"{self.__class__.__name__}: Едет со скоростью"  # Выводим сообщение о движении колесного транспорта (название класса)
              f"{self.speed} км/ч на {self.wheels} колесах.")  # Добавляем информацию о скорости и количестве колес

class Car(WheeledTransport):
    """
    A class to represent a car.
    """

    def __init__(self, speed: float, capacity: int, fuel_type: str) -> None:
        """
        Initialize the Car object with a speed, capacity, and fuel type.

        :param speed: The speed of the car.
        :param capacity: The capacity of the car.
        :param fuel_type: The type of fuel the car uses.
        """
        super().__init__(speed, capacity, wheels=4)  # Вызываем конструктор базового класса WheeledTransport, устанавливая количество колес равным 4
        self.fuel_type: str = fuel_type  # Инициализируем атрибут fuel_type (тип топлива)

    def move(self) -> None:
        """
        Move the car.
        """
        print(f"{self.__class__.__name__}: Едет на {self.fuel_type} "  # Выводим сообщение о движении автомобиля (название класса)
              f"со скоростью {self.speed} км/ч.")  # Добавляем информацию о типе топлива и скорости

    def honk(self) -> None:
        """
        Honk the car.
        """
        print("Автомобиль: Бип-бип!")  # Выводим звук автомобиля
```
При выполнении задания необходимо построить UML-диаграмма классов приложения
<image src="image.png">