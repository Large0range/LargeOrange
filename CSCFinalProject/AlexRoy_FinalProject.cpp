// File Name: AlexRoy_FinalProject.cpp
// Written by: Alex Roy
// Description: A program for customers of a coffee shop to order online
// Challenges: 
// Time Spent: 2 days
// Given Input:              Expected Output: 
// --------------------      -------------------------
// 1) 
// 2) 
// 3) 
// Revision History
// Date:        Revised By:     Action:
// ------------------------------------------------------------------
// 10/12/2023    (AR)         (created the program)




#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>


//MENU OUTPUT
//Hot Toppings: 
//1) Cream
//2) Milk
//3) Almond Milk
//4) Vanilla
//5) Sugar
//Please Enter the Number Of The Topping You Would like: 


//Program Flow:
//Choose hot or cold
//Choose toppings
//Ask if all done
//Choose more toppings if not
//Display total and ask pickup type if yes

double totalCost = 0;


const double TOPPINGS_PRICE_LIST[] = {
    0.12, // cream
    0.15, // milk
    0.17, // almond milk
    0.20, // vanilla
    0.25, // sugar
    0.45, // caramel
    0.79  // hazel nut
};

const std::string TOPPINGS_NAME_LIST[] = {
    "Cream       ",
    "Milk        ",
    "Almond Milk ",
    "Vanilla     ",
    "Sugar       ",
    "Caramel     ",
    "Hazel Nut   "
};

const double SIZE_PRICING_LIST[] = {
    2.00,  // small
    5.00,  // medium
    10.00, // large
};

const std::string SIZE_NAME_LIST[] = {
    "Small       ",
    "Medium      ",
    "Large       "
};

std::string lowercase(std::string string) { // converts a string to lowercase
    const char *f = string.c_str(); // convert string to a c string
    char buffer[string.length()]; // create a buffer string of same size

    for (int i = 0; i < string.length(); i++) buffer[i] = tolower(f[i]); // loop over c string and input lowercase characters into buffer string

    return std::string (buffer); // return string class of buffer string
}

int ValidateMenuBuffer(std::string stringBuffer, int min, int max) { // function for abstracting the validating of a given input, takes a string buffer, returns number or -1 if failed
    int scoreReturn = -1; // score to return, set to -1 if any checks fail

    try { 
        scoreReturn = std::stoi(stringBuffer); // attempt to convert string buffer to real number
    } catch (...) {} // do nothing if fails, next line guarantees score return is -1

    if (scoreReturn < min || scoreReturn > max) scoreReturn = -1; // if the converted number is out of range (0-100) then set it to -1

    if (scoreReturn == -1) std::cout << "Invalid Choice, Please Only Type A Number Between " << min << " and " << max << std::endl; // if any checks failed then tell the user the entered score is invalid

    return scoreReturn; // return the number or failed check flag to the called function
}

void hotToppings(std::vector<int> *orders) { // function to be called if the user wants a hot coffee
    int choice;
    std::string choiceBuffer; // buffer for input validation
    
    do {
        std::cout << "Hot Toppings:\n1) Cream " << TOPPINGS_PRICE_LIST[0] << "$" << std::endl; // list each topping price
        std::cout << "2) Milk " << TOPPINGS_PRICE_LIST[1] << "$" << std::endl; 
        std::cout << "3) Almond Milk " << TOPPINGS_PRICE_LIST[2] << "$" << std::endl;
        std::cout << "4) Vanilla " << TOPPINGS_PRICE_LIST[3] << "$" << std::endl;
        std::cout << "5) Sugar " << TOPPINGS_PRICE_LIST[4] << "$" << std::endl;
        std::cout << "Please Enter The Number Of The Topping You Would Like: "; // Display menu in above format
        std::getline(std::cin, choiceBuffer); // store the input from the user

        choice = ValidateMenuBuffer(choiceBuffer, 1, 5); // validate the choice buffer and store the result in the integer choice variable
    } while (choice == -1);

    totalCost += TOPPINGS_PRICE_LIST[choice-1]; // if all went well then just add the cost to the static total cost variable
    orders->push_back(choice-1); // add choice to the order list
}

void coldToppings(std::vector<int> *orders) { // function to be called if the user wants a cold coffee
    int choice;
    std::string choiceBuffer; // buffer for input validation
    
    do {
        std::cout << "Cold Toppings:\n1) Cream " << TOPPINGS_PRICE_LIST[0] << "$" << std::endl; // list each topping price
        std::cout << "2) Milk " << TOPPINGS_PRICE_LIST[1] << "$" << std::endl;
        std::cout << "3) Almond Milk " << TOPPINGS_PRICE_LIST[2] << "$" << std::endl;
        std::cout << "4) Vanilla " << TOPPINGS_PRICE_LIST[3] << "$" << std::endl;
        std::cout << "5) Sugar " << TOPPINGS_PRICE_LIST[4] << "$" << std::endl;
        std::cout << "6) Caramel " << TOPPINGS_PRICE_LIST[5] << "$" << std::endl;
        std::cout << "7) Hazel Nut " << TOPPINGS_PRICE_LIST[6] << "$" << std::endl;
        std::cout << "Please Enter The Number Of The Topping You Would Like: "; // Display menu in above format
        std::getline(std::cin, choiceBuffer); // store the input from the user

        choice = ValidateMenuBuffer(choiceBuffer, 1, 7); // validate the choice buffer and store the result in the integer choice variable
    } while (choice == -1);

    totalCost += TOPPINGS_PRICE_LIST[choice-1]; // if all went well then just add the cost to the static total cost variable
    orders->push_back(choice-1); // add choice to the order list
}

void createReceipt(int sizeType, int coffeeType, std::vector<int> *orders) { // function for creating the Receipt.txt, takes size index, coffee type index(hot/cold), and the vector choices used for indexing
    std::ofstream receiptFile("Receipt.txt"); // open the Receipt.txt file
    
    receiptFile << "--------Coffee For Coders--------" << std::endl; // tagline of the company
    if (coffeeType == 1) receiptFile << "Hot Coffee With" << std::endl; // if the Coffee Type is Hot then output that
    else receiptFile << "Cold Coffee With" << std::endl; // otherwise output cold

    std::for_each(orders->begin(), orders->end(), [&receiptFile](int choice) { // for each goes through the iterators, then calls the lambda function
        receiptFile << "  " << TOPPINGS_NAME_LIST[choice] << "  " << TOPPINGS_PRICE_LIST[choice] << "$" << std::endl; // output each topping name and topping price
    });
    
    receiptFile << "Size" << std::endl; // size section
    receiptFile << "  " << SIZE_NAME_LIST[sizeType] << "  " << SIZE_PRICING_LIST[sizeType] << "$" << std::endl; // output the size that the user chose and its price
    receiptFile << "Total Cost:     " << totalCost << "$" << std::endl; // end with the total cost
    receiptFile << "---------------------------------"; // output to show that the receipt is done, stylistic

    receiptFile.close(); // close the output file
}


int main() {
    std::string typeBuffer; // variable to store the user selection of coffee type
    int coffeeType = -1; // variable to store conversion to usable numeric value
    std::vector<int> orders; // vector for taking topping choices

    do {
        std::cout << "What type of coffee do you want\n1) Hot\n2) Cold\nPlease Enter The Number: "; // prompt the user for the type of coffee
        std::getline(std::cin, typeBuffer); // store the user input in the type variable
        coffeeType = ValidateMenuBuffer(typeBuffer, 1, 2); // validate the input and store the converted result into the choice variable
    } while (coffeeType == -1); // if validation failed then repeat

    std::string moreToppingsBuffer; // buffer for more toppings choice
    if (!(coffeeType-1)) {    
        do {
            hotToppings(&orders);
            std::cout << "Do you want to add more toppings (Y/N)? "; // ask if the user wants more toppings
            std::getline(std::cin, moreToppingsBuffer);
        } while (lowercase(moreToppingsBuffer).c_str()[0] != 'n'); // check if the input is anything but no, allows the user to simply press enter
    } // if user inputted a 1 then we can subtract one and invert the check to see if they chose hot
    else {
        do {
            coldToppings(&orders);
            std::cout << "Do you want to add more toppings (Y/N)? "; // same thing as above
            std::getline(std::cin, moreToppingsBuffer);
        } while (lowercase(moreToppingsBuffer).c_str()[0] != 'n');
    } // if they did not then they must have chosen cold

    //sizing menu
    int size; // size integer used for list indexing
	std::string sizeBuffer; // buffer used for input validation
    do {
        std::cout << "What size would you like?\n1) Small " << SIZE_PRICING_LIST[0] << "$" << std::endl; // ask the user what size they wanted, goes through each
        std::cout << "2) Medium " << SIZE_PRICING_LIST[1] << "$" << std::endl;
        std::cout << "3) Large " << SIZE_PRICING_LIST[2] << "$" << std::endl;
        std::cout << "Please Enter The Number Of The Size You Want: ";
        std::getline(std::cin, sizeBuffer); // get the input from the user
        
        size = ValidateMenuBuffer(sizeBuffer, 1, 3); // validate the buffer that the input was put into
    } while (size == -1); // if the validation failed then it will be -1, forcing the code to redo

    totalCost += SIZE_PRICING_LIST[size-1]; // add the size to the total cost

    std::cout << "Your total is " << totalCost  << "$" << std::endl; // display the total cost to the user

    std::string paymentBuffer; // buffer used for input validation
    int paymentType = -1; // integer used for indexing
    do { 
        std::cout << "Would you like to pay instore or online?\n1) Instore\n2) Online\nPlease enter the number of your choice: "; // ask the user how they want to pay
        std::getline(std::cin, paymentBuffer); // get input from the user
        paymentType = ValidateMenuBuffer(paymentBuffer, 1, 2);  // validate the buffer
    } while (paymentType == -1); // if the validation failed the code will redo 

    if (paymentType == 2) // if the user wants to pay online then create the receipt
        createReceipt(size-1, coffeeType, &orders); 
    return 0; // return exit code 0
}
