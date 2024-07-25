/**
 * @file tree.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header for the red-black tree container
 * @version 1.0
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_TREE_H_
#define SRC_MODULES_TREE_H_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>
#include <utility>

namespace s21 {

template <typename key_type, typename value_type>
class tree {
 private:
  enum Colors { RED, BLACK };
  class Node;
  class TreeIterator;

  Node *root_{};
  Node *sentinel_{};

 public:
  using iterator = TreeIterator;

  tree() noexcept = default;
  tree(const key_type key, const value_type value);
  ~tree();

  iterator begin() const noexcept;
  iterator end() const noexcept;

  value_type search(const key_type &key) const;
  void insert(const key_type key, const value_type value);
  void remove(const key_type &key) noexcept;
  std::string structure() const noexcept;

 private:
  void createNode(const key_type &key, const value_type &value, Node *&node,
                  Node *parent = nullptr);
  void balancingTree(Node *node) noexcept;
  void rotateLeft(Node *old_root) noexcept;
  void rotateRight(Node *old_root) noexcept;
  void cleanTree(Node *node) noexcept;
  Node *findNode(Node *node, const key_type &key) const noexcept;
  static Node *findMin(Node *node) noexcept;
  static Node *findMax(Node *node) noexcept;
  void deleteTwoChild(Node *&node) noexcept;
  void deleteOneChild(Node *&node, Node *&child) noexcept;
  void deleteRedNoChild(Node *&node) noexcept;
  void deleteBlackNoChild(Node *&node) noexcept;
  void redParBlackSonRedLeft(Node *&node) noexcept;
  void redParBlackSonRedRight(Node *&node) noexcept;
  void blackParRedSonBlackRight(Node *&node) noexcept;
  void blackParRedBrosBlackRightRedLeft(Node *&node) noexcept;
  void blackParBlackBrosBlackAll(Node *&node) noexcept;
  void blackParBlackBrosRedRightGran(Node *&node) noexcept;
  void blackParBlackBrosRedLeftOrAllGran(Node *&node) noexcept;
  void fixDoubleBlack(Node *&node) noexcept;
  void removeMemory(Node *&node, Node *ptr_copy) noexcept;
  void swapColors(Node *node) noexcept;
  std::string printNodes(const Node *node, int indent = 0,
                         bool last = true) const noexcept;
};

template <typename key_type, typename value_type>
class tree<key_type, value_type>::Node {
 public:
  key_type key;
  value_type value;
  Colors color;
  Node *parent;
  Node *left{};
  Node *right{};

  Node(const key_type &k, const value_type &v, Colors c = RED, Node *p = 0)
      : key(k), value(v), color{c}, parent{p} {};
};

template <typename key_type, typename value_type>
class tree<key_type, value_type>::TreeIterator {
 private:
  Node *ptr_{};
  Node *first{};
  Node *last{};

 public:
  TreeIterator() noexcept = default;
  TreeIterator(Node *node, Node *root, Node *sentinel) noexcept;
  TreeIterator(const iterator &other) noexcept;

  iterator &operator=(const iterator &other) noexcept;
  iterator &operator--() noexcept;
  iterator &operator++() noexcept;
  iterator operator+(const int shift) const noexcept;
  iterator operator-(const int shift) const noexcept;
  bool operator==(iterator other) const noexcept;
  bool operator!=(iterator other) const noexcept;
};

template <typename key_type, typename value_type>
tree<key_type, value_type>::tree(const key_type key, const value_type value) {
  createNode(key, value, root_);
  sentinel_ = new Node{key_type{}, value_type{}, BLACK, nullptr};
}

template <typename key_type, typename value_type>
tree<key_type, value_type>::~tree() {
  cleanTree(root_);
  delete sentinel_;
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator
tree<key_type, value_type>::begin() const noexcept {
  return iterator{findMin(root_), root_, sentinel_};
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator tree<key_type, value_type>::end()
    const noexcept {
  return iterator{sentinel_, root_, findMax(root_)};
}

template <typename key_type, typename value_type>
std::string tree<key_type, value_type>::structure() const noexcept {
  std::string str = printNodes(root_);

  return str;
}

template <typename key_type, typename value_type>
value_type tree<key_type, value_type>::search(const key_type &key) const {
  Node *value = findNode(root_, key);

  return (value) ? value->value : value_type{};
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::insert(const key_type key,
                                        const value_type value) {
  createNode(key, value, root_);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::remove(const key_type &key) noexcept {
  Node *node = findNode(root_, key);

  if (!node) {
    return;
  }

  Node *left = node->left;
  Node *right = node->right;

  if (node->color == RED) {
    if (!left && !right) {
      deleteRedNoChild(node);
    } else if (left && right) {
      deleteTwoChild(node);
    }
  } else {
    if (!left && !right) {
      deleteBlackNoChild(node);
    } else if (!left && right) {
      deleteOneChild(node, node->right);
    } else if (left && !right) {
      deleteOneChild(node, node->left);
    } else {
      deleteTwoChild(node);
    }
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::createNode(const key_type &key,
                                            const value_type &value,
                                            Node *&node, Node *parent) {
  if (!node) {
    node = new Node{key, value, RED, parent};

    if (node->parent && node->parent->color == RED) {
      balancingTree(node);
    }
  } else {
    if (key < node->key) {
      createNode(key, value, node->left, node);
    } else {
      createNode(key, value, node->right, node);
    }
  }

  if (root_) {
    root_->color = BLACK;
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::balancingTree(Node *node) noexcept {
  while (node->parent && node->parent->color == RED) {
    Node *parent = node->parent;
    Node *grandparent = parent->parent;
    Node *uncle =
        (parent == grandparent->left) ? grandparent->right : grandparent->left;

    if (uncle && uncle->color == RED) {
      parent->color = BLACK;
      uncle->color = BLACK;
      grandparent->color = RED;
      node = grandparent;
    } else {
      if (node == parent->right && parent == grandparent->left) {
        rotateLeft(parent);
        node = parent;
        parent = node->parent;
      } else if (node == parent->left && parent == grandparent->right) {
        rotateRight(parent);
        node = parent;
        parent = node->parent;
      }

      parent->color = BLACK;
      grandparent->color = RED;

      if (parent == grandparent->left) {
        rotateRight(grandparent);
      } else {
        rotateLeft(grandparent);
      }
    }
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::rotateLeft(Node *old_root) noexcept {
  Node *new_root = old_root->right;

  if (new_root->left) {
    new_root->left->parent = old_root;
  }

  old_root->right = new_root->left;
  new_root->left = old_root;

  if (!old_root->parent) {
    root_ = new_root;
  } else if (old_root == old_root->parent->left) {
    old_root->parent->left = new_root;
  } else {
    old_root->parent->right = new_root;
  }

  new_root->parent = std::exchange(old_root->parent, new_root);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::rotateRight(Node *old_root) noexcept {
  Node *new_root = old_root->left;

  if (new_root->right) {
    new_root->right->parent = old_root;
  }

  old_root->left = new_root->right;
  new_root->right = old_root;

  if (!old_root->parent) {
    root_ = new_root;
  } else if (old_root == old_root->parent->left) {
    old_root->parent->left = new_root;
  } else {
    old_root->parent->right = new_root;
  }

  new_root->parent = std::exchange(old_root->parent, new_root);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::swapColors(Node *node) noexcept {
  if (node == nullptr || node->left == nullptr || node->right == nullptr) {
    return;
  }

  if (node->left->color == RED && node->right->color == RED) {
    node->left->color = node->right->color = BLACK;
    node->color = RED;

    if (node->parent && node->parent != root_) {
      swapColors(node->parent);
    }
  }

  if (root_) {
    root_->color = BLACK;
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::cleanTree(Node *node) noexcept {
  if (node) {
    cleanTree(node->left);
    cleanTree(node->right);
    delete node;
  }
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *tree<key_type, value_type>::findNode(
    Node *node, const key_type &key) const noexcept {
  if (!node) {
    return nullptr;
  }

  if (node->key > key) {
    return findNode(node->left, key);
  } else if (node->key < key) {
    return findNode(node->right, key);
  } else {
    return node;
  }
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *tree<key_type, value_type>::findMax(
    Node *node) noexcept {
  while (node->right) {
    node = node->right;
  }

  return node;
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *tree<key_type, value_type>::findMin(
    Node *node) noexcept {
  while (node->left) {
    node = node->left;
  }

  return node;
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::removeMemory(Node *&parent,
                                              Node *ptr_copy) noexcept {
  if (parent->left == ptr_copy) {
    parent->left = nullptr;
  } else {
    parent->right = nullptr;
  }

  delete ptr_copy;
  ptr_copy = nullptr;
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::deleteOneChild(Node *&node,
                                                Node *&child) noexcept {
  Node *ch = child;

  node->key = child->key;
  node->value = child->value;
  child = nullptr;

  delete ch;
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::deleteRedNoChild(Node *&node) noexcept {
  Node *parent{node->parent};

  if (parent) {
    if (parent->left == node) {
      parent->left = nullptr;
    } else {
      parent->right = nullptr;
    }
  }

  delete node;
  node = nullptr;
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::deleteTwoChild(Node *&node) noexcept {
  Node *swap = findMax(node->left);
  if (!(swap && !(swap->left && swap->right))) {
    swap = findMin(node->right);
  }

  std::swap(swap->key, node->key);
  std::swap(swap->value, node->value);

  if (!swap->left && !swap->right) {
    if (swap->color == RED) {
      deleteRedNoChild(swap);
    } else {
      deleteBlackNoChild(swap);
    }
  } else if (!swap->left && swap->right) {
    deleteOneChild(swap, swap->right);
  } else if (swap->left && !swap->right) {
    deleteOneChild(swap, swap->left);
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::deleteBlackNoChild(Node *&node) noexcept {
  if (!node->parent) {
    return;
  }

  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  if (brother && parent->color == RED && brother->color == BLACK) {
    if (!brother->left && !brother->right) {
      std::swap(brother->color, parent->color);
      removeMemory(parent, node);
    } else if ((is_left && brother->right && brother->right->color == RED) ||
               (!is_left && brother->left && brother->left->color == RED)) {
      redParBlackSonRedLeft(node);
    } else if ((is_left && brother->left && brother->left->color == RED) ||
               (!is_left && brother->right && brother->right->color == RED)) {
      redParBlackSonRedRight(node);
    }
  } else if (brother && parent->color == BLACK && brother->color == BLACK) {
    if (!brother->left && !brother->right) {
      blackParBlackBrosBlackAll(node);
    } else if ((is_left && !brother->right && brother->left) ||
               (!is_left && !brother->left && brother->right)) {
      blackParBlackBrosRedRightGran(node);
    } else {
      blackParBlackBrosRedLeftOrAllGran(node);
    }
  } else if (brother && node->parent->color == BLACK && brother->color == RED) {
    if ((is_left && brother->left && brother->left->color == BLACK) ||
        (!is_left && brother->right && brother->right->color == BLACK)) {
      Node *grgrson = (is_left) ? brother->left->right : brother->right->left;
      if (grgrson && grgrson->color == RED) {
        blackParRedBrosBlackRightRedLeft(node);
      } else {
        blackParRedSonBlackRight(node);
      }
    }
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::redParBlackSonRedLeft(Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  removeMemory(parent, node);
  (is_left) ? rotateLeft(brother->parent) : rotateRight(brother->parent);
  swapColors(brother);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::redParBlackSonRedRight(Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  removeMemory(parent, node);
  (is_left) ? rotateRight(brother) : rotateLeft(brother);
  std::swap(brother->color, brother->parent->color);
  (is_left) ? rotateLeft(parent) : rotateRight(parent);
  swapColors(parent->parent);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::blackParRedSonBlackRight(
    Node *&node) noexcept {
  Node *parent = node->parent;
  bool is_left = (parent->left == node) ? true : false;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  Node *grandson = (is_left) ? brother->left : brother->right;

  std::swap(brother->color, grandson->color);
  removeMemory(parent, node);
  (is_left) ? rotateLeft(parent) : rotateRight(parent);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::blackParRedBrosBlackRightRedLeft(
    Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;

  removeMemory(parent, node);
  rotateLeft(brother->parent);
  std::swap(brother->color, parent->color);
  rotateLeft(parent);
  swapColors(parent->parent);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::blackParBlackBrosBlackAll(
    Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;

  brother->color = RED;
  removeMemory(parent, node);

  if (parent->color == BLACK) {
    fixDoubleBlack(parent);
  } else {
    parent->color = BLACK;
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::fixDoubleBlack(Node *&node) noexcept {
  if (node == root_) {
    return;
  }

  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;

  if (brother->color == RED) {
    parent->color = RED;
    brother->color = BLACK;

    (brother == parent->left) ? rotateRight(parent) : rotateLeft(parent);
    fixDoubleBlack(node);
  } else {
    if ((brother->left && brother->left->color == BLACK) &&
        (brother->right && brother->right->color == BLACK)) {
      brother->color = RED;
      if (parent->color == BLACK) {
        fixDoubleBlack(parent);
      } else {
        parent->color = BLACK;
      }
    } else {
      if (brother == parent->left) {
        if (brother->left && brother->left->color == RED) {
          brother->left->color = std::exchange(brother->color, parent->color);
          rotateRight(parent);
        } else {
          if (brother->right && brother->right->color == RED) {
            brother->right->color = parent->color;
            rotateLeft(brother);
            rotateRight(parent);
          }
        }
      } else {
        if (brother->right && brother->right->color == RED) {
          brother->right->color = std::exchange(brother->color, parent->color);
          rotateLeft(parent);
        } else {
          if (brother->left && brother->left->color == RED) {
            brother->left->color = parent->color;
            rotateRight(brother);
            rotateLeft(parent);
          }
        }
      }
      parent->color = BLACK;
    }
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::blackParBlackBrosRedLeftOrAllGran(
    Node *&node) noexcept {
  Node *parent = node->parent;
  bool is_left = (parent->left == node) ? true : false;

  removeMemory(parent, node);
  if (is_left) {
    rotateLeft(parent);
    if (parent->parent && parent->parent->right) {
      parent->parent->right->color = BLACK;
    } else if (root_ == parent) {
      root_->right->color = BLACK;
    }
  } else {
    rotateRight(parent);
    if (parent->parent && parent->parent->left) {
      parent->parent->left->color = BLACK;
    } else if (root_ == parent) {
      root_->left->color = BLACK;
    }
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::blackParBlackBrosRedRightGran(
    Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  removeMemory(parent, node);
  (is_left) ? rotateRight(brother) : rotateLeft(brother);
  std::swap(brother->color, brother->parent->color);
  (is_left) ? rotateLeft(parent) : rotateRight(parent);
  brother->color = BLACK;
}

template <typename key_type, typename value_type>
std::string tree<key_type, value_type>::printNodes(const Node *node, int indent,
                                                   bool last) const noexcept {
  std::string str{};

  if (node) {
    str = std::string(indent, ' ');
    if (last) {
      str += "R---";
      str += (node->color == RED ? "{R:" : "{B:");
    } else {
      str += "L---";
      str += (node->color == RED ? "{R:" : "{B:");
    }
    char *char_str = static_cast<char *>(malloc(50));
    std::snprintf(char_str, 50, "%d", node->key);
    str += std::string(char_str);
    str += "}\n";
    if (char_str) {
      free(char_str);
    }

    str += printNodes(node->left, indent + 4, false);
    str += printNodes(node->right, indent + 4, true);
  }

  return str;
}

template <typename key_type, typename value_type>
tree<key_type, value_type>::iterator::TreeIterator(Node *node, Node *root,
                                                   Node *sentinel) noexcept
    : ptr_{node}, first{root}, last{sentinel} {}

template <typename key_type, typename value_type>
tree<key_type, value_type>::iterator::TreeIterator(
    const iterator &other) noexcept
    : ptr_{other.ptr_}, first{other.first}, last{other.last} {}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator &
tree<key_type, value_type>::iterator::operator=(
    const iterator &other) noexcept {
  ptr_ = other.ptr_;
  first = other.first;
  last = other.last;

  return *this;
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator &
tree<key_type, value_type>::iterator::operator--() noexcept {
  if (!ptr_) {
    if (last == findMax(first)) {
      std::swap(ptr_, last);
    }

    return *this;
  }

  if (ptr_->left) {
    ptr_ = findMax(ptr_->left);
  } else {
    if (ptr_ != findMin(first)) {
      Node *parent = ptr_->parent;

      while (parent && ptr_ == parent->left) {
        ptr_ = parent;
        parent = parent->parent;
      }

      ptr_ = parent;
    }
  }

  return *this;
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator &
tree<key_type, value_type>::iterator::operator++() noexcept {
  if (!ptr_) {
    if (ptr_ == findMax(first)) {
      std::swap(ptr_, last);
    }

    return *this;
  }

  if (ptr_->right) {
    ptr_ = findMin(ptr_->right);
  } else {
    Node *parent = ptr_->parent;

    while (parent && ptr_ == parent->right) {
      ptr_ = parent;
      parent = parent->parent;
    }

    ptr_ = parent;
  }

  return *this;
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator
tree<key_type, value_type>::iterator::operator+(
    const int shift) const noexcept {
  iterator copy{*this};

  for (int i = 0; i < shift; i++) {
    ++copy;
  }

  return copy;
}

template <typename key_type, typename value_type>
bool tree<key_type, value_type>::iterator::operator==(
    iterator other) const noexcept {
  return (ptr_ == other.ptr_) ? true : false;
}

template <typename key_type, typename value_type>
bool tree<key_type, value_type>::iterator::operator!=(
    iterator other) const noexcept {
  return (ptr_ != other.ptr_) ? true : false;
}

}  // namespace s21

#endif  // SRC_MODULES_TREE_H_
