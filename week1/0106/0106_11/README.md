# Урок 11. Пример объектно-ориентированной программы на Python.
## Практическая работа

Может ли в этой программе ученик учиться без учителя? Если да, пусть научится чему-нибудь сам.

Добавьте в класс Pupil метож, позволяющий ученику случайно "забывать" какую-нибудь часть своих знаний


```PYTHON
#main.py
import test

lesson = test.Data("class", "object", "inheritance", "polymorphism",
                   "encapsulation")
marIvanna = test.Teacher()
vasy = test.Pupil()
pety = test.Pupil()
marIvanna.teach(lesson[2], vasy, pety)
marIvanna.teach(lesson[0], pety)
print(vasy.knowledge)
print(pety.knowledge)

pety.take(lesson[1])
print(pety.knowledge)
pety.lose()
print(pety.knowledge)
```
---
```PYTHON
#test.py
from random import randint


class Pupil:
    def __init__(self):
        self.knowledge = []

    def take(self, info):
        self.knowledge.append(info)

    def lose(self):
        if self.knowledge.__len__() > 0:
            num = randint(0, self.knowledge.__len__()-1)
            del self.knowledge[num]


class Teacher:
    def teach(self, info, *pupil):
        for i in pupil:
            i.take(info)


class Data:
    def __init__(self, *info):
        self.info = list(info)

    def __getitem__(self, i):
        return self.info[i]

```