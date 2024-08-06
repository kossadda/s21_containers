/**
 * @file set.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header for the set container.
 * @version 1.0
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_CONTAINERS_SET_H_
#define SRC_CONTAINERS_SET_H_

#include <initializer_list>  // for init_list type
#include <limits>            // for max()
#include <string>            // for string type

#include "./tree.h"

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief A set container template class.
 *
 * @details
 * This template class set provides a set similar to std::set in the C++
 * Standard Library. It manages a balanced binary search tree of elements of
 * type K, supporting various operations including iteration, element access,
 * and size management.
 *
 * @tparam K The type of keys stored in the set.
 */
template <typename K>
class set {
 public:
  // Container types

  class SetConstIterator;
  class SetIterator;

  // Type aliases

  using key_type = const K;                    ///< Type of keys
  using value_type = const K;                  ///< Type of values
  using reference = value_type &;              ///< Reference to value
  using const_reference = const value_type &;  ///< Const reference to value
  using size_type = std::size_t;               ///< Containers size type
  using iterator = SetIterator;                ///< For read/write elements
  using const_iterator = SetConstIterator;     ///< For read elements
  using iterator_bool = std::pair<iterator, bool>;  ///< Pair iterator-bool

  // Constructors/assignment operators/destructor

  set() noexcept = default;
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  set &operator=(set &&s);
  set &operator=(const set &s);

  // Set Iterators

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Set Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Set Modifiers

  void clear();
  iterator_bool insert(const_reference value);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  void swap(set &other);
  void merge(set &other);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

  // Set Lookup

  iterator find(const key_type &key) const noexcept;
  bool conatains(const key_type &key) const noexcept;

 private:
  // Fields

  tree<const key_type, const key_type> tree_{};  ///< Tree of elements
};

/**
 * @brief An iterator for the set.
 *
 * @details
 * This class represents an iterator for the set. It allows traversal
 * of the set and access to its elements.
 *
 * @tparam K The type of keys stored in the set.
 */
template <typename K>
class set<K>::SetIterator : public tree<const K, const K>::TreeIterator {
 public:
  // Type aliases

  using _tree_it = typename tree<const K, const K>::TreeIterator;

  // Constructors

  SetIterator() noexcept = default;
  SetIterator(const SetIterator &other) noexcept : _tree_it{other} {}
  SetIterator(const _tree_it &other) noexcept : _tree_it{other} {}

  // Operators

  iterator &operator=(const iterator &other) noexcept;
  iterator &operator++() noexcept;
  iterator &operator--() noexcept;
  iterator operator++(int) noexcept;
  iterator operator--(int) noexcept;
  iterator operator+(size_type shift) const noexcept;
  iterator operator-(size_type shift) const noexcept;
  reference operator*() noexcept;
};

/**
 * @brief A constant iterator for the set.
 *
 * @details
 * This class represents a constant iterator for the set. It allows
 * traversal of the set and read-only access to its elements.
 *
 * @tparam K The type of keys stored in the set.
 */
template <typename K>
class set<K>::SetConstIterator
    : public tree<const K, const K>::TreeConstIterator {
 public:
  // Type aliases

  using _tree_cit = typename tree<const K, const K>::TreeConstIterator;

  // Constructors

  SetConstIterator() noexcept = default;
  SetConstIterator(const iterator &other) noexcept : _tree_cit(other) {}
  SetConstIterator(const const_iterator &other) noexcept : _tree_cit(other) {}
  SetConstIterator(const _tree_cit &other) noexcept : _tree_cit(other) {}

  // Operators

  const_iterator &operator=(const const_iterator &other) noexcept;
  const_iterator &operator++() noexcept;
  const_iterator &operator--() noexcept;
  const_iterator operator++(int) noexcept;
  const_iterator operator--(int) noexcept;
  const_iterator operator+(size_type shift) const noexcept;
  const_iterator operator-(size_type shift) const noexcept;
  const_reference operator*() const noexcept;
};

////////////////////////////////////////////////////////////////////////////////
//                              SET CONSTRUCTORS                              //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs a set with elements from an initializer list.
 *
 * @details
 * This constructor initializes the set with elements from the given
 * initializer list. It creates a new tree and inserts all elements from the
 * list into the tree.
 *
 * @param[in] items The initializer list of values to insert into the set.
 */
template <typename K>
set<K>::set(std::initializer_list<value_type> const &items) {
  for (auto i : items) {
    tree_.insert({i, i});
  }
}

/**
 * @brief Copy constructor for the set.
 *
 * @details
 * This constructor creates a new set by copying the elements from another set.
 * It initializes the tree with the elements from the source set.
 *
 * @param[in] s The set to copy from.
 */
template <typename K>
set<K>::set(const set &s) : tree_{s.tree_} {}

/**
 * @brief Move constructor for the set.
 *
 * @details
 * This constructor creates a new set by moving the elements from another set.
 * It takes ownership of the tree from the source set, leaving the source set
 * in a valid but unspecified state.
 *
 * @param[in] s The set to move from.
 */
template <typename K>
set<K>::set(set &&s) : tree_{std::move(s.tree_)} {}

/**
 * @brief Move assignment operator for the set.
 *
 * @details
 * This operator moves the elements from another set to the current set.
 * It first cleans up the current set and then moves the elements from the
 * source set.
 *
 * @param[in] s The set to move from.
 * @return set<K>& - reference to the assigned set.
 */
template <typename K>
set<K> &set<K>::operator=(set &&s) {
  if (this != &s) {
    tree_.clear();
    new (this) set{std::move(s)};
  }

  return *this;
}

/**
 * @brief Copy assignment operator for the set.
 *
 * @details
 * This operator copies the elements from another set to the current set.
 * It first cleans up the current set and then copies the elements from the
 * source set.
 *
 * @param[in] s The set to copy from.
 * @return set<K>& - reference to the assigned set.
 */
template <typename K>
set<K> &set<K>::operator=(const set &s) {
  if (this != &s) {
    tree_.clear();
    new (this) set{s};
  }

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
//                               SET ITERATORS                                //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Returns an iterator to the beginning of the set.
 *
 * @details
 * This method returns an iterator to the first element of the set.
 *
 * @return iterator - an iterator to the beginning of the set.
 */
template <typename K>
auto set<K>::begin() const noexcept -> iterator {
  return tree_.begin();
}

/**
 * @brief Returns an iterator to the end of the set.
 *
 * @details
 * This method returns an iterator to the element following the last element
 * of the set.
 *
 * @return iterator - an iterator to the end of the set.
 */
template <typename K>
auto set<K>::end() const noexcept -> iterator {
  return tree_.end();
}

/**
 * @brief Returns a const iterator to the beginning of the set.
 *
 * @details
 * This method returns a const iterator to the first element of the set.
 *
 * @return const_iterator - a const iterator to the beginning of the set.
 */
template <typename K>
auto set<K>::cbegin() const noexcept -> const_iterator {
  return tree_.cbegin();
}

/**
 * @brief Returns a const iterator to the end of the set.
 *
 * @details
 * This method returns a const iterator to the element following the last
 * element of the set.
 *
 * @return const_iterator - a const iterator to the end of the set.
 */
template <typename K>
auto set<K>::cend() const noexcept -> const_iterator {
  return tree_.cend();
}

////////////////////////////////////////////////////////////////////////////////
//                                SET CAPACITY                                //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the set is empty.
 *
 * @details
 * This method returns true if the set contains no elements, and false
 * otherwise.
 *
 * @return bool - true if the set is empty, false otherwise.
 */
template <typename K>
bool set<K>::empty() const noexcept {
  return (!tree_.size()) ? true : false;
}

/**
 * @brief Returns the number of elements in the set.
 *
 * @details
 * This method returns the number of elements currently stored in the set.
 *
 * @return size_type - the number of elements in the set.
 */
template <typename K>
auto set<K>::size() const noexcept -> size_type {
  return tree_.size();
}

/**
 * @brief Returns the maximum number of elements the set can hold.
 *
 * @return size_type - the maximum number of elements.
 */
template <typename K>
auto set<K>::max_size() const noexcept -> size_type {
  return tree_.max_size();
}

////////////////////////////////////////////////////////////////////////////////
//                                SET MODIFIERS                               //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Clears the contents of the set.
 *
 * @details
 * This method removes all elements from the set, leaving it empty.
 */
template <typename K>
void set<K>::clear() {
  tree_.clear();
}

/**
 * @brief Inserts a new element into the set.
 *
 * @details
 * This method inserts a new element with the given value into the set.
 * If the element already exists, it returns an iterator to the existing
 * element.
 *
 * @param[in] value The value to insert.
 * @return iterator_bool - a pair containing an iterator to the inserted element
 * and a bool indicating whether the insertion took place.
 */
template <typename K>
auto set<K>::insert(const_reference value) -> iterator_bool {
  iterator it = tree_.insert({value, value});

  return (it != end()) ? iterator_bool{it, true}
                       : iterator_bool{tree_.find(value), false};
}

/**
 * @brief Erases the element at the specified position.
 *
 * @details
 * This method removes the element at the specified position from the set.
 *
 * @param[in] pos The position of the element to erase.
 * @return iterator - an iterator to the element following the erased element,
 * or end() if the erased element was the last element.
 */
template <typename K>
auto set<K>::erase(const_iterator pos) -> iterator {
  return tree_.erase(*pos);
}

/**
 * @brief Erases the elements in the specified range.
 *
 * @details
 * This method removes the elements in the range [first, last) from the set.
 *
 * @param[in] first The position of the first element to erase.
 * @param[in] last The position following the last element to erase.
 * @return iterator - an iterator to the element following the last erased
 * element, or end() if the last erased element was the last element.
 * @throws std::range_error if the range is invalid.
 */
template <typename K>
auto set<K>::erase(const_iterator first, const_iterator last) -> iterator {
  return tree_.erase(first, last);
}

/**
 * @brief Swaps the contents of the set with another set.
 *
 * @details
 * This method swaps the contents of the set with the contents of another set.
 *
 * @param[in,out] other The set to swap with.
 */
template <typename K>
void set<K>::swap(set &other) {
  std::swap(tree_, other.tree_);
}

/**
 * @brief Merges the contents of another set into the current set.
 *
 * @details
 * This method merges the contents of another set into the current set.
 * The elements from the other set are inserted into the current set.
 *
 * @param[in,out] other The set to merge with.
 */
template <typename K>
void set<K>::merge(set &other) {
  tree_.merge(other.tree_);
}

/**
 * @brief Inserts a new element into the set, constructed in place.
 *
 * @details
 * This method constructs a new element directly in the set using the provided
 * arguments, and inserts it into the set. This can be more efficient than
 * inserting an already constructed element, as it avoids unnecessary copying or
 * moving. The method ensures that the set properties are maintained after the
 * insertion.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param args The arguments to forward to the constructor of the element.
 * @return A pair consisting of an iterator to the inserted element (or to the
 * element that prevented the insertion) and a bool indicating whether the
 * insertion took place.
 */
template <typename K>
template <typename... Args>
auto set<K>::emplace(Args &&...args) -> std::pair<iterator, bool> {
  return tree_.emplace(std::forward<Args>(args)...,
                       std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
//                                  SET LOOKUP                                //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Searches for an element with the specified key.
 *
 * @details
 * This method searches for an element with the specified key in the set.
 * If the key is found, it returns an iterator to the element. If the key is
 * not found, it returns an iterator to `end()`.
 *
 * @param[in] key The key to search for.
 * @return iterator - an iterator to the element with the specified key, or
 * `end()` if the key is not found.
 */
template <typename K>
auto set<K>::find(const key_type &key) const noexcept -> iterator {
  return tree_.find(key);
}

/**
 * @brief Checks if the set contains an element with the specified key.
 *
 * @details
 * This method returns true if the set contains an element with the specified
 * key, and false otherwise.
 *
 * @param[in] key The key to search for.
 * @return bool - true if the set contains an element with the specified key,
 * false otherwise.
 */
template <typename K>
bool set<K>::conatains(const key_type &key) const noexcept {
  return (tree_.find(key) != tree_.end()) ? true : false;
}

////////////////////////////////////////////////////////////////////////////////
//                           SET ITERATOR OPERATORS                           //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Assignment operator for the set iterator.
 *
 * @param[in] other The iterator to assign from.
 * @return iterator& - reference to the assigned iterator.
 */
template <typename K>
auto set<K>::iterator::operator=(const iterator &other) noexcept -> iterator & {
  this->ptr_ = other.ptr_;
  this->first_ = other.first_;
  this->last_ = other.last_;

  return *this;
}

/**
 * @brief Pre-increment operator for the set iterator.
 *
 * @return iterator& - reference to the incremented iterator.
 */
template <typename K>
auto set<K>::iterator::operator++() noexcept -> iterator & {
  *this += 1;

  return *this;
}

/**
 * @brief Post-increment operator for the set iterator.
 *
 * @return iterator - the original iterator before the increment.
 */
template <typename K>
auto set<K>::iterator::operator++(int) noexcept -> iterator {
  iterator copy{*this};

  *this += 1;

  return copy;
}

/**
 * @brief Pre-decrement operator for the set iterator.
 *
 * @return iterator& - reference to the decremented iterator.
 */
template <typename K>
auto set<K>::iterator::operator--() noexcept -> iterator & {
  *this -= 1;

  return *this;
}

/**
 * @brief Post-decrement operator for the set iterator.
 *
 * @return iterator - the original iterator before the decrement.
 */
template <typename K>
auto set<K>::iterator::operator--(int) noexcept -> iterator {
  iterator copy{*this};

  *this -= 1;

  return copy;
}

/**
 * @brief Addition operator for the set iterator.
 *
 * @param[in] shift The number of positions to shift.
 * @return iterator - the shifted iterator.
 */
template <typename K>
auto set<K>::iterator::operator+(size_type shift) const noexcept -> iterator {
  return _tree_it{*this} + shift;
}

/**
 * @brief Subtraction operator for the set iterator.
 *
 * @param[in] shift The number of positions to shift.
 * @return iterator - the shifted iterator.
 */
template <typename K>
auto set<K>::iterator::operator-(size_type shift) const noexcept -> iterator {
  return _tree_it{*this} - shift;
}

/**
 * @brief Dereference operator for the set iterator.
 *
 * @return reference - reference to the value at the current position.
 */
template <typename K>
auto set<K>::iterator::operator*() noexcept -> reference {
  return (*this->ptr_->pair).first;
}

////////////////////////////////////////////////////////////////////////////////
//                        SET CONST ITERATOR OPERATORS                        //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Assignment operator for the set const_iterator.
 *
 * @param[in] other The const_iterator to assign from.
 * @return const_iterator& - reference to the assigned const_iterator.
 */
template <typename K>
auto set<K>::const_iterator::operator=(const const_iterator &other) noexcept
    -> const_iterator & {
  this->ptr_ = other.ptr_;
  this->first_ = other.first_;
  this->last_ = other.last_;

  return *this;
}

/**
 * @brief Pre-increment operator for the set const_iterator.
 *
 * @return const_iterator& - reference to the incremented const_iterator.
 */
template <typename K>
auto set<K>::const_iterator::operator++() noexcept -> const_iterator & {
  *this += 1;

  return *this;
}

/**
 * @brief Post-increment operator for the set const_iterator.
 *
 * @return const_iterator - the original const_iterator before the increment.
 */
template <typename K>
auto set<K>::const_iterator::operator++(int) noexcept -> const_iterator {
  const_iterator copy{*this};

  *this += 1;

  return copy;
}

/**
 * @brief Pre-decrement operator for the set const_iterator.
 *
 * @return const_iterator& - reference to the decremented const_iterator.
 */
template <typename K>
auto set<K>::const_iterator::operator--() noexcept -> const_iterator & {
  *this -= 1;

  return *this;
}

/**
 * @brief Post-decrement operator for the set const_iterator.
 *
 * @return const_iterator - the original const_iterator before the decrement.
 */
template <typename K>
auto set<K>::const_iterator::operator--(int) noexcept -> const_iterator {
  const_iterator copy{*this};

  *this -= 1;

  return copy;
}

/**
 * @brief Addition operator for the set const_iterator.
 *
 * @param[in] shift The number of positions to shift.
 * @return const_iterator - the shifted const_iterator.
 */
template <typename K>
auto set<K>::const_iterator::operator+(size_type shift) const noexcept
    -> const_iterator {
  return _tree_cit{*this} + shift;
}

/**
 * @brief Subtraction operator for the set const_iterator.
 *
 * @param[in] shift The number of positions to shift.
 * @return const_iterator - the shifted const_iterator.
 */
template <typename K>
auto set<K>::const_iterator::operator-(size_type shift) const noexcept
    -> const_iterator {
  return _tree_cit{*this} - shift;
}

/**
 * @brief Dereference operator for the set const_iterator.
 *
 * @return const_reference - const reference to the value at the current
 * position.
 */
template <typename K>
auto set<K>::const_iterator::operator*() const noexcept -> const_reference {
  return (*this->ptr_->pair).first;
}

}  // namespace s21

#endif  // SRC_CONTAINERS_SET_H_
