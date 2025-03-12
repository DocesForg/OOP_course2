#deposit.py
# Программирование на языке высокого уровня (Python).
# Задание № 04.03.03. Вариант 21
#
# Выполнил: Мальцев Виталий Игоревич
# Группа: ПИЖ-б-о-23-2(2)



from typing import Tuple, Dict, Union, cast


class TimeDeposit:
    """Абстрактный класс - срочный вклад.

    https://ru.wikipedia.org/wiki/Срочный_вклад.

    Поля:
      - self.name (str): наименование;
      - self._interest_rate (float): процент по вкладу (0; 100];
      - self._period_limit (tuple (int, int)):
            допустимый срок вклада в месяцах [от; до);
      - self._sum_limit (tuple (float, float)):
            допустимая сумма вклада [от; до).
    Свойства:
      - self.currency (str): знак/наименование валюты.
    Методы:
      - self._check_self(initial_sum, period): проверяет соответствие данных
            ограничениям вклада;
      - self.get_profit(initial_sum, period): возвращает прибыль по вкладу;
      - self.get_sum(initial_sum, period):
            возвращает сумму по окончании вклада.
    """

    def __init__(self, name: str, interest_rate: float,
                 period_limit: Tuple[int, int],
                 sum_limit: Tuple[float, float]) -> None:
        """Инициализирует атрибуты класса TimeDeposit."""
        self.name: str = name  # Устанавливаем наименование вклада.
        self._interest_rate: float = interest_rate  # Устанавливаем процентную ставку.
        self._period_limit: Tuple[int, int] = period_limit  # Устанавливаем лимит по сроку вклада.
        self._sum_limit: Tuple[float, float] = sum_limit  # Устанавливаем лимит по сумме вклада.
        self._check_self()  # Проверяем допустимость установленных значений.

    def __str__(self) -> str:
        """Вернуть строкое представление депозита.

        Формат вывода:

        Наименование:       Срочный Вклад
        Валюта:             руб.
        Процентная ставка:  5
        Срок (мес.):        [6; 18)
        Сумма:              [1,000; 100,000)
        """
        return (f"Наименование:       {self.name}\n"  # Добавляем наименование вклада.
                f"Валюта:             {self.currency}\n"  # Добавляем валюту вклада.
                f"Процентная ставка:  {self._interest_rate}\n"  # Добавляем процентную ставку.
                f"Срок (мес.):        {self._period_limit}\n"  # Добавляем срок вклада.
                f"Сумма:              {self._sum_limit}")  # Добавляем сумму вклада.

    @property
    def currency(self) -> str:
        """Возвращает валюту вклада (руб.)."""
        return "руб."  # Не изменяется

    def _check_self(self) -> None:
        """Проверить, что данные депозита являются допустимыми."""
        assert 0 < self._interest_rate <= 100, \
            "Неверно указан процент по вкладу!"  # Проверяем, что процентная ставка находится в допустимом диапазоне.
        assert 1 <= self._period_limit[0] < self._period_limit[1], \
            "Неверно указаны ограничения по сроку вклада!"  # Проверяем, что ограничения по сроку вклада указаны верно.
        assert 0 < self._sum_limit[0] <= self._sum_limit[1], \
            "Неверно указаны ограничения по сумме вклада!"  # Проверяем, что ограничения по сумме вклада указаны верно.

    def _check_user_params(self, initial_sum, period) -> None:
        """Проверить, что данные депозита соответствуют его ограничениям."""
        is_sum_ok = self._sum_limit[0] <= initial_sum < self._sum_limit[1]  # Проверяем, что сумма вклада соответствует ограничениям.
        is_period_ok = self._period_limit[0] <= period < self._period_limit[1]  # Проверяем, что срок вклада соответствует ограничениям.
        assert is_sum_ok and is_period_ok, "Условия вклада не соблюдены!"  # Утверждаем, что оба условия (сумма и срок) соблюдены.

    def get_profit(self, initial_sum, period) -> float:
        """Вернуть прибыль по вкладу вклада клиента.

        Параметры:
          - initial_sum (float): первоначальная сумма;
          - period (int): количество месяцев размещения вклада.

        Формула:
          первоначальная_сумма * % / 100 * период / 12
        """
        # Проверить, укладывается ли вклад в ограничения
        self._check_user_params(initial_sum, period)  # Проверяем, что параметры вклада соответствуют ограничениям.
        # Выполнить расчет
        return initial_sum * self._interest_rate / 100 * period / 12  # Рассчитываем прибыль по вкладу.

    def get_sum(self, initial_sum, period) -> float:
        """Вернуть сумму вклада клиента после начисления прибыли.

        Параметры:
          - initial_sum (float): первоначальная сумма;
          - period (int): количество месяцев размещения вклада.
        """
        # Проверить, укладывается ли вклад в ограничения
        return initial_sum + self.get_profit(initial_sum, period)  # Возвращаем сумму вклада после начисления прибыли.


class BonusTimeDeposit(TimeDeposit):
    """Cрочный вклад c получением бонуса к концу срока вклада.

    Бонус начисляется как % от прибыли, если вклад больше определенной суммы.

    Атрибуты:
      - self._bonus (dict ("percent"=int, "sum"=float)):
        % от прибыли, мин. сумма;
    """

    def __init__(self, name: str, interest_rate: float,
                 period_limit: Tuple[int, int],
                 sum_limit: Tuple[float, float],
                 bonus: Dict[str, float]) -> None:
        """Инициализировать атрибуты класса."""
        self._bonus: Dict[str, float] = bonus  # Устанавливаем атрибут бонуса (процент и минимальная сумма).

        super().__init__(name, interest_rate, period_limit, sum_limit)  # Вызываем конструктор родительского класса.

    def __str__(self) -> str:
        """Вернуть строкое представление депозита.

        К информации о родителе добавляется информацию о бонусе.

        Формат вывода:

        Наименование:       Бонусный Вклад
        Валюта:             руб.
        Процентная ставка:  5
        Срок (мес.):        [6; 18)
        Сумма:              [1,000; 100,000)
        Бонус (%):          5
        Бонус (мин. сумма): 2,000
        """
        return (super().__str__() + "\n"  # Вызываем метод __str__ родительского класса.
                f"Бонус (%):          {self._bonus['percent']}\n"  # Добавляем информацию о проценте бонуса.
                f"Бонус (мин. сумма): {self._bonus['sum']}")  # Добавляем информацию о минимальной сумме для получения бонуса.

    def _check_self(self) -> None:
        """Проверить, что данные депозита являются допустимыми.

        Дополняем родительский метод проверкой бонуса.
        """
        super()._check_self()  # Вызываем метод _check_self родительского класса.
        assert self._bonus["percent"] > 0, "Неверно указан процент бонуса!"  # Проверяем, что процент бонуса указан верно.
        assert self._bonus["sum"] > 0, ("Неверно указана"
                                        "минимальная сумма бонуса!")  # Проверяем, что минимальная сумма для получения бонуса указана верно.

    def get_profit(self, initial_sum, period) -> float:
        """Вернуть прибыль по вкладу вклада клиента.

        Параметры:
          - initial_sum (float): первоначальная сумма;
          - period (int): количество месяцев размещения вклада.

        Формула:
          - прибыль = сумма * процент / 100 * период / 12

        Для подсчета прибыли используется родительский метод.
        Далее, если первоначальная сумма > необходимой,
        начисляется бонус.
        """
        profit = super().get_profit(initial_sum, period)  # Получаем прибыль по вкладу, используя метод родительского класса.
        if initial_sum >= self._bonus["sum"]:  # Проверяем, превышает ли первоначальная сумма минимальную сумму для получения бонуса.
            profit += profit * self._bonus["percent"] / 100  # Начисляем бонус к прибыли.
        return profit  # Возвращаем итоговую прибыль с учетом бонуса.


class CompoundTimeDeposit(TimeDeposit):
    """Cрочный вклад c ежемесячной капитализацией процентов."""

    def __str__(self) -> str:
        """Вернуть строкое представление депозита.

        К информации о родителе добавляется информация о капитализации.

        Формат вывода:

        Наименование:       Вклад с Капитализацией
        Валюта:             руб.
        Процентная ставка:  5
        Срок (мес.):        [6; 18)
        Сумма:              [1,000; 100,000)
        Капитализация %   : Да
        """
        return super().__str__() + "\nКапитализация %   : Да"  # Вызываем метод __str__ родительского класса и добавляем информацию о капитализации.

    def get_profit(self, initial_sum, period) -> float:
        """Вернуть прибыль по вкладу вклада клиента.

        Параметры:
          - initial_sum (float): первоначальная сумма;
          - period (int): количество месяцев размещения вклада.

        Родительский метод для подсчета прибыли использовать не нужно,
        переопределив его полностью - расчет осуществляется по новой формуле.
        Капитализация процентов осуществляется ежемесячно.

        Нужно не забыть про самостоятельный вызов проверки параметров.

        Формула:
          первоначальная_сумма * (1 + % / 100 / 12) ** период -
          первоначальная_сумма
        """
        self._check_user_params(initial_sum, period)  # Проверяем, что параметры вклада соответствуют ограничениям.
        return (initial_sum * (1 + self._interest_rate / 100 / 12) ** period -
                initial_sum)  # Рассчитываем прибыль с учетом ежемесячной капитализации процентов.
# ---


deposits_data: Dict[str,
                    Union[float, Tuple[int, int], Tuple[float, float]]] = {
    "interest_rate": 5.0,  # Процентная ставка по вкладу.
    "period_limit": (6, 18),  # Ограничения по сроку вклада (от 6 до 18 месяцев).
    "sum_limit": (1000.0, 100000.0)  # Ограничения по сумме вклада (от 1000 до 100000).
}

deposits = (
    TimeDeposit("Сохраняй",
                interest_rate=cast(float,
                                   deposits_data["interest_rate"]),
                period_limit=cast(Tuple[int, int],
                                  deposits_data["period_limit"]),
                sum_limit=cast(Tuple[float, float],
                               deposits_data["sum_limit"])),  # Создаем экземпляр класса TimeDeposit.

    BonusTimeDeposit("Бонусный 2",
                     interest_rate=cast(float, deposits_data["interest_rate"]),
                     period_limit=cast(Tuple[int, int],
                                       deposits_data["period_limit"]),
                     sum_limit=cast(Tuple[float, float],
                                    deposits_data["sum_limit"]),
                     bonus={"percent": 5.0, "sum": 2000.0}),  # Создаем экземпляр класса BonusTimeDeposit.

    CompoundTimeDeposit("С капитализацией",
                        interest_rate=cast(float,
                                           deposits_data["interest_rate"]),
                        period_limit=cast(Tuple[int, int],
                                          deposits_data["period_limit"]),
                        sum_limit=cast(Tuple[float, float],
                                       deposits_data["sum_limit"]))  # Создаем экземпляр класса CompoundTimeDeposit.
)
