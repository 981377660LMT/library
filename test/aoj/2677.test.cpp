#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2677"
#include "my_template.hpp"
#include "other/io.hpp"
#include "graph/hld.hpp"

void solve() {
  LL(N);
  Graph<int, 1> G(N);
  FOR(v, 1, N) {
    LL(p);
    --p;
    G.add(p, v);
  }
  G.build();

  int p = 0;
  vc<int> V;
  auto add = [&](int v) -> void { V.eb(v); };
  add(0);
  while (p < len(V)) {
    int v = V[p++];
    vc<int> TO;
    for (auto&& e: G[v]) TO.eb(e.to);
    sort(all(TO));
    for (auto&& x: TO) add(x);
  }
  HLD<decltype(G)> hld(G);
  ll ANS = 0;
  FOR(i, len(V) - 1) {
    int a = V[i], b = V[i + 1];
    ANS += hld.dist(a, b);
  }
  print(ANS);
}

signed main() {
  cout << fixed << setprecision(15);

  ll T = 1;
  // LL(T);
  FOR(T) solve();

  return 0;
}
