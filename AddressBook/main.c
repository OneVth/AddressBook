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
#include "contact_store.h"


/* MAIN FUNCTION **************************************************/
int main(void)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Test_ContactStore_Destroy();
#endif
	ContactStore* pLeftStore = ContactStore_Create();
	ContactStore* pRightStore = ContactStore_Create();
	ContactStore* pResultStore = ContactStore_Create();

	ContactStore_AddToEnd(pLeftStore, &(Contact){ 10, "Alice", "010-0000-1111" });
	ContactStore_AddToEnd(pLeftStore, &(Contact){ 20, "Betty", "010-0000-2222" });
	
	ContactStore_AddToEnd(pRightStore, &(Contact){ 20, "Betty", "010-0000-2222" });
	ContactStore_AddToEnd(pRightStore, &(Contact){ 30, "John", "010-0000-3333" });

	ContactStore_CombineByOp(pResultStore, pLeftStore, pRightStore, "OR");
	ContactStore_PrintAll(pResultStore);

	ContactStore_Destroy(pResultStore);
	pResultStore = ContactStore_Create();

	ContactStore_CombineByOp(pResultStore, pLeftStore, pRightStore, "AND");
	ContactStore_PrintAll(pResultStore);

	ContactStore_Destroy(pResultStore);
	ContactStore_Destroy(pLeftStore);
	ContactStore_Destroy(pRightStore);
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