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

#ifndef SRC_MODULES_VECTOR_H_
#define SRC_MODULES_VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief A dynamic array container template class.
 *
 * @details
 * This template class `vector` provides a dynamic array similar to
 * `std::vector` in the C++ Standard Library. It manages a dynamic array of
 * elements of type `T`, supporting various operations including iteration,
 * element access, and size management.
 *
 * @tparam value_type The type of elements stored in the vector.
 */
template <typename value_type>
class vector {
  class VectorIterator;

 public:
  using pointer = value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using iterator = vector<value_type>::VectorIterator;
  using const_iterator = const iterator;

 private:
  size_type size_{};
  size_type capacity_{};
  value_type *arr_{};

  pointer allocateMemory();
  void freeMemory() noexcept;

 public:
  vector() noexcept = default;
  explicit vector(size_type n, const_reference value = value_type{});
  vector(const std::initializer_list<value_type> &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector() noexcept;
  vector &operator=(vector &&v);

  // Vector Iterators
  iterator begin() const noexcept;
  iterator end() const noexcept;

  // Vector Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  // Vector Element access
  reference at(size_type pos) const;
  reference operator[](size_type pos) const noexcept;
  const_reference front() const noexcept;
  const_reference back() const noexcept;
  pointer data() const noexcept;

  // Vector Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value, size_type count = 1);
  void erase(iterator pos, iterator last_pos = iterator{});
};

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
 * @tparam value_type The type of the elements to be iterated over.
 */
template <typename value_type>
class vector<value_type>::VectorIterator {
 private:
  pointer ptr_{};

 public:
  VectorIterator() noexcept = default;
  explicit VectorIterator(const pointer ptr);
  VectorIterator(const iterator &other);

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
  pointer ptr() const noexcept;
};

////////////////////////////////////////////////////////////////////////////////
//                                    VECTOR                                  //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs a vector with a specified number of elements, each
 * initialized to a given value.
 *
 * @details
 * This constructor initializes the vector with `n` elements, each set to
 * `value`. It allocates memory for the elements, sets the size and capacity of
 * the vector to `n`, and fills the allocated memory with copies of `value`.
 *
 * @param[in] n The number of elements to be created in the vector.
 * @param[in] value The value to initialize the elements with. Defaults to a
 * default-constructed `value_type` if not provided.
 */
template <typename value_type>
vector<value_type>::vector(size_type n, const_reference value)
    : size_{n}, capacity_{n}, arr_{allocateMemory()} {
  if (size_) {
    std::fill(arr_, arr_ + size_, value);
  }
}

/**
 * @brief Constructs a vector from an initializer list.
 *
 * @details
 * Initializes the vector with the elements from the initializer list.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[in] items The initializer list containing elements.
 */
template <typename value_type>
vector<value_type>::vector(const std::initializer_list<value_type> &items)
    : size_{items.size()}, capacity_{items.size()}, arr_{allocateMemory()} {
  std::copy(items.begin(), items.begin() + size_, arr_);
}

/**
 * @brief Copy constructor.
 *
 * @details
 * Constructs a vector by copying another vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[in] v The vector to copy.
 */
template <typename value_type>
vector<value_type>::vector(const vector &v)
    : size_{v.size_}, capacity_{v.capacity_}, arr_{allocateMemory()} {
  std::copy(v.arr_, v.arr_ + v.size_, arr_);
}

/**
 * @brief Move constructor.
 *
 * @details
 * Constructs a vector by moving another vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[out] v The vector to move.
 */
template <typename value_type>
vector<value_type>::vector(vector &&v) noexcept
    : size_{std::exchange(v.size_, 0)},
      capacity_{std::exchange(v.capacity_, 0)},
      arr_{std::exchange(v.arr_, nullptr)} {}

/**
 * @brief Destructor.
 *
 * @details
 * Destroys the vector and frees allocated memory.
 *
 * @tparam value_type The type of elements stored in the vector.
 */
template <typename value_type>
vector<value_type>::~vector() noexcept {
  freeMemory();
}

/**
 * @brief Move assignment operator.
 *
 * @details
 * Assigns the contents of another vector to this vector using move semantics.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[out] v The vector to move.
 * @return vector& - reference to the assigned vector.
 */
template <typename value_type>
vector<value_type> &vector<value_type>::operator=(vector &&v) {
  freeMemory();
  new (this) vector{std::move(v)};

  return *this;
}

/**
 * @brief Allocates memory for the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return pointer A pointer to the allocated memory.
 * @throw std::bad_alloc - if the allocation failed.
 */
template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::allocateMemory() {
  return new value_type[capacity_]{};
}

/**
 * @brief Frees the memory allocated for the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 */
template <typename value_type>
void vector<value_type>::freeMemory() noexcept {
  if (arr_ != nullptr) {
    delete[] arr_;
    arr_ = nullptr;
  }

  size_ = capacity_ = 0;
}

/**
 * @brief Returns an iterator to the beginning of the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return iterator - an iterator to the beginning of the vector.
 */
template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin()
    const noexcept {
  return iterator{arr_};
}

/**
 * @brief Returns an iterator to the end of the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return iterator - an iterator to the end of the vector.
 */
template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() const noexcept {
  return iterator{arr_ + size_};
}

/**
 * @brief Checks if the vector is empty.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return true if the vector is empty, false otherwise.
 */
template <typename value_type>
bool vector<value_type>::empty() const noexcept {
  return (size_) ? false : true;
}

/**
 * @brief Returns the number of elements in the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return size_type - the number of elements in the vector.
 */
template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size()
    const noexcept {
  return size_;
}

/**
 * @brief Returns the maximum number of elements the vector can hold.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return size_type - the maximum number of elements.
 */
template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

/**
 * @brief Reserves memory for the specified number of elements.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[in] size The number of elements to reserve memory for.
 * @throw std::length_error - if the reserve size greater than max_size().
 */
template <typename value_type>
void vector<value_type>::reserve(size_type size) {
  if (size > max_size())
    throw std::length_error("vector::reserve() - size greater than max_size()");

  if (size > capacity_) {
    size_type vector_size = size_;
    vector expand(size);
    std::copy(arr_, arr_ + size_, expand.arr_);
    *this = std::move(expand);
    size_ = vector_size;
  }
}

/**
 * @brief Returns the current capacity of the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return size_type - the current capacity.
 */
template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity()
    const noexcept {
  return capacity_;
}

/**
 * @brief Reduces the capacity of the vector to fit its size.
 *
 * @tparam value_type The type of elements stored in the vector.
 */
template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (size_ != capacity_) {
    vector squeeze(size_);
    std::copy(arr_, arr_ + size_, squeeze.arr_);
    *this = std::move(squeeze);
  }
}

/**
 * @brief Returns a reference to the element at the specified position.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[in] pos The position of the element.
 * @return reference - a reference to the element at the specified position.
 * @throw std::out_of_range - if element position out of vector range.
 */
template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(
    size_type pos) const {
  if (pos >= size_)
    throw std::out_of_range("vector::at() - pos out of vector range");

  return *(arr_ + pos);
}

/**
 * @brief Returns a reference to the element at the specified position.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[in] pos The position of the element.
 * @return reference - a reference to the element at the specified position.
 */
template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) const noexcept {
  return *(arr_ + pos);
}

/**
 * @brief Returns a reference to the first element in the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return const_reference - a reference to the first element.
 */
template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front()
    const noexcept {
  return *arr_;
}

/**
 * @brief Returns a reference to the last element in the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return const_reference - a reference to the last element.
 */
template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back()
    const noexcept {
  return *(arr_ + size_ - 1);
}

/**
 * @brief Returns a pointer to the first element in the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return pointer - a pointer to the first element.
 */
template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::data() const noexcept {
  return arr_;
}

/**
 * @brief Removes all elements from the vector and sets its size to 0.
 *
 * @details
 * This method sets the vector's size to 0. The vector's capacity remains
 * unchanged, and the memory allocated for the elements is still available for
 * reuse.
 *
 * @tparam value_type The type of elements stored in the vector.
 */
template <typename value_type>
void vector<value_type>::clear() noexcept {
  size_ = 0;
}

/**
 * @brief Inserts multiple elements at the specified position in the vector.
 *
 * @details
 * This function inserts `count` copies of `value` before the element at the
 * specified iterator position `pos`. If the capacity of the vector is not
 * sufficient to hold the new elements, the vector will be resized to twice its
 * current capacity or the new size, whichever is larger. Existing elements are
 * moved to make space for the new elements, and the size of the vector is
 * updated accordingly.
 *
 * @param[in] pos Iterator position at which to insert the new elements.
 * @param[in] value The value to insert.
 * @param[in] count The number of copies of `value` to insert.
 * @return iterator - an iterator pointing to the first of the newly inserted
 * elements.
 * @throw std::out_of_range - if pos is not a valid iterator within the vector.
 */
template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value, size_type count) {
  if (pos.ptr() < arr_ || pos.ptr() > arr_ + size_) {
    throw std::out_of_range("vector::insert() - pos is not at vectors range");
  }

  size_type ins_pos = pos - begin();
  size_type new_size = size_ + count;

  if (capacity_ < new_size) {
    reserve((capacity_ * 2 >= new_size) ? capacity_ * 2 : new_size);
  }

  std::move_backward(arr_ + ins_pos, arr_ + size_, arr_ + size_ + count);
  std::fill(arr_ + ins_pos, arr_ + ins_pos + count, value);

  size_ = new_size;

  return begin() + ins_pos;
}

/**
 * @brief Removes elements from the vector within the specified range.
 *
 * @details
 * This function removes elements in the range [pos, last_pos). If `last_pos` is
 * not provided, it removes the single element at the position `pos`.
 *
 * @param[in] pos An iterator pointing to the first element to be removed.
 * @param[in] last_pos An iterator pointing to one past the last element to be
 * removed. Defaults to nullptr.
 *
 * @throw std::range_error - if pos or last_pos are out of the bounds of the
 * vector or if last_pos is before pos.
 */
template <typename value_type>
void vector<value_type>::erase(iterator pos, iterator last_pos) {
  if (last_pos.ptr() == nullptr) {
    last_pos = pos + 1;
  }

  if (pos.ptr() < arr_ || pos.ptr() > arr_ + capacity_ ||
      last_pos.ptr() < arr_ || last_pos.ptr() > arr_ + capacity_ ||
      last_pos.ptr() < pos.ptr()) {
    throw std::range_error("vector::erase() - invalid vector range");
  }

  size_type range = last_pos - pos;

  if (range) {
    std::copy(pos.ptr() + range, arr_ + size_, pos.ptr());
    size_ -= range;
  }
}

////////////////////////////////////////////////////////////////////////////////
//                                  ITERATORS                                 //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructor with a pointer.
 *
 * @details
 * Takes a pointer to value_type as input and converts it to an object of type
 * iterator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] ptr Pointer to the element.
 */
template <typename value_type>
vector<value_type>::iterator::VectorIterator(const pointer ptr) : ptr_{ptr} {}

/**
 * @brief Copy constructor from other iterator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The iterator to copy from.
 */
template <typename value_type>
vector<value_type>::iterator::VectorIterator(const iterator &other)
    : ptr_{other.ptr_} {}

/**
 * @brief Dereference operator for constant access.
 *
 * @return const_reference - reference to the value pointed by the iterator.
 * @throw std::invalid_argument - if the iterator is empty.
 */
template <typename value_type>
typename vector<value_type>::const_reference
vector<value_type>::iterator::operator*() const {
  if (!ptr_)
    throw std::invalid_argument(
        "iterator::operator*() - trying to dereference an empty iterator");

  return *ptr_;
}

/**
 * @brief Dereference operator for non-constant access.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return reference - reference to the value pointed by the iterator.
 * @throw std::invalid_argument - if the iterator is empty.
 */
template <typename value_type>
typename vector<value_type>::reference
vector<value_type>::iterator::operator*() {
  if (!ptr_)
    throw std::invalid_argument(
        "iterator::operator*() - trying to dereference an empty iterator");

  return *ptr_;
}

/**
 * @brief Assignment operator from other iterator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The iterator to assign from.
 */
template <typename value_type>
void vector<value_type>::iterator::operator=(const iterator &other) noexcept {
  ptr_ = other.ptr_;
}

/**
 * @brief Assignment operator from a pointer.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] ptr Pointer to the element.
 */
template <typename value_type>
void vector<value_type>::iterator::operator=(pointer ptr) noexcept {
  ptr_ = ptr;
}

/**
 * @brief Pre-decrement operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return reference - reference to the updated iterator.
 */
template <typename value_type>
typename vector<value_type>::iterator &
vector<value_type>::iterator::operator--() noexcept {
  ptr_--;

  return *this;
}

/**
 * @brief Post-decrement operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return iterator - copy of the iterator before the decrement.
 */
template <typename value_type>
const typename vector<value_type>::iterator
vector<value_type>::iterator::operator--(int) noexcept {
  iterator copy{*this};
  ptr_--;

  return copy;
}

/**
 * @brief Pre-increment operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return reference - reference to the updated iterator.
 */
template <typename value_type>
typename vector<value_type>::iterator &
vector<value_type>::iterator::operator++() noexcept {
  ptr_++;

  return *this;
}

/**
 * @brief Post-increment operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return iterator - copy of the iterator before the increment.
 */
template <typename value_type>
const typename vector<value_type>::iterator
vector<value_type>::iterator::operator++(int) noexcept {
  iterator copy{*this};
  ptr_++;

  return copy;
}

/**
 * @brief Subtraction operator for shifting the iterator by a given number of
 * positions.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] shift Number of positions to shift.
 * @return iterator - new iterator shifted by the specified positions.
 */
template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator-(
    const int shift) const noexcept {
  iterator copy(*this);
  copy.ptr_ -= shift;

  return copy;
}

/**
 * @brief Difference operator to calculate the distance between two iterators.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The other iterator to calculate the distance from.
 * @return size_type - distance between the iterators.
 */
template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::iterator::operator-(
    const iterator &other) const noexcept {
  return (ptr_ > other.ptr_) ? ptr_ - other.ptr_ : other.ptr_ - ptr_;
}

/**
 * @brief Addition operator for shifting the iterator by a given number of
 * positions.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] shift Number of positions to shift.
 * @return iterator - new iterator shifted by the specified positions.
 */
template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator+(
    const int shift) const noexcept {
  iterator copy(*this);
  copy.ptr_ += shift;

  return copy;
}

/**
 * @brief Subtraction assignment operator to shift the iterator by a given
 * number of positions.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] shift Number of positions to shift.
 */
template <typename value_type>
void vector<value_type>::iterator::operator-=(const int shift) noexcept {
  ptr_ -= shift;
}

/**
 * @brief Addition assignment operator to shift the iterator by a given number
 * of positions.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] shift Number of positions to shift.
 */
template <typename value_type>
void vector<value_type>::iterator::operator+=(const int shift) noexcept {
  ptr_ += shift;
}

/**
 * @brief Equality comparison operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The other iterator to compare with.
 * @return true - if the iterators are equal.
 * @return false - if the iterators are not equal.
 */
template <typename value_type>
bool vector<value_type>::iterator::operator==(iterator other) const noexcept {
  return ptr_ == other.ptr_;
}

/**
 * @brief Inequality comparison operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The other iterator to compare with.
 * @return true - if the iterators are not equal.
 * @return false - if the iterators are equal.
 */
template <typename value_type>
bool vector<value_type>::iterator::operator!=(iterator other) const noexcept {
  return ptr_ != other.ptr_;
}

/**
 * @brief Returns a pointer to the first element in the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return pointer - a pointer to the first element.
 */
template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::iterator::ptr()
    const noexcept {
  return ptr_;
}

}  // namespace s21

#endif  // SRC_MODULES_VECTOR_H_
