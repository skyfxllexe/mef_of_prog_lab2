from random_word import RandomWords
from random import randint
r = RandomWords()

job_title = [r.get_random_word() for x in range(100000)]
subdivision = [r.get_random_word() + "_subdivision" for x in range(30)]
n = 1000000
with open('data.txt', 'w') as file:
    file.write(f"{n}\n")
    for i in range(n):
        file.write(f"{job_title[randint(0, 99999)]} {r.get_random_word().title()} {r.get_random_word().title()} ")
        file.write(str(i) + " " + subdivision[randint(0,29)] + "\n")