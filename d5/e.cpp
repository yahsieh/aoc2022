#include <bits/stdc++.h>
using namespace std;

void parse(const string& s, vector<deque<char>>& dq) {
    if (s.empty() || s[1] == '1') return;
    int N = dq.size();
    for (int i = 1; i < N; i++) {
        if (s[((i - 1) << 2)] == '[') {
            dq[i].push_front(s[((i - 1) << 2) + 1]);
        }
    }
}

string q1() {
    string s = "";
    getline(cin, s);
    int sz = (s.size() - 3) / 4 + 1;
    vector<deque<char>> dq(sz + 1);
    parse(s, dq);
    while (!s.empty()) {
        getline(cin, s);
        parse(s, dq);
    }
    string from, to;
    int a, b, cnt;
    while (cin >> s >> cnt >> from >> a >> to >> b) {
        for (int i = 0; i < cnt; i++) {
            dq[b].push_back(dq[a].back());
            dq[a].pop_back();
        }
    }
    string ret = "";
    for (int i = 1; i < dq.size(); i++) {
        ret += dq[i].back();
    }
    return ret;
}

string q2() {
    string s = "";
    getline(cin, s);
    int sz = (s.size() - 3) / 4 + 1;
    vector<deque<char>> dq(sz + 1);
    parse(s, dq);
    while (!s.empty()) {
        getline(cin, s);
        parse(s, dq);
    }
    string from, to;
    int a, b, cnt;
    deque<char> tmp;
    while (cin >> s >> cnt >> from >> a >> to >> b) {
        for (int i = 0; i < cnt; i++) {
            tmp.push_back(dq[a].back());
            dq[a].pop_back();
        }
        while (!tmp.empty()) {
            dq[b].push_back(tmp.back());
            tmp.pop_back();
        }
    }
    string ret = "";
    for (int i = 1; i < dq.size(); i++) {
        ret += dq[i].back();
    }
    return ret;
}

int main() {
    cout << q2() << endl;
    return 0;
}