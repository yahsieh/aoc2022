#include <bits/stdc++.h>
using namespace std;
#define POOL_SIZE 100000
#define DEBUG_FLAG 0
#define DEBUG(x)      \
    if (DEBUG_FLAG) { \
        x;            \
    }

class Dir {
   public:
    int parent;
    string name;
    bool isFile;
    int fileSize;
    vector<int> child;
    Dir() : parent(0), name(""), isFile(false), fileSize(0){};
    Dir(int p, string _s, bool b, int sz)
        : parent(p), name(_s), isFile(b), fileSize(sz){};
};

int psize;
vector<Dir> pool;
int find(const Dir& cur, const string& s) {
    for (const auto& i : cur.child) {
        if (pool[i].name == s) return i;
    }
    return -1;
}

void add(Dir& cur, const int& curIdx, const string& name, bool isFile = false,
         int sz = 0) {
    if (psize >= POOL_SIZE) {
        cerr << "reached pool limit=" << POOL_SIZE << endl;
        exit(-1);
    }
    cur.child.push_back(psize);
    pool[psize] = Dir{curIdx, name, isFile, sz};
    ++psize;
}

void parse() {
    psize = 1;
    vector<string> v;
    string s;
    while (getline(cin, s)) v.push_back(s);
    pool.resize(POOL_SIZE);
    int cur = 0;
    int index = 0;
    while (index < v.size()) {
        if (v[index][0] == '$') {
            if (v[index][2] == 'c') {
                if (v[index][5] == '/' && v[index].size() == 6) {
                    cur = 0;
                } else {
                    if (v[index][5] == '.' && v[index][6] == '.') {
                        cur = pool[cur].parent;
                    } else {
                        auto dirName = v[index].substr(5);
                        auto f = find(pool[cur], dirName);
                        if (f == -1) {
                            cerr << "error: cd to " << dirName
                                 << " not found in " << pool[cur].name << endl;
                            for (const auto& i : pool[cur].child) {
                                if (!pool[i].isFile)
                                    cerr << pool[i].name << endl;
                            }
                            exit(-1);
                        } else {
                            cur = f;
                        }
                    }
                }
                ++index;
            } else {
                ++index;
                while (index < v.size() && v[index][0] != '$') {
                    if (v[index][0] == 'd') {
                        auto dirName = v[index].substr(4);
                        add(pool[cur], cur, dirName);
                    } else {
                        auto whitespace = v[index].find(' ');
                        auto sz = stoi(v[index].substr(0, whitespace));
                        auto fname = v[index].substr(whitespace + 1);
                        add(pool[cur], cur, fname, true, sz);
                    }
                    ++index;
                }
            }
        }
    }
}

pair<int, int> calc(const Dir& cur, const int k) {
    int fileSum = 0, dirSum = 0;
    for (const auto& i : cur.child) {
        if (pool[i].isFile) {
            DEBUG(cerr << pool[i].name << " : " << pool[i].fileSize << endl)
            fileSum += pool[i].fileSize;
        } else {
            const auto& [fs, ds] = calc(pool[i], k);
            DEBUG(cerr << pool[i].name << "/ : " << fs << endl)
            fileSum += fs;
            dirSum += ds;
            if (fs <= k) dirSum += fs;
        }
    }
    return {fileSum, dirSum};
}

int calc(Dir& cur) {
    if (cur.fileSize == 0) {
        int fileSum = 0;
        for (const auto& i : cur.child) {
            if (pool[i].isFile) {
                DEBUG(cerr << pool[i].name << " : " << pool[i].fileSize << endl)
                fileSum += pool[i].fileSize;
            } else {
                const auto& fs = calc(pool[i]);
                DEBUG(cerr << pool[i].name << "/ : " << fs << endl)
                fileSum += fs;
            }
        }
        cur.fileSize = fileSum;
    }
    return cur.fileSize;
}

int q1(int k) { return calc(pool[0], k).second; }

int q2() {
    set<int> st;
    st.insert(0);
    int64_t used = calc(pool[0]);
    int64_t need = 30000000 - (70000000 - used);
    DEBUG(cerr << "used = " << used << ", need to free = " << need << endl)
    for (int i = 0; i < psize; i++) {
        if (!pool[i].isFile) st.insert(pool[i].fileSize);
    }
    return *st.lower_bound(need);
}

int main() {
    parse();
    cout << q1(100000) << endl;
    cout << q2() << endl;
    return 0;
}