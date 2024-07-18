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

#include <initializer_list>
// #include <utility>

#include "./iterator.h"

/// @brief Namespace for working with containers
namespace containers {

/**
 * @brief A dynamic array container template class.
 *
 * @details
 * This template class `vector` provides a dynamic array similar to
 * `std::vector` in the C++ Standard Library. It manages a dynamic array of
 * elements of type `T`, supporting various operations including iteration,
 * element access, and size management.
 *
 * @tparam T the type of elements stored in the vector.
 */
template <class value_type>
class vector {
  typedef _iterators::iterator<value_type> VectorIterator;
  typedef const _iterators::iterator<value_type> VectorConstIterator;

 public:
  using pointer = value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  value_type *arr_ = nullptr;

  pointer allocateMemory();
  void removeVector() noexcept;

 public:
  vector() noexcept = default;
  explicit vector(const size_type n);
  vector(const std::initializer_list<value_type> &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector() noexcept;

  iterator begin() const noexcept;
  iterator end() const noexcept;

  // vector operator=(vector &&v);
};

template <typename value_type>
vector<value_type>::vector(size_type n)
    : size_{n}, capacity_{n}, arr_{allocateMemory()} {}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &item)
    : size_{item.size()}, capacity_{item.size()}, arr_{allocateMemory()} {
  std::copy(item.begin(), item.begin() + size_, arr_);
}

template <typename value_type>
vector<value_type>::vector(const vector &v) : size_{v.size_}, capacity_{v.capacity_}, arr_{allocateMemory()} {
  std::copy(v.arr_, v.arr_ + v.size_, arr_);
}

template <typename value_type>
vector<value_type>::~vector() noexcept {
  removeVector();
}

template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::allocateMemory() {
  return new value_type[capacity_]{};
}

template <typename value_type>
void vector<value_type>::removeVector() noexcept {
  delete[] arr_;
  arr_ = nullptr;
  size_ = capacity_ = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin()
    const noexcept {
  return iterator{arr_};
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() const noexcept {
  return iterator{arr_ + size_};
}

}  // namespace containers

#endif  // SRC_MODULES_VECTOR_H_
