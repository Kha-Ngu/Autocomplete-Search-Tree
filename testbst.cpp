// /**
//  * Testing BST - Binary Search Tree functions
//  *
//  * This file has series of tests for BST
//  * Each test is independent and uses assert statements
//  * Test functions are of the form
//  *
//  *      test_netidXX()
//  *
//  * where netid is UW netid and XX is the test number starting from 01
//  *
//  * Test functions can only use the public functions from BST
//  * testBSTAll() is called from main in main.cpp
//  * testBSTAll calls all other functions
//  * @author Multiple
//  * @date ongoing
//  */

#include "bstmap.h"
#include <cassert>
#include <sstream>

using namespace std;

// global value for testing
// NOLINTNEXTLINE
stringstream globalSS;

// need to reset SS before calling this
void printer(const BSTMap::value_type &p) {
  globalSS << "[" << p.first << "=" << p.second << "]";
}

// // Testing == and []
void test01() {
  cout << "Starting test01" << endl;
  cout << "* Testing ==, !=, [] and copy constructor" << endl;
  BSTMap b1;
  auto val = b1["hello"];
  assert(val == 0);
  b1["hello"] = 5;
  val = b1["hello"];
  assert(val == 5);
  b1["world"] = 42;

  BSTMap b2;
  assert(b1 != b2);
  b2["hello"] = 5;
  b2["world"] = 42;
  assert(b1 == b2);

  BSTMap b3(b2);
  assert(b1 == b3);
  cout << "Ending tes01" << endl;
}

// Testing traversal
void test02() {
  cout << "Starting test02" << endl;
  cout << "* Testing traversal" << endl;
  BSTMap b;
  b["x"] = 10;
  b["f"] = 5;
  b["b"] = 3;
  b["e"] = 4;
  b["z"] = 50;
  // cout << b;

  globalSS.str("");
  b.inorder(printer);
  string order = globalSS.str();
  assert(order == "[b=3][e=4][f=5][x=10][z=50]");

  globalSS.str("");
  b.preorder(printer);
  order = globalSS.str();
  assert(order == "[x=10][f=5][b=3][e=4][z=50]");

  globalSS.str("");
  b.postorder(printer);
  order = globalSS.str();
  assert(order == "[e=4][b=3][f=5][z=50][x=10]");
  cout << "Ending test02" << endl;
}

// Testing rebalance
void test03() {
  cout << "Starting test03" << endl;
  cout << "* Testing rebalance" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  assert(b.height() == 6);
  // cout << b << endl;
  b.rebalance();
  assert(b.height() == 3);
  // cout << b << endl;
  b.clear();
  assert(b.height() == 0);
  cout << "Ending test03" << endl;
}

// Test 4: Deletion (erase)
void test_khangu04() {
  cout << "Starting test_khangu04" << endl;
  cout << "* Testing erase functionality" << endl;
  BSTMap b;
  b["a"] = 1;
  b["b"] = 2;
  b["c"] = 3;

  assert(b.size() == 3);
  assert(b.erase("b") == true); // Successful deletion
  assert(b.size() == 2);
  assert(!b.contains("b"));

  assert(b.erase("nonexistent") == false); // Deleting non-existent key
  assert(b.size() == 2);
  cout << "Ending test04" << endl;
}

// Test 5: Edge cases (empty BST)
void test_khangu05() {
  cout << "Starting test_khangu05" << endl;
  cout << "* Testing empty BST edge case" << endl;
  BSTMap b;
  assert(b.empty());
  assert(b.empty());
  assert(!b.contains("anykey"));

  b["key"] = 100;
  assert(!b.empty());
  assert(b.size() == 1);
  assert(b.contains("key"));
  cout << "Ending test05" << endl;
}

// Test 06: Insertion and Prefix Search
void test_khangu06() {
  cout << "Starting test_khangu06" << endl;
  cout << "* Testing Insertion and Prefix Search" << endl;
  BSTMap bst;
  bst["Seat Pleasant, Maryland, United States"] = 4542;
  bst["Seaton, South Australia, Australia"] = 9704;
  bst["Seaton, United Kingdom"] = 5240;
  bst["Seaton Delaval, United Kingdom"] = 7219;
  bst["Seattle, Washington, United States"] = 608660;

  vector<BSTMap::value_type> matches = bst.getAll("Seat");
  for (size_t i = 0; i < matches.size(); i++) {
    for (size_t j = i + 1; j < matches.size(); j++) {
      if (matches[j].second > matches[i].second) {
        swap(matches[i], matches[j]);
      }
    }
  }

  // Expected output
  vector<pair<string, uint64_t>> expected = {
      {"Seattle, Washington, United States", 608660},
      {"Seaton, South Australia, Australia", 9704},
      {"Seaton Delaval, United Kingdom", 7219},
      {"Seaton, United Kingdom", 5240},
      {"Seat Pleasant, Maryland, United States", 4542}};

  // Compare matches to expected output
  assert(matches.size() == expected.size());

  for (size_t i = 0; i < matches.size(); ++i) {
    assert(matches[i].first == expected[i].first);
    assert(matches[i].second == expected[i].second);
  }
  cout << "Ending test_khangu06\n";
}

// Test 7: Adding terms with weights into BST
void test_khangu07() {
  cout << "Starting test_khangu07" << endl;
  cout << "* Testing Adding Terms with Weights" << endl;
  BSTMap bst;
  bst["UW Seattle"] = 10;
  bst["UW Bothell"] = 21;
  bst["Washington State"] = 1;
  bst["Seattle University"] = 0;
  bst["CWU"] = 100;

  assert(bst.size() == 5);
  assert(bst.contains("Seattle University"));
  assert(bst["Washington State"] == 1);
  cout << "Ending test_khangu07\n";
}

// Test 8: Rebalancing the BST
void test_khangu08() {
  cout << "Starting test_khangu08" << endl;
  cout << "* Testing Rebalancing" << endl;
  BSTMap bst;
  bst["1"] = 1;
  bst["2"] = 2;
  bst["3"] = 3;
  bst["4"] = 4;
  bst["5"] = 5;
  bst["6"] = 6;

  assert(bst.height() == 6);
  bst.rebalance();
  assert(bst.height() <= 3);

  cout << "Ending test_khangu08\n";
}

// Test 9: Equality Operators
void test_khangu09() {
  cout << "Starting test_khangu09" << endl;
  cout << "* Testing Equality Operators" << endl;
  BSTMap bst1;
  BSTMap bst2;
  bst1["key1"] = 100;
  bst1["key2"] = 200;
  bst2["key1"] = 100;
  bst2["key2"] = 200;

  assert(bst1 == bst2);
  bst2["key3"] = 300;
  assert(bst1 != bst2);

  cout << "Ending test_khangu09\n";
}

// Test 10: Constructors and Destructor
void test_khangu10() {
  cout << "Starting test_khangu10" << endl;
  cout << "* Testing Constructors and Destructor" << endl;
  BSTMap bst1;
  bst1["A"] = 1;
  bst1["B"] = 2;

  BSTMap bst2(bst1); // Copy constructor
  assert(bst1 == bst2);

  vector<BSTMap::value_type> v = {{"X", 100}, {"Y", 200}};
  BSTMap bst3(v); // Constructor from vector
  assert(bst3.size() == 2);
  assert(bst3.contains("X") && bst3["X"] == 100);

  cout << "Ending test_khangu10\n";
}

// Test 11: Traversal Methods
// Global vectors to collect traversal results
vector<string> inorderResult;
vector<string> preorderResult;
vector<string> postorderResult;

// Static function to collect inorder traversal results
void collectInorder(const BSTMap::value_type &item) {
  inorderResult.push_back(item.first);
}
// Static function to collect preorder traversal results
void collectPreorder(const BSTMap::value_type &item) {
  preorderResult.push_back(item.first);
}
// Static function to collect postorder traversal results
void collectPostorder(const BSTMap::value_type &item) {
  postorderResult.push_back(item.first);
}
// Test 11: Testing Traversal Correctness
void test_khangu11() {
  cout << "Starting test_khangu11" << endl;
  cout << "* Testing Traversals" << endl;
  BSTMap bst;
  bst["B"] = 2;
  bst["A"] = 1;
  bst["C"] = 3;

  // Perform traversals
  bst.inorder(collectInorder);
  bst.preorder(collectPreorder);
  bst.postorder(collectPostorder);

  // Validate the traversal orders
  assert((inorderResult == vector<string>{"A", "B", "C"}));
  assert((preorderResult == vector<string>{"B", "A", "C"}));
  assert((postorderResult == vector<string>{"A", "C", "B"}));

  cout << "Ending test_khangu11\n";
}

// Test: count() Method
void test_khangu12() {
  cout << "Starting test_khangu12" << endl;
  cout << "* Testing Count" << endl;
  BSTMap bst;
  bst["A"] = 10;
  bst["B"] = 20;
  bst["C"] = 30;

  assert(bst.count("A") == 1);
  assert(bst.count("B") == 1);
  assert(bst.count("Z") == 0);

  cout << "Ending test_khangu12\n";
}

// Test: operator[] Method
void test_khangu13() {
  cout << "Starting test_khangu13" << endl;
  cout << "* Testing [] Operator" << endl;
  BSTMap bst;

  // Inserting values
  bst["Key1"] = 100;
  bst["Key2"] = 200;

  // Checking values
  assert(bst["Key1"] == 100);
  assert(bst["Key2"] == 200);

  // Modifying values
  bst["Key1"] = 150;
  assert(bst["Key1"] == 150);

  // Accessing a non-existing key should insert it with default value 0
  assert(bst["NewKey"] == 0);
  bst["NewKey"] = 300;
  assert(bst["NewKey"] == 300);

  cout << "Ending test_khangu13\n";
}

// Calling all test functions
void testBSTAll() {
  test01();
  test02();
  test03();
  test_khangu04();
  test_khangu05();
  test_khangu06();
  test_khangu07();
  test_khangu08();
  test_khangu09();
  test_khangu10();
  test_khangu11();
  test_khangu12();
  test_khangu13();
  cout << "-----------------------------------------------------"
       << endl; // Separate ac and bst tests for readability
}