/**
 * @file multiset.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_MULTISET_H_
#define SRC_MODULES_MULTISET_H_

#include "./set.h"

namespace s21 {

template <typename K>
class multiset {
 private:
  // Container types

  typedef typename set<K>::const_iterator MultisetConstIterator;
  typedef typename set<K>::iterator MultisetIterator;

 public:
  // Type aliases

  using key_type = const K;                      ///< Type of keys
  using value_type = const K;                    ///< Type of values
  using reference = value_type &;                ///< Reference to value
  using const_reference = const value_type &;    ///< Const reference to value
  using size_type = std::size_t;                 ///< Containers size type
  using iterator = MultisetIterator;             ///< For read/write elements
  using const_iterator = MultisetConstIterator;  ///< For read elements
  using iterator_bool = std::pair<iterator, bool>;       ///< Pair iterator-bool
  using iterator_range = std::pair<iterator, iterator>;  ///< Pair iterator-bool

 private:
  tree<const key_type, const key_type> tree_{
      tree<const key_type, const key_type>::NON_UNIQUE};  ///< Tree of elements
  size_type size_{};                                      ///< Size of multiset

 public:
  // Constructors/assignment operators/destructor

  multiset() noexcept = default;
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);
  multiset &operator=(multiset &&ms);
  multiset &operator=(const multiset &ms);

  // Multiset Iterators

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Multiset Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Multiset Modifiers

  void clear();
  iterator_bool insert(const_reference value);
  iterator erase(const_iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);

  // Multiset Lookup

  size_type count(const key_type &key) const noexcept;
  iterator find(const key_type &key) const noexcept;
  bool conatains(const key_type &key) const noexcept;
  iterator_bool equal_range(const key_type &key) const noexcept;
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
};

template <typename K>
multiset<K>::multiset(std::initializer_list<value_type> const &items) {
  for (auto i : items) {
    tree_.insert({i, i});
  }

  size_ = tree_.size();
}

template <typename K>
multiset<K>::multiset(const multiset &ms)
    : tree_{ms.tree_}, size_{tree_.size()} {}

template <typename K>
multiset<K>::multiset(multiset &&s)
    : tree_{std::move(s.tree_)}, size_{std::exchange(s.size_, 0)} {}

template <typename K>
auto multiset<K>::operator=(multiset &&ms) -> multiset & {
  if (this != &ms) {
    tree_.clear();
    new (this) multiset{std::move(ms)};
  }

  return *this;
}

template <typename K>
auto multiset<K>::operator=(const multiset &ms) -> multiset & {
  if (this != &ms) {
    tree_.clear();
    new (this) multiset{ms};
  }

  return *this;
}

template <typename K>
bool multiset<K>::empty() const noexcept {
  return (!size_) ? true : false;
}

template <typename K>
auto multiset<K>::size() const noexcept -> size_type {
  return size_;
}

template <typename K>
auto multiset<K>::max_size() const noexcept -> size_type {
  return tree_.max_size();
}

template <typename K>
auto multiset<K>::begin() const noexcept -> iterator {
  return tree_.begin();
}

template <typename K>
auto multiset<K>::end() const noexcept -> iterator {
  return tree_.end();
}

template <typename K>
auto multiset<K>::cbegin() const noexcept -> const_iterator {
  return tree_.cbegin();
}

template <typename K>
auto multiset<K>::cend() const noexcept -> const_iterator {
  return tree_.cend();
}

}  // namespace s21

#endif  // SRC_MODULES_MULTISET_H_
