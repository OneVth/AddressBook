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
#include "tests/test.h"

// Contact include
#include "contact.h"
#include "contact_store.h"


/* MAIN FUNCTION **************************************************/
//int main(void)
//{
//	_wsetlocale(LC_ALL, L"korean");
//	// UI event loop handler
//	int (*pfMenu[UI_FUNC_COUNT])(LPCWSTR) = {
//		UI_ExitMenu,
//		UI_PrintAll,
//		UI_InsertNode,
//		UI_DeleteNode,
//		UI_Search,
//		UI_EditNode
//	};
//
//	OPTION option = MENU_EXIT;
//	while ((option = PrintMenu()) != MENU_EXIT)
//	{
//		system("cls");
//		pfMenu[option](FILE_PATH);
//	}
//	return 0;
//}

// Test function for debugging
int main(void)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Test_ContactStore_Destroy();
	Test_Contact_Destroy();
	Test_RBT_Destroy();
#endif
	/*ContactStore_RBT* pResult = ContactStore_RBT_Create();
	ContactStore_RBT* pLeft = ContactStore_RBT_Create();
	ContactStore_RBT* pRight = ContactStore_RBT_Create();

	Contact* c1 = Contact_Create(10, "Alice", "010-0000-1111");
	Contact* c2 = Contact_Create(20, "Betty", "010-0000-2222");
	Contact* c3 = Contact_Create(25, "Edward", "010-0000-2222");
	Contact* c4 = Contact_Create(30, "Kevin", "010-0000-3333");

	ContactStore_RBT_Insert(pLeft, c1);
	ContactStore_RBT_Insert(pLeft, c2);
	ContactStore_RBT_Insert(pRight, c3);
	ContactStore_RBT_Insert(pRight, c4);

	ContactStore_RBT_CombineByOp(pResult, pLeft, pRight, "OR");
	UI_PrintRBT(pResult);

	Contact_Destroy(c1);
	Contact_Destroy(c2);
	Contact_Destroy(c3);
	Contact_Destroy(c4);
	ContactStore_RBT_Destroy(pResult);
	ContactStore_RBT_Destroy(pLeft);
	ContactStore_RBT_Destroy(pRight);*/
	Test_RBT_Insert();
	return 0;
}