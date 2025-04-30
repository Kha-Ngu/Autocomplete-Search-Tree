#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "bstmap.h"

using namespace std;

class Autocomplete {
public:
  // Constructor
  Autocomplete() = default;
  // Reads data from a file and populates the BST with phrases and their
  // corresponding weights
  void readFile(const string &fileName);
  // Retrieves a list of phrases from the BST that start with the given prefix
  vector<BSTMap::value_type> complete(const string &prefix) const;

private:
  // BST of phrases and their frequency
  BSTMap phrases;

  // sorter
  bool static sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b);
};

#endif // AUTOCOMPLETE_H
