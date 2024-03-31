#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
/**
  Example showing the function programming ideas in
  C++ 11. Features used here are part of standard language.
**/
template <typename F, typename Tuple, size_t... S>
decltype (auto)
apply_tuple_impl (F &&fn, Tuple &&t, std::index_sequence<S...>)
{
  return std::forward<F> (fn) (std::get<S> (std::forward<Tuple> (t))...);
}

template <typename F, typename Tuple>
decltype (auto)
apply_from_tuple (F &&fn, Tuple &&t)
{
  std::size_t constexpr tSize
      = std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
  return apply_tuple_impl (std::forward<F> (fn), std::forward<Tuple> (t),
                           std::make_index_sequence<tSize> ());
}

template <typename... C>
auto
value_tuple (const int &i, C... rest)
{
  return std::make_tuple (rest[i]...);
}
template <typename Collection, typename... C>
size_t
get_size (const Collection &F, C... rest)
{
  return F.size ();
}
template <class Collection> class FP : public Collection
{
public:
  template <typename T> FP (std::initializer_list<T> list) : Collection (list)
  {
  }

  template <typename... Args> FP (Args... args) { Collection (args...); }

  FP () : Collection () {}

  FP (Collection &c) : Collection (c) {}

  template <typename unop>
  FP<Collection>
  each (unop op)
  {
    std::for_each (this->begin (), this->end (), op);
    return *this;
  }

  template <typename unop>
  FP<Collection>
  map (unop op)
  {
    std::transform (this->begin (), this->end (), this->begin (), op);
    return *this;
  }

  template <typename unop, class... C>
  FP<Collection>
  thread (unop op, C... c)
  {
    this->clear ();
    const size_t size = get_size (c...);
    for (int i = 0; i < size; i++)
      this->push_back (apply_from_tuple (op, value_tuple (i, c...)));
    return *this;
  }

  template <typename TResult, typename F>

  TResult
  fold (const TResult &startValue, const F &f)
  {
    TResult result = startValue;
    auto p = this->begin ();
    while (p != this->end ())
      result = f (result, *p++);
    return result;
  }

  template <typename binop>
  FP<Collection>
  zip (Collection fc, Collection sc, binop op)
  {
    std::transform (fc.begin (), fc.end (), sc.begin (), fc.begin (), op);
    Collection::assign (fc.begin (), fc.end ());
    return *this;
  }

  template <typename Condition>
  bool
  exists (Condition con)
  {
    auto exist = std::find_if (this->begin (), this->end (), con);
    return exist != this->end ();
  }

  template <typename Predicate>
  Collection
  filterNot (Predicate predicate)
  {
    auto returnIterator
        = std::remove_if (this->begin (), this->end (), predicate);
    this->erase (returnIterator, std::end (this));
    return *this;
  }

  //    template <typename Predicate>
  //    Collection filter(Predicate predicate) {
  //        auto fnCol = filterNot(col,[predicate](typename
  //        Collection::value_type i) { return !predicate(i);}); return fnCol;
  //    }
};