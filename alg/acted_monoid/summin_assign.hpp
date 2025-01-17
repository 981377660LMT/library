#include "alg/monoid/summin.hpp"
#include "alg/monoid/assign.hpp"

template <typename E, ll none_val>
struct ActedMonoid_CntSumMin_Assign {
  using Monoid_X = Monoid_SumMin<E>;
  using Monoid_A = Monoid_Assign<ll, none_val>;
  using X = typename Monoid_X::value_type;
  using A = typename Monoid_A::value_type;
  static constexpr X act(const X& x, const A& a, const ll& size) {
    if (a == Monoid_A::unit()) return x;
    return {E(size) * a, a};
  }
};
