/**
 * @file iterator.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-07-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_ITERATOR_H_
#define SRC_MODULES_ITERATOR_H_

#include <algorithm>
#include <cstddef>
#include <iostream>

/// @brief Namespace for working with iterators.
namespace _iterators {

/**
 * @brief A bidirectional iterator class template.
 *
 * @details
 * This class template provides a bidirectional iterator for a collection of
 * elements of type `T`. It supports various iterator operations, including
 * incrementing and decrementing the iterator, as well as arithmetic operations
 * to advance the iterator by a specific number of positions. Comparison
 * operators and dereference operators are also provided to interact with
 * the elements pointed to by the iterator.
 *
 * @tparam T the type of the elements to be iterated over.
 */
template <typename value_type>
class iterator {
 public:
  using pointer = value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 private:
  value_type *ptr_ = nullptr;
  int index_ = 0;

 public:
  iterator() noexcept = default;
  explicit iterator(const pointer ptr);
  iterator(const iterator &other);

  void operator=(const iterator &other) noexcept;
  void operator=(pointer ptr) noexcept;
  iterator &operator--() noexcept;
  iterator &operator++() noexcept;
  const iterator operator--(int) noexcept;
  const iterator operator++(int) noexcept;
  iterator operator+(const int shift) const noexcept;
  iterator operator-(const int shift) const noexcept;
  size_type operator-(const iterator &other) const noexcept;
  void operator-=(const int shift) noexcept;
  void operator+=(const int shift) noexcept;
  bool operator==(iterator other) const noexcept;
  bool operator!=(iterator other) const noexcept;
  const_reference operator*() const;
  reference operator*();
};

/**
 * @brief Constructor with a pointer.
 *
 * @details
 * Takes a pointer to value_type as input and converts it to an object of type
 * iterator.
 *
 * @param[in] ptr pointer to the element.
 */
template <typename value_type>
iterator<value_type>::iterator(const pointer ptr) : ptr_{ptr} {}

/**
 * @brief Copy constructor from other iterator.
 *
 * @param[in] other the iterator to copy from.
 */
template <typename value_type>
iterator<value_type>::iterator(const iterator &other)
    : ptr_{other.ptr_}, index_{other.index_} {}

/**
 * @brief Dereference operator for constant access.
 *
 * @return const_reference - reference to the value pointed by the iterator.
 * @throws std::invalid_argument - if the iterator is empty.
 */
template <typename value_type>
typename iterator<value_type>::const_reference iterator<value_type>::operator*()
    const {
  if (!ptr_)
    throw std::invalid_argument("Trying to dereference an empty iterator");

  return *ptr_;
}

/**
 * @brief Dereference operator for non-constant access.
 *
 * @return reference - reference to the value pointed by the iterator.
 * @throws std::invalid_argument - if the iterator is empty.
 */
template <typename value_type>
typename iterator<value_type>::reference iterator<value_type>::operator*() {
  if (!ptr_)
    throw std::invalid_argument("Trying to dereference an empty iterator");

  return *ptr_;
}

/**
 * @brief Assignment operator from other iterator.
 *
 * @param[in] other the iterator to assign from.
 */
template <typename value_type>
void iterator<value_type>::operator=(const iterator &other) noexcept {
  ptr_ = other.ptr_;
  index_ = other.index_;
}

/**
 * @brief Assignment operator from a pointer.
 *
 * @param[in] ptr pointer to the element.
 */
template <typename value_type>
void iterator<value_type>::operator=(pointer ptr) noexcept {
  ptr_ = ptr;
  index_ = 0;
}

/**
 * @brief Pre-decrement operator.
 *
 * @return reference - reference to the updated iterator.
 */
template <typename value_type>
iterator<value_type> &iterator<value_type>::operator--() noexcept {
  ptr_--;
  index_--;

  return *this;
}

/**
 * @brief Post-decrement operator.
 *
 * @return iterator - copy of the iterator before the decrement.
 */
template <typename value_type>
const iterator<value_type> iterator<value_type>::operator--(
    int) noexcept {
  iterator copy{*this};
  ptr_--;
  index_--;

  return copy;
}

/**
 * @brief Pre-increment operator.
 *
 * @return reference - reference to the updated iterator.
 */
template <typename value_type>
iterator<value_type> &iterator<value_type>::operator++() noexcept {
  ptr_++;
  index_++;

  return *this;
}

/**
 * @brief Post-increment operator.
 *
 * @return iterator - copy of the iterator before the increment.
 */
template <typename value_type>
const iterator<value_type> iterator<value_type>::operator++(
    int) noexcept {
  iterator copy{*this};
  ptr_++;
  index_++;

  return copy;
}

/**
 * @brief Subtraction operator for shifting the iterator by a given number of
 * positions.
 *
 * @param[in] shift number of positions to shift.
 * @return iterator - new iterator shifted by the specified positions.
 */
template <typename value_type>
iterator<value_type> iterator<value_type>::operator-(
    const int shift) const noexcept {
  iterator copy(*this);
  copy.index_ -= shift;
  copy.ptr_ -= shift;

  return copy;
}

/**
 * @brief Difference operator to calculate the distance between two iterators.
 *
 * @param[in] other the other iterator to calculate the distance from.
 * @return size_type - distance between the iterators.
 */
template <typename value_type>
typename iterator<value_type>::size_type iterator<value_type>::operator-(const iterator &other) const noexcept {
  return (ptr_ > other.ptr_) ? ptr_ - other.ptr_ : other.ptr_ - ptr_;
}

/**
 * @brief Addition operator for shifting the iterator by a given number of
 * positions.
 *
 * @param[in] shift number of positions to shift.
 * @return iterator - new iterator shifted by the specified positions.
 */
template <typename value_type>
iterator<value_type> iterator<value_type>::operator+(
    const int shift) const noexcept {
  iterator copy(*this);
  copy.index_ += shift;
  copy.ptr_ += shift;

  return copy;
}

/**
 * @brief Subtraction assignment operator to shift the iterator by a given
 * number of positions.
 *
 * @param[in] shift number of positions to shift.
 */
template <typename value_type>
void iterator<value_type>::operator-=(const int shift) noexcept {
  index_ -= shift;
  ptr_ -= shift;
}

/**
 * @brief Addition assignment operator to shift the iterator by a given number
 * of positions.
 *
 * @param[in] shift number of positions to shift.
 */
template <typename value_type>
void iterator<value_type>::operator+=(const int shift) noexcept {
  index_ += shift;
  ptr_ += shift;
}

/**
 * @brief Equality comparison operator.
 *
 * @param[in] other the other iterator to compare with.
 * @return true - if the iterators are equal.
 * @return false - if the iterators are not equal.
 */
template <typename value_type>
bool iterator<value_type>::operator==(iterator other) const noexcept {
  return ptr_ == other.ptr_;
}

/**
 * @brief Inequality comparison operator.
 *
 * @param[in] other the other iterator to compare with.
 * @return true - if the iterators are not equal.
 * @return false - if the iterators are equal.
 */
template <typename value_type>
bool iterator<value_type>::operator!=(iterator other) const noexcept {
  return ptr_ != other.ptr_;
}

}  // namespace _iterators

#endif  // SRC_MODULES_ITERATOR_H_
