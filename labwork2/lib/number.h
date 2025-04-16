#pragma once
#include <cinttypes>
#include <iostream>
#include <cstring>

// Структура для большого целого числа
struct uint2022_t {
    static const int CAPACITY = 70; // 70 * 4 = 280 байт < 300 байт
    uint32_t data[CAPACITY] = {0};  // Массив 32-битных слов, младший разряд — data[0]
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

// Преобразование из uint32_t
uint2022_t from_uint(uint32_t i);

// Преобразование из строки (десятичное число)
uint2022_t from_string(const char* ch);

// Арифметика
uint2022_t operator+(const uint2022_t& first, const uint2022_t& second);
uint2022_t operator-(const uint2022_t& first, const uint2022_t& second);
uint2022_t operator*(const uint2022_t& first, const uint2022_t& second);
uint2022_t operator/(const uint2022_t& first, const uint2022_t& second);
uint2022_t operator%(const uint2022_t& first, const uint2022_t& second);

// Сравнение
bool operator==(const uint2022_t& first, const uint2022_t& second);
bool operator!=(const uint2022_t& first, const uint2022_t& second);

// Вывод в консоль
std::ostream& operator<<(std::ostream& str, const uint2022_t& val);
