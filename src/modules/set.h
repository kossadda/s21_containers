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

#ifndef SRC_MODULES_SET_H_
#define SRC_MODULES_SET_H_

#include <limits>

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
 private:
  // Container types

  class SetConstIterator;
  class SetIterator;

 public:
  // Type aliases

  using key_type = const K;                    ///< Type of keys
  using value_type = const K;                  ///< Type of values
  using reference = value_type &;              ///< Reference to value
  using const_reference = const value_type &;  ///< Const reference to value
  using size_type = std::size_t;               ///< Containers size type
  using iterator = SetIterator;                ///< For read/write elements
  using const_iterator = SetConstIterator;     ///< For read elements
  using iterator_bool = std::pair<iterator, bool>;  ///< Pair iterator-bool
  using pair = std::pair<K, K>;                     ///< Pair key-value

 private:
  tree<const key_type, const key_type> tree_{};  ///< Tree of elements
  size_type size_{};                             ///< Size of set

 public:
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

  // Map Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Map Modifiers

  void clear();
  iterator_bool insert(const_reference value);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  void swap(set &other);
  void merge(set &other);

  // Map Lookup

  iterator find(const key_type &key) const noexcept;
  bool conatains(const key_type &key) const noexcept;
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
  using _tree_it = typename tree<const K, const K>::TreeIterator;

  SetIterator() noexcept = default;
  SetIterator(const SetIterator &other) noexcept : _tree_it{other} {}
  SetIterator(const _tree_it &other) noexcept : _tree_it{other} {}

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
  using _tree_cit = typename tree<const K, const K>::TreeConstIterator;

  SetConstIterator() noexcept = default;
  SetConstIterator(const iterator &other) noexcept : _tree_cit(other) {}
  SetConstIterator(const const_iterator &other) noexcept : _tree_cit(other) {}
  SetConstIterator(const _tree_cit &other) noexcept : _tree_cit(other) {}

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

  size_ = tree_.size();
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
set<K>::set(const set &s) : tree_{s.tree_}, size_{tree_.size()} {}

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
set<K>::set(set &&s)
    : tree_{std::move(s.tree_)}, size_{std::exchange(s.size_, 0)} {}

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
typename set<K>::iterator set<K>::begin() const noexcept {
  return tree_.begin();
}

template <typename K>
typename set<K>::const_iterator set<K>::cbegin() const noexcept {
  return tree_.cbegin();
}

template <typename K>
typename set<K>::iterator set<K>::end() const noexcept {
  return tree_.end();
}

template <typename K>
typename set<K>::const_iterator set<K>::cend() const noexcept {
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
  return (!size_) ? true : false;
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
typename set<K>::size_type set<K>::size() const noexcept {
  return size_;
}

/**
 * @brief Returns the maximum number of elements the set can hold.
 *
 * @return size_type - the maximum number of elements.
 */
template <typename K>
typename set<K>::size_type set<K>::max_size() const noexcept {
  size_type num_of_ptr = 4;
  size_type ptr_size = 8;
  size_type node_size = num_of_ptr * ptr_size + sizeof(size_type);
  return std::numeric_limits<size_type>::max() / sizeof(node_size) / 10;
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
  size_ = tree_.size();
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
typename set<K>::iterator_bool set<K>::insert(const_reference value) {
  iterator it = tree_.insert({value, value});
  size_ = tree_.size();

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
typename set<K>::iterator set<K>::erase(const_iterator pos) {
  iterator it = tree_.erase(*pos);
  size_ = tree_.size();

  return it;
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
typename set<K>::iterator set<K>::erase(const_iterator first,
                                        const_iterator last) {
  iterator it = tree_.erase(first, last);
  size_ = tree_.size();

  return it;
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
  std::swap(size_, other.size_);
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
  size_ = tree_.size();
  other.size_ = other.tree_.size();
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
typename set<K>::iterator set<K>::find(const key_type &key) const noexcept {
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
typename set<K>::iterator &set<K>::iterator::operator=(
    const iterator &other) noexcept {
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
typename set<K>::iterator &set<K>::iterator::operator++() noexcept {
  *this += 1;

  return *this;
}

/**
 * @brief Post-increment operator for the set iterator.
 *
 * @return iterator - the original iterator before the increment.
 */
template <typename K>
typename set<K>::iterator set<K>::iterator::operator++(int) noexcept {
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
typename set<K>::iterator &set<K>::iterator::operator--() noexcept {
  *this -= 1;

  return *this;
}

/**
 * @brief Post-decrement operator for the set iterator.
 *
 * @return iterator - the original iterator before the decrement.
 */
template <typename K>
typename set<K>::iterator set<K>::iterator::operator--(int) noexcept {
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
typename set<K>::iterator set<K>::iterator::operator+(
    size_type shift) const noexcept {
  return _tree_it{*this} + shift;
}

/**
 * @brief Subtraction operator for the set iterator.
 *
 * @param[in] shift The number of positions to shift.
 * @return iterator - the shifted iterator.
 */
template <typename K>
typename set<K>::iterator set<K>::iterator::operator-(
    size_type shift) const noexcept {
  return _tree_it{*this} - shift;
}

/**
 * @brief Dereference operator for the set iterator.
 *
 * @return reference - reference to the value at the current position.
 */
template <typename K>
typename set<K>::reference set<K>::iterator::operator*() noexcept {
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
typename set<K>::const_iterator &set<K>::const_iterator::operator=(
    const const_iterator &other) noexcept {
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
typename set<K>::const_iterator &set<K>::const_iterator::operator++() noexcept {
  *this += 1;

  return *this;
}

/**
 * @brief Post-increment operator for the set const_iterator.
 *
 * @return const_iterator - the original const_iterator before the increment.
 */
template <typename K>
typename set<K>::const_iterator set<K>::const_iterator::operator++(
    int) noexcept {
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
typename set<K>::const_iterator &set<K>::const_iterator::operator--() noexcept {
  *this -= 1;

  return *this;
}

/**
 * @brief Post-decrement operator for the set const_iterator.
 *
 * @return const_iterator - the original const_iterator before the decrement.
 */
template <typename K>
typename set<K>::const_iterator set<K>::const_iterator::operator--(
    int) noexcept {
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
typename set<K>::const_iterator set<K>::const_iterator::operator+(
    size_type shift) const noexcept {
  return _tree_cit{*this} + shift;
}

/**
 * @brief Subtraction operator for the set const_iterator.
 *
 * @param[in] shift The number of positions to shift.
 * @return const_iterator - the shifted const_iterator.
 */
template <typename K>
typename set<K>::const_iterator set<K>::const_iterator::operator-(
    size_type shift) const noexcept {
  return _tree_cit{*this} - shift;
}

/**
 * @brief Dereference operator for the set const_iterator.
 *
 * @return const_reference - const reference to the value at the current
 * position.
 */
template <typename K>
typename set<K>::const_reference set<K>::const_iterator::operator*()
    const noexcept {
  return (*this->ptr_->pair).first;
}

}  // namespace s21

#endif  // SRC_MODULES_SET_H_
