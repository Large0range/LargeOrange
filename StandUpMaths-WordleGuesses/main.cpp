// File Name: main.cpp
// Written By: Alex Roy
// Description: A program to return as many 5 letters words with unique characters that there are 
// Revision History
// Date:          Revised By:           Action
// -------------------------------------------------------
// 17/10/2023      AR                   Created the program with some rudamentary proto code that will slow down with more expansive word lists <--- trimming with buildlist.cpp is required and cuts time 

#include <iostream>
#include <fstream>

bool sharesLetter(std::string s1, std::string s2) { // function to check if there is a shared letter between two strings
	for (int i = 0; i < 5; i++) { // since we know every word is only 5 letters just loop 5 times 
		for (int j = 0; j < 5; j++) { //inbedded loop to go over each letter of the other string
			if (s1.c_str()[i] == '\0') break; // break if we are comparing '\0' in either --> null terminating characters follow every string in C++
			if (s2.c_str()[j] == '\0') continue; // ^
			if (s1.c_str()[i] == s2.c_str()[j]) // if the two letters are the same then automatically return true
				return true;
		}
	}

	return false; //if code reaches here then logically there are no letters that are the same
}

int main() {
	std::string string; // string variable to store the getline of the wordlist file

	std::string list[1380]; // create a string array that stores each added word
	int addedWords = 1; // initialize addedWords counter at 1 to allow for adding the first word of the file

	std::ifstream wordfile ("wordlist.txt"); // open the wordlist file for reading
	std::getline(wordfile, string); // get the first word of the wordlist file
	list[0] = string; // set the first element of the array to the first word
		
	while (wordfile.good()) { // make sure that there is still a line available
		std::getline(wordfile, string); // get the word on the wordlist line
		for (int i = 0; i < addedWords; i++) { // loop over every already added word !!!!!REALLY INEFFICIENT!!!!!!
			if (sharesLetter(list[i], string)) break; // if any letter is shared then break
			else if (i == addedWords-1) { // if there is no letters shared and it is the last element in the array 
				list[addedWords] = string; // add the string to the last element of the wordlist
				addedWords++; // increment the added words counter
			}
		}
	}

	for (int i = 0; i < addedWords; i++) { // loop over every element in the array !!!!!!ALSO REALLY INEFFICIENT!!!!!!
		std::cout << list[i] << std::endl; // print every element onto the screen
	}

	wordfile.close(); // close the wordlist file
}
