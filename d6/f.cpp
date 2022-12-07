#include <bits/stdc++.h>
using namespace std;

int q1(const string& s, int k) {
    vector<int> exist(26);
    int cnt = 0;
    int i;
    for (i = 0; i < k; i++) {
        if (++exist[s[i] - 'a'] == 1) ++cnt;
    }
    while (i < s.size() && cnt != k) {
        auto prev = i - k;
        if (--exist[s[prev] - 'a'] == 0) --cnt;
        if (++exist[s[i] - 'a'] == 1) ++cnt;
        ++i;
    }
    return i;
}

int main() {
    string s;
    cin >> s;
    cout << q1(s, 4) << endl;
    cout << q1(s, 14) << endl;
    return 0;
}