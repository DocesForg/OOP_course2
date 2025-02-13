# Настройка рабочего окружения.
## Эксперемент с библиотекой pytest

```PYTHON
# pytest.ini
[pytest]
addopts = -vv -p no:cacheprovider
```

В файле `pytest.ini` хранятся настройки библиотеки.

```PYTHON
#test_programm.py
try:
    import main
except ImportError:
    raise AssertionError("Модуль 'main' не обнаружен")

EXPECTED_FUNC_NAME = "say_hello"


def test_say_hello_exists():
    assert hasattr(main, EXPECTED_FUNC_NAME), (
        f"Функция '{EXPECTED_FUNC_NAME}' не обнаружена в модуле 'main'")


def test_say_hello_without_exceptions():
    try:
        main.say_hello()
    except Exception as error:
        raise AssertionError(
            f"При запуске функции '{EXPECTED_FUNC_NAME}' возникло"
            f"исключение: '{type(error).__name__}': '{error}"
        )

```

Эти тесты проверяют:
- наличие функции с именем say_hello в коде из файла `main.py`
- что эта функция запускается без ошибок

```PYTHON
#main.py
def say_hello():
    print("Привет, Практикум!")
```

