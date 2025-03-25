/* INCLUDES	*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "common.h"
#include "control.h"
#include "ui.h"

/* MAIN FUNCTION **************************************************/
int main(void)
{
	int (*pfMenu[UI_FUNC_COUNT])(const char*) = {
		UI_ExitMenu, 
		UI_PrintAll,
		UI_InsertNode, 
		UI_DeleteNode, 
		UI_Search, 
		UI_EditNode 
	};

	OPTION option = PrintMenu();
	do
	{
		system("cls");
		pfMenu[option](FILE_PATH);
		_getch();
	} while ((option = PrintMenu()) != EXIT);

	return 0;
}