#include "string_preprocessor.h"

namespace preprocessing {

namespace {
  std::string to_lower(std::string s) {
    for (char& c : s) {
      c = std::tolower(c);
    }
    return s;
  }
}

StringPreprocessor::StringPreprocessor() {
}

void StringPreprocessor::set_forbidden_chars(const std::string& chars) {
  chars_ = to_lower(chars);
}

void StringPreprocessor::set_forbidden_words(const std::vector<std::string>& words) {
  words_ = words;
  for (std::string& word : words_) {
    word = to_lower(word);
  }
}

std::string StringPreprocessor::preprocess(std::string original) const {
  original = to_lower(original);
  std::string result;
  for (size_t i = 0; i < original.size(); ++i) {
    bool match_any_word = false;
    for (const std::string& word : words_) {
      if (original.substr(i, word.size()) == word) {
        i += word.size() - 1;
        match_any_word = true;
        break;
      }
    }
    if (match_any_word) {
      continue;
    }
    if (chars_.find(original[i]) != std::string::npos)
      continue;
    result += original[i];
  }
  return result;
}

}
