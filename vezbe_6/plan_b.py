import numpy as np
from scipy.optimize import linprog
from copy import deepcopy


def next_variation(variation, base):
    carry = 1
    for i in range(len(variation)):
        variation[i] += carry
        if variation[i] == base:
            variation[i] = 0
            carry = 1
        else:
            carry = 0
            break

    return carry == 0


def change_x(x, x_round, delta_x, variation):
    j = 0
    for i in range(len(x)):
        if x_round[i] == 0:
            x[i] = 0
        else:
            x[i] = x_round[i] + delta_x[variation[j]]
            j += 1
            if x[i] < 0:
                x[i] = 0
    return x


if __name__ == '__main__':
    p = np.array([480, 650, 580, 390])

    A_ub = np.array([[1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0],
                     [0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0],
                     [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1],
                     [480, 650, 580, 390, 0, 0, 0, 0, 0, 0, 0, 0],
                     [0, 0, 0, 0, 480, 650, 580, 390, 0, 0, 0, 0],
                     [0, 0, 0, 0, 0, 0, 0, 0, 480, 650, 580, 390],
                     [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0],
                     [0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0],
                     [0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0],
                     [0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1]])

    b_ub = np.array([10, 16, 8, 6800, 8700, 4300, 18, 15, 23, 12])

    c = np.array([310, 380, 350, 285, 310, 380, 350, 285, 310, 380, 350, 285])

    res = linprog(c=-c, A_ub=A_ub, b_ub=b_ub, method='simplex')

    if np.allclose(np.round(res.x).astype(np.int32), res.x):
        print('Celobrojno')
        x_best = res.x
        f_max = -res.fun
    else:
        print('Nije celobrojno')
        num_non_zero = np.count_nonzero(res.x)

        variation = np.zeros(num_non_zero, dtype=np.int32)
        delta_x = np.array([-3, -2, -1, 0, 1, 2, 3])

        x_round = np.round(res.x)
        x = np.zeros_like(x_round)

        f_max = 0
        x_best = None
        x = change_x(x, x_round, delta_x, variation)
        if (A_ub @ x <= b_ub).all():
            f_max = c.dot(x)
            x_best = x

        while next_variation(variation, len(delta_x)):
            x = change_x(x, x_round, delta_x, variation)
            if (A_ub @ x <= b_ub).all():
                f = c.dot(x)
                if f > f_max:
                    f_max = f
                    x_best = deepcopy(x)

    x_best = x_best.astype(np.int32)
    # %% Ispis
    print('{}{:>12}{:>10}'.format('x', 'float', 'int'))
    for i in range(23):
        print('-', end='')
    print()

    for i in range(len(res.x)):
        print('x{:d}{:d}{:10.2f}{:10d}'.format(i // 4 + 1, i % 4 + 1, res.x[i], x_best[i]))

    print('\nZ(float) = {:.2f}\nZ(int) = {:.2f}'.format(-res.fun, f_max))
