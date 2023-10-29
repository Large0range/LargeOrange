// File Name: Ch3_Wk5_P2_ARoy.cpp
// Written By: Alex Roy
// Description: A program to perform the choice operation of the user and check if their answer was correct 
// Challenges:
// Time Spent: 5 minutes
// Revision History
// Date:          Revised By:           Action
// -------------------------------------------------------
// 03/10/2023      AR                    Created the program
// 05/10/2023      AR                    Added checks to avoid choosing out of range and 0 as divisor
// 17/10/2023      AR                    Revised operation choice system, replaced with array of function pointers

#include <iostream>

float addition(float a1, float a2) { //define addition function 
	return a1+a2;
}

float subtraction(float a1, float a2) { //define subtraction function
	return a1-a2;
}

float multiplication(float a1, float a2) { //define multiplication function
	return a1*a2;
}

float division(float a1, float a2) { //define division function
	return a1/a2;
}


int main() {
	std::string OperationChoiceString; // declare a string to hold the input for the operation choice
	std::string FirstNumberString; // declare a string to hold the input for the first number
	std::string SecondNumberString; // declare a string to hold the input for the second number
	std::string AnswerString; // declare a string to hold the answer for the input from the user 

	float (*functions[])(float, float) = {addition, subtraction, multiplication, division}; //array of function pointers to be indexed by operation choice


	float FirstNumber; // declare a float for the first number 
	float SecondNumber; // declare a float for the second number
	float Answer; // declare a float for the answer
	float RealAnswer; // declare a float for the calculated answer
	int OperationChoice; // declare a integer to hold the operation choice


	while (true) { // SAME FOR THE NEXT 4 BLOCKS
		try {
			std::cout << "Enter the number of the operation" << std::endl; // prompt user 
			std::cout << "1) Addition" << std::endl;
			std::cout << "2) Subtraction" << std::endl;
			std::cout << "3) Multiplication" << std::endl;
			std::cout << "4) Division" << std::endl;
			std::cout << ">";
			std::cin >> OperationChoiceString; // store string into string

			OperationChoice = std::stoi(OperationChoiceString); // attempt conversion
			if (OperationChoice > 4) throw std::invalid_argument("Bruh"); // throw an error(error message is negligable as it is not shown) if the number is out of range

			break;
		} catch (...) { // catch all errors
			std::cout << "Invalid input you may have inputed a character or a number out of range" << std::endl; // tell the something went wrong
		}
	}


	while (true) {
		try {
			std::cout << "First number: ";
			std::cin >> FirstNumberString;

			FirstNumber = std::stof(FirstNumberString);

			break;
		} catch (...) {
			std::cout << "Invalid input you may have inputed a character instead of a number" << std::endl;
		}
	}

	while (true) {
		try {
			std::cout << "Second number: ";
			std::cin >> SecondNumberString;

			SecondNumber = std::stof(SecondNumberString);
			
			if (OperationChoice == 4 && SecondNumber == 0) throw std::invalid_argument("Bruh"); // throw an error if the operation is division and the divisor is 0
			break;
		} catch (...) {
			std::cout << "Invalid input you may have inputed a character or put 0 as a divisor" << std::endl;
		}
	}

	while (true) {
		try {
			std::cout << "What is the answer? ";
			std::cin >> AnswerString;

			Answer = std::stof(AnswerString);

			break;
		} catch (...) {
			std::cout << "Invalid input you may have inputed a character instead of a number" << std::endl;
		}
	}

	
	RealAnswer = functions[OperationChoice-1](FirstNumber, SecondNumber); // Set real answer to indexed array pointer of function --> Operation Choice indexes array of function pointers, that pointer is then used to perform the operation
	

	if (RealAnswer == Answer) std::cout << "Congradulations, You got it correct!" << std::endl; // say congradulations if the user was correct
	else std::cout << "I'm sorry, the correct answer is " << RealAnswer << std::endl; // tell the user the correct answer if they were wrong

	return 0; // return exit code 0
}
