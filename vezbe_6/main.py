import numpy as np
from scipy.optimize import linprog


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
    num_racks = 3
    num_server_types = 4
    k = np.array([310, 380, 350, 285])
    c = np.repeat(k, num_racks)

    b_num_servers_per_rack = np.array([10, 16, 8])
    A_num_servers_per_rack = np.array([np.tile([1, 0, 0], num_server_types),
                                       np.tile([0, 1, 0], num_server_types),
                                       np.tile([0, 0, 1], num_server_types)])

    p = np.array([480, 650, 580, 390])

    b_power_per_rack = np.array([6800, 8700, 4300])

    power_rack_row = lambda n: [p[(i - n) % num_server_types] if i % num_racks == n else 0 for i in
                                range(num_racks * num_server_types)]

    A_power_per_rack = np.array([power_rack_row(i) for i in range(num_racks)])

    b_num_servers_overall = np.array([18, 15, 23, 12])

    A_num_servers_overall = np.repeat(np.eye(num_server_types), num_racks, axis=1)

    A_ub = np.vstack((A_num_servers_per_rack, A_power_per_rack, A_num_servers_overall))
    b_ub = np.concatenate((b_num_servers_per_rack, b_power_per_rack, b_num_servers_overall))

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
                    x_best = x

        print(f_max, x_best)



