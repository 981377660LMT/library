#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"
#include "my_template.hpp"
#include "other/io.hpp"

#include "linalg/det_mod.hpp"

void solve() {
  LL(N, mod);
  VV(int, A, N, N);
  int ANS = det_mod(A, mod);
  print(ANS);
}

signed main() {
  cout << fixed << setprecision(15);

  solve();

  return 0;
}
