/**
 * @file map.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_MAP_H_
#define SRC_MODULES_MAP_H_

#include "./tree.h"

namespace s21 {

template <typename key_type, typename value_type>
class map {
 private:
  // Container types
  class MapConstIterator;
  class MapIterator;

 public:
  // Type aliases
  using pointer = value_type *;             ///< Pointer to value_type
  using reference = value_type &;           ///< Reference to value_type
  using const_reference = const reference;  ///< Const refer to value_type
  using size_type = std::size_t;            ///< Containers size type
  using iterator = SetIterator;             ///< For read/write elements
  using const_iterator = SetConstIterator;  ///< For read elements

 private:
  size_type size_{};      ///< Size of vector
  size_type capacity_{};  ///< Current capacity of vector
  value_type *arr_{};     ///< Array of elements

 public:
  // Constructors/assignment operators/destructor
  map() noexcept = default;
};

}  // namespace s21

#endif  // SRC_MODULES_MAP_H_
