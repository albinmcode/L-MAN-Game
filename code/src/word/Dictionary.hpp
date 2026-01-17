#pragma once

#include <string>
#include <vector>

struct dictIndex {
  std::string word;
  std::string translation;
};

class Dictionary {
 private:
  /// Vector containing dictionary list of {word, translation}  
  std::vector<dictIndex> wordsList;

 private:
  /// @brief Private constructor for singleton pattern
  Dictionary() =  default;

 public:
  /// @brief Singleton instance
  static Dictionary& getInstance() {
    static Dictionary instance;
    return instance;
  }
  ~Dictionary() = default;

  /// @brief Load from specified file path
  bool loadFromCSV(std::string path);
  /// Obtain the number of words in the dictionary 
  inline size_t size() const {
    return this->wordsList.size();
  }
  /// Obtain the specified word at index
  /// @throw std::out_of_range
  dictIndex& at(size_t index);
};
