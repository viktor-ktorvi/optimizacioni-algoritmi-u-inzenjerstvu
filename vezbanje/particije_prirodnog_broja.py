import numpy as np


def print_partition(partition):
    for p in partition:
        if p != 0:
            print(p, ' ', end='')
    print('')


if __name__ == '__main__':
    N = 7
    partition = np.zeros(N, dtype=np.int32)
    partition[0] = N
    print_partition(partition)

    pointer = 1
    # while partition != np.ones_like(partition):
    for i in range(4):
        if partition[pointer] == 0:
            partition[pointer] += 1
            partition[pointer - 1] -= 1

        elif partition[pointer] == 1:
            partition[pointer - 1] -= 1
            partition[pointer] += 1
            pointer += 1

        # Can't be bothered to finish
        print_partition(partition)