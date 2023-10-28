#include <iostream>
#include <fstream>

bool undesirable(std::string s1, std::string badboys) {
	int l = badboys.length();
	for (int i = 0; i < l; i++) {
		if (s1.find(badboys.c_str()[i]) != std::string::npos) return true;
	}

	return false;
}

bool repeatLetters(std::string s1) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == j) continue;
			if (s1.c_str()[i] == s1.c_str()[j]) return true;
		}
	}

	return false;
}

int main() {
	std::string string; //string to hold line

	std::ifstream allwordsFile ("allwords.txt"); //open allwords.txt 
	std::ofstream wordlistFile ("wordlist.txt"); //open wordlist.txt

	while (allwordsFile.good()) { //while allwords.txt has a line
		std::getline(allwordsFile, string); // pull line from allwords.txt
		if (string.length() != 5) continue; // if the line has more than 5 letters skip it
		if (undesirable(string, "-.\'")) continue;
		if (repeatLetters(string)) continue;
		

		wordlistFile << string << '\n'; // output the word to wordlist.txt as it's own line
	}

	allwordsFile.close(); // close both streams
	wordlistFile.close();

	return 0; // exit with code 0
}
