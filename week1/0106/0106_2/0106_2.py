import random  # Импортируем модуль для генерации случайных чисел

# Определяем класс "Воин"
class Warrior:
    def __init__(self, name):
        self.name = name  # Устанавливаем имя для воина
        self.health = 100  # Изначальное количество здоровья воина

    def attack(self, other):
        damage = 20  # Урон от одного удара
        other.health -= damage  # Уменьшаем здоровье противника на 20
        print(f"{self.name} атакует {other.name}. У {other.name} осталось {other.health} здоровья.")  # Выводим сообщение об атаке

# Создаем двух экземпляров класса "Воин"
warrior1 = Warrior("Воин 1")
warrior2 = Warrior("Воин 2")

# Пока оба воина живы, продолжаем бой
while warrior1.health > 0 and warrior2.health > 0:
    # Случайным образом выбираем, кто атакует
    attacker = random.choice([warrior1, warrior2])  # Случайно выбираем атакующего
    defender = warrior1 if attacker == warrior2 else warrior2  # Если атакует первый, то защищается второй, и наоборот

    # Атакуем
    attacker.attack(defender)  # Осуществляем атаку

# После окончания цикла, проверяем, кто победил
if warrior1.health <= 0:
    print(f"{warrior2.name} одержал победу!")  # Победил второй воин
else:
    print(f"{warrior1.name} одержал победу!")  # Победил первый воин

