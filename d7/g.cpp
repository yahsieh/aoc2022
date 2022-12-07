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

class DirPool {
   private:
    size_t psize;
    vector<Dir> data;

   public:
    DirPool(int n = 1) {
        psize = 1;
        data.resize(n);
    }
    int find(const int& idx, const string& s) {
        const auto& cur = data[idx];
        for (const auto& i : cur.child) {
            if (data[i].name == s) return i;
        }
        return -1;
    }
    void add(const int& idx, const string& name, bool isFile = false,
             int sz = 0) {
        auto& cur = data[idx];
        if (psize >= data.size()) data.push_back(Dir{});
        cur.child.push_back(psize);
        data[psize] = Dir{idx, name, isFile, sz};
        ++psize;
    }
    int dirSize(const int pIndex) {
        auto& cur = get(pIndex);
        if (cur.fileSize == 0) {
            int fileSum = 0;
            for (const auto& i : cur.child) {
                const auto& next = get(i);
                if (next.isFile) {
                    DEBUG(cerr << next.name << " : " << next.fileSize << endl)
                    fileSum += next.fileSize;
                } else {
                    const auto& fs = dirSize(i);
                    DEBUG(cerr << next.name << "/ : " << fs << endl)
                    fileSum += fs;
                }
            }
            cur.fileSize = fileSum;
        }
        return cur.fileSize;
    }
    vector<int> allDirSize() {
        vector<int> ret;
        dirSize(0);
        for (size_t i = 0; i < psize; i++) {
            if (!data[i].isFile) ret.push_back(data[i].fileSize);
        }
        return ret;
    }

    Dir& get(const int& idx) { return data[idx]; }
    const Dir& get(const int& idx) const { return data[idx]; }
};

DirPool parse() {
    DirPool pool(POOL_SIZE);
    vector<string> v;
    string s;
    while (getline(cin, s)) v.push_back(s);
    size_t pIndex = 0;
    size_t index = 0;
    while (index < v.size()) {
        if (v[index][0] == '$') {
            if (v[index][2] == 'c') {
                if (v[index][5] == '/' && v[index].size() == 6) {
                    pIndex = 0;
                } else {
                    auto cur = pool.get(pIndex);
                    if (v[index][5] == '.' && v[index][6] == '.') {
                        pIndex = cur.parent;
                    } else {
                        auto dirName = v[index].substr(5);
                        auto f = pool.find(pIndex, dirName);
                        if (f == -1) {
                            cerr << "error: cd to " << dirName
                                 << " not found in " << cur.name << endl;
                            for (const auto& i : cur.child) {
                                const auto& next = pool.get(i);
                                if (!next.isFile) cerr << next.name << endl;
                            }
                            exit(-1);
                        } else {
                            pIndex = f;
                        }
                    }
                }
                ++index;
            } else {
                ++index;
                while (index < v.size() && v[index][0] != '$') {
                    if (v[index][0] == 'd') {
                        auto dirName = v[index].substr(4);
                        pool.add(pIndex, dirName);
                    } else {
                        auto whitespace = v[index].find(' ');
                        auto sz = stoi(v[index].substr(0, whitespace));
                        auto fname = v[index].substr(whitespace + 1);
                        pool.add(pIndex, fname, true, sz);
                    }
                    ++index;
                }
            }
        }
    }
    return pool;
}

pair<int, int> calc(const DirPool& pool, const int pIndex, const int k) {
    int fileSum = 0, dirSum = 0;
    const auto& cur = pool.get(pIndex);
    for (const auto& i : cur.child) {
        auto& next = pool.get(i);
        if (next.isFile) {
            DEBUG(cerr << next.name << " : " << next.fileSize << endl)
            fileSum += next.fileSize;
        } else {
            const auto& [fs, ds] = calc(pool, i, k);
            DEBUG(cerr << next.name << "/ : " << fs << endl)
            fileSum += fs;
            dirSum += ds;
            if (fs <= k) dirSum += fs;
        }
    }
    return {fileSum, dirSum};
}
int q1(const DirPool& pool, int k) { return calc(pool, 0, k).second; }

int q2(DirPool& pool) {
    int64_t used = pool.dirSize(0);
    int64_t need = 30000000 - (70000000 - used);
    DEBUG(cerr << "used = " << used << ", need to free = " << need << endl)
    vector<int> dirs = pool.allDirSize();
    set<int> st(dirs.begin(), dirs.end());
    st.insert(0);
    return *st.lower_bound(need);
}

int main() {
    auto pool = parse();
    cout << q1(pool, 100000) << endl;
    cout << q2(pool) << endl;
    return 0;
}