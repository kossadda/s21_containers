/**
 * @file list.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Declaration of the list class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_CONTAINERS_LIST_H_
#define SRC_CONTAINERS_LIST_H_

#include <iostream>
#include <limits>  // for std::numeric_limits

namespace s21 {
/**
 * @brief Class that implements a list.
 *
 * @details
 *
 * List is a sequence container that stores a set of elements with arbitrary
 * size, in the form of nodes connected in sequence by pointers. Each node
 * stores a value corresponding to an element in the list, and a pointer to the
 * next element. This container design allows you to avoid a rigidly fixed size,
 * such as in a static array, and makes adding a new element to the container
 * more user-friendly.
 *
 * @tparam value_type The type of the value stored in the node.
 */
template <typename T>
class list {
  class ListIterator;
  class ListConstIterator;

 public:
  using value_type = T;  ///< Alias for the type of values stored in the list.
  using reference =
      T &;  ///< Alias for a reference to the type of values stored in the list.
  using const_reference = const T &;  ///< Alias for a constant reference to the
                                      ///< type of values stored in the list.
  using size_type =
      std::size_t;  ///< Alias for the type used for size measurements.
  using iterator = ListIterator;  ///< Alias for the iterator type for the list.
  using const_iterator = ListConstIterator;  ///< Alias for the constant
                                             ///< iterator type for the list.
  using pointer =
      T *;  ///< Alias for a pointer to the type of values stored in the list.
  using const_pointer = const T *;  ///< Alias for a constant pointer to the
                                    ///< type of values stored in the list.

  // List Functions

  list() noexcept = default;
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list &operator=(const list &l);
  list(list &&l);
  list &operator=(list &&l);

  ~list() noexcept;

  // List Element Access
  const_reference front() const;
  const_reference back() const;

  // List Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // List Capacity
  bool empty() const noexcept;
  size_type size() const;
  size_type max_size() const;

  // List Modifiers

  void clear() noexcept;
  iterator insert(const_iterator pos, const_reference value);
  iterator erase(const_iterator pos);
  void push_back(const_reference value) noexcept;
  void pop_back() noexcept;
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  template <typename... Args>
  reference emplace_front(Args &&...args);

  template <class... Args>
  reference emplace_back(Args &&...args);

  // Other

  bool operator==(const list &l) const;
  void print() const;

 private:
  struct Node;

  Node *head_{nullptr};  ///< Pointer to the first node in the list. If the list
                         ///< is empty, this is `nullptr`.
  Node *tail_{nullptr};  ///< Pointer to the last node in the list. If the list
                         ///< is empty, this is `nullptr`.
  size_type size_{0};    ///< Number of elements in the list. Initialized to `0`
                         ///< and updated as elements are added or removed.

  void copy_from(const list &l);
  void quick_sort(Node *left, Node *right);
  Node *partition(Node *left, Node *right);
};

/**
 * @brief A node in the doubly linked list.
 * @tparam value_type The type of the value stored in the node.
 */
template <typename value_type>
struct list<value_type>::Node {
  friend class list;

  value_type value;  ///< The value stored in the node. Represents the actual
                     ///< data held by the node.
  Node *prev;        ///< Pointer to the previous node in the list. Points to
                     ///< `nullptr` if this node is the head of the list.
  Node *next;  ///< Pointer to the next node in the list. Points to `nullptr` if
               ///< this node is the tail of the list.

  explicit Node(const_reference val)
      : value{val}, prev{nullptr}, next{nullptr} {}
};

/**
 * @brief Iterator class for iterating over a doubly linked list.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
class list<value_type>::ListIterator {
 public:
  friend class list;

  ListIterator() noexcept = default;
  explicit ListIterator(Node *node) noexcept : node_{node} {}

  reference operator*();
  pointer operator->();
  ListIterator &operator++();
  ListIterator operator++(int);
  ListIterator &operator--();
  ListIterator operator--(int);
  bool operator==(const ListIterator &other) const;
  bool operator!=(const ListIterator &other) const;

  operator const_iterator() const noexcept { return const_iterator{node_}; }

 private:
  Node *node_{nullptr};  ///< Pointer to the node. Initially set to `nullptr`.
                         ///< Used to reference nodes in various operations.
};

/**
 * @brief Iterator class for iterating through a constant list.
 * @tparam value_type The type of elements stored in the list.
 */
template <typename value_type>
class list<value_type>::ListConstIterator {
 public:
  friend class list;

  ListConstIterator() noexcept = default;
  explicit ListConstIterator(Node *node) : node_{node} {}

  const_reference operator*() const;
  const_pointer operator->() const;
  ListConstIterator &operator++();
  ListConstIterator operator++(int);
  ListConstIterator &operator--();
  ListConstIterator operator--(int);
  bool operator==(const ListConstIterator &other) const;
  bool operator!=(const ListConstIterator &other) const;

 private:
  Node *node_{nullptr};  ///< Pointer to the node in the list. Used to keep
                         ///< track of the node's position within the list.
                         ///< Initially set to `nullptr`.
};

// ListIterator ###############################################################

/**
 * @brief Dereference operator.
 * @return Reference to the value stored in the current node.
 */
template <typename value_type>
auto list<value_type>::ListIterator::operator*() -> reference {
  static value_type default_value{};
  return node_ ? node_->value : default_value;
}

/**
 * @brief Arrow operator.
 * @return Pointer to the value stored in the current node.
 */
template <typename value_type>
auto list<value_type>::ListIterator::operator->() -> pointer {
  return &(node_->value);
}

/**
 * @brief Pre-increment operator (++i).
 * @return Reference to the updated iterator.
 */
template <typename value_type>
auto list<value_type>::ListIterator::operator++() -> ListIterator & {
  node_ = node_->next;

  return *this;
}

/**
 * @brief Post-increment operator (i++).
 * @return A copy of the iterator before the increment.
 */
template <typename value_type>
auto list<value_type>::ListIterator::operator++(int) -> ListIterator {
  ListIterator tmp{*this};
  ++(*this);

  return tmp;
}

/**
 * @brief Pre-decrement operator (--i).
 * @return Reference to the updated iterator.
 */
template <typename value_type>
auto list<value_type>::ListIterator::operator--() -> ListIterator & {
  node_ = node_->prev;

  return *this;
}

/**
 * @brief Post-decrement operator (i--).
 * @return A copy of the iterator before decrementing.
 */
template <typename value_type>
auto list<value_type>::ListIterator::operator--(int) -> ListIterator {
  ListIterator tmp{*this};
  --(*this);

  return tmp;
}

/**
 * @brief Equality comparison operator.
 * @param other The iterator to compare against.
 * @return true if both iterators point to the same node, false otherwise.
 */
template <typename value_type>
bool list<value_type>::ListIterator::operator==(
    const ListIterator &other) const {
  return node_ == other.node_;
}

/**
 * @brief Inequality comparison operator.
 * @param other The iterator to compare against.
 * @return true if the iterators point to different nodes, false otherwise.
 */
template <typename value_type>
bool list<value_type>::ListIterator::operator!=(
    const ListIterator &other) const {
  return !(*this == other);
}

// ListConstIterator ##########################################################

/**
 * @brief Dereference operator.
 * @return const_reference A reference to the value of the current node.
 */
template <typename value_type>
auto list<value_type>::ListConstIterator::operator*() const -> const_reference {
  static value_type default_value{};
  return node_ ? node_->value : default_value;
}

/**
 * @brief Member access operator.
 * @return const_pointer A pointer to the value of the current node.
 */
template <typename value_type>
auto list<value_type>::ListConstIterator::operator->() const -> const_pointer {
  return &(node_->value);
}

/**
 * @brief Pre-increment operator (++i).
 * @return Reference to the updated iterator.
 */
template <typename value_type>
auto list<value_type>::ListConstIterator::operator++() -> ListConstIterator & {
  node_ = node_->next;

  return (*this);
}

/**
 * @brief Post-increment operator (i++).
 * @return A copy of the iterator before the increment.
 */
template <typename value_type>
auto list<value_type>::ListConstIterator::operator++(int) -> ListConstIterator {
  ListConstIterator tmp{*this};
  ++(*this);

  return tmp;
}

/**
 * @brief Pre-decrement operator (--i).
 * @return Reference to the updated iterator.
 */
template <typename value_type>
auto list<value_type>::ListConstIterator::operator--() -> ListConstIterator & {
  node_ = node_->prev;

  return (*this);
}

/**
 * @brief Post-decrement operator (i--).
 * @return A copy of the iterator before decrementing.
 */
template <typename value_type>
auto list<value_type>::ListConstIterator::operator--(int) -> ListConstIterator {
  ListConstIterator tmp{*this};
  --(*this);

  return tmp;
}

/**
 * @brief Equality comparison operator.
 * @param other The iterator to compare against.
 * @return true if both iterators point to the same node, false otherwise.
 */
template <typename value_type>
bool list<value_type>::ListConstIterator::operator==(
    const ListConstIterator &other) const {
  return node_ == other.node_;
}

/**
 * @brief Inequality comparison operator.
 * @param other The iterator to compare against.
 * @return true if the iterators point to different nodes, false otherwise.
 */
template <typename value_type>
bool list<value_type>::ListConstIterator::operator!=(
    const ListConstIterator &other) const {
  return !(*this == other);
}

// List ########################################################################

/**
 * @brief Constructs a new list with a specified number of default-initialized
 * elements.
 *
 * @details
 *
 * This constructor initializes an empty list and appends `n`
 * default-initialized elements to the list.
 *
 * @note We should not send a negative n, as the original (and our
 * implementation) goes into an infinite loop. Exceptions are not thrown in this
 * case.
 *
 * @param n The number of elements to add to the list.
 */
template <typename value_type>
list<value_type>::list(size_type n) {
  for (size_type i = 0; i < n; i++) {
    push_back(value_type());
  }
}

/**
 * @brief Constructs a new list from an initializer list of values.
 *
 * @details
 *
 * This constructor initializes an empty list and appends each element
 * from the given initializer list to the end of the list.
 *
 * @param items An initializer list of values to populate the list.
 */
template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) {
  for (const value_type &item : items) {
    push_back(item);
  }
}

/**
 * @brief Copy constructor for creating a new list as a copy of another list.
 *
 * @details
 *
 * This constructor initializes a new list as a copy of the provided list `l`.
 * It initializes the head, tail, and size of the new list and then copies all
 * elements from `l` to the new list using the `copy_from` method.
 *
 * @param l The list to be copied.
 */
template <typename value_type>
list<value_type>::list(const list &l)
    : head_{nullptr}, tail_{nullptr}, size_{0} {
  copy_from(l);
}

/**
 * @brief Assignment operator.
 *
 * @details
 *
 * Copies the contents of list @p l into the current list.
 *
 * @param l The list to copy from.
 * @return Reference to the current list object after copying.
 */
template <typename value_type>
auto list<value_type>::operator=(const list &l) -> list & {
  if (this != l) {
    clear();
    copy_from(l);
  }

  return *this;
}

/**
 * @brief Move constructor.
 *
 * @details
 *
 * Constructs a new list by transferring ownership of the data from the
 * specified list `l` to this list. The source list `l` is left in an
 * empty state.
 *
 * @param l The list to move from.
 */
template <typename value_type>
list<value_type>::list(list &&l)
    : head_{l.head_}, tail_{l.tail_}, size_{l.size_} {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
}

/**
 * @brief Move assignment operator.
 *
 * @details
 *
 * Moves the contents of the list l into the current list and returns a
 * reference to the modified list.
 * @param l The list to move from.
 * @return list reference
 */
template <typename value_type>
auto list<value_type>::operator=(list &&l) -> list & {
  if (this != &l) {
    clear();
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;

    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }

  return std::move(*this);
}

/**
 * @brief Destructor for the list class.
 */
template <typename value_type>
list<value_type>::~list() noexcept {
  clear();
}

/**
 * @brief Access the first element.
 * @return const_reference A reference to the first element in the list.
 * @throw std::out_of_range if the list is empty.
 */
template <typename value_type>
auto list<value_type>::front() const -> const_reference {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }

  return head_->value;
}

/**
 * @brief Access the last element.
 * @return const_reference A reference to the last element in the list.
 * @throw std::out_of_range if the list is empty.
 */
template <typename value_type>
auto list<value_type>::back() const -> const_reference {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }

  return tail_->value;
}

/**
 * @brief Returns an iterator to the beginning of the list.
 * @return iterator An iterator to the first element in the list.
 */
template <typename value_type>
auto list<value_type>::begin() -> iterator {
  return empty() ? iterator{nullptr} : iterator{head_};
}

/**
 * @brief Returns an iterator to the end of the list.
 * @return iterator An iterator to the element following the last element in the
 * list.
 */
template <typename value_type>
auto list<value_type>::end() -> iterator {
  return iterator{nullptr};
}

/**
 * @brief Returns a constant iterator to the beginning of the list.
 * @return A constant iterator to the beginning of the list or `nullptr` if the
 * list is empty.
 */
template <typename value_type>
auto list<value_type>::cbegin() const -> const_iterator {
  return empty() ? const_iterator{nullptr} : const_iterator{head_};
}

/**
 * @brief Returns a constant iterator to the end of the list.
 * @details
 *
 * This function returns a constant iterator pointing to one past the last
 * element of the list, which is represented by `nullptr`.
 *
 * @return A constant iterator to the end of the list.
 */
template <typename value_type>
auto list<value_type>::cend() const -> const_iterator {
  return const_iterator{nullptr};
}

/**
 * @brief Checks whether the container is empty.
 */
template <typename value_type>
bool list<value_type>::empty() const noexcept {
  return size_ == 0;
}

/**
 * @brief Returns the number of elements in the list.
 * @return size_type The number of elements in the list.
 */
template <typename value_type>
auto list<value_type>::size() const -> size_type {
  return size_;
}

/**
 * @brief Returns the maximum possible number of elements the list can hold.
 * @details
 *
 * This function returns the largest possible value for the size of the list,
 * which is determined by the implementation-defined limit for the size type.
 *
 * @return The maximum possible number of elements the list can hold.
 */
template <typename value_type>
auto list<value_type>::max_size() const -> size_type {
  return std::numeric_limits<size_type>::max();
}

/**
 * @brief Clear the contents of the list.
 */
template <typename value_type>
void list<value_type>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }
}

/**
 * @brief Inserts a new element before the specified position.
 *
 * @details
 *
 * This function inserts a new node containing the given value before the
 * position indicated by the iterator `pos`. If `pos` is an end iterator,
 * the new node is inserted at the end of the list. The list is adjusted
 * accordingly, and the size of the list is increased by one.
 *
 * @param pos An iterator pointing to the position before which the new element
 * will be inserted. If `pos` is an end iterator, the new element is appended to
 * the end of the list.
 * @param value The value to be inserted into the list.
 * @return An iterator pointing to the newly inserted element.
 */
template <typename value_type>
auto list<value_type>::insert(const_iterator pos, const_reference value)
    -> iterator {
  Node *new_node = new Node(value);

  if (!pos.node_) {
    new_node->prev = tail_;

    if (tail_) {
      tail_->next = new_node;
    } else {
      head_ = new_node;
    }

    tail_ = new_node;

  } else {
    new_node->prev = pos.node_->prev;
    new_node->next = pos.node_;

    if (pos.node_->prev) {
      pos.node_->prev->next = new_node;
    } else {
      head_ = new_node;
    }

    pos.node_->prev = new_node;
  }

  ++size_;

  return iterator(new_node);
}

/**
 * @brief Removes the element at the specified position.
 *
 * @details
 *
 * This function removes the node pointed to by the iterator `pos` from the
 * list. After the removal, the list is adjusted accordingly, and the size
 * of the list is decreased by one. The iterator returned points to the element
 * following the removed element. If the list is empty or the iterator is
 * equal to the end iterator, the end iterator is returned.
 *
 * @note The original function does not handle the case where `pos` is a null
 * iterator. In the original implementation, attempting to remove an element
 * when `pos` is equal to `end()` may lead to undefined behavior such as double
 * free or corruption. It is recommended to ensure that `pos` is a valid
 * iterator within the list before calling this function to avoid such issues.
 * Our implementation only removes an item if the list is not empty. We consider
 * it inexpedient to imitate the behaviour of the original method.
 * The method returns void, while the original returns iterator. We implemented
 * it as in the original function. Guys from pedago, pay more attention.
 *
 * @param pos An iterator pointing to the element to be removed.
 * @return An iterator pointing to the element following the removed element,
 * or the end iterator if the list is empty or `pos` is the end
 * iterator.
 */
template <typename value_type>
auto list<value_type>::erase(const_iterator pos) -> iterator {
  if ((pos != end()) && (!empty())) {
    Node *node_to_remove = pos.node_;
    iterator next_it = iterator(node_to_remove->next);

    if (node_to_remove == head_) {
      head_ = node_to_remove->next;
    } else if (node_to_remove == tail_) {
      tail_ = node_to_remove->prev;
      tail_->next = nullptr;
    } else {
      node_to_remove->next->prev = node_to_remove->prev;
      node_to_remove->prev->next = node_to_remove->next;
    }

    delete node_to_remove;
    --size_;

    return next_it;
  }

  return end();
}

/**
 * @brief Adds a new node with the given value to the end of the list.
 *
 * @details
 *
 * This function creates a new node containing the specified value and appends
 * it to the end of the list. If memory allocation fails, an error message is
 * printed to the standard error stream (std::cerr)
 *
 * @param value The value to be added to the list.
 */
template <typename value_type>
void list<value_type>::push_back(const_reference value) noexcept {
  Node *new_node = new Node{value};

  if (!head_) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->next = new_node;
    new_node->prev = tail_;
    tail_ = new_node;
  }

  ++size_;
}

/**
 * @brief Removes the last element of the list.
 */
template <typename value_type>
void list<value_type>::pop_back() noexcept {
  if (empty()) {
    std::cerr << "list is empty" << std::endl;
  } else {
    if (size_ == 1) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      Node *prev = tail_->prev;
      delete tail_;
      tail_ = prev;
      tail_->next = nullptr;
    }

    size_--;
  }
}

/**
 * @brief Inserts an element at the beginning of the list.
 *
 * @details
 *
 * This function creates a new node with the given value and inserts it
 * at the front of the list. If the list is empty, the new node becomes
 * both the head and the tail of the list. Otherwise, the new node is
 * inserted before the current head, and the head pointer is updated to
 * the new node. The size of the list is increased by one.
 *
 * @param value The value to be inserted at the beginning of the list.
 */
template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  Node *new_node = new Node(value);

  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }

  ++size_;
}

/**
 * @brief Removes the element at the beginning of the list.
 *
 * @details
 *
 * This function removes the node at the front of the list. If the list
 * becomes empty as a result of this operation, both the head and tail
 * pointers are set to `nullptr`. Otherwise, the head pointer is updated
 * to the next node, and the new head's `prev` pointer is set to `nullptr`.
 * The removed node is deleted, and the size of the list is decreased by one.
 *
 * @note If the list is empty when this function is called, the behavior of
 * the function is currently undefined. It is recommended to check if the list
 * is empty before calling this function to avoid unexpected behavior.
 *
 */
template <typename value_type>
void list<value_type>::pop_front() {
  if (head_) {
    Node *old_head = head_;
    head_ = head_->next;

    if (head_) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr;
    }

    delete old_head;
    --size_;
  }
}

/**
 * @brief Swaps the contents of this list with another list.
 *
 * @details
 *
 * This function exchanges the elements and internal state of this list with
 * another list of the same type. After the swap, the two lists will contain
 * the elements that were originally in the other list and vice versa. This
 * function operates in constant time.
 *
 * @param other The list to swap contents with. It must be of the same type as
 * this list.

 */
template <typename value_type>
void list<value_type>::swap(list &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

/**
 * @brief Merges the elements of another list into this list.
 *
 * @details
 *
 * This function merges the elements from another list into this list. The
 * elements from the other list are inserted into this list in a sorted manner,
 * assuming both lists are sorted. After merging, the other list will be empty.
 *
 * @param other The list to merge with this list. It must be of the same type as
 * this list and must be sorted.
 */
template <typename value_type>
void list<value_type>::merge(list &other) {
  auto this_it = begin();
  auto other_it = other.begin();

  while (this_it != end() && other_it != other.end()) {
    if (*other_it < *this_it) {
      insert(this_it, std::move(*other_it));
      other_it = other.erase(other_it);
    } else {
      ++this_it;
    }
  }

  while (other_it != other.end()) {
    push_back(std::move(*other_it));
    other_it = other.erase(other_it);
  }
}

/**
 * @brief Splices elements from another list into this list at the specified
 * position.
 *
 * @details
 *
 * This function transfers all elements from another list to this list,
 * inserting them at the position specified by the `pos` iterator. After
 * splicing, the other list will be empty, and its elements will be removed from
 * it. If the two lists are the same or the other list is empty, the function
 * does nothing. If this list is empty, it swaps the contents with the other
 * list.
 *
 * @param pos The position in this list where the elements from the other list
 * should be inserted. This iterator should be valid for this list.
 * @param other The list whose elements are to be spliced into this list. It
 * must be of the same type as this list.
 */
template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (this == &other || other.empty()) {
    return;
  }

  if (empty()) {
    swap(other);
  } else {
    auto pos_node = pos.node_;
    auto first_other = other.head_;
    auto last_other = other.tail_;

    if (pos_node == head_) {
      head_ = first_other;
    } else {
      pos_node->prev->next = first_other;
      first_other->prev = pos_node->prev;
    }

    last_other->next = pos_node;
    pos_node->prev = last_other;

    other.head_ = nullptr;
    other.tail_ = nullptr;

    size_ += other.size_;
    other.size_ = 0;
  }
}

/**
 * @brief Reverses the order of elements in the list.
 *
 * @details
 *
 * This function reverses the elements in the list by swapping the `next` and
 * `prev` pointers of each node. After reversal, the `head_` will point to what
 * was previously the last node, and the `tail_` will point to what was
 * previously the first node. If the list has fewer than two elements, the
 * function returns without making any changes.
 *
 */
template <typename value_type>
void list<value_type>::reverse() {
  if (size_ < 2) {
    return;
  }

  Node *current = head_;
  Node *next_node = nullptr;
  Node *prev_node = nullptr;

  while (current != nullptr) {
    next_node = current->next;
    current->next = prev_node;
    current->prev = next_node;
    prev_node = current;
    current = next_node;
  }

  tail_ = head_;
  head_ = prev_node;
}

/**
 * @brief Removes consecutive duplicate elements from the list.
 *
 * @details
 *
 * This function iterates through the list and removes nodes with values that
 * are identical to the next node's value. Only consecutive duplicate elements
 * are removed, and the list is modified in place. If the list is empty or has
 * fewer than two elements, the function returns without making any changes.
 */
template <typename value_type>
void list<value_type>::unique() {
  if (empty() || !head_->next) {
    return;
  }

  Node *current = head_;

  while (current && current->next) {
    if (current->value == current->next->value) {
      Node *node_to_remove = current->next;
      current->next = node_to_remove->next;

      if (node_to_remove->next) {
        node_to_remove->next->prev = current;
      } else {
        tail_ = current;
      }

      delete node_to_remove;
      --size_;
    } else {
      current = current->next;
    }
  }
}

/**
 * @brief Sorts the elements in the list in ascending order.
 *
 * @details
 *
 * This function uses the quicksort algorithm to sort the elements of the list.
 * It will only perform sorting if the list contains more than one element. If
 * the list is empty or contains a single element, no action is taken.
 */
template <typename value_type>
void list<value_type>::sort() {
  if (size_ > 1) {
    quick_sort(head_, tail_);
  }
}

/**
 * @brief Inserts a new element at the end of the list.
 *
 * @details
 *
 * This function creates a new element in the list using the provided arguments.
 * The element is constructed in-place at the end of the list. If the list is
 * empty, the new element becomes both the head and the tail of the list.
 *
 * @param args The arguments used to construct the new element.
 * @return A reference to the newly added element in the list.
 */
template <typename value_type>
template <typename... Args>
auto list<value_type>::emplace(const_iterator pos, Args &&...args) -> iterator {
  Node *new_node = new Node(value_type{std::forward<Args>(args)...});

  Node *current = pos.node_;

  if (!current) {
    if (!tail_) {
      head_ = tail_ = new_node;
    } else {
      new_node->prev = tail_;
      tail_->next = new_node;
      tail_ = new_node;
    }
  } else {
    new_node->next = current;
    new_node->prev = current->prev;

    if (current->prev) {
      current->prev->next = new_node;
    } else {
      head_ = new_node;
    }
    current->prev = new_node;
  }

  ++size_;

  return iterator(new_node);
}

/**
 * @brief Inserts a new element at the beginning of the list.
 *
 * @details
 *
 * This function constructs a new element in the list using the provided
 * arguments, and inserts it at the front of the list. If the list is empty, the
 * new element becomes both the head and the tail of the list.
 *
 * @param args The arguments used to construct the new element.
 * @return A reference to the newly added element at the front of the list.
 */
template <typename value_type>
template <typename... Args>
auto list<value_type>::emplace_front(Args &&...args) -> reference {
  Node *new_node = new Node{value_type{std::forward<Args>(args)...}};

  if (!head_) {
    head_ = tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }

  ++size_;

  return new_node->value;
}

/**
 * @brief Inserts a new element at the end of the list.
 *
 * @details
 *
 * This function constructs a new element in the list using the provided
 * arguments, and inserts it at the back of the list. If the list is empty, the
 * new element becomes both the head and the tail of the list.
 *
 * @param args The arguments used to construct the new element.
 * @return A reference to the newly added element at the end of the list.
 */
template <typename value_type>
template <typename... Args>
auto list<value_type>::emplace_back(Args &&...args) -> reference {
  Node *new_node = new Node{value_type{std::forward<Args>(args)...}};

  if (!tail_) {
    head_ = tail_ = new_node;
  } else {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
  }

  ++size_;

  return new_node->value;
}

/**
 * @brief Copies elements from another list to the current list.
 *
 * @details
 *
 * This method copies all elements from the provided list `l` to the current
 * list. It iterates through the elements of `l` and appends each element to the
 * current list.
 *
 * @param l The list from which elements will be copied.
 */
template <typename value_type>
void list<value_type>::copy_from(const list &l) {
  Node *current = l.head_;

  while (current) {
    push_back(current->value);
    current = current->next;
  }
}

/**
 * @brief Recursively sorts the elements in the list using the quicksort
 * algorithm.
 *
 * @details
 *
 * This function is a recursive implementation of the quicksort algorithm that
 * sorts the elements between the given `left` and `right` nodes. It selects a
 * pivot element, partitions the list around the pivot, and then recursively
 * sorts the partitions.
 *
 * @param left Pointer to the starting node of the segment to be sorted.
 * @param right Pointer to the ending node of the segment to be sorted.
 */
template <typename value_type>
void list<value_type>::quick_sort(Node *left, Node *right) {
  if (!left || !right) return;
  if (left != right && left != right->next) {
    Node *pivot = partition(left, right);
    quick_sort(left, pivot->prev);
    quick_sort(pivot->next, right);
  }
}

/**
 * @brief Partitions the list around a pivot for quicksort.
 *
 * @details
 *
 * This function partitions the list segment between `left` and `right` nodes.
 * The element at the `right` node is chosen as the pivot. The function
 * rearranges the nodes such that all elements less than or equal to the pivot
 * come before it, and all elements greater than the pivot come after it.
 * Finally, it places the pivot element in its correct position.
 *
 * @param left Pointer to the starting node of the segment to be partitioned.
 * @param right Pointer to the ending node (pivot) of the segment to be
 * partitioned.
 * @return Pointer to the node that holds the pivot element after partitioning.
 */
template <typename value_type>
auto list<value_type>::partition(Node *left, Node *right) -> Node * {
  value_type pivot_value = right->value;
  Node *i = left->prev;

  for (Node *j = left; j != right; j = j->next) {
    if (j->value <= pivot_value) {
      i = (i == nullptr) ? left : i->next;
      std::swap(i->value, j->value);
    }
  }

  i = (i == nullptr) ? left : i->next;
  std::swap(i->value, right->value);

  return i;
}

/**
 * @brief Equality operator to compare two lists.
 *
 * @param l The list to compare with the current list.
 * @retval true if both lists have the same size and all corresponding elements
 * are equal.
 * @retval false if the sizes of the lists are different or if at least one
 * element differs.
 */
template <typename value_type>
bool list<value_type>::operator==(const list &l) const {
  if (size_ != l.size_) {
    return false;
  }

  Node *current_1 = head_;
  Node *current_2 = l.head_;

  while (current_1 && current_2) {
    if (current_1->value != current_2->value) {
      return false;
    }

    current_1 = current_1->next;
    current_2 = current_2->next;
  }

  return true;
}

/**
 * @brief Prints the elements of the list to the standard output.
 *
 * @details
 *
 * This function iterates over all elements in the list, starting from the
 * beginning and ending at the end, and prints each element followed by a space.
 * After printing all elements, it outputs a newline character.
 */
template <typename value_type>
void list<value_type>::print() const {
  for (auto it = cbegin(); it != cend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

}  // namespace s21

#endif  // SRC_CONTAINERS_LIST_H_
