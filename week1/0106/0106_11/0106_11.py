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
