import sys
from itertools import groupby, accumulate

T = int(input())
for t in range(1, T + 1):
    n, b, f = [int(s) for s in input().split()]

    ps = []
    for dep in reversed(range(5)):
        sz = 2 ** dep
        print(''.join([str(j // sz % 2) for j in range(n)]))
        sys.stdout.flush()

        p = input()
        ps.append(p)
    ps.reverse()


    def solve(dep, l, r, pl, pr):
        if pr - pl == r - l: return []
        if dep == -1: return [l] if pl == pr else []

        sz, p, pm = 2 ** dep, ps[dep], pr
        for i in range(pl, pr):
            if p[i] == '1':
                pm = i
                break
        m = min(l + sz, r)
        lans = solve(dep - 1, l, m, pl, pm)
        rans = solve(dep - 1, m, r, pm, pr)
        return lans + rans

    l = [len(list(g)) for k, g in groupby(ps[4])]
    sl = accumulate(l)
    ans = []
    for i, li, sli in zip(range(0, n, 16), l, sl):
        ans += solve(3, i, min(i + 16, n), sli - li, sli)

    print(' '.join(str(i) for i in sorted(ans)))
    sys.stdout.flush()

    ver = int(input())
    if ver == -1:
        exit(-1)
exit(0)
