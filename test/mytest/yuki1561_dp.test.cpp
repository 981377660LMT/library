#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "my_template.hpp"
#include "other/io.hpp"

#include "ds/hashmap.hpp"
#include "random/hash_vector.hpp"
#include "mod/modint.hpp"
#include "other/connected_dp.hpp"

using mint = modint107;

pair<int, vc<mint>> calc_yuki1561(int N, int LIM) {
  HashMapLL<int> MP;
  vvc<int> states;
  vc<pi> edges;
  states.eb(vc<int>(N, -1));
  states.eb(vc<int>(N, -1));
  MP[hash_vector(states[0])] = 0;

  int p = -1;
  while (1) {
    if (++p == len(states)) break;
    if (p == 1) {
      edges.eb(1, 1);
      continue;
    }
    vc<int> now = states[p];
    for (auto&& [nxt, convert]: connected_dp::next_states(now)) {
      // 今の成分数、消える成分数
      int a = 0, b = 0;
      FOR(v, N) if (now[v] == v) {
        ++a;
        if (convert[v] == -1) ++b;
      }
      // 消える成分があってよいのは、終状態にいくときのみ
      if (b >= 2) continue;
      if (b == 1) {
        if (MAX(nxt) != -1) continue;
        edges.eb(p, 1);
        continue;
      }
      ll h = hash_vector<int>(nxt);
      if (!MP.count(h)) {
        MP[h] = len(states);
        states.eb(nxt);
      }
      edges.eb(p, MP[h]);
    }
  }

  int S = len(states);
  vc<mint> dp(S);
  vc<mint> f(LIM);
  dp[0] = 1;
  FOR(i, LIM) {
    vc<mint> newdp(S);
    for (auto&& [a, b]: edges) newdp[b] += dp[a];
    swap(dp, newdp);
    f[i] = dp[1];
  }
  return {S, f};
}

void test() {
  assert(calc_yuki1561(2, 100).se[2] == mint(13));
  assert(calc_yuki1561(5, 100).se[6] == mint(45280509));
  assert(calc_yuki1561(6, 100).se[5] == mint(45280509));
  assert(calc_yuki1561(7, 100).se[77] == mint(713420418));
  assert(calc_yuki1561(9, 0).fi == 2189);
}

void solve() {
  LL(a, b);
  print(a + b);
}

signed main() {
  cout << fixed << setprecision(15);

  test();
  solve();

  return 0;
}