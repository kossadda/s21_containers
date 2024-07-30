/**
 * @file map.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header for the map container.
 * @version 1.0
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_MAP_H_
#define SRC_MODULES_MAP_H_

#include <limits>

#include "./tree.h"

/// @brief Namespace for working with containers
namespace s21 {

/**
 * @brief A map container template class.
 *
 * @details
 * This template class map provides a map similar to std::map in the C++
 * Standard Library. It manages a balanced binary search tree of elements of
 * type K and M, supporting various operations including iteration, element
 * access, and size management.
 *
 * @tparam K The type of keys stored in the map.
 * @tparam M The type of values stored in the map.
 */
template <typename K, typename M>
class map {
 private:
  // Container types

  typedef typename tree<K, M>::const_iterator MapConstIterator;
  typedef typename tree<K, M>::iterator MapIterator;

 public:
  // Type aliases

  using key_type = K;                               ///< Type of pairs key
  using mapped_type = M;                            ///< Type of keys value
  using value_type = std::pair<K, M>;               ///< Pair key-value
  using reference = value_type &;                   ///< Reference to pair
  using const_reference = const value_type &;       ///< Const reference to pair
  using size_type = std::size_t;                    ///< Containers size type
  using iterator = MapIterator;                     ///< For read/write elements
  using const_iterator = MapConstIterator;          ///< For read elements
  using iterator_bool = std::pair<iterator, bool>;  ///< Pair iterator-bool

 private:
  tree<key_type, mapped_type> tree_{};  ///< Tree of elements
  size_type size_{};                    ///< Size of map

 public:
  // Constructors/assignment operators/destructor

  map() noexcept = default;
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  map &operator=(map &&m);
  map &operator=(const map &m);

  // Map Element access

  mapped_type &at(const key_type &key) const;
  mapped_type &operator[](const key_type &key) noexcept;
  const mapped_type &operator[](const key_type &key) const noexcept;

  // Map Iterators

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Map Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Map Modifiers

  void clear();
  iterator_bool insert(const_reference value);
  iterator_bool insert(const key_type &key, const mapped_type &obj);
  iterator_bool insert_or_assign(const key_type &key, const mapped_type &obj);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  size_type erase(const key_type &key);
  void swap(map &other);
  void merge(map &other);

  // Map Lookup

  bool conatains(const key_type &key) const noexcept;
};

////////////////////////////////////////////////////////////////////////////////
//                              MAP CONSTRUCTORS                              //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs a map with elements from an initializer list.
 *
 * @details
 * This constructor initializes the map with elements from the given
 * initializer list. It creates a new tree and inserts all elements from the
 * list into the tree.
 *
 * @param[in] items The initializer list of key-value pairs to insert into the
 * map.
 */
template <typename K, typename M>
map<K, M>::map(std::initializer_list<value_type> const &items)
    : tree_{items}, size_{tree_.size()} {}

/**
 * @brief Copy constructor for the map.
 *
 * @details
 * This constructor creates a new map by copying the elements from another map.
 * It initializes the tree with the elements from the source map.
 *
 * @param[in] m The map to copy from.
 */
template <typename K, typename M>
map<K, M>::map(const map &m) : tree_{m.tree_}, size_{m.size_} {}

/**
 * @brief Move constructor for the map.
 *
 * @details
 * This constructor creates a new map by moving the elements from another map.
 * It takes ownership of the tree from the source map, leaving the source map
 * in a valid but unspecified state.
 *
 * @param[in] m The map to move from.
 */
template <typename K, typename M>
map<K, M>::map(map &&m)
    : tree_{std::move(m.tree_)}, size_{std::exchange(m.size_, 0)} {}

/**
 * @brief Move assignment operator for the map.
 *
 * @details
 * This operator moves the elements from another map to the current map.
 * It first cleans up the current map and then moves the elements from the
 * source map.
 *
 * @param[in] m The map to move from.
 * @return map<K, M>& - reference to the assigned map.
 */
template <typename K, typename M>
map<K, M> &map<K, M>::operator=(map &&m) {
  if (this != &m) {
    tree_.clear();
    new (this) map{std::move(m)};
  }

  return *this;
}

/**
 * @brief Copy assignment operator for the map.
 *
 * @details
 * This operator copies the elements from another map to the current map.
 * It first cleans up the current map and then copies the elements from the
 * source map.
 *
 * @param[in] m The map to copy from.
 * @return map<K, M>& - reference to the assigned map.
 */
template <typename K, typename M>
map<K, M> &map<K, M>::operator=(const map &m) {
  if (this != &m) {
    tree_.clear();
    new (this) map{m};
  }

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
//                              MAP ELEMENT ACCESS                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Accesses the value associated with a given key.
 *
 * @details
 * This method returns a reference to the value associated with the given key.
 * If the key is not found, it throws an std::out_of_range exception.
 *
 * @param[in] key The key to search for.
 * @return mapped_type& - reference to the value associated with the key.
 * @throws std::out_of_range if the key is not found.
 */
template <typename K, typename M>
typename map<K, M>::mapped_type &map<K, M>::at(const key_type &key) const {
  auto it = tree_.find(key);

  if (it == tree_.end()) {
    throw std::out_of_range("map::at() - missing element");
  }

  return (*it).second;
}

/**
 * @brief Accesses or inserts a value associated with a given key.
 *
 * @details
 * This method returns a reference to the value associated with the given key.
 * If the key is not found, it inserts a new element with the given key and a
 * default-constructed value.
 *
 * @param[in] key The key to search for.
 * @return mapped_type& - reference to the value associated with the key.
 */
template <typename K, typename M>
typename map<K, M>::mapped_type &map<K, M>::operator[](
    const key_type &key) noexcept {
  auto it = tree_.find(key);

  if (it == tree_.end()) {
    it = tree_.insert({key, mapped_type{}});
    ++size_;
  }

  return (*it).second;
}

/**
 * @brief Accesses the value associated with a given key (const version).
 *
 * @details
 * This method returns a const reference to the value associated with the given
 * key. If the key is not found, it throws an std::out_of_range exception.
 *
 * @param[in] key The key to search for.
 * @return const mapped_type& - const reference to the value associated with the
 * key.
 * @throws std::out_of_range if the key is not found.
 */
template <typename K, typename M>
const typename map<K, M>::mapped_type &map<K, M>::operator[](
    const key_type &key) const noexcept {
  return (*tree_.find(key)).second;
}

////////////////////////////////////////////////////////////////////////////////
//                                MAP ITERATORS                               //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Returns an iterator to the beginning of the map.
 *
 * @details
 * This method returns an iterator to the first element of the map.
 *
 * @return iterator - an iterator to the beginning of the map.
 */
template <typename K, typename M>
typename map<K, M>::iterator map<K, M>::begin() const noexcept {
  return tree_.begin();
}

/**
 * @brief Returns an iterator to the end of the map.
 *
 * @details
 * This method returns an iterator to the element following the last element
 * of the map.
 *
 * @return iterator - an iterator to the end of the map.
 */
template <typename K, typename M>
typename map<K, M>::iterator map<K, M>::end() const noexcept {
  return tree_.end();
}

/**
 * @brief Returns a const iterator to the beginning of the map.
 *
 * @details
 * This method returns a const iterator to the first element of the map.
 *
 * @return const_iterator - a const iterator to the beginning of the map.
 */
template <typename K, typename M>
typename map<K, M>::const_iterator map<K, M>::cbegin() const noexcept {
  return tree_.cbegin();
}

/**
 * @brief Returns a const iterator to the end of the map.
 *
 * @details
 * This method returns a const iterator to the element following the last
 * element of the map.
 *
 * @return const_iterator - a const iterator to the end of the map.
 */
template <typename K, typename M>
typename map<K, M>::const_iterator map<K, M>::cend() const noexcept {
  return tree_.cend();
}

////////////////////////////////////////////////////////////////////////////////
//                                 MAP CAPACITY                               //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the map is empty.
 *
 * @details
 * This method returns true if the map contains no elements, and false
 * otherwise.
 *
 * @return bool - true if the map is empty, false otherwise.
 */
template <typename K, typename M>
bool map<K, M>::empty() const noexcept {
  return (!size_) ? true : false;
}

/**
 * @brief Returns the number of elements in the map.
 *
 * @details
 * This method returns the number of elements currently stored in the map.
 *
 * @return size_type - the number of elements in the map.
 */
template <typename K, typename M>
typename map<K, M>::size_type map<K, M>::size() const noexcept {
  return size_;
}

/**
 * @brief Returns the maximum number of elements the vector can hold.
 *
 * @return size_type - the maximum number of elements.
 */
template <typename K, typename M>
typename map<K, M>::size_type map<K, M>::max_size() const noexcept {
  size_type num_of_ptr = 4;
  size_type ptr_size = 8;
  size_type node_size = num_of_ptr * ptr_size + sizeof(size_type);
  return std::numeric_limits<size_type>::max() / sizeof(node_size) / 10;
}

////////////////////////////////////////////////////////////////////////////////
//                                MAP MODIFIERS                               //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Clears the contents of the map.
 *
 * @details
 * This method removes all elements from the map, leaving it empty.
 *
 */
template <typename K, typename M>
void map<K, M>::clear() {
  size_ = 0;
  tree_.clear();
}

/**
 * @brief Inserts a new element into the map.
 *
 * @details
 * This method inserts a new element with the given value into the map.
 * If the element already exists, it returns an iterator to the existing
 * element.
 *
 * @param[in] value The value to insert.
 * @return iterator_bool - a pair containing an iterator to the inserted element
 * and a bool indicating whether the insertion took place.
 */
template <typename K, typename M>
typename map<K, M>::iterator_bool map<K, M>::insert(const_reference value) {
  auto it = tree_.insert(value);
  size_ = tree_.size();

  return (it != tree_.end()) ? iterator_bool{it, true}
                             : iterator_bool{tree_.find(value.first), false};
}

/**
 * @brief Inserts a new element with the given key and value into the map.
 *
 * @details
 * This method inserts a new element with the given key and value into the map.
 * If the element already exists, it returns an iterator to the existing
 * element.
 *
 * @param[in] key The key of the element to insert.
 * @param[in] obj The value of the element to insert.
 * @return iterator_bool - a pair containing an iterator to the inserted element
 * and a bool indicating whether the insertion took place.
 */
template <typename K, typename M>
typename map<K, M>::iterator_bool map<K, M>::insert(const key_type &key,
                                                    const mapped_type &obj) {
  auto it = tree_.insert({key, obj});
  size_ = tree_.size();

  return (it != end()) ? iterator_bool{it, true}
                       : iterator_bool{tree_.find(key), false};
}

/**
 * @brief Inserts a new element with the given key and value into the map, or
 * assigns the value if the key already exists.
 *
 * @details
 * This method inserts a new element with the given key and value into the map.
 * If the element already exists, it assigns the new value to the existing
 * element.
 *
 * @param[in] key The key of the element to insert or assign.
 * @param[in] obj The value of the element to insert or assign.
 * @return iterator_bool - a pair containing an iterator to the inserted or
 * assigned element and a bool indicating whether the insertion took place.
 */
template <typename K, typename M>
typename map<K, M>::iterator_bool map<K, M>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  auto it = tree_.find(key);
  bool obj_exists{false};

  if (it == tree_.end()) {
    it = tree_.insert({key, obj});
    size_ = tree_.size();
    obj_exists = true;
  } else {
    (*it).second = obj;
  }

  return iterator_bool{it, obj_exists};
}

/**
 * @brief Erases the element at the specified position.
 *
 * @details
 * This method removes the element at the specified position from the map.
 *
 * @param[in] pos The position of the element to erase.
 * @return iterator - an iterator to the element following the erased element,
 * or end() if the erased element was the last element.
 */
template <typename K, typename M>
typename map<K, M>::iterator map<K, M>::erase(const_iterator pos) {
  auto it = tree_.erase((*pos).first);
  size_ = tree_.size();

  return it;
}

/**
 * @brief Erases the elements in the specified range.
 *
 * @details
 * This method removes the elements in the range [first, last) from the map.
 *
 * @param[in] first The position of the first element to erase.
 * @param[in] last The position following the last element to erase.
 * @return iterator - an iterator to the element following the last erased
 * element, or end() if the last erased element was the last element.
 * @throws std::range_error if the range is invalid.
 */
template <typename K, typename M>
typename map<K, M>::iterator map<K, M>::erase(const_iterator first,
                                              const_iterator last) {
  iterator it = tree_.erase(first, last);
  size_ = tree_.size();

  return it;
}

/**
 * @brief Erases the elements with the specified key.
 *
 * @details
 * This method removes all elements with the specified key from the map.
 *
 * @param[in] key The key of the elements to erase.
 * @return size_type - the number of elements erased.
 */
template <typename K, typename M>
typename map<K, M>::size_type map<K, M>::erase(const key_type &key) {
  auto it = tree_.erase(key);
  size_ = tree_.size();

  return (it != tree_.end()) ? true : false;
}

/**
 * @brief Swaps the contents of the map with another map.
 *
 * @details
 * This method swaps the contents of the map with the contents of another map.
 *
 * @param[in,out] other The map to swap with.
 */
template <typename K, typename M>
void map<K, M>::swap(map &other) {
  std::swap(size_, other.size_);
  std::swap(tree_, other.tree_);
}

/**
 * @brief Merges the contents of another map into the current map.
 *
 * @details
 * This method merges the contents of another map into the current map.
 * The elements from the other map are inserted into the current map.
 *
 * @param[in,out] other The map to merge with.
 */
template <typename K, typename M>
void map<K, M>::merge(map &other) {
  tree_.merge(other.tree_);
  size_ = tree_.size();
  other.size_ = other.tree_.size();
}

////////////////////////////////////////////////////////////////////////////////
//                                  MAP LOOKUP                                //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the map contains an element with the specified key.
 *
 * @details
 * This method returns true if the map contains an element with the specified
 * key, and false otherwise.
 *
 * @param[in] key The key to search for.
 * @return bool - true if the map contains an element with the specified key,
 * false otherwise.
 */
template <typename K, typename M>
bool map<K, M>::conatains(const key_type &key) const noexcept {
  return (tree_.find(key) != tree_.end()) ? true : false;
}

}  // namespace s21

#endif  // SRC_MODULES_MAP_H_
