#include "graph/base.hpp"
#include "graph/shortest_path/bfs01.hpp"

/*
https://maspypy.com/%e9%87%8d%e5%bf%83%e5%88%86%e8%a7%a3%e3%83%bb1-3%e9%87%8d%e5%bf%83%e5%88%86%e8%a7%a3%e3%81%ae%e3%81%8a%e7%b5%b5%e6%8f%8f%e3%81%8d
1/3 CD のみ扱う
centroid_decomposition_1：長さ 2 以上のパス全体
*/

template <typename F>
void centroid_decomposition_1_dfs(vc<int>& par, vc<int> vs, F f) {
  const int N = len(par);
  assert(N > 1);
  if (N == 2) { return; }
  int c = -1;
  vc<int> sz(N, 1);
  FOR_R(i, N) {
    if (sz[i] >= ceil<int>(N, 2)) {
      c = i;
      break;
    }
    sz[par[i]] += sz[i];
  }
  vc<int> color(N, -1);
  int take = 0;
  vc<int> ord(N, -1);
  ord[c] = 0;
  int p = 1;
  FOR(v, 1, N) {
    if (par[v] == c && take + sz[v] <= floor<int>(N - 1, 2)) {
      color[v] = 0, ord[v] = p++, take += sz[v];
    }
  }
  FOR(i, 1, N) {
    if (color[par[i]] == 0) color[i] = 0, ord[i] = p++;
  }
  int n0 = p - 1;
  int a = c;
  while (1) {
    a = par[a];
    if (a == -1) break;
    color[a] = 1, ord[a] = p++;
  }
  FOR(i, N) {
    if (i != c && color[i] == -1) color[i] = 1, ord[i] = p++;
  }
  assert(p == N);
  int n1 = N - 1 - n0;
  vc<int> par0(n0 + 1, -1), par1(n1 + 1, -1), par2(N, -1);
  vc<int> V0(n0 + 1), V1(n1 + 1), V2(N);
  FOR(v, N) {
    int i = ord[v];
    V2[i] = vs[v];
    if (color[v] != 1) { V0[i] = vs[v]; }
    if (color[v] != 0) { V1[max(i - n0, 0)] = vs[v]; }
  }
  FOR(v, 1, N) {
    int a = ord[v], b = ord[par[v]];
    if (a > b) swap(a, b);
    par2[b] = a;
    if (color[v] != 1 && color[par[v]] != 1) par0[b] = a;
    if (color[v] != 0 && color[par[v]] != 0)
      par1[max(b - n0, 0)] = max(a - n0, 0);
  }
  f(par2, V2, n0, n1);
  centroid_decomposition_1_dfs(par0, V0, f);
  centroid_decomposition_1_dfs(par1, V1, f);
}

// 長さ 1 のパスは別処理することに注意
// 長さ 2 以上のパスすべてに対する計算をしたい
// f(G, V, n1, n2)
// G: oriented
// V: label in original tree, dfs order
// color=1: V[1:1+n1]
// color=2: V[1+n1:1+n1+n2]
template <typename GT, typename F>
void centroid_decomposition_1(GT& G, F f) {
  if (G.N == 1) return;
  if constexpr (GT::is_directed) {
    vc<int> V = toposort(G);
    G = G.rearrange(V, true);
    centroid_decomposition_1_dfs(G, V, f);
  } else {
    Graph<typename GT::cost_type, true> H = to_directed_tree(G);
    vc<int> V = toposort(H);
    H = H.rearrange(V, true);
    centroid_decomposition_1_dfs(H, V, f);
  }
}

/*
https://maspypy.com/%e9%87%8d%e5%bf%83%e5%88%86%e8%a7%a3%e3%83%bb1-3%e9%87%8d%e5%bf%83%e5%88%86%e8%a7%a3%e3%81%ae%e3%81%8a%e7%b5%b5%e6%8f%8f%e3%81%8d
1/3 CD のみ扱う
centroid_decomposition_1：長さ 2 以上のパス全体
*/

template <typename F>
void centroid_decomposition_2_dfs(vc<int>& par, vc<int>& vs, vc<int>& real,
                                  F f) {
  const int N = len(par);
  assert(N > 1);
  if (N == 2) {
    if (real[0] && real[1]) {
      vc<int> color = {0, 1};
      f(par, vs, color);
    }
    return;
  }
  int c = -1;
  vc<int> sz(N, 1);
  FOR_R(i, N) {
    if (sz[i] >= ceil<int>(N, 2)) {
      c = i;
      break;
    }
    sz[par[i]] += sz[i];
  }
  vc<int> color(N, -1);
  int take = 0;
  vc<int> ord(N, -1);
  ord[c] = 0;
  int p = 1;
  FOR(v, 1, N) {
    if (par[v] == c && take + sz[v] <= floor<int>(N - 1, 2)) {
      color[v] = 0, ord[v] = p++, take += sz[v];
    }
  }
  FOR(i, 1, N) {
    if (color[par[i]] == 0) color[i] = 0, ord[i] = p++;
  }
  int n0 = p - 1;
  int a = c;
  while (1) {
    a = par[a];
    if (a == -1) break;
    color[a] = 1, ord[a] = p++;
  }
  FOR(i, N) {
    if (i != c && color[i] == -1) color[i] = 1, ord[i] = p++;
  }
  assert(p == N);
  int n1 = N - 1 - n0;
  vc<int> par0(n0 + 1, -1), par1(n1 + 1, -1), par2(N, -1);
  vc<int> V0(n0 + 1), V1(n1 + 1), V2(N);
  vc<int> rea0(n0 + 1), rea1(n1 + 1), rea2(N);
  FOR(v, N) {
    int i = ord[v];
    V2[i] = vs[v], rea2[i] = real[v];
    if (color[v] != 1) { V0[i] = vs[v], rea0[i] = real[v]; }
    if (color[v] != 0) {
      V1[max(i - n0, 0)] = vs[v], rea1[max(i - n0, 0)] = real[v];
    }
  }
  FOR(v, 1, N) {
    int a = ord[v], b = ord[par[v]];
    if (a > b) swap(a, b);
    par2[b] = a;
    if (color[v] != 1 && color[par[v]] != 1) par0[b] = a;
    if (color[v] != 0 && color[par[v]] != 0)
      par1[max(b - n0, 0)] = max(a - n0, 0);
  }
  if (real[c]) {
    color.assign(N, -1);
    color[0] = 0;
    FOR(i, 1, N) color[i] = rea2[i] ? 1 : -1;
    f(par2, V2, color);
    rea0[0] = rea1[0] = rea2[0] = 0;
  }
  color.assign(N, -1);
  FOR(i, 1, N) if (rea2[i]) color[i] = (i <= n0 ? 0 : 1);
  f(par2, V2, color);
  centroid_decomposition_2_dfs(par0, V0, rea0, f);
  centroid_decomposition_2_dfs(par1, V1, rea1, f);
}

// f(par, V, color)
// V: label in original tree, dfs order
// color in [-1,0,1], color=-1: virtual
template <int MODE, typename GT, typename F>
void centroid_decomposition(GT& G, F f) {
  const int N = G.N;
  if (N == 1) return;
  vc<int> V(N), par(N, -1);
  int l = 0, r = 0;
  V[r++] = 0;
  while (l < r) {
    int v = V[l++];
    for (auto& e: G[v]) {
      if (e.to != par[v]) V[r++] = e.to, par[e.to] = v;
    }
  }
  assert(r == N);
  vc<int> new_idx(N);
  FOR(i, N) new_idx[V[i]] = i;
  vc<int> tmp(N, -1);
  FOR(i, 1, N) {
    int j = par[i];
    tmp[new_idx[i]] = new_idx[j];
  }
  swap(par, tmp);
  static_assert(MODE == 1 || MODE == 2);
  if constexpr (MODE == 1) {
    centroid_decomposition_1_dfs(par, V, f);
  } else {
    vc<int> real(N, 1);
    centroid_decomposition_2_dfs(par, V, real, f);
  }
}
