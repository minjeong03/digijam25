
#include "WordList.h"
#include <fstream>

WordList::WordList()
{

}

WordList CreateWordList(const std::vector<std::string>& wordlistpath)
{
	WordList wordlist;

	for (int i = 0; i < wordlistpath.size(); ++i)
	{
		std::ifstream inputFile(wordlistpath[i]);

		if (!inputFile.is_open()) {
			// Error
			return wordlist;
		}

		std::string temp;
		while (std::getline(inputFile, temp))
		{
			wordlist.words.push_back(temp);
		}


		inputFile.close();
	}


	return wordlist;
}

std::string WordList::GetRandomWord() const
{
	if (words.empty()) return "EMPTY!!!";

	int randomIndex = std::rand() % words.size();

	return words[randomIndex];
}
