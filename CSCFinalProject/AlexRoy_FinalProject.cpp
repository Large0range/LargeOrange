#include <iostream>
#include <cstring>


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

enum HOT { // enum type for prices of hot coffee toppings
    Hcream,
    Hmilk,
    Halmond_milk,
    Hvanilla,
    Hsugar
};

const double HOT_TOPPINGS_INDEXING_LIST[] = {
    0.12, // cream
    0.15, // milk
    0.17, // almond milk
    0.20, // vanilla
    0.25  // sugar
};

enum COLD { // enum type for prices of cold coffee toppings
    Ccream,
    Cmilk,
    Calmond_milk,
    Cvanilla,
    Csugar,
    Ccaramel,
    Chazelnut
};

const double COLD_TOPPINGS_INDEXING_LIST[] = {
    0.12, // cream
    0.15, // milk
    0.17, // almond milk
    0.20, // vanilla
    0.25, // sugar
    0.45, // caramel
    0.79  // hazel nut
};

enum SIZE { // enum type for prices of small, medium, and large
    small,
    medium,
    large
};

const double SIZE_INDEXING_LIST[] = {
    2.00,  // small
    5.00,  // medium
    10.00, // large
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

void hotToppings() { // function to be called if the user wants a hot coffee
    int choice;

    do {
        std::string choiceBuffer; // buffer for input validation
        std::cout << "Hot Toppings:\n1) Cream\n2) Milk\n3) Almond Milk\n4) Vanilla\n5) Sugar\nPlease Enter The Number Of The Topping You Would Like: "; // Display menu in above format
        std::getline(std::cin, choiceBuffer); // store the input from the user

        choice = ValidateMenuBuffer(choiceBuffer, 1, 5); // validate the choice buffer and store the result in the integer choice variable
    } while (choice == -1);

    totalCost += HOT_TOPPINGS_INDEXING_LIST[choice-1]; // if all went well then just add the cost to the static total cost variable
}

void coldToppings() { // function to be called if the user wants a cold coffee
    int choice;

    do {
        std::string choiceBuffer; // buffer for input validation
        std::cout << "Cold Toppings:\n1) Cream\n2) Milk\n3) Almond Milk\n4) Vanilla\n5) Sugar\n6) Caramel\n7) Hazel Nut\nPlease Enter The Number Of The Topping You Would Like: "; // Display menu in above format
        std::getline(std::cin, choiceBuffer); // store the input from the user

        choice = ValidateMenuBuffer(choiceBuffer, 1, 7); // validate the choice buffer and store the result in the integer choice variable
    } while (choice == -1);

    totalCost += COLD_TOPPINGS_INDEXING_LIST[choice-1]; // if all went well then just add the cost to the static total cost variable
}


int main() {
    std::string type; // variable to store the user selection of coffee type
    int choice = -1; // variable to store conversion to usable numeric value

    do {
        std::cout << "What type of coffee do you want\n1) Hot\n2) Cold\nPlease Enter The Number: "; // prompt the user for the type of coffee
        std::getline(std::cin, type); // store the user input in the type variable
        choice = ValidateMenuBuffer(type, 1, 2); // validate the input and store the converted result into the choice variable
    } while (choice == -1); // if validation failed then repeat

    if (!(choice-1)) hotToppings(); // if user inputted a 1 then we can subtract one and invert the check to see if they chose hot
    else coldToppings(); // if they did not then they must have chosen cold

    //sizing menu
    int size;
    do {
	std::string sizeBuffer;
	std::cout << "What size would you like?\n1) Small\n2) Medium\n3) Large\nPlease Enter The Number Of The Size You Want: ";
	std::getline(std::cin, sizeBuffer);
	
	size = ValidateMenuBuffer(sizeBuffer, 1, 3);
    } while (size == -1);

    totalCost += SIZE_INDEXING_LIST[size-1];

    std::cout << totalCost << std::endl;

    return 0; // return exit code 0
}
