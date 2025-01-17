#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
#include "my_template.hpp"
#include "other/io.hpp"
#include "geo/base.hpp"
#include "geo/angle_sort.hpp"

void solve() {
  LL(N);
  VEC(pi, P, N);
  angle_sort(P);
  FOR(i, N) print(P[i]);
}

signed main() {
  solve();

  return 0;
}
