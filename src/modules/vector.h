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

namespace container {

#include "iterator.h"

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
    T *m_ptr;
    size_t m_index;

   public:
    iterator() noexcept : m_ptr{}, m_index{} {};
    explicit iterator(pointer ptr) : m_ptr{ptr}, m_index{} {};
    explicit iterator(const iterator &other) : m_ptr{other.getPtr()}, m_index{other} {};

    pointer getCurrent() const noexcept { return m_ptr + m_index; };
    pointer getPtr() const noexcept { return m_ptr; };
    size_type getIndex() const noexcept { return m_index; };

    const_reference operator*() const;
    void operator=(const_iterator_reference other) noexcept;
    void operator=(pointer ptr) noexcept;
  };

 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;

  T *alloc();
  void remove() noexcept;

 public:
  vector() noexcept;
  ~vector() noexcept;
  vector(const size_type n);
  vector(const std::initializer_list<value_type> &items);
  vector(const vector &v);
  vector(vector &&v);

  size_type size() const noexcept { return m_size; };
  size_type max_size() const noexcept { return m_capacity; };
  iterator begin() const noexcept;

  vector operator=(vector &&v);
};

template <typename T>
const T &vector<T>::iterator::operator*() const {
  if (!m_ptr) {
    throw std::invalid_argument("Trying to dereference an empty iterator");
  }

  return *m_ptr;
}

template <typename T>
class vector<T>::iterator vector<T>::begin() const noexcept {
  return iterator{arr};
}

template <typename T>
void vector<T>::iterator::operator=(const_iterator_reference other) noexcept {
  m_ptr = other.getPtr();
  m_index = other.getIndex();
}

template <typename T>
void vector<T>::iterator::operator=(pointer ptr) noexcept {
  m_ptr = ptr;
  m_index = 0;
}











template <typename T>
T *vector<T>::alloc() {
  return new T[m_capacity]{};
}

template <typename T>
void vector<T>::remove() noexcept {
  delete[] arr;
  arr = nullptr;
  m_size = m_capacity = 0;
}

template <typename T>
vector<T>::vector() noexcept : m_size{}, m_capacity{}, arr{} {}

template <typename T>
vector<T>::~vector() noexcept {
  remove();
}

template <typename T>
vector<T>::vector(size_type n) : m_size{n}, m_capacity{n}, arr{alloc()} {}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &item)
    : m_size{item.size()}, m_capacity{item.size()}, arr{alloc()} {
  std::copy(item.begin(), item.begin() + m_size, arr);
}

// template <typename T>
// vector<T>::vector(vector &&v) : m_size{v.size()}, m_capacity{v.max_size()} {
//   delete[] arr;
//   Alloc();

//   std::copy()
// }

}  // namespace container

#endif  // _VECTOR_H_