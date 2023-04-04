#include <algorithm>
#include <iterator>
#include <functional>
#include <random>
#include <iostream>

//
// insertion_sort1(first,last,compare_func)
//   * based on pseudo-code at https://en.wikipedia.org/wiki/Insertion_sort
//     (first algorithm presented)
//
template <typename Iter, typename CompareFunc>
void insertion_sort1(Iter const& first, Iter const& last, CompareFunc const& cmp)
{
  using std::swap;
  using std::prev;
  using std::iter_swap;

  for (auto i = first; i != last; ++i)
    for (auto j = i; j != first && !cmp(*prev(j),*j); --j)
      iter_swap(j,prev(j));
}

//
// insertion_sort2(first,last,compare_func)
//   * based on pseudo-code at https://en.wikipedia.org/wiki/Insertion_sort
//     (second algorithm presented)
//
// In the Wikipedia article:
//   * i amd j are indices
//   * i starts at 1 and loop continues while i < length(A)
//   * j starts at i-1 and loop continues while i >= 0
//
// Resolving issues with an iterator implementation:
//   * i < length(A) is not the same as i_iter != last
//     so start i at the second location, i.e., i_iter = next(first) so
//     i_iter != last is equivalent
//       - this requires if (first == last) return; before any code so length is >= 1
//   * j = i-1 is equivalent to j_iter = prev(i_iter)
//     BUT while j >= 0 cannot be done with while j_iter != prev(first)!
//     SO start j_iter = i_iter and access prev(j_iter) when needed
//        which makes while j >= 0 become while j_iter != first
//        and all j+1 positions are j_iter positions
//
// Finally do all value assignments with std::move() so moves are used and if 
// such move assignments are not supported then copying is done.
//
template <typename Iter, typename CompareFunc>
void insertion_sort2(Iter const& first, Iter const& last, CompareFunc const& cmp)
{
  using std::swap;
  using std::prev;

  if (first == last)
    return;

  for (auto i = next(first); i != last; ++i)
  {
    auto tmp = std::move(*i);
    auto j = i;
    for (; j != first && cmp(tmp,*prev(j)); --j)
      *j = *prev(j);
    *j = std::move(tmp);
  }
}

int main()
{
  using namespace std;

  random_device rd;
  default_random_engine re(rd());
  uniform_int_distribution<unsigned> ud(0,9);

  vector<unsigned> v;
  generate_n(
    back_inserter(v),
    15,
    [&]() { return ud(re); }
  );

#if 0
  insertion_sort1(begin(v), end(v), std::less<>{});
#else
  insertion_sort2(begin(v), end(v), std::less<>{});
#endif

  copy(begin(v), end(v), ostream_iterator<unsigned>(cout," "));
  cout << '\n';
}
