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

/**
 * @brief A red-black tree container template class.
 *
 * @details
 * This template class tree provides a red-black tree similar to
 * std::map in the C++ Standard Library. It manages a balanced binary search
 * tree of elements of type key_type and value_type, supporting various
 * operations including iteration, element access, and size management.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 */
template <typename key_type, typename value_type>
class tree {
 private:
  // Container types
  class TreeIterator;
  class Node;
  enum Colors { RED, BLACK };

 public:
  // Type aliases
  using iterator = TreeIterator;  ///< For read/write elements

 private:
  Node *root_{};      ///< Root of tree
  Node *sentinel_{};  ///< Dummy element

 public:
  // Constructors/destructor
  tree() noexcept = default;
  tree(const key_type key, const value_type value);
  ~tree();

  // Tree Iterators
  iterator begin() const noexcept;
  iterator end() const noexcept;

  // Working with tree
  value_type search(const key_type &key) const;
  void insert(const key_type key, const value_type value);
  void remove(const key_type &key) noexcept;
  std::string structure() const noexcept;

 private:
  // Add/remove nodes
  void createNode(const key_type &key, const value_type &value, Node *&node,
                  Node *parent = nullptr);
  void cleanTree(Node *node) noexcept;
  void removeMemory(Node *&node, Node *ptr_copy) noexcept;

  // Tree balancing
  void balancingTree(Node *node) noexcept;
  void fixDoubleBlack(Node *&node) noexcept;
  void rotateLeft(Node *old_root) noexcept;
  void rotateRight(Node *old_root) noexcept;
  void swapColors(Node *node) noexcept;

  // Tree searching
  Node *findNode(Node *node, const key_type &key) const noexcept;
  static Node *findMax(Node *node) noexcept;
  static Node *findMin(Node *node) noexcept;

  // Cases of node removal
  void deleteTwoChild(Node *&node) noexcept;
  void deleteOneChild(Node *&node, Node *&child) noexcept;
  void deleteRedNoChild(Node *&node) noexcept;
  void deleteBlackNoChild(Node *&node) noexcept;

  // Black no child node removal cases
  void redParBlackSonRedLeft(Node *&node) noexcept;
  void redParBlackSonRedRight(Node *&node) noexcept;
  void blackParRedSonBlackRight(Node *&node) noexcept;
  void blackParRedBrosBlackRightRedLeft(Node *&node) noexcept;
  void blackParBlackBrosBlackAll(Node *&node) noexcept;
  void blackParBlackBrosRedRightGran(Node *&node) noexcept;
  void blackParBlackBrosRedLeftOrAllGran(Node *&node) noexcept;

  // Printing
  std::string printNodes(const Node *node, int indent = 0,
                         bool last = true) const noexcept;
};

/**
 * @brief An iterator for the red-black tree.
 *
 * @details
 * This class represents an iterator for the red-black tree. It allows traversal
 * of the tree and access to its elements.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 */
template <typename key_type, typename value_type>
class tree<key_type, value_type>::TreeIterator {
 private:
  Node *ptr_{};   ///< Pointer to the current node
  Node *first{};  ///< Pointer to the lowest node
  Node *last{};   ///< Pointer to a dummy node

 public:
  // Constructors
  TreeIterator() noexcept = default;
  TreeIterator(Node *node, Node *root, Node *sentinel) noexcept;
  TreeIterator(const iterator &other) noexcept;

  // Operators
  iterator &operator=(const iterator &other) noexcept;
  iterator &operator--() noexcept;
  iterator &operator++() noexcept;
  iterator operator+(const int shift) const noexcept;
  iterator operator-(const int shift) const noexcept;
  bool operator==(iterator other) const noexcept;
  bool operator!=(iterator other) const noexcept;
};

/**
 * @brief A node in the red-black tree.
 *
 * @details
 * This class represents a node in the red-black tree. It contains the key,
 * value, color, parent, left child, and right child of the node.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 */
template <typename key_type, typename value_type>
class tree<key_type, value_type>::Node {
 public:
  key_type key;      ///< Node key
  value_type value;  ///< Node value
  Colors color;      ///< Color of node (red/black)
  Node *parent;      ///< Parent of this node
  Node *left{};      ///< Left son of this node
  Node *right{};     ///< Right son of this node

  Node(const key_type &k, const value_type &v, Colors c = RED, Node *p = 0);
};

/**
 * @brief Constructs a new node.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] k The key of the node.
 * @param[in] v The value of the node.
 * @param[in] c The color of the node.
 * @param[in] p The parent of the node.
 */
template <typename key_type, typename value_type>
tree<key_type, value_type>::Node::Node(const key_type &k, const value_type &v,
                                       Colors c, Node *p)
    : key(k), value(v), color{c}, parent{p} {}

////////////////////////////////////////////////////////////////////////////////
//                              TREE CONSTRUCTORS                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs a tree with a single node.
 *
 * @details
 * This constructor initializes the tree with a single node containing the given
 * key and value.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] key The key of the node.
 * @param[in] value The value of the node.
 */
template <typename key_type, typename value_type>
tree<key_type, value_type>::tree(const key_type key, const value_type value) {
  createNode(key, value, root_);
  sentinel_ = new Node{key_type{}, value_type{}, BLACK, nullptr};
}

/**
 * @brief Destructor.
 *
 * @details
 * Destroys the tree and frees allocated memory.
 */
template <typename key_type, typename value_type>
tree<key_type, value_type>::~tree() {
  cleanTree(root_);
  delete sentinel_;
}

////////////////////////////////////////////////////////////////////////////////
//                               TREE ITERATORS                               //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Returns an iterator to the beginning of the tree.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @return iterator - an iterator to the beginning of the tree.
 */
template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator
tree<key_type, value_type>::begin() const noexcept {
  return iterator{findMin(root_), root_, sentinel_};
}

/**
 * @brief Returns an iterator to the end of the tree.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @return iterator - an iterator to the end of the tree.
 */
template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator tree<key_type, value_type>::end()
    const noexcept {
  return iterator{sentinel_, root_, findMax(root_)};
}

////////////////////////////////////////////////////////////////////////////////
//                             WORKING WITH TREE                              //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Searches for a value associated with a given key.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] key The key to search for.
 * @return value_type - the value associated with the key, or a
 * default-constructed value_type if the key is not found.
 */
template <typename key_type, typename value_type>
value_type tree<key_type, value_type>::search(const key_type &key) const {
  Node *value = findNode(root_, key);

  return (value) ? value->value : value_type{};
}

/**
 * @brief Inserts a new node with the given key and value into the tree.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] key The key of the node.
 * @param[in] value The value of the node.
 */
template <typename key_type, typename value_type>
void tree<key_type, value_type>::insert(const key_type key,
                                        const value_type value) {
  createNode(key, value, root_);
}

/**
 * @brief Removes the node with the given key from the tree.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] key The key of the node to remove.
 */
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

/**
 * @brief Returns a string representation of the tree structure.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @return std::string - a string representation of the tree structure.
 */
template <typename key_type, typename value_type>
std::string tree<key_type, value_type>::structure() const noexcept {
  std::string str = printNodes(root_);

  return str;
}

////////////////////////////////////////////////////////////////////////////////
//                              ADD/REMOVE NODES                              //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Creates a new node with the given key and value.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] key The key of the node.
 * @param[in] value The value of the node.
 * @param[in,out] node A reference to the node pointer where the new node will
 * be created.
 * @param[in] parent The parent of the new node.
 */
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

/**
 * @brief Cleans the tree by deleting all nodes.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] node The root node of the tree.
 */
template <typename key_type, typename value_type>
void tree<key_type, value_type>::cleanTree(Node *node) noexcept {
  if (node) {
    cleanTree(node->left);
    cleanTree(node->right);
    delete node;
  }
}

/**
 * @brief Removes the memory of the given node.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] parent The parent of the node to remove.
 * @param[in,out] ptr_copy The node to remove.
 */
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

////////////////////////////////////////////////////////////////////////////////
//                                BALANCING TREE                              //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Balances the tree after inserting a new node.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] node The newly inserted node.
 */
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

/**
 * @brief Fixes a double black violation.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node with the double black violation.
 */
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

/**
 * @brief Performs a left rotation at the given node.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] old_root The node at which to perform the rotation.
 */
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

/**
 * @brief Performs a right rotation at the given node.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] old_root The node at which to perform the rotation.
 */
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

/**
 * @brief Swaps the colors of the given node and its children.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] node The node at which to swap colors.
 */
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

////////////////////////////////////////////////////////////////////////////////
//                                TREE SEARCHING                              //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Finds the node with the given key.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] node The root node of the tree.
 * @param[in] key The key to search for.
 * @return Node* - the node with the given key, or nullptr if the key is not
 * found.
 */
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

/**
 * @brief Finds the node with the maximum key in the tree.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] node The root node of the tree.
 * @return Node* - the node with the maximum key.
 */
template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *tree<key_type, value_type>::findMax(
    Node *node) noexcept {
  while (node->right) {
    node = node->right;
  }

  return node;
}

/**
 * @brief Finds the node with the minimum key in the tree.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] node The root node of the tree.
 * @return Node* - the node with the minimum key.
 */
template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *tree<key_type, value_type>::findMin(
    Node *node) noexcept {
  while (node->left) {
    node = node->left;
  }

  return node;
}

////////////////////////////////////////////////////////////////////////////////
//                           CASES OF NODE REMOVAL                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Deletes a node with two children.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
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

/**
 * @brief Deletes a node with one child.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 * @param[in,out] child The child of the node to delete.
 */
template <typename key_type, typename value_type>
void tree<key_type, value_type>::deleteOneChild(Node *&node,
                                                Node *&child) noexcept {
  Node *ch = child;

  node->key = child->key;
  node->value = child->value;
  child = nullptr;

  delete ch;
}

/**
 * @brief Deletes a red node with no children.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
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

/**
 * @brief Deletes a black node with no children.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
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

////////////////////////////////////////////////////////////////////////////////
//                     BLACK NO CHILD NODE REMOVAL CASES                      //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Handles the case where the node to delete has a red parent and a black
 * brother with a red left child.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
template <typename key_type, typename value_type>
void tree<key_type, value_type>::redParBlackSonRedLeft(Node *&node) noexcept {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  removeMemory(parent, node);
  (is_left) ? rotateLeft(brother->parent) : rotateRight(brother->parent);
  swapColors(brother);
}

/**
 * @brief Handles the case where the node to delete has a red parent and a black
 * brother with a red right child.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
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

/**
 * @brief Handles the case where the node to delete has a black parent and a red
 * brother with a black right child.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
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

/**
 * @brief Handles the case where the node to delete has a black parent and a red
 * brother with a black right child and a red left child.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
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

/**
 * @brief Handles the case where the node to delete has a black parent and a
 * black brother with no children.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
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

/**
 * @brief Handles the case where the node to delete has a black parent and a
 * black brother with a red right grandchild.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
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

/**
 * @brief Handles the case where the node to delete has a black parent and a
 * black brother with a red left child or all grandchildren.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in,out] node The node to delete.
 */
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

////////////////////////////////////////////////////////////////////////////////
//                                  PRINTING                                  //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Prints the nodes of the tree in a structured format.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] node The root node of the tree.
 * @param[in] indent The indentation level for printing.
 * @param[in] last Whether the node is the last child of its parent.
 * @return std::string - a string representation of the tree structure.
 */
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

////////////////////////////////////////////////////////////////////////////////
//                        TREE ITERATOR CONSTRUCTORS                          //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructs a tree iterator.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] node The node to which the iterator points.
 * @param[in] root The root node of the tree.
 * @param[in] sentinel The sentinel node of the tree.
 */
template <typename key_type, typename value_type>
tree<key_type, value_type>::iterator::TreeIterator(Node *node, Node *root,
                                                   Node *sentinel) noexcept
    : ptr_{node}, first{root}, last{sentinel} {}

/**
 * @brief Copy constructor for the tree iterator.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] other The iterator to copy from.
 */
template <typename key_type, typename value_type>
tree<key_type, value_type>::iterator::TreeIterator(
    const iterator &other) noexcept
    : ptr_{other.ptr_}, first{other.first}, last{other.last} {}

////////////////////////////////////////////////////////////////////////////////
//                           TREE ITERATOR OPERATORS                          //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Assignment operator for the tree iterator.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] other The iterator to assign from.
 * @return iterator& - reference to the assigned iterator.
 */
template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator &
tree<key_type, value_type>::iterator::operator=(
    const iterator &other) noexcept {
  ptr_ = other.ptr_;
  first = other.first;
  last = other.last;

  return *this;
}

/**
 * @brief Pre-decrement operator for the tree iterator.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @return iterator& - reference to the decremented iterator.
 */
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

/**
 * @brief Pre-increment operator for the tree iterator.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @return iterator& - reference to the incremented iterator.
 */
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

/**
 * @brief Addition operator for the tree iterator.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] shift The number of positions to shift.
 * @return iterator - the shifted iterator.
 */
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

/**
 * @brief Addition operator for the tree iterator.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] shift The number of positions to shift.
 * @return iterator - the shifted iterator.
 */
template <typename key_type, typename value_type>
typename tree<key_type, value_type>::iterator
tree<key_type, value_type>::iterator::operator-(
    const int shift) const noexcept {
  iterator copy{*this};

  for (int i = 0; i < shift; i++) {
    --copy;
  }

  return copy;
}

/**
 * @brief Equality comparison operator for the tree iterator.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] other The iterator to compare with.
 * @return true if the iterators are equal, false otherwise.
 */
template <typename key_type, typename value_type>
bool tree<key_type, value_type>::iterator::operator==(
    iterator other) const noexcept {
  return (ptr_ == other.ptr_) ? true : false;
}

/**
 * @brief Inequality comparison operator for the tree iterator.
 *
 * @tparam key_type The type of keys stored in the tree.
 * @tparam value_type The type of values stored in the tree.
 * @param[in] other The iterator to compare with.
 * @return true if the iterators are not equal, false otherwise.
 */
template <typename key_type, typename value_type>
bool tree<key_type, value_type>::iterator::operator!=(
    iterator other) const noexcept {
  return (ptr_ != other.ptr_) ? true : false;
}

}  // namespace s21

#endif  // SRC_MODULES_TREE_H_
