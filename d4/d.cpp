#include <bits/stdc++.h>
using namespace std;

int contain(int l, int r, int p, int q) {
    return (int)(p <= r && q <= r && p >= l && q >= l);
}

int q1() {
    char p, q, r;
    int cnt = 0;
    uint32_t a, b, c, d;
    while (cin >> a >> p >> b >> q >> c >> r >> d) {
        if (b - a >= d - c) {
            cnt += contain(a, b, c, d);
        } else {
            cnt += contain(c, d, a, b);
        }
    }
    return cnt;
}

int q2() {
    char p, q, r;
    int cnt = 0;
    uint32_t a, b, c, d;
    while (cin >> a >> p >> b >> q >> c >> r >> d) {
        if (b < d) {
            cnt += (int)(c <= b);
        } else {
            cnt += (int)(a <= d);
        }
    }
    return cnt;
}

int main() {
    cout << q2() << endl;
    return 0;
}