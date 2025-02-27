people = ["Антон", "Соня", "Коля"]

say_to_all = lambda greeting: [
    print(f"{greeting}, {name}!") for name in people]

say_to_all("Привет")
say_to_all("До завтра")
