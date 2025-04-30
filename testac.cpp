#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Global Autocomplete instances to reuse data and speed up tests
Autocomplete acSmall;
Autocomplete acCities;
Autocomplete acWiktionary;

// Load data only once
void loadData() {
  static bool smallLoaded = false;
  static bool citiesLoaded = false;
  static bool wiktionaryLoaded = false;

  if (!smallLoaded) {
    acSmall.readFile("small.txt");
    smallLoaded = true;
  }
  if (!citiesLoaded) {
    acCities.readFile("cities.txt");
    citiesLoaded = true;
  }
  if (!wiktionaryLoaded) {
    acWiktionary.readFile("wiktionary.txt");
    wiktionaryLoaded = true;
  }
}

// Test 1: Basic Autocomplete
void testAC01() {
  cout << "Starting AC test01" << endl;
  cout << "* Testing basic autocomplete" << endl;
  loadData();
  auto v = acSmall.complete("hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending tesAC01" << endl;
}

// Test 2: Cities Autocomplete
void testAC02() {
  cout << "Starting AC test02" << endl;
  cout << "* Testing cities autocomplete" << endl;
  loadData();
  auto v = acCities.complete("Sea");
  assert(v.size() == 47);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  cout << "Ending tesAC02" << endl;
}

// Test 3: Non-existent Prefix
void testAC03() {
  cout << "Starting AC test03" << endl;
  cout << "* Testing non-existent prefix" << endl;
  loadData();
  auto v = acSmall.complete("xyz"); // No match expected
  assert(v.empty());
  cout << "Ending testAC03" << endl;
}

// Test 4: Empty Prefix (return all phrases)
void testAC04() {
  cout << "Starting AC test04" << endl;
  cout << "* Testing empty prefix (return all phrases)" << endl;
  loadData();
  auto v = acSmall.complete(""); // Should return all entries
  assert(v.size() == 10);
  assert(v[0].second == 30); // Highest frequency should be first
  cout << "Ending testAC04" << endl;
}

// Test 5: Exact Match
void testAC05() {
  cout << "Starting AC test05" << endl;
  cout << "* Testing exact match" << endl;
  loadData();
  auto v = acSmall.complete("help"); // Should return exactly "help"
  assert(v.size() == 1);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  cout << "Ending testAC05" << endl;
}

// Test 6: Edge Case - No Matching Prefix
void testAC06() {
  cout << "Starting AC test06" << endl;
  cout << "* Testing No Matching Prefix" << endl;
  loadData();
  auto v = acCities.complete("XYZ"); // No match
  assert(v.empty());
  cout << "Ending testAC06" << endl;
}

// Test 7: Edge Case - Empty Prefix (return all phrases)
void testAC07() {
  cout << "Starting AC test07" << endl;
  cout << "* Testing Empty Prefix" << endl;
  loadData();
  auto v = acWiktionary.complete("");
  assert(v.size() == 10000);
  assert(v[0].first == "the"); // Highest frequency first
  cout << "Ending testAC07" << endl;
}

// Test 8: Partial Matches for Multiple Prefixes
void testAC08() {
  cout << "Starting AC test08" << endl;
  cout << "* Testing Partial Matches" << endl;
  loadData();
  auto v = acCities.complete("New");
  assert(!v.empty());
  assert(v[0].first == "New York, New York, United States");
  assert(v[0].second == 8175133);
  cout << "Ending testAC08" << endl;
}

// Test 9: Exact Match with Wiktionary
void testAC09() {
  cout << "Starting AC test09" << endl;
  cout << "* Testing Exact Match" << endl;
  loadData();
  auto v = acWiktionary.complete("in");
  assert(v.size() == 272);
  cout << "Ending testAC09" << endl;
}

// Test 10: Partial Match with Specific Prefix
void testAC10() {
  cout << "Starting AC test10" << endl;
  cout << "* Testing Partial Match" << endl;
  loadData();
  auto v = acCities.complete("Seat");
  assert(v.size() == 5);
  cout << "Ending testAC10" << endl;
}

// Calling All Test Functions
void testACAll() {
  testAC01();
  testAC02();
  testAC03();
  testAC04();
  testAC05();
  testAC06();
  testAC07();
  testAC08();
  testAC09();
  testAC10();
}
