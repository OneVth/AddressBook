#pragma once
#include <Windows.h>
#include "common.h"

#define UI_FUNC_COUNT 6
#define RECORDS_PER_PAGE 10

typedef enum { 
	MENU_EXIT, MENU_PRINT, MENU_INSERT, MENU_DELETE, MENU_SEARCH, MENU_EDIT 
} OPTION;


// *******************************************************************
// UI input functions
// *******************************************************************

/// <summary>
/// Gets inputs for inserting a new record.
/// </summary>
/// <param name="name">Buffer to store the name.</param>
/// <param name="age">Pointer to store the age.</param>
/// <param name="phone">Buffer to store the phone number.</param>
/// <returns>1 if all inputs are valid; 0 otherwise.</returns>
int UI_GetInsertInfo(char* name, int* age, char* phone);

/// <summary>
/// Gets a valid name input from the user.
/// </summary>
/// <returns>1 after a successful input; 0 otherwise</returns>
int UI_GetName(char* buffer);

// Header file for ui module.

/// <summary>
/// Gets a valid phone number from the user and formats it without hypens.
/// </summary>
/// <returns>1 if input is valid; 0 otherwise.</returns>
int UI_GetPhone(char* buffer);

/// <summary>
/// Gets a valid age from the user and ensures it is within the allowed range.
/// </summary>
/// <returns>1 if the age is valid; 0 otherwise.</returns>
int UI_GetAge(int* age);

/// <summary>
/// 
/// </summary>
/// <param name="buffer"></param>
/// <returns></returns>
int UI_GetSearchString(char* buffer);

// *******************************************************************
// UI output functions
// *******************************************************************

void UI_PrintRBT(ContactStore_RBT* store);
void UI_PrintList(ContactStore* store);

// *******************************************************************
// UI event loop functions
// *******************************************************************

OPTION PrintMenu(void);		// event loop
int UI_ExitMenu(LPCWSTR path);

int UI_PrintAll(LPCWSTR path);

/// <summary>
/// Insert a new node into file after getting user input.
/// </summary>
/// <param name="PATH">The file path to insert the node into.</param>
/// <returns>1 if insertion successful; 0 otherwise.</returns>
int UI_InsertNode(LPCWSTR path);

int UI_DeleteNode(LPCWSTR path);

int UI_Search(LPCWSTR path);

int UI_EditNode(LPCWSTR path);
