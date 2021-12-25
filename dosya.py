from random import randint
from random import seed

f = open("girdi2.txt", "w")

seed(69420)

thread_count = int(input("kaç thread: "))
intCount = int(input("kaç sayı: "))

f.write(str(thread_count)+"\n")
f.write(str(intCount)+"\n")

for i in range(intCount):
    value = randint(1,1000000)
    f.write(str(value)+"\n")



