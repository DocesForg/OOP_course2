number = [1, 3, 4, 6, 9, 11]

result = [x**2 for x in number if x % 3 == 0]

print(sum(result))
