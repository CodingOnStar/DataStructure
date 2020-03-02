def sub_seq_sum(n):
    MaxSum = 0
    for i in range(len(n)):
        for j in range(i, len(n)):
            ThisSum = 0
            for k in range(i, j+1):  # 注意range的右边取不到
                ThisSum += n[k]
                if ThisSum > MaxSum:
                    MaxSum = ThisSum

    print(MaxSum)


def Sub_seq_sum(n):
    MaxSum = 0
    for i in range(len(n)):
        ThisSum = 0
        for j in range(i, len(n)):
            ThisSum += n[j]
            if ThisSum > MaxSum:
                MaxSum = ThisSum
    print(MaxSum)


def N_sequence(n):
    MaxSum = 0
    ThisSum = 0
    for i in range(len(n)):
        ThisSum += n[i]
        if ThisSum > MaxSum:
            MaxSum = ThisSum
        elif ThisSum < 0:
            ThisSum = 0
    print(MaxSum)


a = [-1, 2, 5, -6, 8, 4, 1]
# sub_seq_sum(a)
N_sequence(a)
