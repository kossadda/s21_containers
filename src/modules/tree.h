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
  ~tree();

  value_type searh(const key_type &key);

 private:
  Node *root_{};

  void createNode(const key_type &key, const value_type &value, Node *&node,
                  Node *parent = nullptr);
  void balancingTree(Node *node);
  void rotateLeft(Node *&old_root);
  void rotateRight(Node *&old_root);
  void cleanTree(Node *node);
  Node *findNode(Node *node, const key_type &key);
  void deleteNode(const key_type &key);
  void deleteOneChild(Node *&node, Node *&child);
  void deleteRedNoChild(Node *&node);
  void deleteBlackNoChild(Node *&node);

  void printNodes(const Node *node) {
    if (node) {
      if (node->left) printNodes(node->left);
      std::cout << "{" << node->key << ":" << node->value << "} ";
      if (node->right) printNodes(node->right);
    }
  }

 public:
  void print() {
    printNodes(root_);
    std::cout << std::endl;
  }

  void test() {
    createNode(156, 4, root_);
    createNode(10, 4, root_);
    createNode(15, 4, root_);
    createNode(20, 4, root_);
    createNode(25, 42344, root_);
    createNode(30, 4, root_);
    createNode(2, 4, root_);
    createNode(2112, 4, root_);
    createNode(112, 1114, root_);
    createNode(35, 4, root_);
    createNode(40, 4, root_);
    createNode(33, 4, root_);
    // createNode(8, 4, root_);

    // deleteNode(33);
    // deleteNode(40);
    // deleteNode(2);
    deleteNode(33);
    deleteNode(30);
  }
};

template <typename key_type, typename value_type>
tree<key_type, value_type>::~tree() {
  cleanTree(root_);
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
void tree<key_type, value_type>::rotateLeft(Node *&old_root) {
  Node *new_root = old_root->right;
  old_root->right = new_root->left;

  if (new_root->left) {
    new_root->left->parent = old_root;
  }

  new_root->parent = old_root->parent;

  if (!old_root->parent) {
    root_ = new_root;
  } else if (old_root == old_root->parent->left) {
    old_root->parent->left = new_root;
  } else {
    old_root->parent->right = new_root;
  }

  new_root->left = old_root;
  old_root->parent = new_root;
}

template <typename key_type, typename value_type>
void tree<key_type, value_type>::rotateRight(Node *&old_root) {
  Node *new_root = old_root->left;
  old_root->left = new_root->right;

  if (new_root->right) {
    new_root->right->parent = old_root;
  }

  new_root->parent = old_root->parent;

  if (!old_root->parent) {
    root_ = new_root;
  } else if (old_root == old_root->parent->left) {
    old_root->parent->left = new_root;
  } else {
    old_root->parent->right = new_root;
  }

  new_root->right = old_root;
  old_root->parent = new_root;
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
value_type tree<key_type, value_type>::searh(const key_type &key) {
  Node *value = findNode(root_, key);

  return (value) ? value->value : value_type{};
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
void tree<key_type, value_type>::deleteNode(const key_type &key) {
  Node *node = findNode(root_, key);

  if(!node) {
    return;
  }

  if (node->color == RED) {
    if(!node->left && !node->right) {
      deleteRedNoChild(node);
    }
  } else {
    if(!node->left && !node->right) {
      // deleteBlackNoChild(node);
    } else if(!node->left && node->right) {
      deleteOneChild(node, node->right);
    }  else if(node->left && !node->right) {
      deleteOneChild(node, node->left);
    }
  }
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

  if(parent) {
    if(parent->left == node) {
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
  Node *parent{node->parent};

  if(parent) {
    if(parent->left == node) {
      parent->left = nullptr;
    } else {
      parent->right = nullptr;
    }
  }

  delete node;
  node = nullptr;
}

}  // namespace s21

#endif  // SRC_MODULES_TREE_H_
