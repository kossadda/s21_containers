/**
 * @file queue.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Declaration of the queue class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_CONTAINERS_QUEUE_H_
#define SRC_CONTAINERS_QUEUE_H_

namespace s21 {

/**
 * @brief Template class for a queue data structure.
 *
 * @tparam T The type of elements stored in the queue.
 * @tparam Container The type of the underlying container used to store the
 * elements. Defaults to s21::list<T> if not specified.
 */
template <typename T, typename Container = list<T>>
class queue {
 public:
  using value_type = T;  ///< Alias for the type of values stored in the queue.
  using reference = T
      &;  ///< Alias for a mutable reference to an element stored in the queue.
  using const_reference = const T &;  ///< Alias for a read-only reference to an
                                      ///< element stored in the queue.
  using size_type = std::size_t;  ///< Alias for the type used to represent the
                                  ///< number of elements in the queue.

  queue() : queue(Container()) {}
  explicit queue(const Container &other);
  explicit queue(Container &&other);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(queue &&q);

  // Queue Element access

  const_reference front() const;
  const_reference back() const;

  // Queue Capacity

  bool empty() const;
  size_type size() const;

  // Queue Modifiers

  void push(const_reference value);
  void pop();
  void swap(queue &other) noexcept;

  template <class... Args>
  void emplace(Args &&...args);

 private:
  Container c;  ///< The container used to store elements in the queue.
};

template <typename value_type, typename Container>
queue<value_type, Container>::queue(const Container &other) : c(other) {}

template <typename value_type, typename Container>
queue<value_type, Container>::queue(Container &&other) : c(std::move(other)) {}

/**
 * @brief Copy constructor.
 *
 * @details
 *
 * Initializes a new queue as a copy of the given queue.
 *
 * @param q The queue to copy from.
 */
template <typename value_type, typename Container>
queue<value_type, Container>::queue(const queue &q) : c(q.c) {}

/**
 * @brief Move constructor.
 *
 * @details
 *
 * Initializes a new queue by moving the contents from the given queue.
 * This leaves the given queue in a valid but unspecified state.
 *
 * @param q The queue to move from.
 */
template <typename value_type, typename Container>
queue<value_type, Container>::queue(queue &&q) : c(std::move(q.c)) {}

/**
 * @brief Destructor.
 */
template <typename value_type, typename Container>
queue<value_type, Container>::~queue() {}

/**
 * @brief Move assignment operator.
 *
 * @details
 *
 * Moves the contents of the given queue into the current queue.
 * After the operation, the given queue is left in a valid but unspecified
 * state.
 * @param q The queue to move from.
 * @return A reference to the modified queue.
 */
template <typename value_type, typename Container>
typename queue<value_type, Container>::queue &
queue<value_type, Container>::operator=(queue &&q) {
  swap(q);

  return *this;
}

/**
 * @brief Returns a constant reference to the first element in the queue.
 *
 * @details
 *
 * Provides access to the first element in the queue without modifying it.
 * If the queue is empty, the behavior is undefined.
 *
 * @note The original queue results in undefined behaviour when trying to call a
 * method for an empty list. Our implementation throws an exception.
 * @throw out_of_range if the queue is empty.
 * @return A constant reference to the first element in the queue.
 */
template <typename value_type, typename Container>
auto queue<value_type, Container>::front() const -> const_reference {
  return c.front();
}

/**
 * @brief Returns a constant reference to the last element in the queue.
 *
 * @details
 *
 * Provides access to the last element in the queue without modifying it.
 * If the queue is empty, the behavior is undefined.
 *
 * @note The original queue results in undefined behaviour when trying to call a
 * method for an empty list. Our implementation throws an exception.
 * @throw out_of_range if the queue is empty.
 * @return A constant reference to the last element in the queue.
 */
template <typename value_type, typename Container>
auto queue<value_type, Container>::back() const -> const_reference {
  return c.back();
}

/**
 * @brief Checks if the queue is empty.
 *
 * @details
 *
 * Returns true if the queue contains no elements, and false otherwise.
 * @return True if the queue is empty, false otherwise.
 */
template <typename value_type, typename Container>
bool queue<value_type, Container>::empty() const {
  return c.empty();
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @details
 *
 * Provides the current size of the queue, indicating how many elements it
 * contains.
 * @return The number of elements in the queue.
 */
template <typename value_type, typename Container>
auto queue<value_type, Container>::size() const -> size_type {
  return c.size();
}

/**
 * @brief Adds an element to the end of the queue.
 *
 * @details
 *
 * Inserts the given element at the end of the queue. This increases the size of
 * the queue by one.
 * @param value The element to add to the queue.
 */
template <typename value_type, typename Container>
void queue<value_type, Container>::push(const_reference value) {
  c.push_back(value);
}

/**
 * @brief Removes the element at the front of the queue.
 *
 * @details
 *
 * Removes the first element from the queue. This decreases the size of the
 * queue by one. If the queue is empty, the behavior is undefined.
 */
template <typename value_type, typename Container>
void queue<value_type, Container>::pop() {
  c.pop_front();
}

/**
 * @brief Swaps the contents of this queue with another queue.
 *
 * @details
 *
 * Exchanges the contents of this queue with the contents of the given queue.
 * Both queues are left in valid but unspecified states. This operation is
 * noexcept, meaning it will not throw exceptions.
 *
 * @param other The queue to swap contents with.
 */
template <typename value_type, typename Container>
void queue<value_type, Container>::swap(queue &other) noexcept {
  c.swap(other.c);
}

/**
 * @brief Constructs and inserts a new element at the end of the queue.
 *
 * @details
 *
 * This function forwards the provided arguments to the constructor of the
 * element type `value_type` and inserts the constructed element at the end
 * of the underlying container `c`. This is typically used to add new elements
 * to the queue while forwarding any number of arguments to the constructor
 * of the element type.
 *
 * @param args The arguments used to construct the new element.
 *
 * @note The `emplace` method does not return any value. It modifies the
 *       underlying container by adding a new element.
 */
template <typename value_type, typename Container>
template <class... Args>
void queue<value_type, Container>::emplace(Args &&...args) {
  c.emplace_back(std::forward<Args>(args)...);
}

}  // namespace s21

#endif  // SRC_CONTAINERS_QUEUE_H_
