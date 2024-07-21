/**
 * @file tree.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Binary tree implementation
 * @version 1.0
 * @date 2024-07-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_TREE_H_
#define SRC_MODULES_TREE_H_

#include <algorithm>
#include <iostream>

namespace s21 {

template <typename key_type, typename value_type>
class tree {
  struct Node;

 public:
  tree() = default;
  tree(const key_type &key, const value_type &value);
  tree(tree &&t);
  tree(const tree &other);
  ~tree();
  tree &operator=(tree &&t);
  tree &operator=(const tree &t);

  void add(const key_type &key, const value_type &value);
  void print();

  void test() {
    Node *kek = findNode("пять", root_);
    std::cout << kek->key_ << std::endl;
    // removeNode(root_->left_);
  }

 private:
  Node *root_{};

  Node *createNode(const key_type &key, const value_type &value);
  void removeNode(Node *&node);
  void push(Node *&node, const key_type &key, const value_type &value);
  void cleanTree(Node *node);
  void printNodes(const Node *node);
  Node *copyTree(const Node *node);
  Node *findNode(const key_type key, Node *current);
  Node *findNode(const value_type key, Node *current);
};

template <typename key_type, typename value_type>
class tree<key_type, value_type>::Node {
 public:
  key_type key_;
  value_type value_;
  Node *left_;
  Node *right_;

  Node(const key_type &key, const value_type &value, Node *left = nullptr,
       Node *right = nullptr)
      : key_(key), value_(value), left_(left), right_(right) {}
};

template <typename key_type, typename value_type>
tree<key_type, value_type>::tree(const key_type &key, const value_type &value)
    : root_{createNode(key, value)} {}

template <typename key_type, typename value_type>
tree<key_type, value_type>::tree(const tree &other)
    : root_{copyTree(other.root_)} {}

template <typename key_type, typename value_type>
tree<key_type, value_type>::tree(tree &&t)
    : root_{std::exchange(t.root_, nullptr)} {}

template <typename key_type, typename value_type>
tree<key_type, value_type> &tree<key_type, value_type>::operator=(tree &&t) {
  if (this != &t) {
    cleanTree(root_);
    root_ = std::exchange(t.root_, nullptr);
  }

  return *this;
}

template <typename key_type, typename value_type>
tree<key_type, value_type> &tree<key_type, value_type>::operator=(const tree &t) {
  if (this != &t) {
    cleanTree(root_);
    root_ = copyTree(t.root_);
  }

  return *this;
}

template <typename key_type, typename value_type>
tree<key_type, value_type>::~tree() {
  cleanTree(root_);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::cleanTree(Node *node) {
  if (node) {
    cleanTree(node->left_);
    cleanTree(node->right_);
    delete node;
  }
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *tree<key_type, value_type>::copyTree(
    const Node *node) {
  if (!node) {
    return nullptr;
  }

  Node *new_node = createNode(node->key_, node->value_);
  new_node->left_ = copyTree(node->left_);
  new_node->right_ = copyTree(node->right_);

  return new_node;
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *
tree<key_type, value_type>::createNode(const key_type &key,
                                       const value_type &value) {
  return new Node{key, value};
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::removeNode(Node *&node) {
  if(!node) {
    return;
  }

  // if (node->right_) {
  //   node->key_ = node->right_->key_;
  //   node->value_ = node->right_->value_;
  //   removeNode
  // }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::add(const key_type &key,
                                      const value_type &value) {
  push(root_, key, value);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::push(Node *&node, const key_type &key,
                                      const value_type &value) {
  if (!node) {
    node = createNode(key, value);
  } else {
    if (key < node->key_) {
      push(node->left_, key, value);
    } else {
      push(node->right_, key, value);
    }
  }
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *tree<key_type, value_type>::findNode(const key_type key, Node *current) {
  if(!current) {
    return nullptr;
  }

  if(key < current->key_) {
    return findNode(key, current->left_);
  } else if(key > current->key_) {
    return findNode(key, current->right_);
  } else {
    return current;
  }
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *tree<key_type, value_type>::findNode(const value_type value, Node *current) {
  if (!current) {
    return nullptr;
  }

  if (current->value_ == value) {
    return current;
  }

  Node* found = findNode(value, current->left_);
  if (found) {
    return found;
  }

  return findNode(value, current->right_);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::print() {
  printNodes(root_);
  std::cout << std::endl;
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::printNodes(const Node *node) {
  if (node) {
    if (node->left_) printNodes(node->left_);
    std::cout << "{" << node->key_ << ":" << node->value_ << "} ";
    if (node->right_) printNodes(node->right_);
  }
}

}  // namespace s21

#endif  // SRC_MODULES_TREE_H_
