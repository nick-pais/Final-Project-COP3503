#include "Inventory.h"
#include "sha256.h"
#include "Menu.h"
#include "itemStruct.h"
#include "profileStruct.h"
#include "FileAccess.h"
#include <stdlib.h>
#include "stdio.h"


using namespace std;

int main(int argc, char const *argv[]) {
	/* code */

	Inventory temp = Inventory();
	Menu session = Menu();
	session.loginMenu();

	return 0;
}
