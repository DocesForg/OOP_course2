# Декораторы для методов класса

## Задание

Реализуйте класс Product.

Атрибуты экземпляра класса:

- name -- название товара, строка;
- retail_price -- розничная цена, число;
- purchase_price -- закупочная цена, число;

Методы:

- Свойство profit должно возвращать разницу между розничной и закупочной ценой товара.
- Статический метод average_price(), который принимает список розничных цен нескольких товаров и возвращает их среднюю розничную цену
- Свойство information должно возвращать строку с информацией о товаре(название, розничная и закупочная цена.)

```PYTHON
class Product:
    """
    A class to represent a product.
    """

    def __init__(self, name: str, retail_price: float, purchase_price: float):
        """
        Initialize the Product object with a name, retail price, and purchase price.

        :param name: The name of the product.
        :param retail_price: The retail price of the product.
        :param purchase_price: The purchase price of the product.
        """
        self.name = name
        self.retail_price = retail_price
        self.purchase_price = purchase_price

    @property
    def profit(self):
        """
        Return the profit of the product.

        :return: The profit of the product.
        """
        return self.retail_price - self.purchase_price

    @staticmethod
    def average_price(prices):
        """
        Return the average price of the products.

        :param prices: A list of prices.
        :return: The average price of the products.
        """
        return sum(prices) / len(prices) if prices else 0

    @property
    def information(self):
        """
        Return the information of the product.

        :return: The information of the product.
        """
        return (f"Товар: {self.name}, розничная цена: {self.retail_price},"
                f"закупочная цена: {self.purchase_price}")


product = Product("Шляпа", 1000, 800)
print(product.profit)
print(Product.average_price([100, 300, 800]))
print(product.information)

```

