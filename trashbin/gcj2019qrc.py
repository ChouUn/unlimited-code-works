import math
from itertools import groupby

T = int(input())
for t in range(1, T + 1):
    m, n = input().split()
    a = [int(s) for s in input().split()]

    ap = [list(g) for k, g in groupby(a)]
    np = len(ap)

    d = math.gcd(ap[0][0], ap[1][0])
    ds = [ap[0][0] // d] if len(ap[0]) % 2 else [d]
    for ai in a:
        ds.append(ai // ds[-1])
    S = {val: idx for idx, val in enumerate(sorted(set(ds)))}

    print('Case #{}: '.format(t) + ''.join([chr(S[di] + 65) for di in ds]))
