#include <bits/stdc++.h>
using namespace std;

int calc1(const char &c) {
  if (c >= 'a' && c <= 'z')
    return (int)(c - 'a' + 1);
  else
    return (int)(c - 'A' + 27);
}

char getPriority(const string &s) {
  int l = 0, r = s.size() - 1, m = l + (r - l) / 2;
  vector<bool> left(256);
  for (int i = 0; i <= m; i++)
    left[(size_t)s[i]] = true;
  for (int i = m + 1; i <= r; i++)
    if (left[(size_t)s[i]])
      return s[i];
  cerr << "error!\n";
  return '\0';
}

char getCommon(const vector<string> &v) {
  vector<vector<bool>> existChar(3, vector<bool>(256));
  for (int i = 0; i < 3; i++)
    for (const auto &ch : v[i])
      existChar[i][ch] = true;
  for (int i = 0; i < 256; i++) {
    if (existChar[0][i] && existChar[1][i] && existChar[2][i])
      return (char)i;
  }
  cerr << "error!\n";
  return '\0';
}

int q1() {
  string s;
  int ret = 0;
  while (cin >> s) {
    ret += calc1(getPriority(s));
  }
  return ret;
}

int q2() {
  string s;
  int ret = 0;
  while (cin >> s) {
    vector<string> v;
    v.push_back(s);
    for (int i = 0; i < 2; i++) {
      cin >> s;
      v.push_back(s);
    }
    ret += calc1(getCommon(v));
  }
  return ret;
}

int main() {
  cout << q2() << endl;
  return 0;
}
