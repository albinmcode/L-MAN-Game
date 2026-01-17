#include "Dictionary.hpp"

#include <fstream>
#include <iostream>
#include <string>

bool Dictionary::loadFromCSV(std::string path) {
  // ensure list is empty
  this->wordsList.clear();
  // open file
  std::ifstream dictFile(path);
  if (!dictFile) {
    std::cerr << "Cannot open dictionary file";
    return false;
  }

  // read each line
  std::string line;
  size_t delimiter_pos = 0;
  while (std::getline(dictFile, line)) {
    dictIndex newIndex;
    delimiter_pos = line.find(',');
    // skip empty lines
    if (delimiter_pos = std::string::npos) continue;
    // separate index
    newIndex.word = line.substr(0, delimiter_pos);
    newIndex.translation = line.substr(delimiter_pos + 1);
    // save into list
    this->wordsList.push_back(newIndex);
  }
  return true;
}

dictIndex& Dictionary::at(size_t index) {
  if (index >= this->wordsList.size()) {
    throw std::out_of_range("dictionary index out of range");
  }
  return wordsList.at(index);
}
