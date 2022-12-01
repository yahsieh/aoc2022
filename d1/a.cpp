#include <bits/stdc++.h>
using namespace std;

int qselect(vector<int>& v, const int& k) {
    int N = v.size();
    int l = 0, r = v.size() - 1;
    while (l != k) {
        int nl = l;
        int pivot = l + rand() % (r - l + 1);
        int vp = v[pivot];
        for (int i = l; i <= r; i++) {
            if (i == pivot) continue;
            if (v[i] <= vp) {
                swap(v[i], v[nl++]);
                if (nl == pivot) ++nl;
            }
        }
        swap(v[nl], v[pivot]);
        if (nl > k) {
            r = nl - 1;
        } else if (nl < k) {
            l = nl + 1;
        } else {
            l = nl;
            break;
        }
    }
    return v[N - 1] + v[N - 2] + v[N - 3];
}

int q1() {
    string s;
    int mx = 0;
    int cur = 0;
    while (getline(cin, s)) {
        if (s.empty()) {
            mx = max(mx, cur);
            cur = 0;
        } else {
            cur += stoi(s);
        }
    }
    return mx;
}

int q2() {
    string s;
    vector<int> v;
    int cur = 0;
    while (getline(cin, s)) {
        if (s.empty()) {
            v.push_back(cur);
            cur = 0;
        } else {
            cur += stoi(s);
        }
    }
    if (cur != 0) v.push_back(cur);
    return qselect(v, v.size() - 1 - 3);
}

int main() {
    cout << q2() << endl;
    return 0;
}