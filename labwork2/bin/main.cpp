#include <lib/number.h>
#include <iostream>

int main() {
    // Проверка вывода большого числа
    uint2022_t value = from_string("12345678901234567890");
    std::cout << value << std::endl;

    // Объявление переменных
    uint2022_t a = from_uint(12345);
    std::cout << "a = " << a << std::endl;

    // Создание числа из строки
    uint2022_t b = from_string("9876543210");
    std::cout << "b = " << b << std::endl;

    // Сложение
    uint2022_t sum = a + b;
    std::cout << "a + b = " << sum << std::endl;

    // Вычитание
    uint2022_t diff = b - a;
    std::cout << "b - a = " << diff << std::endl;

    // Умножение
    uint2022_t prod = a * b;
    std::cout << "a * b = " << prod << std::endl;

    // Деление
    uint2022_t div = b / a;
    std::cout << "b / a = " << div << std::endl;

    // Сравнение
    std::cout << "a == b? " << (a == b ? "Yes" : "No") << std::endl;
    std::cout << "a != b? " << (a != b ? "Yes" : "No") << std::endl;

    return 0;
}
