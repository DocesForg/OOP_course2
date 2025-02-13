"""Документирование кода"""
import room

r1 = room.Room(float(input("Введите ширину комнаты: ")),
               float(input("Введите длину комнаты: ")),
               float(input("Введите высоту комнаты: ")))
for i in range(int(input("Введите сумму окон и дверей в комнате: "))):
    r1.add_wd(float(input("Введите ширину окна или двери: ")),
              float(input("Ввдетие длину окна или двери: ")))
print(f"Площадь оклеиваемой поверхности: {r1.work_surface()}")
rolls = r1.roll_count(float(input("Введите ширину рулона обоев: ")),
                      float(input("Введите длину рулона обоев: ")))
print(f"Необходимое количество рулонов: {rolls}")
