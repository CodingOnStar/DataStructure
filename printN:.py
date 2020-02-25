from time import *


def print_int(n):
    for i in range(int(n)+1):
        print(i)


def PrintN(n):
    if n >= 0:
        PrintN(n - 1)
        print(n)


m = int(input('The number is:'))
begin_time = time()
print_int(m)
# PrintN(m)
end_time = time()
print('Time is', end_time - begin_time)
