/**
 * @file tree.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Binary red-black tree implementation
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
  enum Colors { RED, BLACK };
  struct Node;

 public:
  tree() = default;
  tree(const key_type key, const value_type value);
  ~tree();

  value_type search(const key_type &key);
  void add(const key_type key, const value_type value);
  void remove(const key_type &key);
  std::string print();

 private:
  Node *root_{};

  void createNode(const key_type &key, const value_type &value, Node *&node,
                  Node *parent = nullptr);
  void balancingTree(Node *node);
  void rotateLeft(Node *old_root);
  void rotateRight(Node *old_root);
  void cleanTree(Node *node);
  Node *findNode(Node *node, const key_type &key);
  void deleteOneChild(Node *&node, Node *&child);
  void deleteRedNoChild(Node *&node);
  void deleteBlackNoChild(Node *&node);
  void redParBlackSonRedLeft(Node *&node);
  void redParBlackSonRedRight(Node *&node);
  void blackParRedSonBlackRight(Node *&node);
  void blackParRedBrosBlackRightRedLeft(Node *&node);
  void blackParBlackBrosBlackAll(Node *&node);
  void blackParBlackBrosRedRightGran(Node *&node);
  void blackParBlackBrosRedLeftOrAllGran(Node *&node);
  void fixDoubleBlack(Node *&node);
  void removeMemory(Node *&node, Node *ptr_copy);
  void swapColors(Node *node);
  std::string printNodes(const Node *node, int indent = 0,
                         bool last = true) const;
};

template <typename key_type, typename value_type>
std::string tree<key_type, value_type>::printNodes(const Node *node, int indent,
                                                   bool last) const {
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
    char *char_str = (char *)malloc(50);
    std::sprintf(char_str, "%d", node->key);
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
std::string tree<key_type, value_type>::print() {
  std::string str = printNodes(root_);

  return str;
}

template <typename key_type, typename value_type>
class tree<key_type, value_type>::Node {
 public:
  key_type key;
  value_type value;
  Colors color{tree::RED};
  Node *parent;
  Node *left{};
  Node *right{};

  Node(const key_type &k, const value_type &v, Colors c = tree::RED,
       Node *p = nullptr)
      : key(k), value(v), color{c}, parent{p} {};
};

template <typename key_type, typename value_type>
tree<key_type, value_type>::tree(const key_type key, const value_type value) {
  createNode(key, value, root_);
}

template <typename key_type, typename value_type>
tree<key_type, value_type>::~tree() {
  cleanTree(root_);
}

template <typename key_type, typename value_type>
value_type tree<key_type, value_type>::search(const key_type &key) {
  Node *value = findNode(root_, key);

  return (value) ? value->value : value_type{};
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::add(const key_type key,
                                     const value_type value) {
  createNode(key, value, root_);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::remove(const key_type &key) {
  Node *node = findNode(root_, key);

  if (!node) {
    return;
  }

  Node *left = node->left;
  Node *right = node->right;

  if (!node) {
    return;
  }

  if (node->color == RED) {
    if (!left && !right) {
      deleteRedNoChild(node);
    }
  } else {
    if (!left && !right) {
      deleteBlackNoChild(node);
    } else if (!left && right) {
      deleteOneChild(node, node->right);
    } else if (left && !right) {
      deleteOneChild(node, node->left);
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
void tree<key_type, value_type>::balancingTree(Node *node) {
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
void tree<key_type, value_type>::rotateLeft(Node *old_root) {
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
void tree<key_type, value_type>::rotateRight(Node *old_root) {
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
void tree<key_type, value_type>::swapColors(Node *node) {
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
void tree<key_type, value_type>::cleanTree(Node *node) {
  if (node) {
    cleanTree(node->left);
    cleanTree(node->right);
    delete node;
  }
}

template <typename key_type, typename value_type>
typename tree<key_type, value_type>::Node *tree<key_type, value_type>::findNode(
    Node *node, const key_type &key) {
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
void tree<key_type, value_type>::removeMemory(Node *&parent, Node *ptr_copy) {
  if (parent->left == ptr_copy) {
    parent->left = nullptr;
  } else {
    parent->right = nullptr;
  }

  delete ptr_copy;
  ptr_copy = nullptr;
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::deleteOneChild(Node *&node, Node *&child) {
  Node *ch = child;

  node->key = child->key;
  node->value = child->value;
  child = nullptr;

  delete ch;
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::deleteRedNoChild(Node *&node) {
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
void tree<key_type, value_type>::deleteBlackNoChild(Node *&node) {
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
void tree<key_type, value_type>::redParBlackSonRedLeft(Node *&node) {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  removeMemory(parent, node);
  (is_left) ? rotateLeft(brother->parent) : rotateRight(brother->parent);
  swapColors(brother);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::redParBlackSonRedRight(Node *&node) {
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
void tree<key_type, value_type>::blackParRedSonBlackRight(Node *&node) {
  Node *parent = node->parent;
  bool is_left = (parent->left == node) ? true : false;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  Node *grandson = (is_left) ? brother->left : brother->right;

  std::swap(brother->color, grandson->color);
  removeMemory(parent, node);
  (is_left) ? rotateLeft(parent) : rotateRight(parent);
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::blackParRedBrosBlackRightRedLeft(Node *&node) {
  Node *parent = node->parent;
  bool is_left = (parent->left == node) ? true : false;
  Node *brother = (parent->left == node) ? parent->right : parent->left;

  removeMemory(parent, node);
  if (is_left) {
    rotateLeft(brother->parent);
    rotateLeft(parent);
  } else {
    rotateRight(brother->parent);
    rotateRight(parent);
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::blackParBlackBrosBlackAll(Node *&node) {
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
void tree<key_type, value_type>::fixDoubleBlack(Node *&node) {
  if (node == root_) {
    node->color = BLACK;
    return;
  }

  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;

  if (brother->color == RED) {
    parent->color = RED;
    brother->color = BLACK;

    (parent->left == node) ? rotateLeft(parent) : rotateRight(parent);
    fixDoubleBlack(node);
  } else {
    if ((brother->left && brother->left->color == RED) ||
        (brother->right && brother->right->color == RED)) {
      if (brother->left && brother->left->color == RED) {
        if (parent->left == node) {
          brother->color = std::exchange(parent->color, BLACK);
          brother->left->color = BLACK;
          rotateRight(parent);
        } else {
          brother->left->color = std::exchange(parent->color, BLACK);
          rotateRight(brother);
          rotateLeft(parent);
        }
      } else {
        if (parent->left == node) {
          brother->right->color = std::exchange(parent->color, BLACK);
          rotateLeft(brother);
          rotateRight(parent);
        } else {
          brother->color = std::exchange(parent->color, BLACK);
          brother->right->color = BLACK;
          rotateLeft(parent);
        }
      }
    } else {
      brother->color = RED;
      if (parent->color == BLACK) {
        fixDoubleBlack(parent);
      } else {
        parent->color = BLACK;
      }
    }
  }
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::blackParBlackBrosRedLeftOrAllGran(
    Node *&node) {
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
void tree<key_type, value_type>::blackParBlackBrosRedRightGran(Node *&node) {
  Node *parent = node->parent;
  Node *brother = (parent->left == node) ? parent->right : parent->left;
  bool is_left = (parent->left == node) ? true : false;

  removeMemory(parent, node);
  (is_left) ? rotateRight(brother) : rotateLeft(brother);
  std::swap(brother->color, brother->parent->color);
  (is_left) ? rotateLeft(parent) : rotateRight(parent);
  brother->color = BLACK;
}

}  // namespace s21

#endif  // SRC_MODULES_TREE_H_
