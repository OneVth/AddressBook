#pragma once

#define FILE_PATH_TEST "test.dat"

// Util functions *******************************************

void Test_Str_IsAllDigit(void);
void Test_Str_IsAllAlpha(void);
void Test_Str_IsPhoneFormat(void);

// These below functions are utility helpers used primarily by UI input parsing.

void Test_ClassifyToken(void);
void Test_SplitSearchExpression(void);

// Data structure functions *******************************************

void Test_List_Init(void);
void Test_List_IsEmpty(void);
void Test_List_HasPhone(void);
void Test_List_Release(void);
void Test_List_InsertAtEnd(void);
void Test_List_InsertAtBeg(void);
void Test_List_DeleteAtEnd(void);
void Test_List_DeleteAtBeg(void);
void Test_List_DeleteByPhone(void);
void Test_List_CombineByOp(void);

// Control functions *******************************************

int CreateTestDataFile(void);
void Test_CreateTestDataFile(void);
void Test_LoadRecordsFromFileByPhone(void);

// ********************************************************************

void Test_CreateFile(void);
void Test_ReadFile(void);
void Test_ListFunctions(void);
void Test_FileIOFunctions(void);
void Test_SearchFunctions(void);
void Test_EditFunctions(void);
void Test_UIFunctions(void);