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

  typedef typename tree<K, M>::const_iterator MapConstIterator;
  typedef typename tree<K, M>::iterator MapIterator;

 public:
  // Type aliases

  using key_type = K;
  using mapped_type = M;
  using value_type = std::pair<key_type, mapped_type>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_reference = const reference;
  using size_type = std::size_t;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using iterator_bool = std::pair<iterator, bool>;

 private:
  size_type size_{};
  tree<key_type, mapped_type> tree_{};

 public:
  // Constructors/assignment operators/destructor

  map() noexcept = default;
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  map &operator=(map &&m);
  map &operator=(const map &m);

  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator_bool insert(const_reference value);
  iterator_bool insert(const key_type &key, const mapped_type &obj);
  iterator_bool insert_or_assign(const key_type &key, const mapped_type &obj);
  iterator erase(const_iterator pos);
  void swap(map &other);
  void merge(map &other);

  mapped_type &at(const key_type &key);
  const mapped_type &operator[](const key_type &key) const;
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
  auto it = tree_.search(key);

  if (it == tree_.end()) {
    throw std::out_of_range("map::at() - missing element");
  }

  return (*it).second;
}

template <typename K, typename M>
const typename map<K, M>::mapped_type &map<K, M>::operator[](
    const key_type &key) const {
  auto pair_it = tree_.search(key);

  return (*pair_it).second;
}

template <typename K, typename M>
typename map<K, M>::mapped_type &map<K, M>::operator[](const key_type &key) {
  auto it = tree_.search(key);

  if (it == tree_.end()) {
    it = tree_.insert({key, mapped_type{}});
    ++size_;
  }

  return (*it).second;
}

template <typename K, typename M>
void map<K, M>::clear() {
  size_ = 0;
  tree_.clear();
}

template <typename K, typename M>
typename map<K, M>::iterator map<K, M>::begin() {
  return tree_.begin();
}

template <typename K, typename M>
typename map<K, M>::iterator map<K, M>::end() {
  return tree_.end();
}

template <typename K, typename M>
typename map<K, M>::const_iterator map<K, M>::cbegin() {
  return tree_.cbegin();
}

template <typename K, typename M>
typename map<K, M>::const_iterator map<K, M>::cend() {
  return tree_.cend();
}

template <typename K, typename M>
bool map<K, M>::empty() {
  return (tree_.begin() == tree_.end()) ? true : false;
}

template <typename K, typename M>
typename map<K, M>::size_type map<K, M>::size() {
  return size_;
}

template <typename K, typename M>
typename map<K, M>::iterator map<K, M>::erase(const_iterator pos) {
  auto it = tree_.erase((*pos).first);

  if (it == tree_.end()) {
    --size;
  }

  return it;
}

template <typename K, typename M>
typename map<K, M>::iterator_bool map<K, M>::insert(const_reference value) {
  auto it = tree_.insert(value);
  ++size_;

  return (it != tree_.end()) ? iterator_bool{it, true}
                             : iterator_bool{tree_.search(value.first), false};
}

template <typename K, typename M>
typename map<K, M>::iterator_bool map<K, M>::insert(const key_type &key,
                                                    const mapped_type &obj) {
  auto it = tree_.insert({key, obj});
  ++size_;

  return (it != end()) ? iterator_bool{it, true}
                       : iterator_bool{tree_.search(key), false};
}

template <typename K, typename M>
typename map<K, M>::iterator_bool map<K, M>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  auto it = tree_.search(key);
  bool obj_exists{false};

  if (it == tree_.end()) {
    it = tree_.insert({key, obj});
    ++size_;
    obj_exists = true;
  } else {
    (*it).second = obj;
  }

  return iterator_bool{it, obj_exists};
}

template <typename K, typename M>
void map<K, M>::swap(map &other) {
  std::swap(size_, other.size_);
  std::swap(tree_, other.tree_);
}


}  // namespace s21

#endif  // SRC_MODULES_MAP_H_
