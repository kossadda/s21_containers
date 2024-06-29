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

#include <initializer_list>
#include <iostream>
#include <utility>

// namespace container {

template <class T>
class vector {
 private:
 public:
  size_t m_size;
  size_t m_capacity;
  T *arr;

  T *Alloc();
  void Remove() noexcept;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector() noexcept;
  ~vector() noexcept;
  vector(const size_type n);
  vector(const std::initializer_list<value_type> &items);
  vector(const vector &v);
  vector(vector &&v);
  vector operator=(vector &&v);

  size_type size() const noexcept { return m_size; };
  size_type max_size() const noexcept { return m_capacity; };
};

template <typename T>
T *vector<T>::Alloc() {
  return new T[m_capacity]{};
}

template <typename T>
void vector<T>::Remove() noexcept {
  delete[] arr;
  arr = nullptr;
  m_size = m_capacity = 0;
}

template <typename T>
vector<T>::vector() noexcept : m_size{}, m_capacity{}, arr{} {}

template <typename T>
vector<T>::~vector() noexcept {
  Remove();
}

template <typename T>
vector<T>::vector(size_type n) : m_size{n}, m_capacity{n}, arr{Alloc()} {}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &item)
    : m_size{item.size()}, m_capacity{item.size()}, arr{Alloc()} {
  std::copy(item.begin(), item.begin() + m_size, arr);
}

// template <typename T>
// vector<T>::vector(vector &&v) : m_size{v.size()}, m_capacity{v.max_size()} {
//   delete[] arr;
//   Alloc();

//   std::copy()
// }

// }  // namespace container

#endif  // _VECTOR_H_