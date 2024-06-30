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

namespace container {

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
    T *m_ptr = nullptr;
    int m_index = 0;

   public:
    iterator() noexcept {};
    explicit iterator(const pointer ptr);
    iterator(const_iterator_reference other);

    void operator=(const_iterator_reference other) noexcept;
    void operator=(pointer ptr) noexcept;
    iterator_reference operator--() noexcept;
    iterator_reference operator++() noexcept;
    iterator operator--(int) noexcept;
    iterator operator++(int) noexcept;
    iterator operator-(const int shift) const noexcept;
    size_type operator-(const_iterator_reference other) const noexcept;
    iterator operator+(const int shift) const noexcept;
    void operator-=(const int shift) noexcept;
    void operator+=(const int shift) noexcept;
    bool operator==(iterator other) const noexcept;
    bool operator!=(iterator other) const noexcept;
    const_reference operator*() const;
    reference operator*();
  };

 private:
  size_t m_size = 0;
  size_t m_capacity = 0;
  T *arr = nullptr;

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
  iterator end() const noexcept;

  vector operator=(vector &&v);
};

template <typename T>
vector<T>::iterator::iterator(const pointer ptr) : m_ptr{ptr} {};

template <typename T>
vector<T>::iterator::iterator(const_iterator_reference other)
    : m_ptr{other.m_ptr}, m_index{other.m_index} {};

template <typename T>
const T &vector<T>::iterator::operator*() const {
  if (!m_ptr)
    throw std::invalid_argument("Trying to dereference an empty iterator");

  return *m_ptr;
}

template <typename T>
T &vector<T>::iterator::operator*() {
  if (!m_ptr)
    throw std::invalid_argument("Trying to dereference an empty iterator");

  return *m_ptr;
}

template <typename T>
void vector<T>::iterator::operator=(const_iterator_reference other) noexcept {
  m_ptr = other.m_ptr;
  m_index = other.m_index;
}

template <typename T>
void vector<T>::iterator::operator=(pointer ptr) noexcept {
  m_ptr = ptr;
  m_index = 0;
}

template <typename T>
class vector<T>::iterator &vector<T>::iterator::operator--() noexcept {
  m_ptr--;
  m_index--;

  return *this;
}

template <typename T>
class vector<T>::iterator vector<T>::iterator::operator--(int) noexcept {
  iterator copy{*this};
  m_ptr--;
  m_index--;

  return copy;
}

template <typename T>
class vector<T>::iterator &vector<T>::iterator::operator++() noexcept {
  m_ptr++;
  m_index++;

  return *this;
}

template <typename T>
class vector<T>::iterator vector<T>::iterator::operator++(int) noexcept {
  iterator copy{*this};
  m_ptr++;
  m_index++;

  return copy;
}

template <typename T>
class vector<T>::iterator vector<T>::iterator::operator-(
    const int shift) const noexcept {
  iterator copy(*this);
  copy.m_index -= shift;
  copy.m_ptr -= shift;

  return copy;
}

template <typename T>
size_t vector<T>::iterator::operator-(
    const_iterator_reference other) const noexcept {
  return (m_ptr > other.m_ptr) ? m_ptr - other.m_ptr : other.m_ptr - m_ptr;
}

template <typename T>
class vector<T>::iterator vector<T>::iterator::operator+(
    const int shift) const noexcept {
  iterator copy(*this);
  copy.m_index += shift;
  copy.m_ptr += shift;

  return copy;
}

template <typename T>
void vector<T>::iterator::operator-=(const int shift) noexcept {
  m_index -= shift;
  m_ptr -= shift;
}

template <typename T>
void vector<T>::iterator::operator+=(const int shift) noexcept {
  m_index += shift;
  m_ptr += shift;
}

template <typename T>
bool vector<T>::iterator::operator==(iterator other) const noexcept {
  return m_ptr == other.m_ptr;
}

template <typename T>
bool vector<T>::iterator::operator!=(iterator other) const noexcept {
  return m_ptr != other.m_ptr;
}

////////////////////////////////////////////////////////////////////////////////

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
class vector<T>::iterator vector<T>::begin() const noexcept {
  return iterator{arr};
}

template <typename T>
class vector<T>::iterator vector<T>::end() const noexcept {
  return iterator{arr + m_size};
}

template <typename T>
vector<T>::vector() noexcept {
}

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