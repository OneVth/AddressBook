#pragma once

#define UI_FUNC_COUNT 6
#define RECORDS_PER_PAGE 10

typedef enum { EXIT, PRINT, INSERT, DELETE, SEARCH, EDIT } OPTION;

OPTION PrintMenu(void);		// event loop

int GetName(char* buffer);
int GetPhone(char* buffer);
int GetAge(int* age);

int UI_ExitMenu(const char* PATH);
int UI_PrintAll(const char* PATH);
int UI_InsertNode(const char* PATH);
int UI_DeleteNode(const char* PATH);
int UI_Search(const char* PATH);
int UI_EditNode(const char* PATH);

int GetSearchString(char* buffer);
int ConvertInputToSearchString(const char* str, int* age, char* name, char* phone);
int ParseSearchInput(const char* input, char temp1[], char temp2[], char op[]);
int SearchNode(const char* input, const char* PATH);

void PrintList(LIST* pL);