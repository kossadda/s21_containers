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
 * This template class vector provides a dynamic array similar to
 * std::vector in the C++ Standard Library. It manages a dynamic array of
 * elements of type value_type, supporting various operations including
 * iteration, element access, and size management.
 *
 * @tparam value_type The type of elements stored in the vector.
 */
template <typename value_type>
class vector {
  class VectorConstIterator;
  class VectorIterator;

 public:
  using pointer = value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;

 private:
  size_type size_{};
  size_type capacity_{};
  value_type *arr_{};

  pointer allocateMemory(size_type size, size_type capacity);
  void freeMemory() noexcept;

 public:
  vector() noexcept = default;
  explicit vector(size_type n, const_reference value = value_type{});
  vector(const std::initializer_list<value_type> &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector() noexcept;
  vector &operator=(vector &&v);
  vector &operator=(const vector &v);

  // Vector Iterators
  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

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
  const_iterator insert(const_iterator pos, const_reference value,
                        size_type count = 1);
  void erase(const_iterator pos, const_iterator last_pos = const_iterator{});
  void push_back(const_reference value);
  void pop_back() noexcept;
  void swap(vector &other) noexcept;
};

/**
 * @brief A constant iterator for the vector class.
 *
 * @details
 * This iterator allows traversal of elements in the vector without modifying
 * them. It supports typical iterator operations such as increment, decrement,
 * addition, subtraction, and dereference.
 *
 * @tparam value_type The type of elements stored in the vector.
 */
template <typename value_type>
class vector<value_type>::VectorConstIterator {
 private:
  pointer ptr_{};

 public:
  VectorConstIterator() noexcept = default;
  explicit VectorConstIterator(const pointer ptr);
  VectorConstIterator(const const_iterator &other);

  // ConstIterator operators
  operator pointer() const noexcept;
  const_iterator &operator=(const const_iterator &other) noexcept;
  const_iterator &operator=(const pointer ptr) noexcept;
  const_iterator &operator--() noexcept;
  const_iterator &operator++() noexcept;
  const_iterator operator--(int) noexcept;
  const_iterator operator++(int) noexcept;
  const_iterator operator+(const int shift) const noexcept;
  const_iterator operator-(const int shift) const noexcept;
  size_type operator-(const const_iterator &other) const noexcept;
  void operator-=(const int shift) noexcept;
  void operator+=(const int shift) noexcept;
  bool operator==(const_iterator other) const noexcept;
  bool operator!=(const_iterator other) const noexcept;
  const_reference operator*() const;
};

/**
 * @brief An iterator for the vector class.
 *
 * @details
 * This iterator allows traversal of elements in the vector and modifying them.
 * It inherits from VectorConstIterator and overrides the dereference operator
 * to allow modification of the elements.
 *
 * @tparam value_type The type of elements stored in the vector.
 */
template <typename value_type>
class vector<value_type>::VectorIterator {
 private:
  pointer ptr_{};

 public:
  VectorIterator() noexcept = default;
  explicit VectorIterator(const pointer ptr);
  VectorIterator(const iterator &other);

  // Iterator operators
  operator pointer() const noexcept;
  iterator &operator=(const iterator &other) noexcept;
  iterator &operator=(const pointer ptr) noexcept;
  iterator &operator--() noexcept;
  iterator &operator++() noexcept;
  iterator operator--(int) noexcept;
  iterator operator++(int) noexcept;
  iterator operator+(const int shift) const noexcept;
  iterator operator-(const int shift) const noexcept;
  size_type operator-(const iterator &other) const noexcept;
  void operator-=(const int shift) noexcept;
  void operator+=(const int shift) noexcept;
  bool operator==(iterator other) const noexcept;
  bool operator!=(iterator other) const noexcept;
  reference operator*();
};

////////////////////////////////////////////////////////////////////////////////
//                         VECTOR PRIVATE METHODS                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocates memory for the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return pointer A pointer to the allocated memory.
 * @throw std::bad_alloc - if the allocation failed.
 */
template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::allocateMemory(
    size_type size, size_type capacity) {
  size_ = size;
  capacity_ = capacity;

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

////////////////////////////////////////////////////////////////////////////////
//                            VECTOR CONSTRUCTORS                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs a vector with a specified number of elements, each
 * initialized to a given value.
 *
 * @details
 * This constructor initializes the vector with n elements, each set to
 * value. It allocates memory for the elements, sets the size and capacity of
 * the vector to n, and fills the allocated memory with copies of value.
 *
 * @param[in] n The number of elements to be created in the vector.
 * @param[in] value The value to initialize the elements with. Defaults to a
 * default-constructed value_type if not provided.
 */
template <typename value_type>
vector<value_type>::vector(size_type n, const_reference value)
    : arr_{allocateMemory(n, n)} {
  if (size_) {
    std::uninitialized_fill(arr_, arr_ + size_, value);
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
    : arr_{allocateMemory(items.size(), items.size())} {
  std::uninitialized_copy(items.begin(), items.begin() + size_, arr_);
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
    : arr_{allocateMemory(v.size_, v.capacity_)} {
  std::uninitialized_copy(v.arr_, v.arr_ + v.size_, arr_);
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
  if (this != &v) {
    freeMemory();
    new (this) vector{std::move(v)};
  }

  return *this;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(const vector &v) {
  if (this != &v) {
    freeMemory();
    new (this) vector{v};
  }

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
//                              VECTOR ITERATORS                              //
////////////////////////////////////////////////////////////////////////////////

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
 * @brief Returns a const_iterator to the beginning of the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return const_iterator - const_iterator to the beginning of the vector.
 */
template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cbegin()
    const noexcept {
  return const_iterator{arr_};
}

/**
 * @brief Returns a const_iterator to the end of the vector.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @return const_iterator - const_iterator to the end of the vector.
 */
template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cend()
    const noexcept {
  return const_iterator{arr_ + size_};
}

////////////////////////////////////////////////////////////////////////////////
//                              VECTOR CAPACITY                               //
////////////////////////////////////////////////////////////////////////////////

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
  if (size > max_size()) {
    throw std::length_error("vector::reserve() - size greater than max_size()");
  }

  if (size > capacity_) {
    capacity_ = size;
    pointer new_arr = new value_type[size]{};
    std::uninitialized_copy(arr_, arr_ + size_, new_arr);
    delete[] arr_;
    arr_ = (capacity_) ? new_arr : nullptr;
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
    capacity_ = size_;
    pointer new_arr = new value_type[size_]{};
    std::copy(arr_, arr_ + size_, new_arr);
    delete[] arr_;
    arr_ = (capacity_) ? new_arr : nullptr;
  }
}

////////////////////////////////////////////////////////////////////////////////
//                          VECTOR ELEMENT ACCESS                             //
////////////////////////////////////////////////////////////////////////////////

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
  if (pos >= size_) {
    throw std::out_of_range("vector::at() - pos out of vector range");
  }

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

////////////////////////////////////////////////////////////////////////////////
//                             VECTOR MODYFIERS                               //
////////////////////////////////////////////////////////////////////////////////

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
 * This function inserts count copies of value before the element at the
 * specified iterator position pos. If the capacity of the vector is not
 * sufficient to hold the new elements, the vector will be resized to twice its
 * current capacity or the new size, whichever is larger. Existing elements are
 * moved to make space for the new elements, and the size of the vector is
 * updated accordingly.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[in] pos Iterator position at which to insert the new elements.
 * @param[in] value The value to insert.
 * @param[in] count The number of copies of value to insert.
 * @return iterator - an iterator pointing to the first of the newly inserted
 * elements.
 * @throw std::out_of_range - if pos is not a valid iterator within the vector.
 */
template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::insert(
    const_iterator pos, const_reference value, size_type count) {
  if (pos < arr_ || pos > arr_ + size_) {
    throw std::out_of_range("vector::insert() - pos is not at vectors range");
  }

  size_type ins_pos = pos - cbegin();
  size_type new_size = size_ + count;

  if (capacity_ < new_size) {
    reserve((capacity_ * 2 >= new_size) ? capacity_ * 2 : new_size);
  }

  std::move_backward(arr_ + ins_pos, arr_ + size_, arr_ + size_ + count);
  std::uninitialized_fill(arr_ + ins_pos, arr_ + ins_pos + count, value);

  size_ = new_size;

  return cbegin() + ins_pos;
}

/**
 * @brief Removes elements from the vector within the specified range.
 *
 * @details
 * This function removes elements in the range [pos, last_pos). If last_pos is
 * not provided, it removes the single element at the position pos.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[in] pos An iterator pointing to the first element to be removed.
 * @param[in] last_pos An iterator pointing to one past the last element to be
 * removed. Defaults to nullptr.
 *
 * @throw std::range_error - if pos or last_pos are out of the bounds of the
 * vector or if last_pos is before pos.
 */
template <typename value_type>
void vector<value_type>::erase(const_iterator pos, const_iterator last_pos) {
  if (last_pos == nullptr) {
    last_pos = pos + 1;
  }

  if (pos < arr_ || pos > arr_ + capacity_ || last_pos < arr_ ||
      last_pos > arr_ + capacity_ || last_pos < pos) {
    throw std::range_error("vector::erase() - invalid vector range");
  }

  size_type range = last_pos - pos;

  if (range) {
    std::copy(static_cast<pointer>(pos + range), arr_ + size_,
              static_cast<pointer>(pos));
    size_ -= range;
  }
}

/**
 * @brief Adds a new element to the end of the vector.
 *
 * @details
 * This method adds a new element to the end of the vector. If the current
 * size of the vector equals its capacity, the method will first reserve
 * additional space to accommodate the new element. The new element is
 * constructed in place using placement new, avoiding the use of the
 * assignment operator.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[in] value The value to be added to the end of the vector.
 */
template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve((capacity_) ? capacity_ * 2 : 1);
  }

  arr_[size_++] = value;
}

/**
 * @brief Removes the last element from the vector.
 *
 * @details
 * This function decreases the size of the vector by one. If the vector is
 * empty, the function does nothing. This method does not free the memory
 * allocated for the elements,it only decreases the size of the vector. The
 * capacity remains unchanged.
 *
 * @tparam value_type The type of elements stored in the vector.
 */
template <typename value_type>
void vector<value_type>::pop_back() noexcept {
  if (size_) {
    size_--;
  }
}

/**
 * @brief Exchanges the contents of the vector with those of another vector.
 *
 * This function swaps the contents of the current vector with the given vector
 * other. It performs the swap by exchanging the internal pointers and metadata,
 * making the operation very efficient.
 *
 * @tparam value_type The type of elements stored in the vector.
 * @param[out] other The vector to swap contents with.
 */
template <typename value_type>
void vector<value_type>::swap(vector &other) noexcept {
  std::swap(other.size_, size_);
  std::swap(other.capacity_, capacity_);
  std::swap(other.arr_, arr_);
}

////////////////////////////////////////////////////////////////////////////////
//                         CONST ITERATOR CONSTRUCTORS                        //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructor with a pointer.
 *
 * @details
 * Takes a pointer to value_type as input and converts it to an object of type
 * const_iterator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] ptr Pointer to the element.
 */
template <typename value_type>
vector<value_type>::const_iterator::VectorConstIterator(const pointer ptr)
    : ptr_{ptr} {}

/**
 * @brief Copy constructor from other const_iterator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The const_iterator to copy from.
 */
template <typename value_type>
vector<value_type>::const_iterator::VectorConstIterator(
    const const_iterator &other)
    : ptr_{other.ptr_} {}

////////////////////////////////////////////////////////////////////////////////
//                          CONST ITERATOR OPERATORS                          //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Converts the const_iterator to a raw pointer of type value_type*.
 *
 * This operator allows for implicit conversion of the const_iterator to a raw
 * pointer of type pointer. It is useful for interfacing with APIs or functions
 * that require a raw pointer, while the const_iterator provides a more
 * convenient and type-safe way to access and traverse elements of the vector.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return pointer - a raw pointer to the underlying element of type value_type
 * that the const_iterator points to.
 */
template <typename value_type>
vector<value_type>::const_iterator::operator value_type *() const noexcept {
  return ptr_;
}

/**
 * @brief Dereference operator for constant access.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return const_reference - reference to the value pointed by the
 * const_iterator.
 * @throw std::invalid_argument - if the const_iterator is empty.
 */
template <typename value_type>
typename vector<value_type>::const_reference
vector<value_type>::const_iterator::operator*() const {
  if (!ptr_) {
    throw std::invalid_argument(
        "const_iterator::operator* - try to dereference an empty iterator");
  }

  return *ptr_;
}

/**
 * @brief Assignment operator from other const_iterator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The const_iterator to assign from.
 * @return const_iterator - reference to the updated const_iterator.
 */
template <typename value_type>
typename vector<value_type>::const_iterator &
vector<value_type>::const_iterator::operator=(
    const const_iterator &other) noexcept {
  ptr_ = other.ptr_;

  return *this;
}

/**
 * @brief Assignment operator from a pointer.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] ptr Pointer to the element.
 * @return const_iterator - reference to the updated const_iterator.
 */
template <typename value_type>
typename vector<value_type>::const_iterator &
vector<value_type>::const_iterator::operator=(const pointer ptr) noexcept {
  ptr_ = ptr;

  return *this;
}

/**
 * @brief Pre-decrement operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return reference - reference to the updated const_iterator.
 */
template <typename value_type>
typename vector<value_type>::const_iterator &
vector<value_type>::const_iterator::operator--() noexcept {
  ptr_--;

  return *this;
}

/**
 * @brief Post-decrement operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return const_iterator - copy of the const_iterator before the decrement.
 */
template <typename value_type>
typename vector<value_type>::const_iterator
vector<value_type>::const_iterator::operator--(int) noexcept {
  const_iterator copy{*this};
  ptr_--;

  return copy;
}

/**
 * @brief Pre-increment operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return reference - reference to the updated const_iterator.
 */
template <typename value_type>
typename vector<value_type>::const_iterator &
vector<value_type>::const_iterator::operator++() noexcept {
  ptr_++;

  return *this;
}

/**
 * @brief Post-increment operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return const_iterator - copy of the const_iterator before the increment.
 */
template <typename value_type>
typename vector<value_type>::const_iterator
vector<value_type>::const_iterator::operator++(int) noexcept {
  const_iterator copy{*this};
  ptr_++;

  return copy;
}

/**
 * @brief Subtraction operator for shifting the const_iterator by a given number
 * of positions.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] shift Number of positions to shift.
 * @return const_iterator - new const_iterator shifted by the specified
 * positions.
 */
template <typename value_type>
typename vector<value_type>::const_iterator
vector<value_type>::const_iterator::operator-(const int shift) const noexcept {
  const_iterator copy{*this};
  copy.ptr_ -= shift;

  return copy;
}

/**
 * @brief Difference operator to calculate the distance between two iterators.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The other const_iterator to calculate the distance from.
 * @return size_type - distance between the iterators.
 */
template <typename value_type>
typename vector<value_type>::size_type
vector<value_type>::const_iterator::operator-(
    const const_iterator &other) const noexcept {
  return (ptr_ > other.ptr_) ? ptr_ - other.ptr_ : other.ptr_ - ptr_;
}

/**
 * @brief Addition operator for shifting the const_iterator by a given number of
 * positions.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] shift Number of positions to shift.
 * @return const_iterator - new const_iterator shifted by the specified
 * positions.
 */
template <typename value_type>
typename vector<value_type>::const_iterator
vector<value_type>::const_iterator::operator+(const int shift) const noexcept {
  const_iterator copy{*this};
  copy.ptr_ += shift;

  return copy;
}

/**
 * @brief Subtraction assignment operator to shift the const_iterator by a given
 * number of positions.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] shift Number of positions to shift.
 */
template <typename value_type>
void vector<value_type>::const_iterator::operator-=(const int shift) noexcept {
  ptr_ -= shift;
}

/**
 * @brief Addition assignment operator to shift the const_iterator by a given
 * number of positions.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] shift Number of positions to shift.
 */
template <typename value_type>
void vector<value_type>::const_iterator::operator+=(const int shift) noexcept {
  ptr_ += shift;
}

/**
 * @brief Equality comparison operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The other const_iterator to compare with.
 * @return true - if the iterators are equal.
 * @return false - if the iterators are not equal.
 */
template <typename value_type>
bool vector<value_type>::const_iterator::operator==(
    const_iterator other) const noexcept {
  return ptr_ == other.ptr_;
}

/**
 * @brief Inequality comparison operator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The other const_iterator to compare with.
 * @return true - if the iterators are not equal.
 * @return false - if the iterators are equal.
 */
template <typename value_type>
bool vector<value_type>::const_iterator::operator!=(
    const_iterator other) const noexcept {
  return ptr_ != other.ptr_;
}

////////////////////////////////////////////////////////////////////////////////
//                            ITERATOR CONSTRUCTORS                           //
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

////////////////////////////////////////////////////////////////////////////////
//                             ITERATOR OPERATORS                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Converts the iterator to a raw pointer of type value_type*.
 *
 * This operator allows for implicit conversion of the iterator to a raw
 * pointer of type pointer. It is useful for interfacing with APIs or functions
 * that require a raw pointer, while the iterator provides a more
 * convenient and type-safe way to access and traverse elements of the vector.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return pointer - a raw pointer to the underlying element of type value_type
 * that the iterator points to.
 */
template <typename value_type>
vector<value_type>::iterator::operator value_type *() const noexcept {
  return ptr_;
}

/**
 * @brief Assignment operator from other iterator.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] other The iterator to assign from.
 * @return iterator - reference to the updated iterator.
 */
template <typename value_type>
typename vector<value_type>::iterator &vector<value_type>::iterator::operator=(
    const iterator &other) noexcept {
  ptr_ = other.ptr_;

  return *this;
}

/**
 * @brief Assignment operator from a pointer.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] ptr Pointer to the element.
 * @return iterator - reference to the updated iterator.
 */
template <typename value_type>
typename vector<value_type>::iterator &vector<value_type>::iterator::operator=(
    const pointer ptr) noexcept {
  ptr_ = ptr;

  return *this;
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
typename vector<value_type>::iterator vector<value_type>::iterator::operator--(
    int) noexcept {
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
typename vector<value_type>::iterator vector<value_type>::iterator::operator++(
    int) noexcept {
  iterator copy{*this};
  ptr_++;

  return copy;
}

/**
 * @brief Subtraction operator for shifting the iterator by a given number
 * of positions.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @param[in] shift Number of positions to shift.
 * @return iterator - new iterator shifted by the specified
 * positions.
 */
template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator-(
    const int shift) const noexcept {
  iterator copy{*this};
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
 * @return iterator - new iterator shifted by the specified
 * positions.
 */
template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator+(
    const int shift) const noexcept {
  iterator copy{*this};
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
 * @brief Addition assignment operator to shift the iterator by a given
 * number of positions.
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
 * @brief Dereference operator for non-constant access.
 *
 * @tparam value_type The type of the elements to be iterated over.
 * @return reference - reference to the value pointed by the iterator.
 * @throw std::invalid_argument - if the iterator is empty.
 */
template <typename value_type>
typename vector<value_type>::reference
vector<value_type>::iterator::operator*() {
  if (!ptr_) {
    throw std::invalid_argument(
        "iterator::operator* - try to dereference an empty iterator");
  }

  return *ptr_;
}

}  // namespace s21

#endif  // SRC_MODULES_VECTOR_H_
