// Header file for test module.

#pragma once

#define FILE_PATH_TEST L".\\Test\\test.dat"

void RunAllTests(void);
void Test_ListFunctions(void);
void Test_UtilFunctions(void);
void Test_ControlFunctions(void);

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

int CreateTestDataFile_Minimal(void);
void Test_CreateTestDataFile_Minimal(void);
void Test_LoadRecordsFromFileByPhone(void);
void Test_SaveListToFile(void);
void Test_LoadRecordsFromFileByName(void);
void Test_LoadRecordsFromFileByAge(void);
void Test_EditRecordPhoneFromFile(void);
void Test_EditRecordAgeFromFile(void);
void Test_EditRecordNameFromFile(void);
void Test_DeleteRecordByPhoneFromFile(void);
void Test_SearchRecordsFromFile(void);

int CreateTestDataFile_CS(void);
void Test_CreateTestDataFile_CS(void);
void Test_ContactStore_Take(void);
void Test_LoadRecordsFromFileByPhone_CS(void);
void Test_SaveListToFile_CS(void);
void Test_LoadRecordsFromFileByName_CS(void);
void Test_LoadRecordsFromFileByAge_CS(void);
void Test_EditRecordAgeFromFile_CS(void);
void Test_EditRecordNameFromFile_CS(void);
void Test_EditRecordPhoneFromFile_CS(void);
void Test_DeleteRecordFromFileByPhone_CS(void);

// ContactStore functions *******************************************

void Test_Contact_Destroy(void);
void Test_ContactLifecycle(void);
void Test_Contact_SetAge(void);
void Test_Contact_SetName(void);
void Test_Contact_SetPhone(void);
void Test_ContactStore_IsEmpty(void);
void Test_ContactStore_HasPhone(void);
void Test_ContactStore_Destroy(void);
void Test_ContactStore_Add(void);
void Test_ContactStore_CombineByOp(void);