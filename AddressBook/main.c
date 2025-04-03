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

/* MAIN FUNCTION **************************************************/
int main(void)
{
	_wsetlocale(LC_ALL, L"korean");
	Test_DeleteRecordByPhoneFromFile();
	//// UI event loop handler
	//int (*pfMenu[UI_FUNC_COUNT])(const char*) = {
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