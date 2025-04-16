#inlude <iostream> // Подключаем библиотеку для ввода/вывода в консоль (например, std::cout)
#include <fstream> // Подключаем библиотеку для работы с файлами (например, std::ifstream)
#include <string> // Подключаем библиотеку для работы со строками (например, std::string)
#include <cstring> // Подключаем библиотеку для работы со строками в стиле C (например, strcmp)

struct Options { // Объявляем структуру для хранения параметров командной строки
    bool lines; // Флаг для подсчета строк
    bool bytes; // Флаг для подсчета байтов
    bool words; // Флаг для подсчета слов
    bool chars; // Флаг для подсчета символов

    Options() { // Конструктор структуры Options. Инициализирует все флаги в false по умолчанию
        lines = false;
        bytes = false;
        words = false;
        chars = false;
    }

    bool is_used() const { // Метод структуры Options, возвращает true, если хотя бы один флаг установлен в true
        return lines || bytes || words || chars; // Использование `||` (логическое ИЛИ), а не `|` (побитовое ИЛИ)
    }
};

size_t GetFileSize(const std::string& path_to_file) { // Функция для получения размера файла в байтах
    std::ifstream in_file(path_to_file, std::ifstream::ate | std::ifstream::binary); // Открываем файл в бинарном режиме, сразу перемещаемся в конец файла

    if (!in_file.is_open()) { // Проверяем, удалось ли открыть файл
        std::cout << "Failed to open " << path_to_file << '\n'; // Выводим сообщение об ошибке, если не удалось
        exit(1); // Завершаем программу с кодом ошибки 1
    }

    return in_file.tellg(); // Возвращаем текущую позицию чтения (т.е. размер файла)
}

void WordCount(const std::string& path_to_file, const Options& option) { // Функция для подсчета строк, слов, байтов и символов в файле
    std::ifstream in_file(path_to_file); // Открываем файл для чтения

    if (!in_file.is_open()) { // Проверяем, удалось ли открыть файл
        std::cout << "Failed to open " << path_to_file << '\n'; // Выводим сообщение об ошибке
        exit(1); // Завершаем программу с кодом ошибки 1
    }

    size_t number_of_bytes = GetFileSize(path_to_file); // Получаем размер файла в байтах
    size_t number_of_lines = 0; // Инициализируем счетчик строк
    size_t number_of_words = 0; // Инициализируем счетчик слов
    size_t number_of_chars = 0; // Инициализируем счетчик символов

    char previous_char = ' '; // Инициализируем предыдущий символ пробелом (нужен для корректного подсчета слов)
    char current_char; // Объявляем переменную для хранения текущего символа

    while (in_file.get(current_char)) { // Читаем файл символ за символом
        if (current_char == '\n') // Если текущий символ - перевод строки
            number_of_lines++; // Увеличиваем счетчик строк

        if (isgraph(current_char) || current_char == '\t') // Если текущий символ - графический или табуляция (отбрасываем управляющие символы, кроме табуляции)
            number_of_chars++; // Увеличиваем счетчик символов

        if (isspace(current_char) && !isspace(previous_char)) // Если текущий символ - пробельный, а предыдущий нет
            number_of_words++; // Увеличиваем счетчик слов

        previous_char = current_char; // Обновляем предыдущий символ
    }

    if (!isspace(previous_char)) // После цикла, проверяем, не закончился ли файл словом (нет пробела в конце)
        number_of_words++; // Если нет, увеличиваем счетчик слов

    // Если пользователь не выбрал ни одной опции
    if (option.is_used() == false) {
        std::cout << number_of_lines << " " // Выводим количество строк
                << number_of_words << " " // Выводим количество слов
                << number_of_bytes << " " // Выводим количество байтов
                << path_to_file << '\n'; // Выводим имя файла
    } else { // Если пользователь выбрал хотя бы одну опцию
        if (option.lines) // Если установлен флаг подсчета строк
            std::cout << number_of_lines << ' '; // Выводим количество строк

        if (option.words) // Если установлен флаг подсчета слов
            std::cout << number_of_words << ' '; // Выводим количество слов

        if (option.bytes) // Если установлен флаг подсчета байтов
            std::cout << number_of_bytes << ' '; // Выводим количество байтов

        if (option.chars) // Если установлен флаг подсчета символов
            std::cout << number_of_chars << ' '; // Выводим количество символов

        std::cout << path_to_file << '\n'; // Выводим имя файла
    }
}

void HandleOptions(const char* arg, Options& option) { // Функция для обработки параметров командной строки
    if (strcmp(arg, "-l") == 0 || strcmp(arg, "--lines") == 0) { // Если аргумент - "-l" или "--lines"
        option.lines = true; // Устанавливаем флаг подсчета строк в true
    } else if (strcmp(arg, "-c") == 0 || strcmp(arg, "--bytes") == 0) { // Если аргумент - "-c" или "--bytes"
        option.bytes = true; // Устанавливаем флаг подсчета байтов в true
    } else if (strcmp(arg, "-w") == 0 || strcmp(arg, "--words") == 0) { // Если аргумент - "-w" или "--words"
        option.words = true; // Устанавливаем флаг подсчета слов в true
    } else if (strcmp(arg, "-m") == 0 || strcmp(arg, "--chars") == 0) { // Если аргумент - "-m" или "--chars"
        option.chars = true; // Устанавливаем флаг подсчета символов в true
    }
}

int main(int argc, char** argv) { // Главная функция программы
    Options option; // Создаем объект структуры Options

    for (int i = 1; i < argc; ++i) { // Перебираем аргументы командной строки (начиная с 1, т.к. argv[0] - имя программы)
        char* arg = argv[i]; // Получаем текущий аргумент

        if (arg[0] == '-') { // Если аргумент начинается с "-" (то есть это опция)
            HandleOptions(arg, option); // Обрабатываем опцию
        } else { // Если аргумент не начинается с "-" (то есть это имя файла)
            WordCount(arg, option); // Вызываем функцию для подсчета в файле
        }
    }

    return 0; // Завершаем программу с кодом возврата 0 (успешное завершение)
}
