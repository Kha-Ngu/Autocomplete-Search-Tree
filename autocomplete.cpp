#include "autocomplete.h"
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

void testBSTAll();

// Reads data from a file and populates the BST with phrases and their
// corresponding weights
void Autocomplete::readFile(const string &fileName) {
  ifstream ifs(fileName);
  if (!ifs) {
    cerr << "Error: Cannot open file " << fileName << endl;
    return;
  }

  string line;
  int count = 0;

  // Skip the header line if it's just a number
  getline(ifs, line);
  if (all_of(line.begin(), line.end(), ::isdigit)) {
    // Header detected (e.g., "10000"), skip it
  } else {
    ifs.seekg(0); // Reset to the beginning if not a header
  }

  while (getline(ifs, line)) {
    istringstream iss(line);
    uint64_t weight;
    string phrase;

    if (!(iss >> weight)) {
      continue; // Skip malformed lines
    }

    getline(iss >> ws, phrase);
    if (!phrase.empty()) {
      phrases[phrase] = weight;
      count++;
    }
  }
  ifs.close();
  phrases.rebalance();
}

// Comparator function to sort key-value pairs in descending order of weight
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// Retrieves a list of phrases from the BST that start with the given prefix
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  vector<BSTMap::value_type> v = phrases.getAll(prefix);
  sort(v.begin(), v.end(), sortByWeight);
  return v;
}
