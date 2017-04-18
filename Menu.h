#include <iostream>
#include "Inventory.h"
#include <string>
#include <vector>

using namespace std;

#ifndef Menu_H_
#define Menu_H_

// Menu class that declares all the functions and
// global variables used in the Menu.cpp file

class Menu{

public:

	Menu();
	Inventory temp;
	void createAccount();
	void deleteAccount();
	void updateAccount();
	void loginMenu();
	void adminMenu();
	void managerMenu();
	void cashierMenu();
	void stockerMenu();
	void addItem();
	void deleteItem();
	void initializeInventory();
	void printInventory();
	void updateQuantity();
	void updateQuantityCashier();
	void updatePrice();


};
#endif
