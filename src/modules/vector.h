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

#ifndef SRC_CONTAINERS_VECTOR_H_
#define SRC_CONTAINERS_VECTOR_H_

#include <algorithm>         // for exchange(), fill(), copy()
#include <initializer_list>  // for init_list type
#include <limits>            // for max()

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief A dynamic array container template class.
 *
 * @details
 * This template class vector provides a dynamic array similar to
 * std::vector in the C++ Standard Library. It manages a dynamic array of
 * elements of type V, supporting various operations including
 * iteration, element access, and size management.
 *
 * @tparam V The type of elements stored in the vector.
 */
template <typename V>
class vector {
 public:
  // Container types

  class VectorConstIterator;
  class VectorIterator;

  // Type aliases

  using value_type = V;                        ///< Type of vectors elements
  using pointer = value_type *;                ///< Pointer to value_type
  using reference = value_type &;              ///< Reference to value_type
  using const_reference = const value_type &;  ///< Const refer to value_type
  using size_type = std::size_t;               ///< Containers size type
  using iterator = VectorIterator;             ///< For read/write elements
  using const_iterator = VectorConstIterator;  ///< For read elements

  // Constructors/assignment operators/destructor

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
  iterator insert(const_iterator pos, const_reference value,
                  size_type count = 1);
  iterator erase(const_iterator pos,
                 const_iterator last_pos = const_iterator{});
  void push_back(const_reference value);
  void pop_back() noexcept;
  void swap(vector &other) noexcept;

  template <typename... Args>
  reference emplace_back(Args &&...args);
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

 private:
  // Fields

  size_type size_{};      ///< Size of vector
  size_type capacity_{};  ///< Current capacity of vector
  value_type *arr_{};     ///< Array of elements

  // Allocating/deallocating memory

  pointer allocateMemory(size_type size, size_type capacity);
  void freeMemory() noexcept;
};

/**
 * @brief A constant iterator for the vector class.
 *
 * @details
 * This iterator allows traversal of elements in the vector without modifying
 * them. It supports typical iterator operations such as increment, decrement,
 * addition, subtraction, and dereference.
 *
 * @tparam V The type of elements stored in the vector.
 */
template <typename V>
class vector<V>::VectorConstIterator {
 public:
  // Constructors

  VectorConstIterator() noexcept = default;
  explicit VectorConstIterator(const pointer ptr);
  VectorConstIterator(const const_iterator &other);

  // Operators

  pointer base() const noexcept;
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

 private:
  // Fields

  pointer ptr_{};  ///< Pointer to the current element
};

/**
 * @brief An iterator for the vector class.
 *
 * @details
 * This iterator allows traversal of elements in the vector and modifying them.
 * It inherits from VectorConstIterator and overrides the dereference operator
 * to allow modification of the elements.
 *
 * @tparam V The type of elements stored in the vector.
 */
template <typename V>
class vector<V>::VectorIterator {
 public:
  // Constructors

  VectorIterator() noexcept = default;
  explicit VectorIterator(const pointer ptr);
  VectorIterator(const iterator &other);

  // Operators

  pointer base() const noexcept;
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

  /**
   * @brief Converts the iterator to a const_iterator.
   *
   * @details
   * This operator allows for the conversion of an iterator to a const_iterator.
   * This is useful when you need to pass an iterator to a function that expects
   * a const_iterator, ensuring that the elements cannot be modified through the
   * iterator.
   *
   * @return const_iterator - a const_iterator initialized with the current
   * iterator's pointer.
   */
  operator const_iterator() const noexcept { return const_iterator{ptr_}; }

 private:
  // Fields

  pointer ptr_{};  ///< Pointer to the current element
};

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
template <typename V>
vector<V>::vector(size_type n, const_reference value)
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
 * @param[in] items The initializer list containing elements.
 */
template <typename V>
vector<V>::vector(const std::initializer_list<value_type> &items)
    : arr_{allocateMemory(items.size(), items.size())} {
  std::uninitialized_copy(items.begin(), items.begin() + size_, arr_);
}

/**
 * @brief Copy constructor.
 *
 * @details
 * Constructs a vector by copying another vector.
 *
 * @param[in] v The vector to copy.
 */
template <typename V>
vector<V>::vector(const vector &v)
    : arr_{allocateMemory(v.size_, v.capacity_)} {
  std::uninitialized_copy(v.arr_, v.arr_ + v.size_, arr_);
}

/**
 * @brief Move constructor.
 *
 * @details
 * Constructs a vector by moving another vector.
 *
 * @param[out] v The vector to move.
 */
template <typename V>
vector<V>::vector(vector &&v) noexcept
    : size_{std::exchange(v.size_, 0)},
      capacity_{std::exchange(v.capacity_, 0)},
      arr_{std::exchange(v.arr_, nullptr)} {}

/**
 * @brief Destructor.
 *
 * @details
 * Destroys the vector and frees allocated memory.
 *
 */
template <typename V>
vector<V>::~vector() noexcept {
  freeMemory();
}

/**
 * @brief Move assignment operator.
 *
 * @details
 * Assigns the contents of another vector to this vector using move semantics.
 *
 * @param[out] v The vector to move.
 * @return vector& - reference to the assigned vector.
 */
template <typename V>
auto vector<V>::operator=(vector &&v) -> vector & {
  if (this != &v) {
    freeMemory();
    new (this) vector{std::move(v)};
  }

  return *this;
}

template <typename V>
auto vector<V>::operator=(const vector &v) -> vector & {
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
 * @return iterator - an iterator to the beginning of the vector.
 */
template <typename V>
auto vector<V>::begin() const noexcept -> iterator {
  return iterator{arr_};
}

/**
 * @brief Returns an iterator to the end of the vector.
 *
 * @return iterator - an iterator to the end of the vector.
 */
template <typename V>
auto vector<V>::end() const noexcept -> iterator {
  return iterator{arr_ + size_};
}

/**
 * @brief Returns a const_iterator to the beginning of the vector.
 *
 * @return const_iterator - const_iterator to the beginning of the vector.
 */
template <typename V>
auto vector<V>::cbegin() const noexcept -> const_iterator {
  return const_iterator{arr_};
}

/**
 * @brief Returns a const_iterator to the end of the vector.
 *
 * @return const_iterator - const_iterator to the end of the vector.
 */
template <typename V>
auto vector<V>::cend() const noexcept -> const_iterator {
  return const_iterator{arr_ + size_};
}

////////////////////////////////////////////////////////////////////////////////
//                              VECTOR CAPACITY                               //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the vector is empty.
 *
 * @return true if the vector is empty, false otherwise.
 */
template <typename V>
bool vector<V>::empty() const noexcept {
  return (size_) ? false : true;
}

/**
 * @brief Returns the number of elements in the vector.
 *
 * @return size_type - the number of elements in the vector.
 */
template <typename V>
auto vector<V>::size() const noexcept -> size_type {
  return size_;
}

/**
 * @brief Returns the maximum number of elements the vector can hold.
 *
 * @return size_type - the maximum number of elements.
 */
template <typename V>
auto vector<V>::max_size() const noexcept -> size_type {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

/**
 * @brief Reserves memory for the specified number of elements.
 *
 * @param[in] size The number of elements to reserve memory for.
 * @throw std::length_error - if the reserve size greater than max_size().
 */
template <typename V>
void vector<V>::reserve(size_type size) {
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
 * @return size_type - the current capacity.
 */
template <typename V>
auto vector<V>::capacity() const noexcept -> size_type {
  return capacity_;
}

/**
 * @brief Reduces the capacity of the vector to fit its size.
 *
 */
template <typename V>
void vector<V>::shrink_to_fit() {
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
 * @param[in] pos The position of the element.
 * @return reference - a reference to the element at the specified position.
 * @throw std::out_of_range - if element position out of vector range.
 */
template <typename V>
auto vector<V>::at(size_type pos) const -> value_type & {
  if (pos >= size_) {
    throw std::out_of_range("vector::at() - pos out of vector range");
  }

  return *(arr_ + pos);
}

/**
 * @brief Returns a reference to the element at the specified position.
 *
 * @param[in] pos The position of the element.
 * @return reference - a reference to the element at the specified position.
 */
template <typename V>
auto vector<V>::operator[](size_type pos) const noexcept -> value_type & {
  return *(arr_ + pos);
}

/**
 * @brief Returns a reference to the first element in the vector.
 *
 * @return const_reference - a reference to the first element.
 */
template <typename V>
auto vector<V>::front() const noexcept -> const_reference {
  return *arr_;
}

/**
 * @brief Returns a reference to the last element in the vector.
 *
 * @return const_reference - a reference to the last element.
 */
template <typename V>
auto vector<V>::back() const noexcept -> const_reference {
  return *(arr_ + size_ - 1);
}

/**
 * @brief Returns a pointer to the first element in the vector.
 *
 * @return pointer - a pointer to the first element.
 */
template <typename V>
auto vector<V>::data() const noexcept -> pointer {
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
 */
template <typename V>
void vector<V>::clear() noexcept {
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
 * @param[in] pos Iterator position at which to insert the new elements.
 * @param[in] value The value to insert.
 * @param[in] count The number of copies of value to insert.
 * @return iterator - an iterator pointing to the first of the newly inserted
 * elements.
 * @throw std::out_of_range - if pos is not a valid iterator within the vector.
 */
template <typename V>
auto vector<V>::insert(const_iterator pos, const_reference value,
                       size_type count) -> iterator {
  if (pos.base() < arr_ || pos.base() > arr_ + size_) {
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

  return begin() + ins_pos;
}

/**
 * @brief Removes elements from the vector within the specified range.
 *
 * @details
 * This function removes elements in the range [pos, last_pos). If last_pos is
 * not provided, it removes the single element at the position pos.
 *
 * @param[in] pos An iterator pointing to the first element to be removed.
 * @param[in] last_pos An iterator pointing to one past the last element to be
 * removed. Defaults to nullptr.
 *
 * @throw std::range_error - if pos or last_pos are out of the bounds of the
 * vector or if last_pos is before pos.
 */
template <typename V>
auto vector<V>::erase(const_iterator pos, const_iterator last_pos) -> iterator {
  if (last_pos.base() == nullptr) {
    last_pos = pos + 1;
  }

  if (pos.base() < arr_ || pos.base() > arr_ + capacity_ ||
      last_pos.base() < arr_ || last_pos.base() > arr_ + capacity_ ||
      last_pos.base() < pos.base()) {
    throw std::range_error("vector::erase() - invalid vector range");
  }

  size_type range = last_pos - pos;

  if (range) {
    std::copy(pos.base() + range, arr_ + size_, pos.base());
    size_ -= range;
  }

  return iterator{pos.base()};
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
 * @param[in] value The value to be added to the end of the vector.
 */
template <typename V>
void vector<V>::push_back(const_reference value) {
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
 */
template <typename V>
void vector<V>::pop_back() noexcept {
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
 * @param[out] other The vector to swap contents with.
 */
template <typename V>
void vector<V>::swap(vector &other) noexcept {
  std::swap(other.size_, size_);
  std::swap(other.capacity_, capacity_);
  std::swap(other.arr_, arr_);
}

/**
 * @brief Adds a new element to the end of the vector.
 *
 * @details
 * This method constructs a new element in place at the end of the vector using
 * the provided arguments. If the current size of the vector equals its
 * capacity, the method will first reserve additional space to accommodate the
 * new element. The new element is constructed in place using placement new,
 * avoiding the use of the assignment operator.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param args The arguments to forward to the constructor of the new element.
 * @return reference - a reference to the newly inserted element.
 */
template <typename V>
template <typename... Args>
auto vector<V>::emplace_back(Args &&...args) -> reference {
  if (size_ == capacity_) {
    reserve((capacity_) ? capacity_ * 2 : 1);
  }

  new (arr_ + size_) value_type{std::forward<Args>(args)...};
  ++size_;

  return *(arr_ + size_ - 1);
}

/**
 * @brief Inserts a new element at the specified position in the vector.
 *
 * @details
 * This method constructs a new element in place at the specified position
 * using the provided arguments. If the current capacity of the vector is not
 * sufficient to hold the new element, the vector will be resized to twice its
 * current capacity or the new size, whichever is larger. Existing elements are
 * moved to make space for the new element, and the size of the vector is
 * updated accordingly.
 *
 * @tparam Args The types of the arguments to forward to the constructor of the
 * element.
 * @param pos An iterator pointing to the position where the new element will be
 * inserted.
 * @param args The arguments to forward to the constructor of the new element.
 * @return iterator - an iterator pointing to the newly inserted element.
 * @throw std::length_error - if the reserve size greater than max_size().
 */
template <typename V>
template <typename... Args>
auto vector<V>::emplace(const_iterator pos, Args &&...args) -> iterator {
  size_type ins_pos = pos - cbegin();

  if (size_ == capacity_) {
    reserve((capacity_) ? capacity_ * 2 : 1);
  }

  std::move_backward(arr_ + ins_pos, arr_ + size_, arr_ + size_ + 1);

  new (arr_ + ins_pos) value_type(std::forward<Args>(args)...);
  ++size_;

  return iterator{arr_ + ins_pos};
}

////////////////////////////////////////////////////////////////////////////////
//                         VECTOR PRIVATE METHODS                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocates memory for the vector.
 *
 * @return pointer A pointer to the allocated memory.
 * @throw std::bad_alloc - if the allocation failed.
 */
template <typename V>
typename vector<V>::pointer vector<V>::allocateMemory(size_type size,
                                                      size_type capacity) {
  size_ = size;
  capacity_ = capacity;

  return new value_type[capacity_]{};
}

/**
 * @brief Frees the memory allocated for the vector.
 *
 */
template <typename V>
void vector<V>::freeMemory() noexcept {
  if (arr_ != nullptr) {
    delete[] arr_;
    arr_ = nullptr;
  }

  size_ = capacity_ = 0;
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
 * @param[in] ptr Pointer to the element.
 */
template <typename V>
vector<V>::const_iterator::VectorConstIterator(const pointer ptr) : ptr_{ptr} {}

/**
 * @brief Copy constructor from other const_iterator.
 *
 * @param[in] other The const_iterator to copy from.
 */
template <typename V>
vector<V>::const_iterator::VectorConstIterator(const const_iterator &other)
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
 * @return pointer - a raw pointer to the underlying element of type value_type
 * that the const_iterator points to.
 */
template <typename V>
auto vector<V>::const_iterator::base() const noexcept -> pointer {
  return ptr_;
}

/**
 * @brief Dereference operator for constant access.
 *
 * @return const_reference - reference to the value pointed by the
 * const_iterator.
 * @throw std::invalid_argument - if the const_iterator is empty.
 */
template <typename V>
auto vector<V>::const_iterator::operator*() const -> const_reference {
  if (!ptr_) {
    throw std::invalid_argument(
        "const_iterator::operator* - try to dereference an empty iterator");
  }

  return *ptr_;
}

/**
 * @brief Assignment operator from other const_iterator.
 *
 * @param[in] other The const_iterator to assign from.
 * @return const_iterator - reference to the updated const_iterator.
 */
template <typename V>
auto vector<V>::const_iterator::operator=(const const_iterator &other) noexcept
    -> const_iterator & {
  ptr_ = other.ptr_;

  return *this;
}

/**
 * @brief Assignment operator from a pointer.
 *
 * @param[in] ptr Pointer to the element.
 * @return const_iterator - reference to the updated const_iterator.
 */
template <typename V>
auto vector<V>::const_iterator::operator=(const pointer ptr) noexcept
    -> const_iterator & {
  ptr_ = ptr;

  return *this;
}

/**
 * @brief Pre-decrement operator.
 *
 * @return reference - reference to the updated const_iterator.
 */
template <typename V>
auto vector<V>::const_iterator::operator--() noexcept -> const_iterator & {
  ptr_--;

  return *this;
}

/**
 * @brief Post-decrement operator.
 *
 * @return const_iterator - copy of the const_iterator before the decrement.
 */
template <typename V>
auto vector<V>::const_iterator::operator--(int) noexcept -> const_iterator {
  const_iterator copy{*this};
  ptr_--;

  return copy;
}

/**
 * @brief Pre-increment operator.
 *
 * @return reference - reference to the updated const_iterator.
 */
template <typename V>
auto vector<V>::const_iterator::operator++() noexcept -> const_iterator & {
  ++ptr_;

  return *this;
}

/**
 * @brief Post-increment operator.
 *
 * @return const_iterator - copy of the const_iterator before the increment.
 */
template <typename V>
auto vector<V>::const_iterator::operator++(int) noexcept -> const_iterator {
  const_iterator copy{*this};
  ++ptr_;

  return copy;
}

/**
 * @brief Subtraction operator for shifting the const_iterator by a given number
 * of positions.
 *
 * @param[in] shift Number of positions to shift.
 * @return const_iterator - new const_iterator shifted by the specified
 * positions.
 */
template <typename V>
auto vector<V>::const_iterator::operator-(const int shift) const noexcept
    -> const_iterator {
  const_iterator copy{*this};
  copy.ptr_ -= shift;

  return copy;
}

/**
 * @brief Difference operator to calculate the distance between two iterators.
 *
 * @param[in] other The other const_iterator to calculate the distance from.
 * @return size_type - distance between the iterators.
 */
template <typename V>
auto vector<V>::const_iterator::operator-(
    const const_iterator &other) const noexcept -> size_type {
  return (ptr_ > other.ptr_) ? ptr_ - other.ptr_ : other.ptr_ - ptr_;
}

/**
 * @brief Addition operator for shifting the const_iterator by a given number of
 * positions.
 *
 * @param[in] shift Number of positions to shift.
 * @return const_iterator - new const_iterator shifted by the specified
 * positions.
 */
template <typename V>
auto vector<V>::const_iterator::operator+(const int shift) const noexcept
    -> const_iterator {
  const_iterator copy{*this};
  copy.ptr_ += shift;

  return copy;
}

/**
 * @brief Subtraction assignment operator to shift the const_iterator by a given
 * number of positions.
 *
 * @param[in] shift Number of positions to shift.
 */
template <typename V>
void vector<V>::const_iterator::operator-=(const int shift) noexcept {
  ptr_ -= shift;
}

/**
 * @brief Addition assignment operator to shift the const_iterator by a given
 * number of positions.
 *
 * @param[in] shift Number of positions to shift.
 */
template <typename V>
void vector<V>::const_iterator::operator+=(const int shift) noexcept {
  ptr_ += shift;
}

/**
 * @brief Equality comparison operator.
 *
 * @param[in] other The other const_iterator to compare with.
 * @return true - if the iterators are equal.
 * @return false - if the iterators are not equal.
 */
template <typename V>
bool vector<V>::const_iterator::operator==(
    const_iterator other) const noexcept {
  return ptr_ == other.ptr_;
}

/**
 * @brief Inequality comparison operator.
 *
 * @param[in] other The other const_iterator to compare with.
 * @return true - if the iterators are not equal.
 * @return false - if the iterators are equal.
 */
template <typename V>
bool vector<V>::const_iterator::operator!=(
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
 * @param[in] ptr Pointer to the element.
 */
template <typename V>
vector<V>::iterator::VectorIterator(const pointer ptr) : ptr_{ptr} {}

/**
 * @brief Copy constructor from other iterator.
 *
 * @param[in] other The iterator to copy from.
 */
template <typename V>
vector<V>::iterator::VectorIterator(const iterator &other) : ptr_{other.ptr_} {}

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
 * @return pointer - a raw pointer to the underlying element of type value_type
 * that the iterator points to.
 */
template <typename V>
auto vector<V>::iterator::base() const noexcept -> pointer {
  return ptr_;
}

/**
 * @brief Assignment operator from other iterator.
 *
 * @param[in] other The iterator to assign from.
 * @return iterator - reference to the updated iterator.
 */
template <typename V>
auto vector<V>::iterator::operator=(const iterator &other) noexcept
    -> iterator & {
  ptr_ = other.ptr_;

  return *this;
}

/**
 * @brief Assignment operator from a pointer.
 *
 * @param[in] ptr Pointer to the element.
 * @return iterator - reference to the updated iterator.
 */
template <typename V>
auto vector<V>::iterator::operator=(const pointer ptr) noexcept -> iterator & {
  ptr_ = ptr;

  return *this;
}

/**
 * @brief Pre-decrement operator.
 *
 * @return reference - reference to the updated iterator.
 */
template <typename V>
auto vector<V>::iterator::operator--() noexcept -> iterator & {
  ptr_--;

  return *this;
}

/**
 * @brief Post-decrement operator.
 *
 * @return iterator - copy of the iterator before the decrement.
 */
template <typename V>
auto vector<V>::iterator::operator--(int) noexcept -> iterator {
  iterator copy{*this};
  ptr_--;

  return copy;
}

/**
 * @brief Pre-increment operator.
 *
 * @return reference - reference to the updated iterator.
 */
template <typename V>
auto vector<V>::iterator::operator++() noexcept -> iterator & {
  ++ptr_;

  return *this;
}

/**
 * @brief Post-increment operator.
 *
 * @return iterator - copy of the iterator before the increment.
 */
template <typename V>
auto vector<V>::iterator::operator++(int) noexcept -> iterator {
  iterator copy{*this};
  ++ptr_;

  return copy;
}

/**
 * @brief Subtraction operator for shifting the iterator by a given number
 * of positions.
 *
 * @param[in] shift Number of positions to shift.
 * @return iterator - new iterator shifted by the specified
 * positions.
 */
template <typename V>
auto vector<V>::iterator::operator-(const int shift) const noexcept
    -> iterator {
  iterator copy{*this};
  copy.ptr_ -= shift;

  return copy;
}

/**
 * @brief Difference operator to calculate the distance between two iterators.
 *
 * @param[in] other The other iterator to calculate the distance from.
 * @return size_type - distance between the iterators.
 */
template <typename V>
auto vector<V>::iterator::operator-(const iterator &other) const noexcept
    -> size_type {
  return (ptr_ > other.ptr_) ? ptr_ - other.ptr_ : other.ptr_ - ptr_;
}

/**
 * @brief Addition operator for shifting the iterator by a given number of
 * positions.
 *
 * @param[in] shift Number of positions to shift.
 * @return iterator - new iterator shifted by the specified
 * positions.
 */
template <typename V>
auto vector<V>::iterator::operator+(const int shift) const noexcept
    -> iterator {
  iterator copy{*this};
  copy.ptr_ += shift;

  return copy;
}

/**
 * @brief Subtraction assignment operator to shift the iterator by a given
 * number of positions.
 *
 * @param[in] shift Number of positions to shift.
 */
template <typename V>
void vector<V>::iterator::operator-=(const int shift) noexcept {
  ptr_ -= shift;
}

/**
 * @brief Addition assignment operator to shift the iterator by a given
 * number of positions.
 *
 * @param[in] shift Number of positions to shift.
 */
template <typename V>
void vector<V>::iterator::operator+=(const int shift) noexcept {
  ptr_ += shift;
}

/**
 * @brief Equality comparison operator.
 *
 * @param[in] other The other iterator to compare with.
 * @return true - if the iterators are equal.
 * @return false - if the iterators are not equal.
 */
template <typename V>
bool vector<V>::iterator::operator==(iterator other) const noexcept {
  return ptr_ == other.ptr_;
}

/**
 * @brief Inequality comparison operator.
 *
 * @param[in] other The other iterator to compare with.
 * @return true - if the iterators are not equal.
 * @return false - if the iterators are equal.
 */
template <typename V>
bool vector<V>::iterator::operator!=(iterator other) const noexcept {
  return ptr_ != other.ptr_;
}

/**
 * @brief Dereference operator for non-constant access.
 *
 * @return reference - reference to the value pointed by the iterator.
 * @throw std::invalid_argument - if the iterator is empty.
 */
template <typename V>
auto vector<V>::iterator::operator*() -> reference {
  if (!ptr_) {
    throw std::invalid_argument(
        "iterator::operator* - try to dereference an empty iterator");
  }

  return *ptr_;
}

}  // namespace s21

#endif  // SRC_CONTAINERS_VECTOR_H_
