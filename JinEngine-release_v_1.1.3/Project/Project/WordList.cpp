
#include "WordList.h"
#include <fstream>

WordList::WordList()
{

}

WordList CreateWordList(const std::string& wordlistpath)
{
	WordList wordlist;

	std::ifstream inputFile(wordlistpath);
	std::string temp;

	
	std::string temp1 = u8"안녕";

	std::string temp2 = u8"잘가";

	if (!inputFile.is_open()) {
		// Error
		return wordlist;
	}

	while (std::getline(inputFile,temp ))
	{
		wordlist.words.push_back(temp);
	}


	inputFile.close();


	return wordlist;
}

std::string WordList::GetRandomWord() const
{
	if (words.empty()) return "EMPTY!!!";

	int randomIndex = std::rand() % words.size();

	return words[randomIndex];
}
