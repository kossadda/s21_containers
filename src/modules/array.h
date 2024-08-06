/**
 * @file array.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Declaration of the array class
 * @version 1.0
 * @date 2024-08-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_CONTAINERS_ARRAY_H_
#define SRC_CONTAINERS_ARRAY_H_

#include <algorithm>  // for std::fill
#include <initializer_list>
#include <iostream>  // for std::size_t

#include "./vector.h"

namespace s21 {

/**
 * @brief
 *
 * @note
 *
 * Aggregate initialisation is used. The default constructor creates an array,
 * of size N, but does not fill it with zeros (as you might expect). In the
 * original container this is not handled in any way, but in our implementation
 * we initialise the static array with zeros.
 */
template <typename T, std::size_t N>
struct array {
  T arr[N]{};

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename vector<T>::iterator;
  using const_iterator = typename vector<const T>::const_iterator;
  using size_type = std::size_t;

  // Array Element access

  constexpr reference at(size_type pos);
  constexpr reference operator[](size_type pos);
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  T *data() noexcept;
  const T *data() const noexcept;

  // Array Iterators

  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;

  // Array Capacity

  constexpr bool empty() const noexcept;
  constexpr size_type size() const noexcept;
  constexpr size_type max_size() const noexcept;

  // Array Modifiers

  void swap(array &other) noexcept;
  void fill(const_reference value);
};

// no explicit construct/copy/destroy for aggregate type

// Array Element access

/**
 * @brief Returns a reference to the element at specified location pos.
 *
 * @details
 *
 * This function provides a checked access to the element at the specified
 * index. If the index is out of bounds, it throws an `std::out_of_range`
 * exception. This method is `constexpr`, allowing its evaluation at compile
 * time if the arguments are constant expressions.
 *
 * @param pos The position of the element to return. The index must be in the
 * range `[1, N)`, where `N` is the size of the array.
 *
 * @return reference A reference to the element at the specified position.
 *
 * @throws std::out_of_range If `pos` is not within the range of the array.
 */
template <typename T, std::size_t N>
constexpr auto array<T, N>::at(size_type pos) -> reference {
  if (pos >= N) {
    throw std::out_of_range("Out of range of the array");
  }

  return arr[pos];
}

/**
 * @brief Returns a reference to the element at specified location pos. No
 * bounds checking is performed.
 *
 * @details
 *
 * This function provides unchecked access to the element at the specified
 * index. If the index is out of bounds, the behavior is undefined. This method
 * is `constexpr`, allowing its evaluation at compile time if the arguments are
 * constant expressions.
 *
 * @param pos The position of the element to return. The index must be in the
 * range `[1, N)`, where `N` is the size of the array.
 *
 * @return reference A reference to the element at the specified position.
 *
 * @warning No bounds checking is performed. Accessing an out-of-bounds index
 * results in undefined behavior.
 */
template <typename T, std::size_t N>
constexpr auto array<T, N>::operator[](size_type pos) -> reference {
  return arr[pos];
}

/**
 * @brief Returns a reference to the first element in the array.
 *
 * @details
 *
 * This function provides access to the first element in the array. The method
 * assumes that the array is not empty. If the array is empty, the behavior is
 * undefined.
 *
 * @return reference A reference to the first element in the array.
 *
 * @warning Accessing the first element of an empty array results in undefined
 * behavior.
 */
template <typename T, std::size_t N>
auto array<T, N>::front() -> reference {
  return *arr;
}

/**
 * @brief Returns a const reference to the first element in the array.
 *
 * @details
 *
 * This function provides read-only access to the first element in the array.
 * The method assumes that the array is not empty. If the array is empty, the
 * behavior is undefined.
 *
 * @return const_reference A const reference to the first element in the array.
 *
 * @warning Accessing the first element of an empty array results in undefined
 * behavior.
 */
template <typename T, std::size_t N>
auto array<T, N>::front() const -> const_reference {
  return *arr;
}

/**
 * @brief Returns a reference to the last element in the array.
 *
 * @details
 *
 * This function provides access to the last element in the array. The method
 * assumes that the array is not empty. If the array is empty, the behavior is
 * undefined.
 *
 * @return reference A reference to the last element in the array.
 *
 * @warning Accessing the last element of an empty array results in undefined
 * behavior.
 */
template <typename T, std::size_t N>
auto array<T, N>::back() -> reference {
  return arr[N - 1];
}

/**
 * @brief Returns a const reference to the last element in the array.
 *
 * @details
 *
 * This function provides read-only access to the last element in the array.
 * The method assumes that the array is not empty. If the array is empty, the
 * behavior is undefined.
 *
 * @return const_reference A const reference to the last element in the array.
 *
 * @warning Accessing the last element of an empty array results in undefined
 * behavior.
 */
template <typename T, std::size_t N>
auto array<T, N>::back() const -> const_reference {
  return arr[N - 1];
}

/**
 * @brief Returns a pointer to the underlying array serving as element storage.
 *
 * @details
 *
 * This function provides direct access to the underlying array that stores the
 * elements. It can be useful for interoperability with C-style arrays or
 * functions that require a pointer to the array data.
 *
 * @return T* A pointer to the first element in the array.
 */
template <typename T, std::size_t N>
auto array<T, N>::data() noexcept -> T * {
  return arr;
}

/**
 * @brief Returns a const pointer to the underlying array serving as element
 * storage.
 *
 * @details
 *
 * This function provides read-only access to the underlying array that stores
 * the elements. It can be useful for interoperability with C-style arrays or
 * functions that require a const pointer to the array data.
 *
 * @return const T* A const pointer to the first element in the array.
 */
template <typename T, std::size_t N>
auto array<T, N>::data() const noexcept -> const T * {
  return arr;
}

/**
 * @brief Returns an iterator to the first element of the array.
 *
 * @details
 *
 * This function provides an iterator to the first element of the array. If the
 * array is empty, the returned iterator will be equal to `end()`.
 *
 * @return iterator An iterator to the first element in the array.
 */
template <typename T, std::size_t N>
auto array<T, N>::begin() noexcept -> iterator {
  return iterator{arr};
}

/**
 * @brief Returns a const iterator to the first element of the array.
 *
 * @details
 *
 * This function provides a read-only iterator to the first element of the
 * array. If the array is empty, the returned iterator will be equal to
 * `cend()`.
 *
 * @return const_iterator A const iterator to the first element in the array.
 */
template <typename T, std::size_t N>
auto array<T, N>::cbegin() const noexcept -> const_iterator {
  return const_iterator{arr};
}

/**
 * @brief Returns an iterator to the position just past the last element of the
 * array.
 *
 * @details
 *
 * This function provides an iterator to the position just past the last element
 * of the array. This iterator serves as a sentinel to mark the end of the range
 * of elements and is used to define the bounds for iteration.
 *
 * @return iterator An iterator to the position just past the last element in
 * the array.
 */
template <typename T, std::size_t N>
auto array<T, N>::end() noexcept -> iterator {
  return iterator{arr + N};
}

/**
 * @brief Returns a const iterator to the position just past the last element of
 * the array.
 *
 * @details
 *
 * This function provides a read-only iterator to the position just past the
 * last element of the array. This iterator serves as a sentinel to mark the end
 * of the range of elements and is used to define the bounds for constant
 * iteration.
 *
 * @return const_iterator A const iterator to the position just past the last
 * element in the array.
 */
template <typename T, std::size_t N>
auto array<T, N>::cend() const noexcept -> const_iterator {
  return const_iterator{arr + N};
}

/**
 * @brief Checks whether the array is empty.
 *
 * @details
 *
 * This function checks if the array has no elements. Since the size of the
 * array is fixed at compile time, this function only checks if the template
 * parameter `N` is zero. For non-zero `N`, the array is always considered
 * non-empty.
 *
 * @return bool `true` if the array size is zero, otherwise `false`.
 */
template <typename T, std::size_t N>
constexpr bool array<T, N>::empty() const noexcept {
  return N == 0;
}

/**
 * @brief Returns the number of elements in the array.
 *
 * @details
 *
 * This function returns the size of the array, which is fixed at compile time
 * and is specified by the template parameter `N`. Since the size of the array
 * does not change, this function provides a constant value.
 *
 * @return size_type The number of elements in the array.
 */
template <typename T, std::size_t N>
constexpr auto array<T, N>::size() const noexcept -> size_type {
  return N;
}

/**
 * @brief Returns the maximum number of elements the array can hold.
 *
 * @details
 *
 * This function returns the maximum number of elements the array can hold. For
 * a fixed-size array, this value is equivalent to the current size of the
 * array, which is determined by the template parameter `N`. Since the size of
 * the array is constant, this function returns the same value as `size()`.
 *
 * @return size_type The maximum number of elements the array can hold.
 */
template <typename T, std::size_t N>
constexpr auto array<T, N>::max_size() const noexcept -> size_type {
  return size();
}

/**
 * @brief Exchanges the contents of this array with another array.
 *
 * @details
 *
 * This function swaps the elements of the current array with those of the
 * `other` array. It performs a pairwise swap of elements between the two
 * arrays. If the arrays are of different sizes, only the elements within the
 * smaller array's size are swapped, and the remaining elements in the larger
 * array remain unchanged.
 *
 * @param other The array to swap with this array. The arrays must be of the
 * same type and size.
 */
template <typename T, std::size_t N>
void array<T, N>::swap(array &other) noexcept {
  for (size_type i = 0; i < N; ++i) {
    std::swap(arr[i], other.arr[i]);
  }
}

/**
 * @brief Fills the array with the specified value.
 *
 * @details
 *
 * This function assigns the given `value` to all elements in the array. It uses
 * the standard library function `std::fill` to set each element in the range
 * from the beginning to the end of the array to the specified value.
 *
 * @param value The value to assign to each element in the array.
 */
template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(data(), data() + N, value);
}

// template<typename T, typename... U>
//   array(T, U...) -> array<T, 1 + sizeof...(U)>;

}  // namespace s21

#endif  // SRC_CONTAINERS_ARRAY_H_
