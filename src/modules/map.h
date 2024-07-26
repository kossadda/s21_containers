/**
 * @file map.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_MAP_H_
#define SRC_MODULES_MAP_H_

#include "./tree.h"

namespace s21 {

template <typename K, typename M>
class map {
 private:
  // Container types

  // typedef  MapConstIterator;
  typedef typename tree<K, M>::iterator MapIterator;

 public:
  // Type aliases

  using key_type = K;
  using mapped_type = M;
  using value_type = std::pair<K, M>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_reference = const reference;
  using size_type = std::size_t;
  using iterator = MapIterator;
  // using const_iterator = MapConstIterator;

 private:
  size_type size_{};
  tree<K, M> tree_{};

 public:
  // Constructors/assignment operators/destructor

  map() noexcept = default;
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  map &operator=(map &&m);
  map &operator=(const map &m);

  iterator begin();

  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);
};

////////////////////////////////////////////////////////////////////////////////
//                              MAP CONSTRUCTORS                              //
////////////////////////////////////////////////////////////////////////////////

template <typename K, typename M>
map<K, M>::map(std::initializer_list<value_type> const &items)
    : size_{items.size()}, tree_{items} {}

template <typename K, typename M>
map<K, M>::map(const map &m) : size_{m.size_}, tree_{m.tree_} {}

template <typename K, typename M>
map<K, M>::map(map &&m)
    : size_{std::exchange(m.size_, 0)}, tree_{std::move(m.tree_)} {}

template <typename K, typename M>
map<K, M> &map<K, M>::operator=(map &&m) {
  if (this != &m) {
    tree_.clear();
    new (this) map{std::move(m)};
  }

  return *this;
}

template <typename K, typename M>
map<K, M> &map<K, M>::operator=(const map &m) {
  if (this != &m) {
    tree_.clear();
    new (this) map{m};
  }

  return *this;
}

template <typename K, typename M>
typename map<K, M>::mapped_type &map<K, M>::at(const key_type &key) {
  auto pair_it = tree_.search(key);

  if (pair_it == typename tree<key_type, mapped_type>::iterator{}) {
    throw std::out_of_range("map::at() - missing element");
  }

  return (*pair_it).second;
}

template <typename K, typename M>
typename map<K, M>::mapped_type &map<K, M>::operator[](const key_type &key) {
  auto pair_it = tree_.search(key);

  return (*pair_it).second;
}

template <typename K, typename M>
typename map<K, M>::iterator map<K, M>::begin() {
  return tree_.begin();
}

}  // namespace s21

#endif  // SRC_MODULES_MAP_H_
