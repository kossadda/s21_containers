/**
 * @file vector.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header for the vector container
 * @version 1.0
 * @date 2024-06-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <utility>

/// @brief Namespace for working with containers
namespace container {

/**
 * @brief A dynamic array container template class.
 * 
 * @details
 * This template class `vector` provides a dynamic array similar to `std::vector`
 * in the C++ Standard Library. It manages a dynamic array of elements of type `T`,
 * supporting various operations including iteration, element access, and size management.
 * 
 * @tparam T the type of elements stored in the vector.
 */
template <class T>
class vector {
 public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class iterator {
   public:
    using iterator_reference = iterator &;
    using const_iterator_reference = const iterator &;

   private:
    T *ptr_ = nullptr;
    int index_ = 0;

   public:
    iterator() noexcept;
    explicit iterator(const pointer ptr);
    iterator(const_iterator_reference other);

    void operator=(const_iterator_reference other) noexcept;
    void operator=(pointer ptr) noexcept;
    iterator_reference operator--() noexcept;
    iterator_reference operator++() noexcept;
    iterator operator--(int) noexcept;
    iterator operator++(int) noexcept;
    iterator operator+(const int shift) const noexcept;
    iterator operator-(const int shift) const noexcept;
    size_type operator-(const_iterator_reference other) const noexcept;
    void operator-=(const int shift) noexcept;
    void operator+=(const int shift) noexcept;
    bool operator==(iterator other) const noexcept;
    bool operator!=(iterator other) const noexcept;
    const_reference operator*() const;
    reference operator*();
  };

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T *arr_ = nullptr;

  T *alloc();
  void remove() noexcept;

 public:
  vector() noexcept;
  ~vector() noexcept;
  vector(const size_type n);
  vector(const std::initializer_list<value_type> &items);
  vector(const vector &v);
  vector(vector &&v);

  size_type size() const noexcept { return size_; };
  size_type max_size() const noexcept { return capacity_; };
  iterator begin() const noexcept;
  iterator end() const noexcept;

  vector operator=(vector &&v);
};

/**
 * @brief Default constructor for vector iterator.
 *
 * @details
 * Creates an empty iterator object containing a null pointer.
 */
template <typename T>
vector<T>::iterator::iterator() noexcept = default;

/**
 * @brief Constructor with a pointer.
 *
 * @details
 * Takes a pointer to value_type as input and converts it to an object of type iterator.
 * 
 * @param[in] ptr pointer to the element.
 */
template <typename T>
vector<T>::iterator::iterator(const pointer ptr) : ptr_{ptr} {}

/**
 * @brief Copy constructor from const_iterator_reference.
 *
 * @param[in] other the const_iterator_reference to copy from.
 */
template <typename T>
vector<T>::iterator::iterator(const_iterator_reference other)
    : ptr_{other.ptr_}, index_{other.index_} {}

/**
 * @brief Dereference operator for constant access.
 *
 * @return const_reference - reference to the value pointed by the iterator.
 * @throws std::invalid_argument - if the iterator is empty.
 */
template <typename T>
const T &vector<T>::iterator::operator*() const {
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
template <typename T>
T &vector<T>::iterator::operator*() {
  if (!ptr_)
    throw std::invalid_argument("Trying to dereference an empty iterator");

  return *ptr_;
}

/**
 * @brief Assignment operator from const_iterator_reference.
 *
 * @param[in] other the const_iterator_reference to assign from.
 */
template <typename T>
void vector<T>::iterator::operator=(const_iterator_reference other) noexcept {
  ptr_ = other.ptr_;
  index_ = other.index_;
}

/**
 * @brief Assignment operator from a pointer.
 *
 * @param[in] ptr pointer to the element.
 */
template <typename T>
void vector<T>::iterator::operator=(pointer ptr) noexcept {
  ptr_ = ptr;
  index_ = 0;
}

/**
 * @brief Pre-decrement operator.
 *
 * @return reference - reference to the updated iterator.
 */
template <typename T>
class vector<T>::iterator &vector<T>::iterator::operator--() noexcept {
  ptr_--;
  index_--;

  return *this;
}

/**
 * @brief Post-decrement operator.
 *
 * @return iterator - copy of the iterator before the decrement.
 */
template <typename T>
class vector<T>::iterator vector<T>::iterator::operator--(int) noexcept {
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
template <typename T>
class vector<T>::iterator &vector<T>::iterator::operator++() noexcept {
  ptr_++;
  index_++;

  return *this;
}

/**
 * @brief Post-increment operator.
 *
 * @return iterator - copy of the iterator before the increment.
 */
template <typename T>
class vector<T>::iterator vector<T>::iterator::operator++(int) noexcept {
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
template <typename T>
class vector<T>::iterator vector<T>::iterator::operator-(
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
template <typename T>
size_t vector<T>::iterator::operator-(
    const_iterator_reference other) const noexcept {
  return (ptr_ > other.ptr_) ? ptr_ - other.ptr_ : other.ptr_ - ptr_;
}

/**
 * @brief Addition operator for shifting the iterator by a given number of
 * positions.
 *
 * @param[in] shift number of positions to shift.
 * @return iterator - new iterator shifted by the specified positions.
 */
template <typename T>
class vector<T>::iterator vector<T>::iterator::operator+(
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
template <typename T>
void vector<T>::iterator::operator-=(const int shift) noexcept {
  index_ -= shift;
  ptr_ -= shift;
}

/**
 * @brief Addition assignment operator to shift the iterator by a given number
 * of positions.
 *
 * @param[in] shift number of positions to shift.
 */
template <typename T>
void vector<T>::iterator::operator+=(const int shift) noexcept {
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
template <typename T>
bool vector<T>::iterator::operator==(iterator other) const noexcept {
  return ptr_ == other.ptr_;
}

/**
 * @brief Inequality comparison operator.
 *
 * @param[in] other the other iterator to compare with.
 * @return true - if the iterators are not equal.
 * @return false - if the iterators are equal.
 */
template <typename T>
bool vector<T>::iterator::operator!=(iterator other) const noexcept {
  return ptr_ != other.ptr_;
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
T *vector<T>::alloc() {
  return new T[capacity_]{};
}

template <typename T>
void vector<T>::remove() noexcept {
  delete[] arr_;
  arr_ = nullptr;
  size_ = capacity_ = 0;
}

template <typename T>
class vector<T>::iterator vector<T>::begin() const noexcept {
  return iterator{arr_};
}

template <typename T>
class vector<T>::iterator vector<T>::end() const noexcept {
  return iterator{arr_ + size_};
}

template <typename T>
vector<T>::vector() noexcept {
}

template <typename T>
vector<T>::~vector() noexcept {
  remove();
}

template <typename T>
vector<T>::vector(size_type n) : size_{n}, capacity_{n}, arr_{alloc()} {}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &item)
    : size_{item.size()}, capacity_{item.size()}, arr_{alloc()} {
  std::copy(item.begin(), item.begin() + size_, arr_);
}

}  // namespace container

#endif  // _VECTOR_H_