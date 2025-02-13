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
