import numpy as np
from scipy.optimize import linprog

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

    x_res_int = np.round(res.x).astype(np.int32)

    # TODO ne valja, treba proveriti vrednosti oko
    assert (A_ub @ x_res_int <= b_ub).all()

    print('{}{:>20}{:>22}'.format('x', 'float', 'int'))

    for i in range(43):
        print('-', end='')
    print()

    counter = 0
    for j in range(num_server_types):
        for i in range(num_racks):
            print('x{:d}{:d}{:20.5f}{:20d}'.format(i + 1, j + 1, res.x[counter], x_res_int[counter]))
            counter += 1

    print()
    print('Dobijene vrednosti zaokruzene na ceo broj zadovoljavaju nejednakosti')
    print('Zmax(float) = {:2.2f}\nZmax(int) = {:2.2f}'.format(-res.fun, np.dot(c, x_res_int)))
    print()

    # print('{:>11}'.format(''), end='')
    # for j in range(num_racks):
    #     print('{:>10}'.format('Ormar %d' % (j + 1)), end='')
    # print()
    #
    # x_mat = x_res_int.reshape((num_server_types, num_racks))
    #
    # for j in range(num_server_types):
    #     print('Server {:d}'.format(j + 1), end='')
    #     for i in range(num_racks):
    #         print('{:10d}'.format(x_mat[j, i]), end='')
    #     print()
    #
    # print('Snaga [W]', end='')
    #
    # for i in range(num_racks):
    #     print('{:10d}'.format(p.dot(x_mat[:, i])), end='')
