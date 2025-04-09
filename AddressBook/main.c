// Entry point of the Address Book program.

/* INCLUDES	*******************************************************/
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

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
#include "contact.h"
#include "contact_store.h"


/* MAIN FUNCTION **************************************************/
int main(void)
{
	_wsetlocale(LC_ALL, L"korean");
	// UI event loop handler
	int (*pfMenu[UI_FUNC_COUNT])(LPCWSTR) = {
		UI_ExitMenu,
		UI_PrintAll_CS,
		UI_InsertNode_CS,
		UI_DeleteNode_CS,
		UI_Search_CS,
		UI_EditNode_CS
	};

	OPTION option = MENU_EXIT;
	while ((option = PrintMenu()) != MENU_EXIT)
	{
		system("cls");
		pfMenu[option](FILE_PATH);
	}
	return 0;
}

// Test function for debugging
//int main(void)
//{
//#ifdef _DEBUG
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	Test_ContactStore_Destroy();
//	Test_Contact_Destroy();
//#endif
//	Test_DeleteRecordFromFileByPhone_CS();
//	return 0;
//}