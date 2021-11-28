import numpy as np


def f_opt(s, x):
    F = 2 ** 26 - x.dot(s)

    if F >= 0:
        return F
    else:
        return 2 ** 26


if __name__ == '__main__':
    f = open(r'Z7.txt')
    content = f.read()
    f.close()
