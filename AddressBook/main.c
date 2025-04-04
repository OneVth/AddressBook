// Entry point of the Address Book program.

/* INCLUDES	*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include "common.h"
#include "control.h"
#include "ui.h"
#include "test.h"

// Contact include
#include "contact_store.h"

/* MAIN FUNCTION **************************************************/
int main(void)
{
	ContactStore* store = CreateContactStore();
	AddContactToEnd(store, &(Contact){ 30, "John", "123-4567-8901" });
	AddContactToEnd(store, &(Contact){ 10, "Alice", "234-5678-9012" });
	AddContactToFront(store, &(Contact){ 20, "Betty", "345-6789-0123" });
	PrintAllContacts(store);
	DestroyContactStore(store);
	//_wsetlocale(LC_ALL, L"korean");
	//// UI event loop handler
	//int (*pfMenu[UI_FUNC_COUNT])(LPCWSTR) = {
	//	UI_ExitMenu, 
	//	UI_PrintAll,
	//	UI_InsertNode, 
	//	UI_DeleteNode, 
	//	UI_Search, 
	//	UI_EditNode 
	//};

	//OPTION option = MENU_EXIT;
	//while ((option = PrintMenu()) != MENU_EXIT)
	//{
	//	system("cls");
	//	pfMenu[option](FILE_PATH);
	//	_getch();
	//}
	
	return 0;
}