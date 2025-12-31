#pragma once
#include <string>
#include <vector>

class WordList
{
public:
    WordList();
    std::string GetRandomWord() const;

private:
    std::vector<std::string> words;
    friend WordList CreateWordList(const std::vector<std::string>& wordlistpath);
};



WordList CreateWordList(const std::vector<std::string>& wordlistpath);

