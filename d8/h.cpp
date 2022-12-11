#include <bits/stdc++.h>
using namespace std;
#define DEBUG_FLAG 0
#define DEBUG(x)      \
    if (DEBUG_FLAG) { \
        x;            \
    }

vector<vector<int>> parse() {
    string s;
    vector<string> in;
    while (cin >> s) in.push_back(s);
    int N = in.size(), M = in[0].size();
    vector<vector<int>> ret(N, vector<int>(M));
    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++)
            ret[r][c] = static_cast<int>(in[r][c] - '0');
    return ret;
}

int q1(const vector<vector<int>>& v) {
    int cnt = 0;
    int R = v.size(), C = v[0].size();
    vector<vector<bool>> rowViz(R, vector<bool>(C)), colViz(R, vector<bool>(C));
    int mx = -1;
    for (int c = 0; c < C; c++) {
        rowViz[0][c] = rowViz[R - 1][c] = true;
        mx = -1;
        for (int i = 0; i < R - 1; i++) {
            if (v[i][c] > mx) {
                mx = v[i][c];
                rowViz[i][c] = true;
            }
        }
        mx = -1;
        for (int i = R - 1; i > 0; i--) {
            if (v[i][c] > mx) {
                mx = v[i][c];
                rowViz[i][c] = true;
            }
        }
    }
    for (int r = 0; r < R; r++) {
        colViz[r][0] = colViz[r][C - 1] = true;
        mx = -1;
        for (int i = 0; i < C - 1; i++) {
            if (v[r][i] > mx) {
                mx = v[r][i];
                colViz[r][i] = true;
            }
        }
        mx = -1;
        for (int i = C - 1; i > 0; i--) {
            if (v[r][i] > mx) {
                mx = v[r][i];
                colViz[r][i] = true;
            }
        }
    }
    DEBUG(for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            cerr << colViz[r][c] << " ";
        }
        cerr << endl;
    })
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (rowViz[r][c] || colViz[r][c]) ++cnt;
            DEBUG(cerr << rowViz[r][c] << " ")
        }
        DEBUG(cerr << endl)
    }
    return cnt;
}

int64_t q2(const vector<vector<int>>& v) {
    int mx;
    int R = v.size(), C = v[0].size();
    vector<vector<vector<int>>> dir(4, vector<vector<int>>(R, vector<int>(C)));
    deque<pair<int, int>> dq;
    int cnt;
    for (int c = 0; c < C; c++) {
        for (int r = 1; r < R; r++) {
            cnt = 1;
            if (!dq.empty()) {
                int height = dq.back().first;
                int cc = dq.back().second;
                while (v[r][c] > height) {
                    cnt += cc;
                    dq.pop_back();
                    if (dq.empty())
                        break;
                    else {
                        height = dq.back().first;
                        cc = dq.back().second;
                    }
                }
            }
            dir[0][r][c] = cnt;
            dq.push_back(make_pair(v[r][c], dir[0][r][c]));
        }
        dq.clear();
        for (int r = R - 2; r >= 0; r--) {
            cnt = 1;
            if (!dq.empty()) {
                int height = dq.back().first;
                int cc = dq.back().second;
                while (v[r][c] > height) {
                    cnt += cc;
                    dq.pop_back();
                    if (dq.empty())
                        break;
                    else {
                        height = dq.back().first;
                        cc = dq.back().second;
                    }
                }
            }
            dir[1][r][c] = cnt;
            dq.push_back(make_pair(v[r][c], dir[1][r][c]));
        }
        dq.clear();
    }
    for (int r = 0; r < R; r++) {
        for (int c = 1; c < C; c++) {
            cnt = 1;
            if (!dq.empty()) {
                int height = dq.back().first;
                int cc = dq.back().second;
                while (v[r][c] > height) {
                    cnt += cc;
                    dq.pop_back();
                    if (dq.empty())
                        break;
                    else {
                        height = dq.back().first;
                        cc = dq.back().second;
                    }
                }
            }
            dir[2][r][c] = cnt;
            dq.push_back(make_pair(v[r][c], dir[2][r][c]));
        }
        dq.clear();
        for (int c = C - 2; c >= 0; c--) {
            cnt = 1;
            if (!dq.empty()) {
                int height = dq.back().first;
                int cc = dq.back().second;
                while (v[r][c] > height) {
                    cnt += cc;
                    dq.pop_back();
                    if (dq.empty())
                        break;
                    else {
                        height = dq.back().first;
                        cc = dq.back().second;
                    }
                }
            }
            dir[3][r][c] = cnt;
            dq.push_back(make_pair(v[r][c], dir[3][r][c]));
        }
        dq.clear();
    }
    int64_t ret = 1;
    DEBUG(for (int i = 0; i < 4; i++) {
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                cout << dir[i][r][c] << " ";
            }
            cout << endl;
        }
        cout << endl;
    })
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            int64_t tmp = 1;
            for (int i = 0; i < 4; i++) {
                tmp *= dir[i][r][c];
            }
            ret = max(ret, tmp);
        }
    }
    return ret;
}

int main() {
    auto input = parse();
    // cout << q1(input) << endl;
    cout << q2(input) << endl;
    return 0;
}