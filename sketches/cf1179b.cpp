//@ Including Header
#include <cul/std>

/**
 *  Name : cf1179b.cpp
 *  Date : 2019/6/22 2:25
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

void dfs_hor(i32 xs, i32 ys, i32 xe, i32 ye);
void dfs_ver(i32 xs, i32 ys, i32 xe, i32 ye);

void hor(i32 xs, i32 ys, i32 xe, i32 ye) {
    i32 i = ys;
    i32 j = ye;
    while (i <= j) {
        if (i <= j) cout << xs << " " << i++ << '\n';
        if (i <= j) cout << xs << " " << j-- << '\n';
    }
}

void ver(i32 xs, i32 ys, i32 xe, i32 ye) {
    i32 i = xs;
    i32 j = xe;
    while (i <= j) {
        if (i <= j) cout << i++ << " " << ys << '\n';
        if (i <= j) cout << j-- << " " << ys << '\n';
    }
}

void dfs_hor(i32 xs, i32 ys, i32 xe, i32 ye) {
    if (xs > xe || ys > ye) return;

    if (xe == xs) { hor(xs, ys, xe, ye); return; }
    if (ye == ys) { ver(xs, ys, xe, ye); return; }

    i32 i = ys;
    i32 j = ye;
    while (i <= ye && ys <= j) {
        cout << xs << " " << i++ << '\n';
        cout << xe << " " << j-- << '\n';
    }

    dfs_ver(xs + 1, ys, xe - 1, ye);
}

void dfs_ver(i32 xs, i32 ys, i32 xe, i32 ye) {
    if (xs > xe || ys > ye) return;

    if (xe == xs) { hor(xs, ys, xe, ye); return; }
    if (ye == ys) { ver(xs, ys, xe, ye); return; }

    i32 i = xs;
    i32 j = xe;
    while (i <= xe && xs <= j) {
        cout << i++ << " " << ys << '\n';
        cout << j-- << " " << ye << '\n';
    }

    dfs_hor(xs, ys + 1, xe, ye - 1);
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i32 n, m;
    cin >> n >> m;
    dfs_hor(1, 1, n, m);

    return 0;
}
