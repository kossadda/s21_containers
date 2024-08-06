/**
 * @file stack.h
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Declaration of the stack class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_CONTAINERS_STACK_H_
#define SRC_CONTAINERS_STACK_H_

#include "./list.h"

namespace s21 {

template <typename T, typename Container = list<T>>
class stack {
 public:
  using value_type =
      typename Container::value_type;  ///< Alias for the type of values stored
                                       ///< in the stack.
  using reference =
      typename Container::reference;  ///< Alias for a reference to the type of
                                      ///< values stored in the stack.
  using const_reference =
      typename Container::const_reference;  ///< Alias for a constant reference
                                            ///< to the type of values stored in
                                            ///< the stack.
  using size_type = typename Container::size_type;  ///< Alias for the type used
                                                    ///< for size measurements.
  // Stack Member functions

  stack() : c{Container()} {}
  explicit stack(const Container &s);
  explicit stack(Container &&s);
  stack(const stack &other);
  stack(stack &&other);
  ~stack() {}
  stack &operator=(stack &&s);

  // Stack Element access

  const_reference top() const;

  // Stack Capacity

  bool empty() const;
  size_type size();

  // Stack Modifiers

  void push(const_reference value);
  void push(value_type &&value);
  void pop();
  void swap(stack &other) noexcept;

  template <class... Args>
  void emplace(Args &&...args);

 private:
  Container c;
};

/**
 * @brief Constructor that takes a constant reference to a container.
 *
 * @details
 *
 * Initializes the stack by copying elements from the provided container.
 * This constructor allows creating a stack using a pre-prepared container.
 *
 * @param s The container to be copied into the stack.
 */
template <typename T, typename Container>
stack<T, Container>::stack(const Container &s) : c(s) {}

/**
 * @brief Move constructor that takes an rvalue reference to a container.
 *
 * @details
 *
 * Initializes the stack by moving elements from the provided container.
 * This constructor allows creating a stack by transferring ownership
 * of the elements from the given container to the new stack.
 *
 * @param other The container to be moved into the stack.
 */
template <typename T, typename Container>
stack<T, Container>::stack(Container &&other) : c(std::move(other)) {}

/**
 * @brief Move constructor for the stack.
 *
 * @details
 *
 * Initializes the stack by moving elements from another stack.
 * This constructor allows creating a stack by transferring ownership
 * of the elements from the given stack to the new stack.
 *
 * @param other The stack to be moved into the new stack.
 */
template <typename T, typename Container>
stack<T, Container>::stack(stack &&other) : c(std::move(other.c)) {}

/**
 * @brief Move assignment operator for the stack.
 *
 * @details
 *
 * Moves the contents of the given stack into the current stack.
 * After the operation, the given stack is left in a valid but unspecified
 * state. This operator allows transferring ownership of elements from one stack
 * to another.
 *
 * @param s The stack to move from.
 * @return A reference to the modified stack.
 */
template <typename value_type, typename Container>
auto stack<value_type, Container>::operator=(stack &&s) -> stack & {
  swap(s);

  return *this;
}

/**
 * @brief Copy constructor for the stack.
 *
 * @details
 *
 * Initializes a new stack as a copy of the given stack.
 * This constructor creates a new stack with the same elements as the provided
 * stack.
 *
 * @param other The stack to copy from.
 */
template <typename T, typename Container>
stack<T, Container>::stack(const stack &other) : c(other.c) {}

/**
 * @brief Returns a constant reference to the top element in the stack.
 *
 * @details
 *
 * Provides access to the top element in the stack without modifying it.
 * If the stack is empty, the behavior is undefined.
 *
 * @note The original stack results in undefined behavior when trying to call a
 * method for an empty stack. Our implementation throws an exception.
 * @throw out_of_range if the stack is empty.
 * @return A constant reference to the top element in the stack.
 */
template <typename value_type, typename Container>
auto stack<value_type, Container>::top() const -> const_reference {
  return c.back();
}

/**
 * @brief Checks if the stack is empty.
 *
 * @details
 *
 * Returns true if the stack contains no elements, and false otherwise.
 *
 * @return True if the stack is empty, false otherwise.
 */
template <typename value_type, typename Container>
bool stack<value_type, Container>::empty() const {
  return c.empty();
}

/**
 * @brief Returns the number of elements in the stack.
 *
 * @details
 *
 * Provides the current size of the stack, indicating how many elements it
 * contains.
 *
 * @return The number of elements in the stack.
 */
template <typename value_type, typename Container>
auto stack<value_type, Container>::size() -> size_type {
  return c.size();
}

/**
 * @brief Adds an element to the top of the stack.
 *
 * @details
 *
 * Inserts the given element at the top of the stack. This increases the size of
 * the stack by one.
 *
 * @param value The element to add to the stack.
 */
template <typename value_type, typename Container>
void stack<value_type, Container>::push(const_reference value) {
  c.push_back(value);
}

/**
 * @brief Adds an rvalue reference element to the top of the stack.
 *
 * @details
 *
 * Inserts the given rvalue reference element at the top of the stack. This
 * increases the size of the stack by one. The element is moved into the stack,
 * rather than copied, which can be more efficient for objects that are
 * expensive to copy.
 *
 * @param value The rvalue reference element to add to the stack.
 */
template <typename value_type, typename Container>
void stack<value_type, Container>::push(value_type &&value) {
  c.push_back(std::move(value));
}

/**
 * @brief Removes the element at the top of the stack.
 *
 * @details
 *
 * Removes the top element from the stack, which decreases the size of the stack
 * by one. If the stack is empty, the behavior is undefined.
 *
 * @note The stack is left in a valid but unspecified state if it is empty
 * before calling this method. Our implementation throws an exception in this
 * case.
 * @throw std::out_of_range if the stack is empty.
 */
template <typename value_type, typename Container>
void stack<value_type, Container>::pop() {
  c.pop_back();
}

/**
 * @brief Swaps the contents of this stack with another stack.
 *
 * @details
 *
 * Exchanges the contents of this stack with the contents of the specified
 * stack. Both stacks are left in valid but unspecified states. This operation
 * is noexcept, meaning it will not throw exceptions.
 *
 * @param other The stack to swap contents with.
 */
template <typename value_type, typename Container>
void stack<value_type, Container>::swap(stack &other) noexcept {
  std::swap(c, other.c);
}

/**
 * @brief Constructs and inserts a new element at the top of the stack.
 *
 * @details
 *
 * This function forwards the provided arguments to the constructor of the
 * element type `value_type` and inserts the constructed element at the top
 * of the underlying container `c`, which is typically a container supporting
 * `emplace_front` such as `std::deque`. This allows for efficient construction
 * of the element in-place at the top of the stack.
 *
 * @tparam Args Variadic template parameters representing the types of arguments
 *         used to construct the new element.
 * @param args The arguments used to construct the new element.
 *
 * @note The `emplace` method does not return any value. It modifies the
 *       underlying container by adding a new element at the top.
 */
template <typename value_type, typename Container>
template <class... Args>
void stack<value_type, Container>::emplace(Args &&...args) {
  c.emplace_back(std::forward<Args>(args)...);
}

}  // namespace s21

#endif  // SRC_CONTAINERS_STACK_H_
