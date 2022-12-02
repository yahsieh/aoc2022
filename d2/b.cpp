#include <bits/stdc++.h>
using namespace std;

int check(const char &a, const char &b) {
  if ((a == 'A' && b == 'Y') || (a == 'B' && b == 'Z') ||
      (a == 'C' && b == 'X'))
    return 2;
  else if ((a == 'A' && b == 'X') || (a == 'B' && b == 'Y') ||
           (a == 'C' && b == 'Z'))
    return 1;
  else
    return 0;
}

int calc(const char &a, const char &b) {
  auto res = check(a, b);
  return res * 3 + (int)(b - 'X' + 1);
}

char strategy(const char &a, const char &b) {
  char c;
  if (b == 'X') {
    if (a == 'A')
      c = 'C';
    else
      c = a - 1;
  } else if (b == 'Y') {
    c = a;
  } else {
    if (a == 'C')
      c = 'A';
    else
      c = a + 1;
  }
  return c;
}

int calc2(const char &a, const char &b) {
  return (b - 'X') * 3 + (int)(strategy(a, b) - 'A') + 1;
}

int q1() {
  char a, b;
  int ret = 0;
  while (cin >> a >> b) {
    ret += calc(a, b);
  }
  return ret;
}

int q2() {
  char a, b;
  int ret = 0;
  while (cin >> a >> b) {
    ret += calc2(a, b);
  }
  return ret;
}

int main() { cout << q2() << endl; }
