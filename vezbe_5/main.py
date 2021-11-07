import numpy as np
from matplotlib import pyplot as plt
from scipy.optimize import minimize


def y_training(x):
    return 0.5 * np.sin(np.pi * x)


def y_out(x, w, n=5):
    return np.sum(np.tanh(x[:, np.newaxis] @ w[:n, np.newaxis].T) * w[n:], axis=1)


def f_opt(w, *args):
    penalty = 0
    for weight in w:
        if not -10 <= weight <= 10:
            penalty += 10
            break

    return np.sum((y_training(args[0]) - y_out(args[0], w, n=5)) ** 2) + penalty


if __name__ == '__main__':
    step = 0.1
    x_in = np.arange(start=-1, stop=1 + step, step=step)

    plt.figure()
    plt.grid()
    plt.plot(x_in, y_training(x_in), label='training')
    plt.title('Training function')
    plt.xlabel('$x_{in}$')
    plt.ylabel('$y_{training}$')

    w = np.random.randn(10).clip(min=-10, max=10)

    res = minimize(f_opt, w, args=x_in, method='Nelder-Mead')

    w_opt = res.x
    y_ = y_out(x_in, w_opt)
    plt.plot(x_in, y_, label='nn output')
    plt.legend()
    plt.show()

    print('Optimalni težinski koeficijenti:')
    for i in range(len(w_opt)):
        print('w_{:d}:{:28.15f}'.format(i, w_opt[i]))

    print('Minimalna pronađena vrednost oprimizacione funkcije je {:3.5f}'.format(res.fun))
