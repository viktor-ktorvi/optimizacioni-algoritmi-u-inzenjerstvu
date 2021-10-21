import numpy as np

if __name__ == '__main__':
    suma = 7.11
    quant = 0.01
    n = 3

    prices = np.arange(start=0, stop=suma + quant, step=quant)
    i = 0
    counter = 0
    print('Opet strasno sporo ali brze')
    for p1 in prices:
        for p2 in prices:
            for p3 in prices:
                i += 1
                if i % 1000 == 0:
                    print("{:2.9f} % od {:d} ({:d}^{:d}) kombinacija".format(i / len(prices) ** n * 100,
                                                                             len(prices) ** n, len(prices), n),
                          end='\r')

                p4 = suma - np.sum([p1, p2, p3])
                if np.sum([p1, p2, p3, p4]) == suma and np.prod([p1, p2, p3, p4]) == suma:
                    counter += 1
                    print("{:d} {:20d} {:20d} {:20d} {:20d}".format(counter, p1, p2, p3, p4))
