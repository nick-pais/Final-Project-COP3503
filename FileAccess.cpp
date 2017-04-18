/*
* File: FileAccess.cpp
* Author: Logan Hughes
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "FileAccess.h"
#include "sha256.h"
#include "itemStruct.h"
#include "profileStruct.h"

using namespace std;

// Checks login.csv file
// If login.csv exists, true is returned, otherwise false is returned
// If login.csv does not exist, it is created with a default admin account
bool loginExists(){
	ofstream loginFileOut;
	ifstream loginFileIn;
	loginFileIn.open("login.csv");
	string checker;
	getline(loginFileIn, checker);
	if (checker.compare("") == 0){ // Checks file for empty string
		// Inserts default credentials and closes fstream objects, then returns false
		loginFileOut.open("login.csv");
		loginFileOut << "admin,a," << sha256("password");
		loginFileOut.close();
		loginFileIn.close();
		return false;
	}
	else {
		// Checks that file exists
		if (loginFileIn.peek() == std::ifstream::traits_type::eof()){
			// Creates file, inserts default credentials, and closes fstream
			// (and necesarily returns true)
			loginFileIn.close();
			loginFileOut.open("login.csv");
			loginFileOut << "admin,a," << sha256("password");
			loginFileOut.close();
		}
		else{
			loginFileIn.close();
		}
		return true;
	}
}
// Checks inventory.csv file
// If inventory.csv exists, true is returned, otherwise false is returned
// If inventory.csv does not exist, it is created
bool inventoryExists(){
	ofstream inventoryFileOut;
	ifstream inventoryFileIn;
	inventoryFileIn.open("inventory.csv");
	string checker;
	getline(inventoryFileIn, checker);
	if (checker.compare("") == 0){
		inventoryFileOut.open("inventory.csv");
		inventoryFileOut.close();
		inventoryFileIn.close();
		return false;
	}
	else {
		inventoryFileIn.close();
		return true;
	}
}

/*
* Authorizes login attempt based on passed username and password
* Returns character corresponding to given position ('a' for admin, etc.)
* Returns 'U' for unfound username and 'P' for bad password
* Will create a new login file if none is found with default credentials
* Username is not case sensitive, password is
*/
char authorize(string name, string password){
	string nameTest = name;
	// Username not case sensitive for authorization
	transform(nameTest.begin(), nameTest.end(), nameTest.begin(), ::tolower);
	string passwordTest = sha256(password); // Encrypts password
	loginExists(); // Assures login file exists
	// Sets flags and variables and opens fstreams
	bool notFoundAccount = true;
	ifstream loginFileIn;
	loginFileIn.open("login.csv");
	string accountLine;
	char letter;
	string checkName, checkPass;
	// Takes in the values of login file to a vector of profiles
	while (getline(loginFileIn, accountLine) && notFoundAccount){
		// Pulls apart each line into its separate variables
		istringstream accountLineStream(accountLine);
		string tempWord;
		getline(accountLineStream, tempWord, ',');
		checkName = tempWord;
		getline(accountLineStream, tempWord, ',');
		letter = tempWord.at(0);
		getline(accountLineStream, tempWord, ',');
		checkPass = tempWord;
		// Checks account information against supplied information
		if (name.compare(checkName) == 0){
			notFoundAccount = false;
			// Checks hash of provided password against stored password
			if (sha256(password).compare(checkPass) == 0){
				loginFileIn.close();
				return letter;
			}
			else{
				loginFileIn.close();
				return 'P'; // 'P' returned for incorrect password
			}
		}
	}
	loginFileIn.close();
	return 'U'; // 'U' returned if method cannot find provided username
}

// Returns a vector of all items in inventory file
// Order is Username, Employee Level, Password Hash
vector<profile> getProfileVector(){
	// Declaring vector and variables and checking and opening file
	vector<profile> myAccounts;
	loginExists();
	ifstream profileFileIn;
	profileFileIn.open("login.csv");
	string intake;
	string myUser, myPass;
	char myLevel;
	// Processes separate lines of csv
	while (getline(profileFileIn, intake)){
		//Separates line into variable values
		istringstream myCurrentLine(intake);
		string tempWord;
		getline(myCurrentLine, tempWord, ',');
		myUser = tempWord;
		getline(myCurrentLine, tempWord, ',');
		myLevel = tempWord.at(0);
		getline(myCurrentLine, tempWord, ',');
		myPass = tempWord;
		// Adds new profile to vector
		profile toAdd;
		toAdd.level = myLevel;
		toAdd.password = myPass;
		toAdd.user = myUser;
		myAccounts.push_back(toAdd);
	}
	profileFileIn.close();
	return myAccounts;
}
// Returns a vector of all items in inventory file
// Order is Item Number, Item Name, Price, Quantity
vector<item> getItemVector(){
	// Declaring vector and variables and checking and opening file
	vector<item> myInventory;
	inventoryExists();
	ifstream inventoryFileIn;
	inventoryFileIn.open("inventory.csv");
	string intake;
	int myItemNumber, myQuantity;
	double myPrice;
	string myItemName, myDescription;
	// Processes separate lines of csv
	while (getline(inventoryFileIn, intake)){
		//Separates line into variable values
		istringstream myCurrentLine(intake);
		string tempWord;
		getline(myCurrentLine, tempWord, ',');
		stringstream toConvertIN(tempWord);
		toConvertIN >> myItemNumber;
		getline(myCurrentLine, tempWord, ',');
		myItemName = tempWord;
		getline(myCurrentLine, tempWord, ',');
		myDescription = tempWord;
		getline(myCurrentLine, tempWord, ',');
		stringstream toConvertP(tempWord);
		toConvertP >> myPrice;
		getline(myCurrentLine, tempWord, ',');
		stringstream toConvertQ(tempWord);
		toConvertQ >> myQuantity;
		item toAdd;
		// Adds new profile to vector
		toAdd.itemNumber = myItemNumber;
		toAdd.name = myItemName;
		toAdd.description = myDescription;
		toAdd.price = myPrice;
		toAdd.quantity = myQuantity;
		myInventory.push_back(toAdd);
	}
	inventoryFileIn.close();
	return myInventory;
}
// Overwrites inventory file with new item vector
void writeInventory(vector<item> myInventory){
	inventoryExists();
	ofstream inventoryFileOut;
	inventoryFileOut.open("inventory.csv");
	clearInventory(); // Clears the inventory file's contents
	// Adds past items to vector, then appends the new one
	for (unsigned int i = 0; i < myInventory.size(); i++){
		inventoryFileOut << myInventory[i].itemNumber << "," << myInventory[i].name << "," << myInventory[i].description << "," << myInventory[i].price << "," << myInventory[i].quantity;
		inventoryFileOut << "\n";
	}
	inventoryFileOut.close();
}
// Overwrites login file with new profile vector
void writeProfile(vector<profile> myAccounts){
	loginExists();
	ofstream loginFileOut;
	loginFileOut.open("login.csv");
	clearLogin(); // Clears the login file's contents
	// Adds past profiles to vector, then appends the new one
	for (unsigned int i = 0; i < myAccounts.size(); i++){
		loginFileOut << myAccounts[i].user << "," << myAccounts[i].level << "," << myAccounts[i].password;
		loginFileOut << "\n";
	}
	loginFileOut.close();
}
/*
* This method will add a new account to the login csv
* If the username exists already and replace is false, the method returns false
* If the username exists already and replace is true,
* the method will replace that profile item with the new information
*/
bool addProfile(char newLevel, string newUser, string newPass, bool replace){
	profile toAdd; // Profile that will be pushed to file
	toAdd.level = newLevel;
	toAdd.user = newUser;
	toAdd.password = sha256(newPass);
	vector<profile> myAccounts = getProfileVector();
	// Checks for profile with same name already in file
	for (unsigned int i = 0; i < myAccounts.size(); i++){
		if (toAdd.user.compare(myAccounts[i].user) == 0){
			if (replace){ // If replace is true, replaces profile with correct name
				myAccounts[i] = toAdd;
				writeProfile(myAccounts);
				return true;
			}
			else{ // Won't add new item if replace is true
				return false;
			}
		}
	}
	// If replace is false, adds new item if none with matching name is found
	if (replace){
		return false;
	}
	else{
		myAccounts.push_back(toAdd);
		writeProfile(myAccounts);
		return true;
	}
	return false;
}
// This method will delete the relevant user from the login file
// If username cannot be found, it returns false, returning true if deletion is successful
bool deleteProfile(string userSearch){
	vector<profile> myAccounts = getProfileVector();
	for (unsigned int i = 0; i < myAccounts.size(); i++){
		if (userSearch.compare(myAccounts[i].user) == 0){
			myAccounts.erase(myAccounts.begin() + i);
			writeProfile(myAccounts);
			return true;
		}
	}
	return false;
}
// Clear the contents of their respective csv files;
void clearLogin(){
	ofstream clear;
	clear.open("login.csv", ios::trunc);
	clear.close();
}
void clearInventory(){
	ofstream clear;
	clear.open("inventory.csv", ios::trunc);
	clear.close();
}
// Method populates the inventory csv with sample items
void populate(){
	vector<item> populator;

	item temp;

	temp.itemNumber = 1;
	temp.name = "Hammer";
	temp.price = 5.12;
	temp.quantity = 12;
	populator.push_back(temp);

	temp.itemNumber = 22;
	temp.name = "Hand Saw";
	temp.price = 12.23;
	temp.quantity = 5;
	populator.push_back(temp);

	temp.itemNumber = 9;
	temp.name = "Drill";
	temp.price = 36.23;
	temp.quantity = 3;
	populator.push_back(temp);

	temp.itemNumber = 12;
	temp.name = "Pliers";
	temp.price = 15.19;
	temp.quantity = 10;
	populator.push_back(temp);

	temp.itemNumber = 192;
	temp.name = "Drill Bit";
	temp.price = 1.13;
	temp.quantity = 5;
	populator.push_back(temp);

	writeInventory(populator);
}
