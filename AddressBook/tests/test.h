// Header file for test module.

#pragma once

#define FILE_PATH_TEST L".\\tests\\test.dat"

void Test_UtilFunctions(void);

// Util functions *******************************************

void Test_Str_IsAllDigit(void);
void Test_Str_IsAllAlpha(void);
void Test_Str_IsPhoneFormat(void);

// These below functions are utility helpers used primarily by UI input parsing.

void Test_ClassifyToken(void);
void Test_SplitSearchExpression(void);

// Control functions *******************************************

int CreateTestDataFile(void);
void Test_CreateTestDataFile(void);
void Test_ContactStore_Take(void);
void Test_LoadRecordsFromFileByPhone(void);
void Test_SaveListToFile(void);
void Test_LoadRecordsFromFileByName(void);
void Test_LoadRecordsFromFileByAge(void);
void Test_EditRecordAgeFromFile(void);
void Test_EditRecordNameFromFile(void);
void Test_EditRecordPhoneFromFile(void);
void Test_DeleteRecordFromFileByPhone(void);
void Test_SearchRecordsFromFile(void);

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

void Test_ContactStore_RBT_IsEmpty(void);
void Test_RBT_Create(void);
void Test_RBT_Destroy(void);
void Test_RBT_Insert(void);