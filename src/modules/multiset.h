/**
 * @file multiset.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header for the multiset container.
 * @version 1.0
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_CONTAINERS_MULTISET_H_
#define SRC_CONTAINERS_MULTISET_H_

#include <initializer_list>  // for init_list type
#include <limits>            // for max()
#include <string>            // for string type

#include "./set.h"

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief A multiset container template class.
 *
 * @details
 * This template class multiset provides a multiset similar to std::multiset in
 * the C++ Standard Library. It manages a balanced binary search tree of
 * elements of type K, supporting various operations including iteration,
 * element access, and size management.
 *
 * @tparam K The type of keys stored in the multiset.
 */
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
  using iterator_range = std::pair<iterator, iterator>;  ///< Pair iterator-bool

 private:
  tree<const key_type, const key_type> tree_{
      tree<const key_type, const key_type>::kNON_UNIQUE};  ///< Tree of elements

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
  iterator insert(const_reference value);
  iterator erase(const_iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);

  template <typename... Args>
  iterator emplace(Args &&...args);

  // Multiset Lookup

  size_type count(const key_type &key) const noexcept;
  iterator find(const key_type &key) const noexcept;
  bool conatains(const key_type &key) const noexcept;
  iterator_range equal_range(const key_type &key) const noexcept;
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
};

////////////////////////////////////////////////////////////////////////////////
//                           MULTISET CONSTRUCTORS                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs a multiset with elements from an initializer list.
 *
 * @details
 * This constructor initializes the multiset with elements from the given
 * initializer list. It creates a new tree and inserts all elements from the
 * list into the tree.
 *
 * @param[in] items The initializer list of values to insert into the multiset.
 */
template <typename K>
multiset<K>::multiset(std::initializer_list<value_type> const &items) {
  for (auto i : items) {
    tree_.insert({i, i});
  }
}

/**
 * @brief Copy constructor for the multiset.
 *
 * @details
 * This constructor creates a new multiset by copying the elements from another
 * multiset. It initializes the tree with the elements from the source multiset.
 *
 * @param[in] ms The multiset to copy from.
 */
template <typename K>
multiset<K>::multiset(const multiset &ms) : tree_{ms.tree_} {}

/**
 * @brief Move constructor for the multiset.
 *
 * @details
 * This constructor creates a new multiset by moving the elements from another
 * multiset. It takes ownership of the tree from the source multiset, leaving
 * the source multiset in a valid but unspecified state.
 *
 * @param[in] ms The multiset to move from.
 */
template <typename K>
multiset<K>::multiset(multiset &&s) : tree_{std::move(s.tree_)} {}

/**
 * @brief Move assignment operator for the multiset.
 *
 * @details
 * This operator moves the elements from another multiset to the current
 * multiset. It first cleans up the current multiset and then moves the elements
 * from the source multiset.
 *
 * @param[in] ms The multiset to move from.
 * @return multiset<K>& - reference to the assigned multiset.
 */
template <typename K>
auto multiset<K>::operator=(multiset &&ms) -> multiset & {
  if (this != &ms) {
    tree_.clear();
    new (this) multiset{std::move(ms)};
  }

  return *this;
}

/**
 * @brief Copy assignment operator for the multiset.
 *
 * @details
 * This operator copies the elements from another multiset to the current
 * multiset. It first cleans up the current multiset and then copies the
 * elements from the source multiset.
 *
 * @param[in] ms The multiset to copy from.
 * @return multiset<K>& - reference to the assigned multiset.
 */
template <typename K>
auto multiset<K>::operator=(const multiset &ms) -> multiset & {
  if (this != &ms) {
    tree_.clear();
    new (this) multiset{ms};
  }

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
//                             MULTISET ITERATORS                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Returns an iterator to the beginning of the multiset.
 *
 * @details
 * This method returns an iterator to the first element of the multiset.
 *
 * @return iterator - an iterator to the beginning of the multiset.
 */
template <typename K>
auto multiset<K>::begin() const noexcept -> iterator {
  return tree_.begin();
}

/**
 * @brief Returns an iterator to the end of the multiset.
 *
 * @details
 * This method returns an iterator to the element following the last element
 * of the multiset.
 *
 * @return iterator - an iterator to the end of the multiset.
 */
template <typename K>
auto multiset<K>::end() const noexcept -> iterator {
  return tree_.end();
}

/**
 * @brief Returns a const iterator to the beginning of the multiset.
 *
 * @details
 * This method returns a const iterator to the first element of the multiset.
 *
 * @return const_iterator - a const iterator to the beginning of the multiset.
 */
template <typename K>
auto multiset<K>::cbegin() const noexcept -> const_iterator {
  return tree_.cbegin();
}

/**
 * @brief Returns a const iterator to the end of the multiset.
 *
 * @details
 * This method returns a const iterator to the element following the last
 * element of the multiset.
 *
 * @return const_iterator - a const iterator to the end of the multiset.
 */
template <typename K>
auto multiset<K>::cend() const noexcept -> const_iterator {
  return tree_.cend();
}

////////////////////////////////////////////////////////////////////////////////
//                             MULTISET CAPACITY                              //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the multiset is empty.
 *
 * @details
 * This method returns true if the multiset contains no elements, and false
 * otherwise.
 *
 * @return bool - true if the multiset is empty, false otherwise.
 */
template <typename K>
bool multiset<K>::empty() const noexcept {
  return (!tree_.size()) ? true : false;
}

/**
 * @brief Returns the number of elements in the multiset.
 *
 * @details
 * This method returns the number of elements currently stored in the multiset.
 *
 * @return size_type - the number of elements in the multiset.
 */
template <typename K>
auto multiset<K>::size() const noexcept -> size_type {
  return tree_.size();
}

/**
 * @brief Returns the maximum number of elements the multiset can hold.
 *
 * @return size_type - the maximum number of elements.
 */
template <typename K>
auto multiset<K>::max_size() const noexcept -> size_type {
  return tree_.max_size();
}

////////////////////////////////////////////////////////////////////////////////
//                             MULTISET MODIFIERS                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Clears the contents of the multiset.
 *
 * @details
 * This method removes all elements from the multiset, leaving it empty.
 */
template <typename K>
void multiset<K>::clear() {
  tree_.clear();
}

/**
 * @brief Inserts a new element into the multiset.
 *
 * @details
 * This method inserts a new element with the given value into the multiset.
 * If the element already exists, it returns an iterator to the existing
 * element.
 *
 * @param[in] value The value to insert.
 * @return iterator - an iterator to the inserted element.
 */
template <typename K>
auto multiset<K>::insert(const_reference value) -> iterator {
  return tree_.insert({value, value});
}

/**
 * @brief Erases the element at the specified position.
 *
 * @details
 * This method removes the element at the specified position from the multiset.
 *
 * @param[in] pos The position of the element to erase.
 * @return iterator - an iterator to the element following the erased element,
 * or end() if the erased element was the last element.
 */
template <typename K>
auto multiset<K>::erase(const_iterator pos) -> iterator {
  return tree_.erase(pos);
}

/**
 * @brief Swaps the contents of the multiset with another multiset.
 *
 * @details
 * This method swaps the contents of the multiset with the contents of another
 * multiset.
 *
 * @param[in,out] other The multiset to swap with.
 */
template <typename K>
void multiset<K>::swap(multiset &other) {
  std::swap(tree_, other.tree_);
}

/**
 * @brief Merges the contents of another multiset into the current multiset.
 *
 * @details
 * This method merges the contents of another multiset into the current
 * multiset. The elements from the other multiset are inserted into the current
 * multiset.
 *
 * @param[in,out] other The multiset to merge with.
 */
template <typename K>
void multiset<K>::merge(multiset &other) {
  tree_.merge(other.tree_);
}

/**
 * @brief Inserts a new element into the multiset, constructed in place.
 *
 * @details
 * This method constructs a new element directly in the multiset using the
 * provided arguments, and inserts it into the set. This can be more efficient
 * than inserting an already constructed element, as it avoids unnecessary
 * copying or moving. The method ensures that the set properties are maintained
 * after the insertion.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param args The arguments to forward to the constructor of the element.
 * @return An iterator to the inserted element.
 */
template <typename K>
template <typename... Args>
auto multiset<K>::emplace(Args &&...args) -> iterator {
  return (tree_.emplace(std::forward<Args>(args)...,
                        std::forward<Args>(args)...))
      .first;
}

////////////////////////////////////////////////////////////////////////////////
//                              MULTISET LOOKUP                               //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Counts the number of elements with the specified key.
 *
 * @details
 * This method returns the number of elements in the multiset with the specified
 * key.
 *
 * @param[in] key The key to search for.
 * @return size_type - the number of elements with the specified key.
 */
template <typename K>
auto multiset<K>::count(const key_type &key) const noexcept -> size_type {
  size_type cnt{};

  for (auto i : *this) {
    if (i == key) {
      ++cnt;
    } else if (i != key && cnt) {
      break;
    }
  }

  return cnt;
}

/**
 * @brief Searches for an element with the specified key.
 *
 * @details
 * This method searches for an element with the specified key in the multiset.
 * If the key is found, it returns an iterator to the element. If the key is
 * not found, it returns an iterator to `end()`.
 *
 * @param[in] key The key to search for.
 * @return iterator - an iterator to the element with the specified key, or
 * `end()` if the key is not found.
 */
template <typename K>
auto multiset<K>::find(const key_type &key) const noexcept -> iterator {
  return tree_.find(key);
}

/**
 * @brief Checks if the multiset contains an element with the specified key.
 *
 * @details
 * This method returns true if the multiset contains an element with the
 * specified key, and false otherwise.
 *
 * @param[in] key The key to search for.
 * @return bool - true if the multiset contains an element with the specified
 * key, false otherwise.
 */
template <typename K>
bool multiset<K>::conatains(const key_type &key) const noexcept {
  return (tree_.find(key) != tree_.end()) ? true : false;
}

/**
 * @brief Returns a range containing all elements with the specified key.
 *
 * @details
 * This method returns a pair of iterators representing the range of elements
 * with the specified key. If the key is not found, both iterators will point
 * to `end()`.
 *
 * @param[in] key The key to search for.
 * @return iterator_range - a pair of iterators representing the range of
 * elements with the specified key.
 */
template <typename K>
auto multiset<K>::equal_range(const key_type &key) const noexcept
    -> iterator_range {
  iterator first{end()};
  iterator last{end()};
  size_type cnt{};

  for (iterator i = begin(); i != end(); i++) {
    if (*i == key && !cnt) {
      first = i;
      ++cnt;
    } else if (*i > key) {
      last = i;
      if (!cnt) {
        first = i;
      }
      break;
    }
  }

  return iterator_range{first, last};
}

/**
 * @brief Returns an iterator to the first element not less than the specified
 * key.
 *
 * @details
 * This method returns an iterator to the first element in the multiset that is
 * not less than the specified key. If no such element is found, it returns an
 * iterator to `end()`.
 *
 * @param[in] key The key to search for.
 * @return iterator - an iterator to the first element not less than the
 * specified key.
 */
template <typename K>
auto multiset<K>::lower_bound(const key_type &key) -> iterator {
  iterator first{end()};

  for (iterator i = begin(); i != end(); i++) {
    if (*i == key) {
      first = i;
      break;
    } else if (*i > key) {
      first = i;
      break;
    }
  }

  return first;
}

/**
 * @brief Returns an iterator to the first element greater than the specified
 * key.
 *
 * @details
 * This method returns an iterator to the first element in the multiset that is
 * greater than the specified key. If no such element is found, it returns an
 * iterator to `end()`.
 *
 * @param[in] key The key to search for.
 * @return iterator - an iterator to the first element greater than the
 * specified key.
 */
template <typename K>
auto multiset<K>::upper_bound(const key_type &key) -> iterator {
  iterator last{end()};

  for (iterator i = begin(); i != end(); i++) {
    if (*i > key) {
      last = i;
      break;
    }
  }

  return last;
}

}  // namespace s21

#endif  // SRC_CONTAINERS_MULTISET_H_
