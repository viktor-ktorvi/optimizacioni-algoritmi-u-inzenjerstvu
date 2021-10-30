import numpy as np
from scipy.special import spherical_jn
from matplotlib import pyplot as plt

if __name__ == '__main__':
    n = 1

    decimal = 12
    tolerance = 10 ** (-decimal)
    high = 20
    x_range = np.random.uniform(low=0, high=high, size=100)

    zeros = []
    for x in x_range:
        xprev = 0
        while np.abs(x - xprev) > tolerance:
            xprev = x
            x = xprev - spherical_jn(n, xprev, derivative=False) / spherical_jn(n, x, derivative=True)

        if x != np.nan and x < high and round(x, decimal) not in zeros:
            zeros.append(round(x, decimal))

    z = np.linspace(start=0, stop=max(zeros), num=1000)

    plt.figure()
    plt.plot(zeros, np.zeros_like(zeros), 'rx', label='zeros')
    plt.grid()
    plt.plot(z, spherical_jn(n=n, z=z, derivative=False), label='$j_{:d}$'.format(n))
    plt.title('Spherical Bessel function of order {:d} with zeros'.format(n))
    plt.xlabel('z')
    plt.ylabel('$j_n$')
    plt.legend()
    plt.show()

    print('Zeros:')
    zeros.sort()
    for zero in zeros:
        print(zero)
