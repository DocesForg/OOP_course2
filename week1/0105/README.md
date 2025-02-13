# Отладка программ.
## Дебаггинг через VS Code

Неутомимый студент Стас Басов написал программу, которая считывает сумму всех чисел в списке и находит среднее значение этой суммы.

```PYTHON
def calculate_sum_and_average(numbers):
    total_sum = 0
    for num in numbers:
        total_sum += num

    average = total_sum // len(numbers)
    return total_sum, average


numbers = [10, 20, 30, 40, 50]
total, avg = calculate_sum_and_average(numbers)
print(f"Сумма чисел: {total}")
print(f"Среднее значение: {avg}")

numbers = [11, 22, 33, 42, 51]
total, avg = calculate_sum_and_average(numbers)
print(f"Сумма чисел: {total}")
print(f"Среднее значение: {avg}")
```

Нужно произвести отладку средствами VS Code.

В результате отладки было обнаружено ошибка заключается в процессе вычисления среднего значения. В коде Стаса используется целочисленное деление, которое отбрасывает дробную часть. Именно из-за это результат в случае, когда среднее значение не целое число будет не верным. Следует заменить целочисленное деление на простое деление.

```PYTHON
# main.py
def calculate_sum_and_average(numbers):
    total_sum = 0
    for num in numbers:
        total_sum += num

    average = total_sum / len(numbers)
    return total_sum, average


numbers = [10, 20, 30, 40, 50]
total, avg = calculate_sum_and_average(numbers)
print(f"Сумма чисел: {total}")
print(f"Среднее значение: {avg}")

numbers = [11, 22, 33, 42, 51]
total, avg = calculate_sum_and_average(numbers)
print(f"Сумма чисел: {total}")
print(f"Среднее значение: {avg}")
```

