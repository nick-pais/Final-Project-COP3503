#include "Inventory.h"
#include "Menu.h"
#include "FileAccess.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// WORKS FOR SURE

// Constructor initializes an inventory to start out with, which is
// hard-coded in the inventory class
Menu::Menu(){
	temp = Inventory();
	if (!inventoryExists()){
		populate();
	}
	vector<item> invFromFile = getItemVector();
	for (unsigned int i = 0; i < invFromFile.size(); i++){
		temp.createItem(invFromFile[i]);
	}
}

// WORKS FOR SURE
// Method for creating accounts, used by the administrator menu
// Calls the addProfile() method which writes the account information
// to a CSV FILE
void Menu::createAccount(){

	// U for can't find username
	// P for passwords don't match
	// a for admin
	// m for manager
	// c for cashier
	// s for stocker
	string username;
	string password;
	char position;
	bool b = true;

	cout << endl;
	cout << "Please enter a username:" << endl;
	cin >> username;
	cout << "Please enter a password:" << endl;
	cin >> password;
	cout << "Please enter a position:" << endl;
	cout << "a. Admin" << endl;
	cout << "m. Manager" << endl;
	cout << "s. Stocker" << endl;
	cout << "c. Cashier" << endl;
	cin >> position;

	// Loops through until it the user has entered a valid position has been
	// entered for the new account
	while (b){
		if((position == 'a' || position == 'm' || position == 'c' || position == 's') && position != 'U' && position != 'P'){

			// If the profile doesn't exist, do nothing
			// otherwise the new account is created with the given parameters
			if(!addProfile(position, username, password, false)){
				cout << endl;
				cout << "Profile already exists" << endl;
				b = false;
			}
			else{
				b = false;
			}
		}

		// Re-asks the user for input for the position of the new account holder
		else{
			cout << endl;
			cout << "Invalid position. Please enter a valid position:" << endl;
			cout << "a. Admin" << endl;
			cout << "m. Manager" << endl;
			cout << "s. Stocker" << endl;
			cout << "c. Cashier" << endl;
			cin >> position;
		}
	}
}

// WORKS FOR SURE
// Method that deletes entire accounts, preventing them from being used to
// login unless they are created again
void Menu::deleteAccount(){

	string username;
	cout << "Please enter the username of the profile you want to delete:" << endl;
	cin >> username;
	cout << endl;
	if(deleteProfile(username)){
		cout << "Profile successfully deleted" << endl;
	}
	else{
		cout << "Profile not found" << endl;
	}
}

// WORKS FOR SURE
// Updates an account's information by allowing users to alter
// an account's username, password, and position
void Menu::updateAccount(){

	string username;
	string password;
	char position;

	cout << "Please enter the username of the account you want to update:" << endl;
	cin >> username;
	cout << "Please enter the new password:" << endl;
	cin >> password;
	cout << "Please enter the new position:" << endl;
	cout << "a. Admin" << endl;
	cout << "m. Manager" << endl;
	cout << "s. Stocker" << endl;
	cout << "c. Cashier" << endl;
	cin >> position;
	cout << endl;


	if(addProfile(position, username, password, true)){
		cout << "Profile updated successfully" << endl;
	}
	else{
		cout << "Unable to update profile" << endl;
	}

}

// WORKS FOR SURE
// This is the menu used to login
// Called when running the program and after logging out
void Menu::loginMenu(){

	// U for can't find username
	// P for passwords don't match
	// a for admin
	// m for manager
	// c for cashier
	// s for stocker

	string username;
	string password;
	char tempLetter;

	int count = 0;
	int limit = 5;


	// Give the user 5 attempts to login correctly
	// Resets after successfully logging in
	while(count < limit){

		cout << "Please enter your username:" << endl;
		cin >> username;
		cout << "Please enter your password:" << endl;
		cin >> password;
		cout << endl;

		// The authorize() function returns a character that decides
		// which menu will be called
		tempLetter = authorize(username, password);

		if (tempLetter == 'a'){
			adminMenu();
		}
		else if (tempLetter == 'm'){
			managerMenu();
		}
		else if (tempLetter == 'c'){
			cashierMenu();
		}
		else if (tempLetter == 's'){
			stockerMenu();
		}
		else if (tempLetter == 'U'){
			cout << "Unable to find account" << endl;
			count++;
			if (limit-count != 0){
				cout << "You have " << limit-count << " login attempts remaining" << endl;
			}
			else{
				cout << "No login attempts remaining\nExiting program" << endl;
			}
			cout << endl;
		}
		else if (tempLetter == 'P'){
			cout << "Unable to find account" << endl;
			count++;
			if (limit-count != 0){
				cout << "You have " << limit-count << " login attempts remaining" << endl;
			}
			else{
				cout << "No login attempts remaining\nExiting program" << endl;
			}
			cout << endl;
		}
		else{
			count++;
			if (limit-count != 0){
				cout << "You have " << limit-count << " login attempts remaining" << endl;
			}
			else{
				cout << "No login attempts remaining\nExiting program" << endl;
				exit(EXIT_SUCCESS);
			}
			cout << endl;
		}
	}
}

// Simply prints the current inventory
void Menu::printInventory(){
	temp.printInventory();
}

// Initializes the inventory
// TODO: CHECK IF WE EVEN USE THIS
void Menu::initializeInventory(){
	temp.populateInventory();
	temp.printInventory();
}

// Adds a new item to the current inventory
void Menu::addItem(){

	string name;
	int itemNumber;
	double price;
	int quantity;
	bool bFail;

	cout << "Please enter the name of the item:" << endl;
	cin.ignore();
	// Allows items of more than one word to be input
	getline(cin, name);

	// The do-while loops in this program ensure that a number is
	// input when asked, and repeatedly asks until one is given
	do{
		cout << "Please enter the item number:" << endl;
		cin >> itemNumber;
		bFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}while(bFail == true);

	do{
		cout << "Please enter the price of the item:" << endl;
		cin >> price;
		bFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}while(bFail == true);

	do{
		cout << "Please enter the quantity of the item" << endl;
		cin >> quantity;
		bFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}while(bFail == true);

	// Requires that the quantity be greater than 0, the number be
	// at least 0, and that the price be at least 0
	if (quantity <= 0 || itemNumber < 0 || price < 0){
		cout << "Invalid input" << endl;
		cout << endl;
		cout << "Press enter to continue" << endl;
	}
	else{
		temp.createItem(name, itemNumber, price, quantity);
		cout << endl;
		cout << "Attempting to add item to inventory" << endl;
		cout << endl;
		cout << "Press enter to continue" << endl;
	}
}

// Deletes entire items from the current inventory
void Menu::deleteItem(){

	int input;
	string name;
	int itemNumber;
	bool bFail;
	bool check;

	// Allows users to delete items by either name or number
	cout << "Delete by name or by item number?" << endl;
	cout << "1. Name" << endl;
	cout << "2. Item Number" << endl;
	cin >> input;

	if (input == 1){
		cout << "Please input the name of the item:" << endl;
		cin.ignore();
		getline(cin, name);

		// Checks if the item exists in the inventory for removal,
		// and executes the method accordingly
		check = temp.deleteItemByName(name);
		cout << endl;
		if (check){
			cout << "Attempting to remove item from inventory" << endl;
			cout << endl;
			cout << "Press enter to continue" << endl;
		}
		else{
			cout << "Attempting to remove item from inventory" << endl;
			cout << endl;
			cout << "Press enter to continue" << endl;
		}
	}

	else if(input == 2){

		// Ensures that a number is entered before continuing
		do{
			cout << "Please enter the item number" << endl;
			cin >> itemNumber;
			bFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);

		// When the number is obtained, deletes the item with the provided
		// item number
		temp.deleteItemByItemNumber(itemNumber);

		cout << endl;
		cout << "Attempting to remove item from inventory" << endl;
		cout << endl;
		cout << "Press enter to continue" << endl;
	}

	else {
		cout << endl;
		cout << "Invalid input" << endl;
		cout << endl;
	}
}

// Allows users, other than cashiers, to change the quantity of any item
// in inventory to another amount
void Menu::updateQuantity(){

	int input;
	string name;
	int itemNumber;
	int newQuantity;
	bool check;
	bool bFail;

	// Allows users to choose if they want to update quantity based on
	// item name or item number
	cout << "Update quantity by name or by item number?" << endl;
	cout << "1. Name" << endl;
	cout << "2. Item Number" << endl;
	cin >> input;

	if (input == 1){
		cout << "Please input the name of the item:" << endl;
		cin.ignore();
		getline(cin, name);
		cout << "Please enter the new quantity:" << endl;
		cin >> newQuantity;

		// If the item exists, changes its quantity
		check = temp.updateQuantityByName(name, newQuantity);
		if (check){
			cout << endl;
			cout << "Attempting to change quantity" << endl;
			cout << endl;
		}
		else{
			cout << endl;
		}
	}

	else if(input == 2){

		do{
			cout << "Please enter the item number" << endl;
			cin >> itemNumber;
			bFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);

		do{
			cout << "Please enter the new quantity:" << endl;
			cin >> newQuantity;
			bFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);

		// Same reasoning for updateQuantityByName
		check = temp.updateQuantityByItemNumber(itemNumber, newQuantity);
		if (check){
			cout << endl;
			cout << "Attempting to change quantity" << endl;
			cout << endl;
			cout << "Press enter to continue" << endl;
		}
		else{
			cout << endl;
		}

	}
	else{
		cout << endl;
		cout << "Invalid input" << endl;
		cout << endl;
	}

}

// Reasoning is essentially the same as updateQuantity()
// Cashiers are only allowed to reduce quantity, not increase it
void Menu::updateQuantityCashier(){

	int input;
	string name;
	int itemNumber;
	int newQuantity;
	item tempCheck;
	bool bFail;
	bool check;

	cout << "Reduce quantity by name or by item number?" << endl;
	cout << "1. Name" << endl;
	cout << "2. Item Number" << endl;
	cin >> input;

	if (input == 1){
		cout << "Please input the name of the item:" << endl;
		cin.ignore();
		getline(cin, name);

		do{
			cout << "Please enter a new quantity less than the current one:" << endl;
			cin >> newQuantity;
			bFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);

		tempCheck = temp.findByItemNameReturnItem(name);
		if (newQuantity >= tempCheck.quantity){
			cout << endl;
			cout << "Invalid entry" << endl;
			cout << endl;
			cout << "Press enter to continue" << endl;
		}
		else{
			check = temp.updateQuantityByName(name, newQuantity);
			if(check){
				cout << endl;
				cout << "Attempting to change quantity" << endl;
				cout << endl;
				cout << "Press enter to continue" << endl;
			}
			else{
				cout << endl;
			}
		}
	}

	else if(input == 2){
		do{
			cout << "Please enter the item number" << endl;
			cin >> itemNumber;
			bFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);

		do{
			cout << "Please enter a new quantity less than the current one:" << endl;
			cin >> newQuantity;
			bFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);

		tempCheck = temp.findByItemNumberReturnItem(itemNumber);

		if (tempCheck.itemNumber == -1){
			cout << endl;
			cout << "Invalid entry" << endl;
			cout << endl;
			cout << "Press enter to continue" << endl;

		}

		else if (newQuantity >= tempCheck.quantity){
			cout << endl;
			cout << "Invalid entry" << endl;
			cout << endl;
			cout << "Press enter to continue" << endl;
		}
		else{
			check = temp.updateQuantityByItemNumber(itemNumber, newQuantity);
			if(check){
				cout << endl;
				cout << "Attempting to change quantity" << endl;
				cout << endl;
				cout << "Press enter to continue" << endl;
			}
			else{
				cout << endl;
			}
		}
	}
	else{
		cout << endl;
		cout << "Invalid input" << endl;
		cout << endl;
	}

}

// Allows users to update the price of an item
void Menu::updatePrice(){

	double newPrice;
	string name;
	bool bFail;
	bool check;

	cout << "Please enter the name of the item: " << endl;
	cin.ignore();
	getline(cin, name);

	do{
		cout << "Please enter the new price" << endl;
		cin >> newPrice;
		bFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}while(bFail == true);

	// If the price was successfully updated, confirms
	check = temp.updatePriceByName(name, newPrice);
	if(check){
		cout << endl;
		cout << "Attempting to change price" << endl;
		cout << endl;
		cout << "Press enter to continue" << endl;
	}
	else{
		cout << endl;
		cout << "Invalid entry" << endl;
		cout << endl;
		cout << "Press enter to continue" << endl;
	}
}

// Menu used by administrators
void Menu::adminMenu(){
	bool b = true;
	int input;
	bool bFail;

	while (b){

		do{
			cout << "Please select an option from the menu: " << endl;
			cout << "1. Add an item to stock" << endl;
			cout << "2. Remove an item from stock" << endl;
			cout << "3. Change quantity of an item in stock" << endl;
			cout << "4. Change price of an item in stock" << endl;
			cout << "5. Print current inventory" << endl;
			cout << "6. Add an account" << endl;
			cout << "7. Delete an account" << endl;
			cout << "8. Update account information" << endl;
			cout << "9. Logout" << endl;
			cout << "10. Exit" << endl;
			cin >> input;
			switch(input){

				case 1:
				addItem();
				break;

				case 2:
				deleteItem();
				break;

				case 3:
				updateQuantity();
				break;

				case 4:
				updatePrice();

				break;

				case 5:
				printInventory();
				break;

				case 6:
				createAccount();
				cout << endl;
				break;

				case 7:
				cout << endl;
				deleteAccount();
				cout << endl;
				break;

				case 8:
				updateAccount();
				cout << endl;
				break;

				case 9:
				cout << endl;
				loginMenu();
				break;

				case 10:
				temp.writeToFile();
				exit(EXIT_SUCCESS);
				break;

				default:
				//cout << "\nPlease enter a valid option from the Menu\n" << endl;
				break;
			}
			bFail = cin.fail();
			cin.clear();
			//cout << "Press enter to continue" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);
	}
}

// Menu used by managers
void Menu::managerMenu(){
	bool b = true;
	int input;
	bool bFail;

	while (b){

		// Managers can do everything Admins can
		// other than edit accounts
		do{
			cout << "Please select an option from the menu: " << endl;
			cout << "1. Add an item to stock" << endl;
			cout << "2. Remove an item from stock" << endl;
			cout << "3. Change quantity of an item in stock" << endl;
			cout << "4. Change price of an item in stock" << endl;
			cout << "5. Print current inventory" << endl;
			cout << "6. Logout" << endl;
			cout << "7. Exit" << endl;
			cin >> input;
			switch(input){

				case 1:
				addItem();
				break;

				case 2:
				deleteItem();
				break;

				case 3:
				updateQuantity();
				break;

				case 4:
				updatePrice();
				break;

				case 5:
				printInventory();
				break;

				case 6:
				cout << endl;
				loginMenu();

				break;

				case 7:
				temp.writeToFile();
				exit(EXIT_SUCCESS);
				break;

				default:
				//cout << "\nPlease enter a valid option from the Menu\n" << endl;
				break;
			}
			bFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);
	}
}

// Menu used by cashiers
void Menu::cashierMenu(){

	bool b = true;
	int input;
	bool bFail;

	while (b){

		// Cashiers are allowed to change the quantity of an item
		// But only allowed to decrease it

		do{
			cout << "Please select an option from the menu: " << endl;
			cout << "1. Change quantity of an item in stock" << endl;
			cout << "2. Print current inventory" << endl;
			cout << "3. Logout" << endl;
			cout << "4. Exit" << endl;
			cin >> input;
			switch(input){

				case 1:
				updateQuantityCashier();
				break;

				case 2:
				printInventory();
				break;

				case 3:
				cout << endl;
				loginMenu();

				break;

				case 4:
				temp.writeToFile();
				exit(EXIT_SUCCESS);
				break;

				default:
				break;
			}
			bFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);
	}
}

// Menu used by stockers
void Menu::stockerMenu(){
	bool b = true;
	int input;
	bool bFail;

	while (b){

		// Stockers are allowed to change the quantity of items
		// in stock, increase or decrease it
		do{
			cout << "Please select an option from the menu: " << endl;
			cout << "1. Change quantity of an item in stock" << endl;
			cout << "2. Print current inventory" << endl;
			cout << "3. Logout" << endl;
			cout << "4. Exit" << endl;
			cin >> input;

			switch(input){

				case 1:
				updateQuantity();
				break;

				case 2:
				printInventory();
				break;

				case 3:
				cout << endl;
				loginMenu();

				break;

				case 4:
				temp.writeToFile();
				exit(EXIT_SUCCESS);
				break;

				default:
				cout << "\nPlease enter a valid option from the Menu\n" << endl;
				break;
			}
			bFail = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}while(bFail == true);

	}
}
