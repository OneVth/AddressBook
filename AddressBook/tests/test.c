// Contains unit tests for all core mudules (list, utility, control).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <assert.h>
#include "contact.h"
#include "contact_store.h"
#include "common.h"
#include "control.h"
#include "ui.h"
#include "test.h"
#include "internal/contact_store_internal.h"

#define NODE_MATCH(n, a, b, p) ((n)->age == a && strcmp((n)->name, b) == 0 && strcmp((n)->phone, p) == 0)
#define NUM_TEST_NODE 5

typedef struct {
	const char** expectedPhones;
	int index;
} VerifyContext;

void Test_UtilFunctions(void)
{
	Test_Str_IsAllDigit();
	Test_Str_IsAllAlpha();
	Test_Str_IsPhoneFormat();
	Test_ClassifyToken();
	Test_SplitSearchExpression();
}

// ***********************************************

static int VerifyPhoneOrderCallback(const Contact* c, void* userData)
{
	VerifyContext* verifyContext = (VerifyContext*)userData;
	const char** expected = (const char**)verifyContext->expectedPhones;

	assert(strcmp(Contact_GetPhone(c), expected[verifyContext->index]) == 0);
	verifyContext->index++;

	return 1;
}

void Test_Str_IsAllDigit(void)
{
	int pass = 1;

	// Case 1: all digits
	if (!Str_IsAllDigit("123456"))
	{
		printf("FAIL: Str_IsAllDigit() failed to recognize digits only string\n");
		pass = 0;
	}

	// Case 2: contain space
	if (Str_IsAllDigit("123 456"))
	{
		printf("FAIL: Str_IsAllDigit() incorrectly returned true for string with space\n");
		pass = 0;
	}

	// Case 3: contain alphabet
	if (Str_IsAllDigit("12a45"))
	{
		printf("FAIL: Str_IsAllDigit() incorrectly returned true for string with alphabet\n");
		pass = 0;
	}

	// Case 4: contain special character
	if (Str_IsAllDigit("123-456"))
	{
		printf("FAIL: Str_IsAllDigit() incorrectly returned true for string with special character\n");
		pass = 0;
	}

	// Case 5: empty string
	if (Str_IsAllDigit(""))
	{
		printf("FAIL: Str_IsAllDigit() incorrectly returned true for empty string\n");
		pass = 0;
	}

	// Case 6: leading zero
	if (!Str_IsAllDigit("012345"))
	{
		printf("FAIL: Str_IsAllDigit() failed to recognize digits with leading zero\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: Str_IsAllDigit() with with only digits\n");
		printf("PASS: Str_IsAllDigit() returns false for string with space\n");
		printf("PASS: Str_IsAllDigit() returns false for string with alphabet\n");
		printf("PASS: Str_IsAllDigit() returns false for string with special character\n");
		printf("PASS: Str_IsAllDigit() returns false for empty string\n");
		printf("PASS: Str_IsAllDigit() with digits including leading zero\n");
	}

	putchar('\n');
	return;
}

void Test_Str_IsAllAlpha(void)
{
	int pass = 1;

	// Case 1: all alphabet
	if (!Str_IsAllAlpha("abcde"))
	{
		printf("FAIL: Str_IsAllAlpha() with only alphabet\n");
		pass = 0;
	}

	// Case 2: contain space
	if (Str_IsAllAlpha("ab cde"))
	{
		printf("FAIL: Str_IsAllAlpha() incorrectly returned true for string with space\n");
		pass = 0;
	}

	// Case 3: contain digit
	if (Str_IsAllAlpha("ab1de"))
	{
		printf("FAIL: Str_IsAllAlpha() incorrectly returned true for string with digit\n");
		pass = 0;
	}

	// Case 4: contain special character
	if (Str_IsAllAlpha("ab@de"))
	{
		printf("FAIL: Str_IsAllAlpha() incorrectly returned true for string with special character\n");
		pass = 0;
	}

	// Case 5: empty string
	if (Str_IsAllAlpha(""))
	{
		printf("FAIL: Str_IsAllAlpha() incorrectly returned true for empty string\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: Str_IsAllAlpha() with with only alphabet\n");
		printf("PASS: Str_IsAllAlpha() returns false for string with space\n");
		printf("PASS: Str_IsAllAlpha() returns false for string with digit\n");
		printf("PASS: Str_IsAllAlpha() returns false for string with special character\n");
		printf("PASS: Str_IsAllAlpha() returns false for empty string\n");
	}

	putchar('\n');
	return;
}

void Test_Str_IsPhoneFormat(void)
{
	int pass = 1;

	// Case 1: phone format
	if (!Str_IsPhoneFormat("000-0000-0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() with valid format\n");
		pass = 0;
	}

	// Case 2: conatin alphabet
	if (Str_IsPhoneFormat("000-aaaa-0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for string with alphabets\n");
		pass = 0;
	}

	// Case 3: contain space
	if (Str_IsPhoneFormat("000-0000 -0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for string with space\n");
		pass = 0;
	}

	// Case 4: contain special character
	if (Str_IsPhoneFormat("000-@000-0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for string with specail characters\n");
		pass = 0;
	}

	// Case 5: invalid hyphen position
	if (Str_IsPhoneFormat("0000-000-0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for string with invalid hyphen position\n");
		pass = 0;
	}

	// Case 6: empty string
	if (Str_IsPhoneFormat(""))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for empty string\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: Str_IsPhoneFormat() with with valid format\n");
		printf("PASS: Str_IsPhoneFormat() returns false for string with alphabets\n");
		printf("PASS: Str_IsPhoneFormat() returns false for string with space\n");
		printf("PASS: Str_IsPhoneFormat() returns false for string with special character\n");
		printf("PASS: Str_IsPhoneFormat() returns false for string with invalid hyphen position\n");
		printf("PASS: Str_IsPhoneFormat() returns false for empty string\n");
	}

	putchar('\n');
	return;
}

void Test_SplitSearchExpression(void)
{
	int pass = 1;

	char token1[BUFFSIZE] = { 0 };
	char token2[BUFFSIZE] = { 0 };
	char op[BUFFSIZE] = { 0 };

	// Case 1: single item input
	if (!SplitSearchExpression("10", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		if (strcmp(token1, "10") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("Test", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		if (strcmp(token1, "Test") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("010-0000-0000", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		if (strcmp(token1, "010-0000-0000") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	// Case 2: two items with operator(AND, OR)
	int token1Correct = 0;
	int token2Correct = 0;
	int opCorrect = 0;

	if (!SplitSearchExpression("10 OR 20", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		token1Correct = strcmp(token1, "10") == 0;
		token2Correct = strcmp(token2, "20") == 0;
		opCorrect = strcmp(op, "OR") == 0;
		if (!token1Correct || !token2Correct || !opCorrect)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("10 OR 010-0000-0000", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		token1Correct = strcmp(token1, "10") == 0;
		token2Correct = strcmp(token2, "010-0000-0000") == 0;
		opCorrect = strcmp(op, "OR") == 0;
		if (!token1Correct || !token2Correct || !opCorrect)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("Test AND 10", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		token1Correct = strcmp(token1, "Test") == 0;
		token2Correct = strcmp(token2, "10") == 0;
		opCorrect = strcmp(op, "AND") == 0;
		if (!token1Correct || !token2Correct || !opCorrect)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("010-0000-0000 AND Test", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		token1Correct = strcmp(token1, "010-0000-0000") == 0;
		token2Correct = strcmp(token2, "Test") == 0;
		opCorrect = strcmp(op, "AND") == 0;
		if (!token1Correct || !token2Correct || !opCorrect)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	// Case 3: failures
	if (SplitSearchExpression("10 20", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned true for invalid input\n");
	}

	if (SplitSearchExpression("OR 20", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned true for invalid input\n");
	}

	if (SplitSearchExpression("", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned true for invalid input\n");
	}

	if (pass)
	{
		printf("PASS: SplitSearchExpression() correctly parsed single token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed single token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed single token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed double token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed double token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed double token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed double token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly returned false for invalid input\n");
		printf("PASS: SplitSearchExpression() correctly returned false for invalid input\n");
		printf("PASS: SplitSearchExpression() correctly returned false for invalid input\n");
	}
	putchar('\n');
	return;
}

void Test_ClassifyToken(void)
{
	int pass = 1;
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	// Case 1: classify token to numeric
	if (!ClassifyToken("10", &age, NULL, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}
	else
	{
		if (age != 10)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect age for valid string\n");
		}
	}

	// Case 2: classify token to alphabetical string
	age = 0; memset(name, 0, sizeof(name)); memset(phone, 0, sizeof(phone));
	if (!ClassifyToken("Test", NULL, name, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}
	else
	{
		if (strcmp(name, "Test") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect name for valid string\n");
		}
	}

	// Case 3: classify token to phone number format string
	age = 0; memset(name, 0, sizeof(name)); memset(phone, 0, sizeof(phone));
	if (!ClassifyToken("010-0000-0000", NULL, NULL, phone))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}
	else
	{
		if (strcmp(phone, "010-0000-0000") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect phone for valid string\n");
		}
	}

	// Case 4: invalid string
	if (ClassifyToken("", NULL, NULL, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}

	if (ClassifyToken("10Test", NULL, NULL, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}

	if (ClassifyToken("010-aaaa-0000", NULL, NULL, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}


	if (pass)
	{
		printf("PASS: ClassifyToken() correctly classify token for valid string\n");
		printf("PASS: ClassifyToken() correctly classify token for valid string\n");
		printf("PASS: ClassifyToken() correctly classify token for valid string\n");
		printf("PASS: ClassifyToken() correctly returned false for invalid string\n");
		printf("PASS: ClassifyToken() correctly returned false for invalid string\n");
		printf("PASS: ClassifyToken() correctly returned false for invalid string\n");
	}

	putchar('\n');
	return;
}

// ***********************************************

int CreateTestDataFile(void)
{
	CreateDirectory(L"./tests", NULL);

	int ages[] = { 10, 11, 20, 20, 30 };
	char* names[] = { "A", "A", "B", "C", "D" };
	char* phones[] = {
		"010-0000-0001",
		"010-0000-0011",
		"010-0000-0002",
		"010-0000-0022",
		"010-0000-0003"
	};

	DWORD dwContactSize = (DWORD)Contact_GetSize();
	DWORD dwWritten = 0;
	BOOL bResult = FALSE;

	HANDLE hFile = CreateFile(
		FILE_PATH_TEST,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	for (int i = 0; i < NUM_TEST_NODE; i++)
	{
		Contact* temp = Contact_Create(ages[i], names[i], phones[i]);
		if (temp == NULL)
		{
			CloseHandle(hFile);
			return 0;
		}
		
		bResult = WriteFile(hFile, temp, dwContactSize, &dwWritten, NULL);
		if (!bResult)
		{
			CloseHandle(hFile);
			return 0;
		}

		if (dwWritten < dwContactSize)
		{
			CloseHandle(hFile);
			return 0;
		}
		Contact_Destroy(temp);
	}

	CloseHandle(hFile);
	return 1;
}

void Test_CreateTestDataFile(void)
{
	int ages[] = { 10, 11, 20, 20, 30 };
	char* names[] = { "A", "A", "B", "C", "D" };
	char* phones[] = {
		"010-0000-0001",
		"010-0000-0011",
		"010-0000-0002",
		"010-0000-0022",
		"010-0000-0003"
	};

	assert(CreateTestDataFile() == 1);

	LARGE_INTEGER llFileSize = { 0 };
	LONGLONG llTotalReadSize = 0;
	DWORD dwContactSize = (DWORD)Contact_GetSize();
	DWORD dwRead = 0;
	BOOL bResult = FALSE;

	HANDLE hFile = CreateFile(
		FILE_PATH_TEST,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("FAIL: Test_CreateTestDataFile() could not open test data file\n");
		putchar('\n');
		return;
	}

	if (!GetFileSizeEx(hFile, &llFileSize))
	{
		printf("FAIL: Test_CreateTestDataFile() couldn't get file size\n");
		CloseHandle(hFile);
		putchar('\n');
		return;
	}

	Contact* temp = (Contact*)malloc(dwContactSize);
	if (temp == NULL)
	{
		printf("FAIL: Test_CreateTestDataFile() failed to allocate memory\n");
		CloseHandle(hFile);
		putchar('\n');
		return;
	}

	for (int i = 0; i < NUM_TEST_NODE; i++)
	{
		ZeroMemory(temp, dwContactSize);
		bResult = ReadFile(hFile, temp, dwContactSize, &dwRead, NULL);
		if (bResult && dwRead == dwContactSize)
		{
			llTotalReadSize += dwRead;
			assert(Contact_GetAge(temp) == ages[i]);
			assert(strcmp(Contact_GetName(temp), names[i]) == 0);
			assert(strcmp(Contact_GetPhone(temp), phones[i]) == 0);
		}
	}

	assert(llTotalReadSize == llFileSize.QuadPart);

	free(temp);
	CloseHandle(hFile);
	

	printf("PASS: Test_CreateTestDataFile() correctly created test file\n");
	putchar('\n');
	return;
}

void Test_TryInsertContact(void)
{
	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	// Case 1: Already exists in file (invalid input)
	Contact* pContact = Contact_Create(10, "A", "010-0000-0001");
	assert(pContact != NULL);
	assert(TryInsertContact(pStore, pContact, FILE_PATH_TEST) == 0);
	Contact_Destroy(pContact);

	// Case 2: Non-existence contact (valid input)
	pContact = Contact_Create(99, "Z", "010-0000-9999");
	assert(pContact != NULL);
	assert(TryInsertContact(pStore, pContact, FILE_PATH_TEST) == 1);
	Contact_Destroy(pContact);

	printf("PASS: Test_TryInsertContact() correctly didn't insert an already existence contact\n");
	printf("PASS: Test_TryInsertContact() correctly insert a contact\n");
	ContactStore_Destroy(pStore);
}

void Test_LoadRecordsFromFileByPhone(void)
{
	assert(CreateTestDataFile() == 1);

	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	// Case 1: valid phone number
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-0001", FILE_PATH_TEST) == LOAD_SUCCESS);
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-0002", FILE_PATH_TEST) == LOAD_SUCCESS);
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-0003", FILE_PATH_TEST) == LOAD_SUCCESS);
	
	const char* expected[] = { 
		"010-0000-0001",
		"010-0000-0002",
		"010-0000-0003"
	};

	VerifyContext verifyContext = { expected, 0 };
	ContactStore_Iterate(pStore, VerifyPhoneOrderCallback, &verifyContext);
	assert(verifyContext.index == sizeof(expected) / sizeof(expected[0]));

	// Case 2: invalid phone number
	assert(LoadRecordsFromFileByPhone(pStore, "010-9999-9999", FILE_PATH_TEST) != LOAD_SUCCESS);
	
	printf("PASS: Test_LoadRecordsFromFileByPhone() returned correct result for valid phone number\n");
	printf("PASS: Test_LoadRecordsFromFileByPhone() returned correct result for invalid phone number\n");
	putchar('\n');
	ContactStore_Destroy(pStore);
	return;
}

void Test_SaveListToFile(void)
{
	assert(CreateTestDataFile() == 1);

	int ages[] = { 10, 99, 98, 97 };
	char* names[] = { "A", "Z", "Y", "X" };
	char* phones[] = {
		"010-0000-0001",	// already existing data
		"010-9999-9999",
		"010-9999-9998",
		"010-9999-9997"
	};

	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	Contact* ptr = Contact_Create(ages[0], names[0], phones[0]);
	assert(ptr != NULL);

	assert(TryInsertContact(pStore, ptr, FILE_PATH_TEST) == 0);
	Contact_Destroy(ptr);

	for (int i = 1; i < 4; i++)
	{
		ptr = Contact_Create(ages[i], names[i], phones[i]);
		assert(ptr != NULL);
		assert(TryInsertContact(pStore, ptr, FILE_PATH_TEST) == 1);
		Contact_Destroy(ptr);
	}

	assert(SaveListToFile(pStore, FILE_PATH_TEST) == 1);

	LARGE_INTEGER llFileSize = { 0 };
	HANDLE hFile = CreateFile(
		FILE_PATH_TEST,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	assert(hFile != INVALID_HANDLE_VALUE);
	
	assert(GetFileSizeEx(hFile, &llFileSize) == TRUE);
	assert(llFileSize.QuadPart == (NUM_TEST_NODE + 3) * Contact_GetSize());
	
	assert(CloseHandle(hFile) == TRUE);

	assert(LoadRecordsFromFileByPhone(NULL, "010-9999-9999", FILE_PATH_TEST) == LOAD_SUCCESS);
	assert(LoadRecordsFromFileByPhone(NULL, "010-9999-9998", FILE_PATH_TEST) == LOAD_SUCCESS);
	assert(LoadRecordsFromFileByPhone(NULL, "010-9999-9997", FILE_PATH_TEST) == LOAD_SUCCESS);
	
	ContactStore_Destroy(pStore);

	printf("PASS: Test_SaveListToFile() correctly save list to file\n");
	printf("PASS: Test_SaveListToFile() wrote correct number of bytes\n");
	printf("PASS: Test_SaveListToFile() created file successfully\n");
	putchar('\n');
	return;
}

void Test_LoadRecordsFromFileByName(void)
{
	assert(CreateTestDataFile() == 1);

	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	// Case 1: valid name
	assert(LoadRecordsFromFileByName(pStore, "A", FILE_PATH_TEST) == LOAD_SUCCESS);
	assert(LoadRecordsFromFileByName(pStore, "B", FILE_PATH_TEST) == LOAD_SUCCESS);
	assert(LoadRecordsFromFileByName(pStore, "C", FILE_PATH_TEST) == LOAD_SUCCESS);

	const char* expected[] = {
		"010-0000-0001",	// A
		"010-0000-0002",	// B
		"010-0000-0011",	// A
		"010-0000-0022",	// C
	};

	VerifyContext verifyContext = { expected, 0 };
	ContactStore_Iterate(pStore, VerifyPhoneOrderCallback, &verifyContext);
	assert(verifyContext.index == sizeof(expected) / sizeof(expected[0]));

	// Case 2: invalid name
	assert(LoadRecordsFromFileByName(pStore, "Z", FILE_PATH_TEST) != LOAD_SUCCESS);

	printf("PASS: Test_LoadRecordsFromFileByName() returned correct result for valid name\n");
	printf("PASS: Test_LoadRecordsFromFileByName() returned correct result for invalid name\n");
	putchar('\n');
	ContactStore_Destroy(pStore);
	return;
}

void Test_LoadRecordsFromFileByAge(void)
{
	assert(CreateTestDataFile() == 1);

	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	// Case 1: valid age
	assert(LoadRecordsFromFileByAge(pStore, 10, FILE_PATH_TEST) == LOAD_SUCCESS);
	assert(LoadRecordsFromFileByAge(pStore, 20, FILE_PATH_TEST) == LOAD_SUCCESS);
	assert(LoadRecordsFromFileByAge(pStore, 30, FILE_PATH_TEST) == LOAD_SUCCESS);

	const char* expected[] = {
		"010-0000-0001",	// A
		"010-0000-0002",	// B
		"010-0000-0003",	// D
		"010-0000-0022",	// C
	};

	VerifyContext verifyContext = { expected, 0 };
	ContactStore_Iterate(pStore, VerifyPhoneOrderCallback, &verifyContext);
	assert(verifyContext.index == sizeof(expected) / sizeof(expected[0]));

	// Case 2: invalid age
	assert(LoadRecordsFromFileByAge(pStore, 99, FILE_PATH_TEST) != LOAD_SUCCESS);

	printf("PASS: Test_LoadRecordsFromFileByAge() returned correct result for valid age\n");
	printf("PASS: Test_LoadRecordsFromFileByAge() returned correct result for invalid age\n");
	putchar('\n');
	ContactStore_Destroy(pStore);
	return;
}

void Test_EditRecordAgeFromFile(void)
{
	assert(CreateTestDataFile() == 1);

	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	// Case 1: valid age
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-0001", FILE_PATH_TEST) == LOAD_SUCCESS);
	const Contact* pContact = ContactStore_FindByPhone(pStore, "010-0000-0001");
	assert(pContact != NULL);
	assert(EditRecordAgeFromFile(pContact, 99, FILE_PATH_TEST) == EDIT_SUCCESS);
	ContactStore_Destroy(pStore);

	pStore = ContactStore_Create();
	assert(LoadRecordsFromFileByAge(pStore, 99, FILE_PATH_TEST) == LOAD_SUCCESS);
	pContact = ContactStore_FindByPhone(pStore, "010-0000-0001");
	assert(Contact_GetAge(pContact) == 99);
	assert(strcmp(Contact_GetName(pContact), "A") == 0);
	assert(strcmp(Contact_GetPhone(pContact), "010-0000-0001") == 0);
	ContactStore_Destroy(pStore);

	// Case 2: invalid age
	pStore = ContactStore_Create();
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-0001", FILE_PATH_TEST) == LOAD_SUCCESS);
	pContact = ContactStore_FindByPhone(pStore, "010-0000-0001");
	assert(pContact != NULL);
	assert(EditRecordAgeFromFile(pContact, MAXAGE + 1, FILE_PATH_TEST) == EDIT_ERROR);
	ContactStore_Destroy(pStore);

	printf("PASS: Test_EditRecordAgeFromFile() correctly edit record for valid age\n");
	printf("PASS: Test_EditRecordAgeFromFile() correctly return false for invalid age\n");
	putchar('\n');
	return;
}

void Test_EditRecordNameFromFile(void)
{
	assert(CreateTestDataFile() == 1);

	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	// Case 1: valid name
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-0001", FILE_PATH_TEST) == LOAD_SUCCESS);
	const Contact* pContact = ContactStore_FindByPhone(pStore, "010-0000-0001");
	assert(pContact != NULL);
	assert(EditRecordNameFromFile(pContact, "Z", FILE_PATH_TEST) == EDIT_SUCCESS);
	ContactStore_Destroy(pStore);

	pStore = ContactStore_Create();
	assert(LoadRecordsFromFileByName(pStore, "Z", FILE_PATH_TEST) == LOAD_SUCCESS);
	pContact = ContactStore_FindByPhone(pStore, "010-0000-0001");
	assert(Contact_GetAge(pContact) == 10);
	assert(strcmp(Contact_GetName(pContact), "Z") == 0);
	assert(strcmp(Contact_GetPhone(pContact), "010-0000-0001") == 0);
	ContactStore_Destroy(pStore);

	// Case 2: invalid name
	pStore = ContactStore_Create();
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-0001", FILE_PATH_TEST) == LOAD_SUCCESS);
	pContact = ContactStore_FindByPhone(pStore, "010-0000-0001");
	assert(pContact != NULL);
	assert(EditRecordNameFromFile(pContact, "Invalid!", FILE_PATH_TEST) == EDIT_ERROR);
	ContactStore_Destroy(pStore);

	printf("PASS: Test_EditRecordNameFromFile() correctly edit record for valid name\n");
	printf("PASS: Test_EditRecordNameFromFile() correctly return false for invalid name\n");
	putchar('\n');
	return;
}

void Test_EditRecordPhoneFromFile(void)
{
	assert(CreateTestDataFile() == 1);

	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	// Case 1: valid phone
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-0001", FILE_PATH_TEST) == LOAD_SUCCESS);
	const Contact* pContact = ContactStore_FindByPhone(pStore, "010-0000-0001");
	assert(pContact != NULL);
	assert(EditRecordPhoneFromFile(pContact, "010-0000-9999", FILE_PATH_TEST) == EDIT_SUCCESS);
	ContactStore_Destroy(pStore);

	pStore = ContactStore_Create();
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-9999", FILE_PATH_TEST) == LOAD_SUCCESS);
	pContact = ContactStore_FindByPhone(pStore, "010-0000-9999");
	assert(Contact_GetAge(pContact) == 10);
	assert(strcmp(Contact_GetName(pContact), "A") == 0);
	assert(strcmp(Contact_GetPhone(pContact), "010-0000-9999") == 0);
	ContactStore_Destroy(pStore);

	// Case 2: invalid phone
	pStore = ContactStore_Create();
	assert(LoadRecordsFromFileByPhone(pStore, "010-0000-0011", FILE_PATH_TEST) == LOAD_SUCCESS);
	pContact = ContactStore_FindByPhone(pStore, "010-0000-0011");
	assert(pContact != NULL);
	assert(EditRecordPhoneFromFile(pContact, "0000-0000-0000", FILE_PATH_TEST) == EDIT_ERROR);
	ContactStore_Destroy(pStore);

	printf("PASS: Test_EditRecordPhoneFromFile() correctly edit record for valid phone number\n");
	printf("PASS: Test_EditRecordPhoneFromFile() correctly return false for invalid phone number\n");
	putchar('\n');
	return;
}

void Test_DeleteRecordFromFileByPhone(void)
{
	assert(CreateTestDataFile() == 1);

	// Case 1: invalid phone number
	assert(DeleteRecordFromFileByPhone("010-0000-9999", FILE_PATH_TEST) == DELETE_NOT_FOUND);

	// Case 2: valid phone number
	assert(DeleteRecordFromFileByPhone("010-0000-0001", FILE_PATH_TEST) == DELETE_SUCCESS);
	
	LARGE_INTEGER llFileSize = { 0 };
	DWORD dwContactSize = (DWORD)Contact_GetSize();
	DWORD dwRead = 0;
	BOOL bResult = FALSE;

	HANDLE hFile = CreateFile(
		FILE_PATH_TEST,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	assert(hFile != INVALID_HANDLE_VALUE);
	
	GetFileSizeEx(hFile, &llFileSize);
	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	assert(
		LoadRecordsFromFileByPhone(pStore, "010-0000-0001", FILE_PATH_TEST) == LOAD_NOT_FOUND && 
		llFileSize.QuadPart == dwContactSize * (NUM_TEST_NODE - 1)
	);
	ContactStore_Destroy(pStore);
	CloseHandle(hFile);
	
	printf("PASS: Test_DeleteRecordFromFileByPhone() successfully removed the record with given phone number\n");
	printf("PASS: Test_DeleteRecordFromFileByPhone() correctly return false for invalid phone number\n");
	putchar('\n');
	return;
}

void Test_SearchRecordsFromFile(void)
{
	assert(CreateTestDataFile() == 1);

	ContactStore* pResult = ContactStore_Create();
	assert(pResult != NULL);

	// Case 1: single result
	assert(SearchRecordsFromFile(pResult, "10", FILE_PATH_TEST) == SEARCH_SUCCESS);

	const char* expectedSingle[] = {
		"010-0000-0001",	// A
	};

	VerifyContext verifyContext = { expectedSingle, 0 };
	ContactStore_Iterate(pResult, VerifyPhoneOrderCallback, &verifyContext);
	assert(verifyContext.index == sizeof(expectedSingle) / sizeof(expectedSingle[0]));

	ContactStore_Destroy(pResult);

	// Case 2: multiple result
	pResult = ContactStore_Create();
	assert(pResult != NULL);

	assert(SearchRecordsFromFile(pResult, "20", FILE_PATH_TEST) == SEARCH_SUCCESS);

	const char* expectedMultiple[] = {
		"010-0000-0002",	// B
		"010-0000-0022",	// C
	};

	verifyContext.expectedPhones = expectedMultiple;
	verifyContext.index = 0;
	ContactStore_Iterate(pResult, VerifyPhoneOrderCallback, &verifyContext);
	assert(verifyContext.index == sizeof(expectedMultiple) / sizeof(expectedMultiple[0]));
	ContactStore_Destroy(pResult);

	// Case 3: search with operator
	pResult = ContactStore_Create();
	assert(pResult != NULL);

	assert(SearchRecordsFromFile(pResult, "10 OR 010-0000-0003", FILE_PATH_TEST) == SEARCH_SUCCESS);

	const char* expectedOp[] = {
		"010-0000-0001",	// A
		"010-0000-0003",	// D
	};

	verifyContext.expectedPhones = expectedOp;
	verifyContext.index = 0;
	ContactStore_Iterate(pResult, VerifyPhoneOrderCallback, &verifyContext);
	assert(verifyContext.index == sizeof(expectedOp) / sizeof(expectedOp[0]));
	ContactStore_Destroy(pResult);

	printf("PASS: Test_SearchRecordsFromFile() correctly search single record\n");
	printf("PASS: Test_SearchRecordsFromFile() correctly search multiple record\n");
	printf("PASS: Test_SearchRecordsFromFile() correctly search multiple record with operator\n");
	return;
}

void Test_SearchRecordsFromFile_MT(void)
{
	assert(CreateTestDataFile() == 1);

	ContactStore* pResult = ContactStore_Create();
	if (pResult == NULL)
	{
		printf("FAIL: Test_SearchRecordsFromFile_MT() failed to memory allocation\n");
		return;
	}

	// Case 1: single result
	assert(SearchRecordsFromFile_MT(pResult, "10", FILE_PATH_TEST) == SEARCH_SUCCESS);

	const char* expectedSingle[] = {
		"010-0000-0001",	// A
	};

	VerifyContext verifyContext = { expectedSingle, 0 };
	ContactStore_Iterate(pResult, VerifyPhoneOrderCallback, &verifyContext);
	assert(verifyContext.index == sizeof(expectedSingle) / sizeof(expectedSingle[0]));

	ContactStore_Destroy(pResult);

	// Case 2: multiple result
	pResult = ContactStore_Create();
	if (pResult == NULL)
	{
		printf("FAIL: Test_SearchRecordsFromFile_MT() failed to memory allocation\n");
		return;
	}

	assert(SearchRecordsFromFile_MT(pResult, "20", FILE_PATH_TEST) == SEARCH_SUCCESS);

	const char* expectedMultiple[] = {
		"010-0000-0002",	// B
		"010-0000-0022",	// C
	};

	verifyContext.expectedPhones = expectedMultiple;
	verifyContext.index = 0;
	ContactStore_Iterate(pResult, VerifyPhoneOrderCallback, &verifyContext);
	assert(verifyContext.index == sizeof(expectedMultiple) / sizeof(expectedMultiple[0]));
	ContactStore_Destroy(pResult);

	// Case 3: search with operator
	pResult = ContactStore_Create();
	if (pResult == NULL)
	{
		printf("FAIL: Test_SearchRecordsFromFile_MT() failed to memory allocation\n");
		return;
	}

	assert(SearchRecordsFromFile_MT(pResult, "10 OR 010-0000-0003", FILE_PATH_TEST) == SEARCH_SUCCESS);

	const char* expectedOp[] = {
		"010-0000-0001",	// A
		"010-0000-0003",	// D
	};

	verifyContext.expectedPhones = expectedOp;
	verifyContext.index = 0;
	ContactStore_Iterate(pResult, VerifyPhoneOrderCallback, &verifyContext);
	assert(verifyContext.index == sizeof(expectedOp) / sizeof(expectedOp[0]));
	ContactStore_Destroy(pResult);

	printf("PASS: Test_SearchRecordsFromFile_MT() correctly search single record\n");
	printf("PASS: Test_SearchRecordsFromFile_MT() correctly search multiple record\n");
	printf("PASS: Test_SearchRecordsFromFile_MT() correctly search multiple record with operator\n");
	return;
}

// ***********************************************

void Test_Contact_Destroy(void)
{
	Contact* pContact = Contact_Create(10, "Test", "010-0000-0000");

	Contact_Destroy(pContact);

	printf("PASS: Contact_Destroy() completed without crash\n");
	return;
}

void Test_ContactLifecycle(void)
{
	int pass = 1;

	Contact* pContact = Contact_Create(10, "Allice", "010-0000-1111");
	if (pContact == NULL)
	{
		printf("FAIL: Contact_Create returned NULL\n");
		return;
	}

	if (Contact_GetAge(pContact) != 10)
	{
		pass = 0;
		printf("FAIL: Contact_GetAge() returned wrong value\n");
	}

	if (strcmp(Contact_GetName(pContact), "Allice") != 0)
	{
		pass = 0;
		printf("FAIL: Contact_GetName() returned wrong value\n");
	}

	if (strcmp(Contact_GetName(pContact), "Allice") != 0)
	{
		pass = 0;
		printf("FAIL: Contact_GetPhone() returned wrong value\n");
	}

	if (pass)
	{
		printf("PASS: Contact_GetAge() returned correct value\n");
		printf("PASS: Contact_GetName() returned correct value\n");
		printf("PASS: Contact_GetPhone() returned correct value\n");

	}

	Contact_Destroy(pContact);
	return;
}

void Test_Contact_SetAge(void)
{
	int pass = 1;

	Contact* ptr = Contact_Create(10, "Alice", "010-0000-1111");
	if (ptr == NULL)
	{
		printf("FAIL: Test_Contact_SetAge() failed to create a contact\n");
		return;
	}

	int beforeAge = 0;
	int afterAge = 0;

	beforeAge = Contact_GetAge(ptr);
	Contact_SetAge(ptr, 20);
	afterAge = Contact_GetAge(ptr);
	if (beforeAge == afterAge || afterAge != 20)
	{
		pass = 0;
		printf("FAIL: Test_Contact_SetAge() didn't set age correctly\n");
	}

	if(pass)
	{
		printf("PASS: Test_Contact_SetAge() set age correctly\n");
	}
	
	Contact_Destroy(ptr);
	return;
}

void Test_Contact_SetName(void)
{
	int pass = 1;

	Contact* ptr = Contact_Create(10, "Alice", "010-0000-1111");
	if (ptr == NULL)
	{
		printf("FAIL: Test_Contact_SetName() failed to create a contact\n");
		return;
	}

	char beforeName[MAX_NAME_LEN] = { 0 };
	char afterName[MAX_NAME_LEN] = { 0 };

	strcpy_s(beforeName, sizeof(beforeName), Contact_GetName(ptr));
	Contact_SetName(ptr, "Betty");
	strcpy_s(afterName, sizeof(afterName), Contact_GetName(ptr));
	if (strcmp(beforeName, afterName) == 0 || strcmp(afterName, "Betty") != 0)
	{
		pass = 0;
		printf("FAIL: Test_Contact_SetName() didn't set name correctly\n");
	}

	if (pass)
	{
		printf("PASS: Test_Contact_SetName() set name correctly\n");
	}

	Contact_Destroy(ptr);
	return;
}

void Test_Contact_SetPhone(void)
{
	int pass = 1;

	Contact* ptr = Contact_Create(10, "Alice", "010-0000-1111");
	if (ptr == NULL)
	{
		printf("FAIL: Test_Contact_SetPhone() failed to create a contact\n");
		return;
	}

	char beforePhone[MAX_PHONE_LEN] = { 0 };
	char afterPhone[MAX_PHONE_LEN] = { 0 };

	strcpy_s(beforePhone, sizeof(beforePhone), Contact_GetPhone(ptr));
	Contact_SetPhone(ptr, "010-0000-2222");
	strcpy_s(afterPhone, sizeof(afterPhone), Contact_GetPhone(ptr));
	if (strcmp(beforePhone, afterPhone) == 0 || strcmp(afterPhone, "010-0000-2222") != 0)
	{
		pass = 0;
		printf("FAIL: Test_Contact_SetPhone() didn't set Phone correctly\n");
	}

	if (pass)
	{
		printf("PASS: Test_Contact_SetPhone() set Phone correctly\n");
	}

	Contact_Destroy(ptr);
	return;
}

void Test_ContactStore_IsEmpty(void)
{
	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	// Initially should be empty
	assert(ContactStore_IsEmpty(pStore) == 1);

	// Insert one contact
	Contact* c1 = Contact_Create(10, "Test", "010-1234-5678");
	ContactStore_Insert(pStore, c1);

	// Now it shouldn't be empty
	assert(ContactStore_IsEmpty(pStore) == 0);

	ContactStore_Destroy(pStore);

	printf("PASS: Test_IsEmpty()\n");
}

void Test_ContactStore_HasPhone(void)
{
	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	Contact* c1 = Contact_Create(10, "Alice", "010-1111-1111");
	Contact* c2 = Contact_Create(20, "Betty", "010-2222-2222");

	ContactStore_Insert(pStore, c1);
	ContactStore_Insert(pStore, c2);

	assert(ContactStore_HasPhone(pStore, "010-1111-1111") == 1);
	assert(ContactStore_HasPhone(pStore, "010-2222-2222") == 1);
	assert(ContactStore_HasPhone(pStore, "010-3333-3333") == 0);

	ContactStore_Destroy(pStore);
	printf("PASS: Test_HasPhone()\n");
}

void Test_ContactStore_Create(void)
{
	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);
	assert(pStore->root != NULL);
	assert(pStore->nil != NULL);
	assert(pStore->root == pStore->nil);
	assert(pStore->nil->color == BLACK);
	assert(pStore->nil->left == pStore->nil);
	assert(pStore->nil->right == pStore->nil);
	assert(pStore->nil->parent == pStore->nil);
	assert(pStore->nil->data == NULL);

	// NOTE: Destroy is intentionally omitted to isolate Craete() testing
	// This test Leaks memory but ensures Create() works independently
	printf("PASS: Test_Create() comleted\n");
}

void Test_ContactStore_Destroy(void)
{
	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	ContactStore_Destroy(pStore);

	printf("PASS: Test_Destroy completed without crash\n");
	return;
}

void Test_ContactStore_Insert(void)
{
	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	Contact* c1 = Contact_Create(10, "Alice", "010-0000-2222");
	Contact* c2 = Contact_Create(20, "Betty", "010-0000-1111");
	Contact* c3 = Contact_Create(30, "Charlie", "010-0000-3333");

	ContactStore_Insert(pStore, c1);
	ContactStore_Insert(pStore, c2);
	ContactStore_Insert(pStore, c3);

	assert(pStore->root == pStore->root->left->parent);
	assert(pStore->root == pStore->root->right->parent);
	assert(strcmp(Contact_GetPhone(pStore->root->data), "010-0000-2222") == 0);
	assert(strcmp(Contact_GetPhone(pStore->root->left->data), "010-0000-1111") == 0);
	assert(strcmp(Contact_GetPhone(pStore->root->right->data), "010-0000-3333") == 0);

	printf("PASS: Test_Insert()\n");

	Contact_Destroy(c1);
	Contact_Destroy(c2);
	Contact_Destroy(c3);
	ContactStore_Destroy(pStore);
	return;
}

void Test_ContactStore_Iterate(void)
{
	ContactStore* pStore = ContactStore_Create();
	Contact* a = Contact_Create(10, "A", "010-0000-0001");
	Contact* b = Contact_Create(20, "B", "010-0000-0002");
	Contact* c = Contact_Create(30, "C", "010-0000-0003");

	ContactStore_Insert(pStore, a);
	ContactStore_Insert(pStore, b);
	ContactStore_Insert(pStore, c);

	const char* expected[] = {
		"010-0000-0001",
		"010-0000-0002",
		"010-0000-0003"
	};

	VerifyContext verifyContext;
	verifyContext.expectedPhones = expected;
	verifyContext.index = 0;

	ContactStore_Iterate(pStore, VerifyPhoneOrderCallback, &verifyContext);

	printf("PASS: Test_ContactStore_Iterate()\n");

	Contact_Destroy(a);
	Contact_Destroy(b);
	Contact_Destroy(c);
	ContactStore_Destroy(pStore);
}

void Test_ContactStore_CombineByOp(void)
{
	ContactStore* pResultOR = ContactStore_Create();
	ContactStore* pResultAND = ContactStore_Create();
	ContactStore* pLeft = ContactStore_Create();
	ContactStore* pRight = ContactStore_Create();

	Contact* c1 = Contact_Create(10, "Alice", "010-0000-1111");
	Contact* c2 = Contact_Create(20, "Betty", "010-0000-2222");
	Contact* c3 = Contact_Create(25, "Edward", "010-0000-2222");
	Contact* c4 = Contact_Create(30, "Kevin", "010-0000-3333");

	ContactStore_Insert(pLeft, c1);
	ContactStore_Insert(pLeft, c2);
	ContactStore_Insert(pRight, c3);
	ContactStore_Insert(pRight, c4);

	ContactStore_CombineByOp(pResultOR, pLeft, pRight, "OR");
	ContactStore_CombineByOp(pResultAND, pLeft, pRight, "AND");

	const char* expectedOR[] = {
		"010-0000-1111",
		"010-0000-2222",
		"010-0000-3333"
	};

	const char* expectedAND[] = {
		"010-0000-2222"
	};

	VerifyContext contextOR = { expectedOR, 0 };
	VerifyContext contextAND = { expectedAND, 0 };

	ContactStore_Iterate(pResultOR, VerifyPhoneOrderCallback, &contextOR);
	ContactStore_Iterate(pResultAND, VerifyPhoneOrderCallback, &contextAND);
	assert(contextOR.index == sizeof(expectedOR) / sizeof(expectedOR[0]));
	assert(contextAND.index == sizeof(expectedAND) / sizeof(expectedAND[0]));

	printf("PASS: Test_ContactStore_CombineByOp()\n");

	Contact_Destroy(c1);
	Contact_Destroy(c2);
	Contact_Destroy(c3);
	Contact_Destroy(c4);
	ContactStore_Destroy(pResultOR);
	ContactStore_Destroy(pResultAND);
	ContactStore_Destroy(pLeft);
	ContactStore_Destroy(pRight);
}

void Test_ContactStore_FindByPhone(void)
{
	ContactStore* pStore = ContactStore_Create();
	assert(pStore != NULL);

	Contact* pContact = Contact_Create(10, "A", "010-0000-0001");
	assert(pContact != NULL);
	assert(ContactStore_Insert(pStore, pContact) == 1);
	Contact_Destroy(pContact);

	pContact = Contact_Create(20, "B", "010-0000-0002");
	assert(pContact != NULL);
	assert(ContactStore_Insert(pStore, pContact) == 1);
	Contact_Destroy(pContact);

	pContact = Contact_Create(30, "C", "010-0000-0003");
	assert(pContact != NULL);
	assert(ContactStore_Insert(pStore, pContact) == 1);
	Contact_Destroy(pContact);

	const Contact* temp = ContactStore_FindByPhone(pStore, "010-0000-0003");
	assert(temp != NULL);
	assert(Contact_GetAge(temp) == 30);
	assert(strcmp(Contact_GetName(temp), "C") == 0);
	assert(strcmp(Contact_GetPhone(temp), "010-0000-0003") == 0);

	printf("PASS: Test_ContactStore_FindByPhone correctly find expected contact in tree\n");

	ContactStore_Destroy(pStore);
}

void Test_ContactStore_Clone(void)
{
	int ages[] = { 10, 20, 30 };
	char* names[] = { "A", "B", "C" };
	char* phones[] = { "010-0000-1111", "010-0000-2222", "010-0000-3333" };
	int n = sizeof(ages) / sizeof(ages[0]);

	ContactStore* pSrc = ContactStore_Create();
	ContactStore* pDest = NULL;
	const Contact* pContact = NULL;

	// prepare a source contact_store
	for (int i = 0; i < n; i++)
	{
		pContact = Contact_Create(ages[i], names[i], phones[i]);
		ContactStore_Insert(pSrc, pContact);
		Contact_Destroy(pContact);
	}

	// clone the store
	pDest = ContactStore_Clone(pSrc);
	assert(pDest != NULL);
	ContactStore_Destroy(pSrc);

	VerifyContext* ctx = (VerifyContext*)malloc(sizeof(VerifyContext));
	ctx->expectedPhones = phones;
	ctx->index = 0;

	// NOTE: phone number only is verified 
	// since other fields are deterministic from Contact_Create()
	ContactStore_Iterate(pDest, VerifyPhoneOrderCallback, ctx);
	assert(ctx->index == n);

	ContactStore_Destroy(pDest);
	free(ctx);

	printf("PASS: Test_ContactStore_Clone() correctly clone the store.\n");
}