#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include "my_template.hpp"
#include "other/io.hpp"
#include "ds/segtree/dynamic_segtree.hpp"
#include "alg/monoid/add.hpp"

void solve() {
  // 動的セグ木での二分探索
  LL(N, Q);
  VEC(int, A, N);
  const int LIM = 1'000'000'000;

  Dynamic_SegTree<Monoid_Add<int>, false, 30'000'000> seg(-LIM, LIM + 1);
  auto root = seg.new_node(-LIM, LIM + 1);
  for (auto&& a: A) root = seg.multiply(root, a, 1);

  FOR(Q) {
    LL(t);
    if (t == 0) {
      LL(x);
      seg.multiply(root, x, 1);
    }
    if (t == 1) {
      auto check = [&](auto e) -> bool { return e == 0; };
      int ANS = seg.max_right(root, check, -LIM);
      print(ANS);
      root = seg.multiply(root, ANS, -1);
    }
    if (t == 2) {
      auto check = [&](auto e) -> bool { return e == 0; };
      int ANS = seg.min_left(root, check, LIM + 1) - 1;
      print(ANS);
      root = seg.multiply(root, ANS, -1);
    }
  }
}

signed main() {
  solve();

  return 0;
}
