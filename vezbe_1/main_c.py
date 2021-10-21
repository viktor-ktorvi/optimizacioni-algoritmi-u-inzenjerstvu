import numpy as np
import itertools


def factorize(num):
    assert num == np.trunc(num)  # is int?
    factors = []
    for i in range(1, np.int32(np.trunc(np.sqrt(num)))):
        if i not in factors:
            div = num / i
            if div == np.trunc(div):
                factors.append(i)

                if div not in factors:
                    factors.append(np.int32(div))

    return factors


if __name__ == '__main__':
    suma = 7.11
    quant = 0.01
    n = 4

    suma = np.int32(suma / quant)
    prod = suma

    factors = factorize(prod)

    counter = 0
    combinations = itertools.combinations(factors, n)
    print('Kombinacija ima {:d}'.format(len(list(combinations))))
    for comb in combinations:
        print(comb)
        if np.sum(comb) == suma and np.prod(comb) == prod:
            counter += 1
            print(counter, comb)

    print('Racuna se veoma brzo')
