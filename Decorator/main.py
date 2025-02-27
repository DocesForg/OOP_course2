def format_float_return(func):
    """
    A decorator to format float return values.

    :param func: The function to be decorated.
    :return: The decorated function.
    """
    def wrapper():
        result = func()
        if isinstance(result, float):
            return round(result, 2)
        else:
            return result
    return wrapper


@format_float_return
def get_float_number():
    """
    A function to return a float number.

    :return: A float number.
    """
    return 3.1454576


@format_float_return
def get_integer_number():
    """
    A function to return an integer number.

    :return: An integer number.
    """
    return 15


print(get_float_number())
print(get_integer_number())
