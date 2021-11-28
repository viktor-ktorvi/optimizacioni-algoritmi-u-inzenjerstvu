import numpy as np
import copy


def f_opt(s, x):
    F = 2 ** 26 - x.dot(s)

    if F >= 0:
        return F
    else:
        return 2 ** 26


if __name__ == '__main__':
    f = open(r'vezbe_7/Z7.txt')
    content = f.read()
    f.close()

    s = np.array([int(token) for token in content.split(',')])
    x = np.zeros(len(s), dtype=np.int8)

    f_prev = f_opt(s, x)
    radius = 0.2

    x_prev = copy.deepcopy(x)

    max_iter = 100000
    T0 = 2 ** 25
    for j in range(20):
        print('f_opt({:d}) = {:d}'.format(j, f_prev))
        T = T0
        for i in range(max_iter):
            x ^= np.random.choice([0, 1], size=(len(x),), p=[1 - radius, radius])
            f_curr = f_opt(s, x)
            dE = f_curr - f_prev

            if dE < 0:
                x_prev = copy.deepcopy(x)
            else:
                p = np.exp(-dE / T)
                p_gen = np.random.rand()

                if p_gen < p:
                    x_prev = copy.deepcopy(x)
                else:
                    x = copy.deepcopy(x_prev)

            f_prev = copy.deepcopy(f_curr)
            T *= 0.95

    print('f_opt({:d}) = {:d}'.format(j, f_prev))
