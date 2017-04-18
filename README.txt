Technical Documentation for Inventory Management System (IMS)
Group Term Project for COP3503
Contributors: Tim Botelho, Chad Lim, Logan Hughes, Nickolas Pais, Robert Parker, Nicholas White.


**Table of Contents**
	1. Basic Uses
		1.1 Default Admin Logon
		
	2. File Functionality
		2.1:File Access
		2.2:Inventory
		2.3:Menu
		2.4:Dab-tabase
		2.5:sha256
		
	3. User Types and Permission
		3.1: Admin
		3.2: Manager
		3.3: Stocker
		3.4: Cashier
		
	4. Full Menu Breakdown


------------------------------------------------------------------------------------------
1. Basic Uses
	Our program is an Inventory Management System (IMS) with export and import capabilities
	from a file. It comes fully integrated with the ability to create users with four 
	different permission levels admin, manager, stocker, and cashier. The IMS can create an
	item with the following tags: Item Number, Name, Price, and Quantity. The different user
	levels can be viewed below along with permissions given in section 3 of this document. 
	
	1.1 Default Admin Login (when program starts): 
		Username: admin
		Password: password
 
------------------------------------------------------------------------------------------
2. File Functionality
	2.1 File Access
		-This class opens the login csv file containing account information and the inventory
		 csv file containing all the inventory data. Makes sure that login information exists
		 and finds and returns user permissions based off login. Writes user data onto file, 
		 overwrites user data if changed, and deletes user data if prompted. Obtains all 
		 inventory data from file and puts it into a vector, writes inventory data onto 
		 file as well as deletes data from file.
		 
	2.2 Inventory
		-This class contains item structs named "item” which contains the data for the item
		 (price, quantity, etc.). The item structs are held in the vector “inventoryList”.
		 This class is used to create, update, remove, and print the items’ data. Each item
		 struct contains data for each item’s number, name, price, and quantity. The items’
		 data is pushed onto a csv file by the File Access class.
		 
	2.3 Menu
		-Contains the menu options for all types of users: the admin, manager, cashier, and
		 stocker. Depending on user permissions (located in section 3) the menu gives users
		 the option to add an item, remove an item, change quantity of item, change price 
		 of item, print the inventory, add an account, delete an account, update account 
		 information, logout of current account, and exit the program altogether.
		
	2.4 Dab-tabase 
		-The main method, it creates a new inventory object and a new menu object. Then it
		 starts a new session for the login menu.
		 
	2.5 sha256
		-Encrypts account information before it is pushed onto the csv file and decrypts 
		when it is accessed. Obtained from http://www.zedwood.com/article/cpp-sha256-function.
		License:
			* Updated to C++, zedwood.com 2012
 			* Based on Olivier Gay's version
			* See Modified BSD License below: 
			*
			* FIPS 180-2 SHA-224/256/384/512 implementation
			* Issue date:  04/30/2005
			* http://www.ouah.org/ogay/sha2/
			*
			* Copyright (C) 2005, 2007 Olivier Gay <olivier.gay@a3.epfl.ch>
 			* All rights reserved.
			*
			* Redistribution and use in source and binary forms, with or without
 			* modification, are permitted provided that the following conditions
 			* are met:
			* 1. Redistributions of source code must retain the above copyright
			*    notice, this list of conditions and the following disclaimer.
 			* 2. Redistributions in binary form must reproduce the above copyright
			*    notice, this list of conditions and the following disclaimer in the
			*    documentation and/or other materials provided with the distribution.
			* 3. Neither the name of the project nor the names of its contributors
 			*    may be used to endorse or promote products derived from this software
 			*    without specific prior written permission.
			*
			* THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
			* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
			* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 			* ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
			* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 			* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 			* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 			* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 			* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 			* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 			* SUCH DAMAGE.
 			*/

------------------------------------------------------------------------------------------
3. User Types and Permission
	3.1: Admin 
		The Admin user is the power user of the inventory management system. They have 
		access to all menu options as listed below.
	
		*********Admin Menu*********
		1. Add an item to stock
		2. Remove an item from stock
		3. Change quantity of an item in stock
		4. Change price of an item in stock
		5. Print current inventory
		6. Add an account
		7. Delete an account
		8. Update account information
		9. Logout
		10. Exit

	3.2: Manager
		The Manager user loses the ability to add, delete, or update user account 
		information.
	
		*********Manager Menu*********
		1. Add an item to stock
		2. Remove an item from stock
		3. Change quantity of an item in stock
		4. Change price of an item in stock
		5. Print current inventory
		6. Logout
		7. Exit
		
	3.3: Stocker
		The Stocker user has the ability to change the quantity of a  an item in the 
		inventory.
	
		*********Stocker Menu*********
		1. Change quantity of an item in stock (Can increase or decrease quantity)
		2. Print current inventory
		3. Logout
		4. Exit
		
	3.4: Cashier
		The Cashier user has the ability to decrease the quantity of a  an item in the 
		inventory. They can't increase the quantity of a stock item, only stocker, manager,
		and admin have that permission.
	
		*********Cashier Menu*********
		1. Change quantity of an item in stock (Can only decrease quantity)
		2. Print current inventory
		3. Logout
		4. Exit
		
------------------------------------------------------------------------------------------	
4. Full Menu Breakdown

		1. Add an item to stock 
			-This menu option allows the user to add an item to the inventory.
			 
		2. Remove an item from stock
			-This menu option allows the user to remove an item from the inventory by 
			 either name or item number. When an item is removed if there are two entries 
			 in the inventory with the same name or item number, the one that was put in 
			 first will be removed first.
			 
		3. Change quantity of an item in stock
			-This menu option allows the user to change a quantity of an item in the inventory, 
			 you can choose to change an item by either its name or item number.
			 
		4. Change price of an item in stock
			-This menu option allows the user to change a price of an item in the inventory, 
			 you can choose to change an item by either its name or item number.
			 
		5. Print current inventory
			-This menu option allows the user to print the current inventory in a table 
			 format.
			
		6. Add an account
			-This menu option allows the user to add a new login account, you can't create
			 two logins with the same name.
			 
		7. Delete an account
			-This menu option allows the user to delete a login account.
			
		8. Update account information
			-This menu option allows the user to update the password and level of permission,
			 you can't change username.
			 
		9. Logout
			-This menu option allows the user to logout, and login to a new account.
			
		10. Exit
			-This menu option allows the user to exit out of the program.
			
------------------------------------------------------------------------------------------	
