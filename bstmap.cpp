// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

// Helper function to copy tree
BSTMap::Node *BSTMap::copyTree(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  Node *newNode = new Node{node->data, nullptr, nullptr};
  newNode->left = copyTree(node->left);
  newNode->right = copyTree(node->right);
  return newNode;
}

// Copy constructor
BSTMap::BSTMap(const BSTMap &bst) {
  clear();
  root = copyTree(bst.root);
}

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  vector<value_type> sortedV = v;
  sort(sortedV.begin(), sortedV.end());
  root = buildBalancedTree(sortedV, 0, static_cast<int>(sortedV.size() - 1));
}

// Destructor
BSTMap::~BSTMap() { clear(); }

// Clear helper function
void BSTMap::clearHelper(Node *node) {
  if (node == nullptr) {
    return;
  }
  clearHelper(node->left);
  clearHelper(node->right);
  delete node;
}

// Clear the BST
void BSTMap::clear() {
  clearHelper(root);
  root = nullptr;
}

// Helper function to build a balanced tree
BSTMap::Node *BSTMap::buildBalancedTree(vector<value_type> &nodes, int start,
                                        int end) {
  if (start > end) {
    return nullptr;
  }
  int mid = start + (end - start) / 2;
  Node *node = new Node{nodes[mid], nullptr, nullptr};
  node->left = buildBalancedTree(nodes, start, mid - 1);
  node->right = buildBalancedTree(nodes, mid + 1, end);
  return node;
}

// Check if BST is empty
bool BSTMap::empty() const { return root == nullptr; }

// Count nodes helper function
int BSTMap::sizeHelper(Node *node) const {
  if (node == nullptr) {
    return 0;
  }
  return 1 + sizeHelper(node->left) + sizeHelper(node->right);
}

// Get number of nodes in BST
int BSTMap::size() const { return sizeHelper(root); }

// Check if key exists
bool BSTMap::contains(const key_type &key) const {
  Node *curr = root;
  while (curr != nullptr) {
    if (key < curr->data.first) {
      curr = curr->left;
    } else if (key > curr->data.first) {
      curr = curr->right;
    } else {
      return true;
    }
  }
  return false;
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  Node **curr = &root;       // Pointer-to-pointer to traverse the tree
  while (*curr != nullptr) { // Traverse the BST
    if (k < (*curr)->data.first) {
      curr = &((*curr)->left);
    } else if (k > (*curr)->data.first) {
      curr = &((*curr)->right);
    } else {
      return (*curr)->data.second; // Key found, return reference
    }
  }
  // Key not found, insert new node with default value 0
  *curr = new Node{{k, 0}, nullptr, nullptr};
  return (*curr)->data.second;
}

// Helper function to find all key-value pairs with a prexif
void BSTMap::getAllHelper(Node *node, const key_type &prefix,
                          vector<value_type> &result) const {
  // Base case: If the current node is null, return (end of branch)
  if (node == nullptr) {
    return;
  }
  // Check if the current node's key starts with the prefix
  if (node->data.first.compare(0, prefix.size(), prefix) == 0) {
    result.push_back(node->data);
    getAllHelper(node->left, prefix, result);
    getAllHelper(node->right, prefix, result);
  }
  // Case 2: If the prefix is lexicographically smaller than the current key,
  // we only need to search the left subtree
  else if (prefix < node->data.first) {
    getAllHelper(node->left, prefix, result);
  }
  // Case 3: If the prefix is greater than the current key,
  // we search the right subtree for potential matches
  else {
    getAllHelper(node->right, prefix, result);
  }
}

// returns a vector of key-value pairs that partially match the key
// Main function used by autocomplete
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  getAllHelper(root, k, v);
  return v;
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0; // Base case: null nodes have height 0
  }
  return 1 + max(getHeight(n->left), getHeight(n->right));
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const key_type &k) const { return contains(k) ? 1 : 0; }

// Helper: Inorder traversal
void BSTMap::inorderHelper(Node *node,
                           void visit(const value_type &item)) const {
  if (node == nullptr) {
    return;
  }
  inorderHelper(node->left, visit);
  visit(node->data);
  inorderHelper(node->right, visit);
}

// Helper: Preorder traversal
void BSTMap::preorderHelper(Node *node,
                            void visit(const value_type &item)) const {
  if (node == nullptr) {
    return;
  }
  visit(node->data);
  preorderHelper(node->left, visit);
  preorderHelper(node->right, visit);
}

// Helper: Postorder traversal
void BSTMap::postorderHelper(Node *node,
                             void visit(const value_type &item)) const {
  if (node == nullptr) {
    return;
  }
  postorderHelper(node->left, visit);
  postorderHelper(node->right, visit);
  visit(node->data);
}

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inorderHelper(root, visit);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {
  preorderHelper(root, visit);
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  postorderHelper(root, visit);
}

// Store nodes inorder in a vector
void BSTMap::storeInorder(Node *node, vector<value_type> &nodes) {
  if (node == nullptr) {
    return;
  }
  storeInorder(node->left, nodes);
  nodes.push_back(node->data);
  storeInorder(node->right, nodes);
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  vector<value_type> nodes;
  storeInorder(root, nodes);
  clear();
  root = buildBalancedTree(nodes, 0, static_cast<int>(nodes.size() - 1));
}

// Helper to compare two trees
bool BSTMap::isEqual(const Node *node1, const Node *node2) const {
  if (node1 == nullptr && node2 == nullptr) {
    return true;
  }
  if (node1 == nullptr || node2 == nullptr) {
    return false;
  }
  return node1->data == node2->data && isEqual(node1->left, node2->left) &&
         isEqual(node1->right, node2->right);
}
// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  return isEqual(root, other.root);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const { return !(*this == other); }

// Recursive helper for erase
bool BSTMap::eraseHelper(Node *&node, const key_type &k) {
  if (node == nullptr) {
    return false;
  }

  if (k < node->data.first) {
    return eraseHelper(node->left, k);
  }
  if (k > node->data.first) {
    return eraseHelper(node->right, k);
  }
  // Found the node to delete
  if (node->left == nullptr) {
    Node *temp = node->right;
    delete node;
    node = temp;
  } else if (node->right == nullptr) {
    Node *temp = node->left;
    delete node;
    node = temp;
  } else {
    // Two children: find in-order successor
    Node *successor = node->right;
    while (successor->left != nullptr) {
      successor = successor->left;
    }
    node->data = successor->data;
    eraseHelper(node->right, successor->data.first);
  }
  return true;
}

// Bonus: Erase method to erase an item from BST
bool BSTMap::erase(const key_type &k) { return eraseHelper(root, k); }
