// Provides core logic for file-based data manipulation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include <PathCch.h>
#include "common.h"
#include "control.h"
#include "contact_store.h"
#include "contact.h"

#pragma comment(lib, "Pathcch.lib")

typedef LOADRESULT(*LOAD_FUNC)(ContactStore*, const void*, LPCWSTR);

typedef enum { BY_AGE, BY_NAME, BY_PHONE } SEARCH_TYPE;

typedef struct {
	const void* keyword;
	LPCWSTR path;
	ContactStore* store;
	LOAD_FUNC* pfLoad;
	SEARCH_TYPE type;
} SearchThreadParam;

EDITRESULT EditRecordAgeFromFile(const Contact* target, const int age, LPCWSTR path)
{
	if (age < 0 || age >= MAXAGE)
		return EDIT_ERROR;

	DWORD dwRead = 0, dwWritten = 0;
	DWORD dwRecordSize = (DWORD)Contact_GetSize();
	BOOL bResult = FALSE;
	HANDLE hFile = CreateFile(
		path,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
		return EDIT_ERROR;

	Contact* temp = (Contact*)malloc(dwRecordSize);
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return EDIT_ERROR;
	}
	while (1)
	{
		ZeroMemory(temp, dwRecordSize);
		bResult = ReadFile(hFile, temp, dwRecordSize, &dwRead, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (dwRead == 0)
			break;

		if (dwRead < dwRecordSize)
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (strcmp(Contact_GetPhone(temp), Contact_GetPhone(target)) == 0)
		{
			if (!Contact_SetAge(temp, age))
			{
				free(temp);
				CloseHandle(hFile);
				return EDIT_ERROR;
			}
			SetFilePointer(hFile, -(LONG)dwRecordSize, NULL, FILE_CURRENT);
			bResult = WriteFile(hFile, temp, dwRecordSize, &dwWritten, NULL);
			free(temp);
			CloseHandle(hFile);

			if (!bResult || dwWritten < dwRecordSize)
				return EDIT_ERROR;

			return EDIT_SUCCESS;
		}
	}

	free(temp);
	CloseHandle(hFile);
	return EDIT_NOT_FOUND;
}

EDITRESULT EditRecordNameFromFile(const Contact* target, const char* name, LPCWSTR path)
{
	if (!Str_IsAllAlpha(name))
		return EDIT_ERROR;

	DWORD dwRead = 0, dwWritten = 0;
	DWORD dwRecordSize = (DWORD)Contact_GetSize();
	BOOL bResult = FALSE;
	HANDLE hFile = CreateFile(
		path,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
		return EDIT_ERROR;

	Contact* temp = (Contact*)malloc(dwRecordSize);
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return EDIT_ERROR;
	}
	while (1)
	{
		ZeroMemory(temp, dwRecordSize);
		bResult = ReadFile(hFile, temp, dwRecordSize, &dwRead, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (dwRead == 0)
			break;

		if (dwRead < dwRecordSize)
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (strcmp(Contact_GetPhone(temp), Contact_GetPhone(target)) == 0)
		{
			if (!Contact_SetName(temp, name))
			{
				free(temp);
				CloseHandle(hFile);
				return EDIT_ERROR;
			}
			SetFilePointer(hFile, -(LONG)dwRecordSize, NULL, FILE_CURRENT);
			bResult = WriteFile(hFile, temp, dwRecordSize, &dwWritten, NULL);
			free(temp);
			CloseHandle(hFile);

			if (!bResult || dwWritten < dwRecordSize)
				return EDIT_ERROR;

			return EDIT_SUCCESS;
		}
	}

	free(temp);
	CloseHandle(hFile);
	return EDIT_NOT_FOUND;
}

EDITRESULT EditRecordPhoneFromFile(const Contact* target, const char* phone, LPCWSTR path)
{
	if (!Str_IsPhoneFormat(phone))
		return EDIT_ERROR;

	DWORD dwRead = 0, dwWritten = 0;
	DWORD dwRecordSize = (DWORD)Contact_GetSize();
	BOOL bResult = FALSE;
	HANDLE hFile = CreateFile(
		path,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
		return EDIT_ERROR;

	Contact* temp = (Contact*)malloc(dwRecordSize);
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return EDIT_ERROR;
	}
	while (1)
	{
		ZeroMemory(temp, dwRecordSize);
		bResult = ReadFile(hFile, temp, dwRecordSize, &dwRead, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (dwRead == 0)
			break;

		if (dwRead < dwRecordSize)
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (strcmp(Contact_GetPhone(temp), Contact_GetPhone(target)) == 0)
		{
			if (!Contact_SetPhone(temp, phone))
			{
				free(temp);
				CloseHandle(hFile);
				return EDIT_ERROR;
			}
			SetFilePointer(hFile, -(LONG)dwRecordSize, NULL, FILE_CURRENT);
			bResult = WriteFile(hFile, temp, dwRecordSize, &dwWritten, NULL);
			free(temp);
			CloseHandle(hFile);

			if (!bResult || dwWritten < dwRecordSize)
				return EDIT_ERROR;

			return EDIT_SUCCESS;
		}
	}

	free(temp);
	CloseHandle(hFile);
	return EDIT_NOT_FOUND;
}

DELETERESULT DeleteRecordFromFileByPhone(const char* phone, LPCWSTR path)
{
	if (!Str_IsPhoneFormat(phone))
		return DELETE_ERROR;

	DELETERESULT recordFound = DELETE_NOT_FOUND;
	DWORD dwContactSize = (DWORD)Contact_GetSize();
	DWORD dwRead = 0, dwWritten = 0;
	BOOL bResult = FALSE;
	HANDLE hFileSource = CreateFile(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFileSource == INVALID_HANDLE_VALUE)
	{
		return DELETE_ERROR;
	}

	wchar_t wTempPath[MAX_PATH] = { 0 };
	wcscpy_s(wTempPath, MAX_PATH, path);
	PathCchRemoveFileSpec(wTempPath, MAX_PATH);
	swprintf(wTempPath, MAX_PATH, L"%s\\%s", wTempPath, L"temp.dat");

	HANDLE hFileTarget = CreateFile(
		wTempPath,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFileTarget == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSource);
		return DELETE_ERROR;
	}

	Contact* temp = (Contact*)malloc(dwContactSize);
	while (1)
	{
		ZeroMemory(temp, dwContactSize);
		bResult = ReadFile(hFileSource, temp, dwContactSize, &dwRead, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFileSource);
			CloseHandle(hFileTarget);
			DeleteFile(wTempPath);
			return DELETE_ERROR;
		}

		if (dwRead == 0)
			break;

		if (dwRead < dwContactSize)
		{
			free(temp);
			CloseHandle(hFileSource);
			CloseHandle(hFileTarget);
			DeleteFile(wTempPath);
			return DELETE_ERROR;
		}

		if (strcmp(Contact_GetPhone(temp), phone) != 0)
		{
			bResult = WriteFile(hFileTarget, temp, dwContactSize, &dwWritten, NULL);
			if (!bResult || dwWritten < dwContactSize)
			{
				free(temp);
				CloseHandle(hFileSource);
				CloseHandle(hFileTarget);
				DeleteFile(wTempPath);
				return DELETE_ERROR;
			}
		}
		else
			recordFound = DELETE_SUCCESS;
	}

	free(temp);
	CloseHandle(hFileSource);
	CloseHandle(hFileTarget);

	if (DeleteFile(path) != TRUE)
		return DELETE_ERROR;
	if (MoveFile(wTempPath, path) != TRUE)
		return DELETE_ERROR;
	return recordFound;
}

int TryInsertContact(ContactStore* store, const Contact* contact, LPCWSTR path)
{
	if (store == NULL || contact == NULL || path == NULL)
		return 0;

	LOADRESULT result = LoadRecordsFromFileByPhone(
		NULL, Contact_GetPhone(contact), path
	);

	switch (result)
	{
	case LOAD_ERROR:
		return -1;
	case LOAD_NOT_FOUND:
		ContactStore_Insert(store, contact);
		return 1;
	case LOAD_SUCCESS:
		return 0;
	default:
		break;
	}
	return 0;
}

LOADRESULT LoadRecordsFromFileByPhone(ContactStore* store, const char* phone, LPCWSTR path)
{
	if (!Str_IsPhoneFormat(phone))
		return LOAD_ERROR;

	HANDLE hFile = CreateFile(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return LOAD_ERROR;
	}

	DWORD recordSize = (DWORD)Contact_GetSize();
	DWORD dwReadSize = -1;
	BOOL bResult = FALSE;

	Contact* temp = (Contact*)malloc(recordSize);
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return LOAD_ERROR;
	}

	while (1)
	{
		ZeroMemory(temp, recordSize);
		bResult = ReadFile(hFile, temp, recordSize, &dwReadSize, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (dwReadSize == 0) // EOF
			break;

		if (dwReadSize < recordSize)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (strcmp(phone, Contact_GetPhone(temp)) == 0)
		{
			ContactStore_Insert(store, temp);
			free(temp);
			CloseHandle(hFile);
			return LOAD_SUCCESS;
		}
	}

	free(temp);
	CloseHandle(hFile);
	return LOAD_NOT_FOUND;
}

LOADRESULT LoadRecordsFromFileByName(ContactStore* store, const char* name, LPCWSTR path)
{
	if (!Str_IsAllAlpha(name))
		return LOAD_ERROR;

	HANDLE hFile = CreateFile(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return LOAD_ERROR;
	}

	DWORD recordSize = (DWORD)Contact_GetSize();
	DWORD dwReadSize = -1;
	BOOL bResult = FALSE;

	Contact* temp = (Contact*)malloc(recordSize);
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return LOAD_ERROR;
	}

	int flag = 0;
	while (1)
	{
		ZeroMemory(temp, recordSize);
		bResult = ReadFile(hFile, temp, recordSize, &dwReadSize, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (dwReadSize == 0) // EOF
			break;

		if (dwReadSize < recordSize)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (strcmp(name, Contact_GetName(temp)) == 0)
		{
			ContactStore_Insert(store, temp);
			flag = 1;
		}
	}

	free(temp);
	CloseHandle(hFile);

	if (flag)
		return LOAD_SUCCESS;
	else
		return LOAD_NOT_FOUND;
}

LOADRESULT LoadRecordsFromFileByAge(ContactStore* store, const int age, LPCWSTR path)
{
	if (age < 0 || age > MAXAGE)
		return LOAD_ERROR;

	HANDLE hFile = CreateFile(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return LOAD_ERROR;
	}

	DWORD recordSize = (DWORD)Contact_GetSize();
	DWORD dwReadSize = -1;
	BOOL bResult = FALSE;

	Contact* temp = (Contact*)malloc(recordSize);
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return LOAD_ERROR;
	}

	int flag = 0;
	while (1)
	{
		ZeroMemory(temp, recordSize);
		bResult = ReadFile(hFile, temp, recordSize, &dwReadSize, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (dwReadSize == 0) // EOF
			break;

		if (dwReadSize < recordSize)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (age == Contact_GetAge(temp))
		{
			ContactStore_Insert(store, temp);
			flag = 1;
		}
	}

	free(temp);
	CloseHandle(hFile);

	if (flag)
		return LOAD_SUCCESS;
	else
		return LOAD_NOT_FOUND;
}

SEARCHRESULT SearchRecordsFromFile(ContactStore* result, const char* input, LPCWSTR path)
{
	int age1 = 0;
	int age2 = 0;
	char name1[MAX_NAME_LEN] = { 0 };
	char name2[MAX_NAME_LEN] = { 0 };
	char phone1[MAX_PHONE_LEN] = { 0 };
	char phone2[MAX_PHONE_LEN] = { 0 };

	char token1[BUFFSIZE] = { 0 };
	char token2[BUFFSIZE] = { 0 };
	char op[BUFFSIZE] = { 0 };

	if (!SplitSearchExpression(input, token1, token2, op))
		return PARSE_FAILED;

	if (!ClassifyToken(token1, &age1, name1, phone1))
		return CONVERT_FAILED;

	if (token2[0] != 0)
	{
		if (strcmp(op, "AND") != 0 && strcmp(op, "and") != 0 &&
			strcmp(op, "OR") != 0 && strcmp(op, "or") != 0)
		{
			return CONVERT_FAILED;
		}

		if (!ClassifyToken(token2, &age2, name2, phone2))
			return CONVERT_FAILED;
	}

	if (op[0] == 0)
	{
		if (age1 != 0)
		{
			LoadRecordsFromFileByAge(result, age1, path);
		}
		else if (name1[0] != 0)
		{
			LoadRecordsFromFileByName(result, name1, path);
		}
		else if (phone1[0] != 0)
		{
			LoadRecordsFromFileByPhone(result, phone1, path);
		}
	}
	else if (op[0] != 0)	// op is "AND" or "OR"
	{
		ContactStore* pTempStore1 = ContactStore_Create();
		ContactStore* pTempStore2 = ContactStore_Create();

		if (age1 != 0 && age2 != 0)
		{
			LoadRecordsFromFileByAge(pTempStore1, age1, path);
			LoadRecordsFromFileByAge(pTempStore2, age2, path);
			ContactStore_CombineByOp(result, pTempStore1, pTempStore2, op);
		}
		else if (age1 != 0 && name2[0] != 0)
		{
			LoadRecordsFromFileByAge(pTempStore1, age1, path);
			LoadRecordsFromFileByName(pTempStore2, name2, path);
			ContactStore_CombineByOp(result, pTempStore1, pTempStore2, op);
		}
		else if (age1 != 0 && phone2[0] != 0)
		{
			LoadRecordsFromFileByAge(pTempStore1, age1, path);
			LoadRecordsFromFileByPhone(pTempStore2, phone2, path);
			ContactStore_CombineByOp(result, pTempStore1, pTempStore2, op);
		}
		else if (name1[0] != 0 && age2 != 0)
		{
			LoadRecordsFromFileByName(pTempStore1, name1, path);
			LoadRecordsFromFileByAge(pTempStore2, age2, path);
			ContactStore_CombineByOp(result, pTempStore1, pTempStore2, op);
		}
		else if (name1[0] != 0 && name2[0] != 0)
		{
			LoadRecordsFromFileByName(pTempStore1, name1, path);
			LoadRecordsFromFileByName(pTempStore2, name2, path);
			ContactStore_CombineByOp(result, pTempStore1, pTempStore2, op);
		}
		else if (name1[0] != 0 && phone2[0] != 0)
		{
			LoadRecordsFromFileByName(pTempStore1, name1, path);
			LoadRecordsFromFileByPhone(pTempStore2, phone2, path);
			ContactStore_CombineByOp(result, pTempStore1, pTempStore2, op);
		}
		else if (phone1[0] != 0 && age2 != 0)
		{
			LoadRecordsFromFileByPhone(pTempStore1, phone1, path);
			LoadRecordsFromFileByAge(pTempStore2, age2, path);
			ContactStore_CombineByOp(result, pTempStore1, pTempStore2, op);
		}
		else if (phone1[0] != 0 && name2[0] != 0)
		{
			LoadRecordsFromFileByPhone(pTempStore1, phone1, path);
			LoadRecordsFromFileByName(pTempStore2, name2, path);
			ContactStore_CombineByOp(result, pTempStore1, pTempStore2, op);
		}
		else if (phone1[0] != 0 && phone2[0] != 0)
		{
			LoadRecordsFromFileByPhone(pTempStore1, phone1, path);
			LoadRecordsFromFileByPhone(pTempStore2, phone2, path);
			ContactStore_CombineByOp(result, pTempStore1, pTempStore2, op);
		}
		ContactStore_Destroy(pTempStore1);
		ContactStore_Destroy(pTempStore2);
	}

	if (!ContactStore_IsEmpty(result))
		return SEARCH_SUCCESS;
	else
		return NO_MATCH;
}

static int SaveContactToFile(const Contact* contact, void* userData)
{
	if (contact == NULL || userData == NULL)
		return 0;

	HANDLE hFile = (HANDLE)userData;
	if (hFile == NULL || hFile == INVALID_HANDLE_VALUE)
		return 0;

	DWORD dwContactSize = (DWORD)Contact_GetSize();
	DWORD dwWritten = 0;
	BOOL bResult = FALSE;

	bResult = WriteFile(hFile, contact, dwContactSize, &dwWritten, NULL);
	if (!bResult || dwWritten < dwContactSize)
	{
		return 0;
	}
	return 1;
}

int SaveListToFile(ContactStore* store, LPCWSTR path)
{
	if (ContactStore_IsEmpty(store))
		return -1;

	if (wcsstr(path, L"..\\Data") != NULL)
	{
		CreateDirectory(L"..\\Data", NULL);
	}

	HANDLE hFile = CreateFile(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	SetFilePointer(hFile, 0, NULL, FILE_END);
	if (!ContactStore_Iterate(store, SaveContactToFile, hFile))
	{
		CloseHandle(hFile);
		return -1;
	}
	CloseHandle(hFile);
	return 1;
}

// multithreaded

static LOADRESULT LoadWrapper_Age(ContactStore* store, const void* keyword, LPCWSTR path)
{
	return LoadRecordsFromFileByAge(store, *(const int*)keyword, path);
}

static LOADRESULT LoadWrapper_Name(ContactStore* store, const void* keyword, LPCWSTR path)
{
	return LoadRecordsFromFileByName(store, (const char*)keyword, path);
}

static LOADRESULT LoadWrapper_Phone(ContactStore* store, const void* keyword, LPCWSTR path)
{
	return LoadRecordsFromFileByPhone(store, (const char*)keyword, path);
}

static DWORD WINAPI SearchThreadProc(void* param)
{
	SearchThreadParam* p = (SearchThreadParam*)param;

	p->pfLoad[p->type](p->store, p->keyword, p->path);

	return 0;
}

SEARCHRESULT SearchRecordsFromFile_MT(ContactStore* result, const char* input, LPCWSTR path)
{
	int age1 = 0;
	int age2 = 0;
	char name1[MAX_NAME_LEN] = { 0 };
	char name2[MAX_NAME_LEN] = { 0 };
	char phone1[MAX_PHONE_LEN] = { 0 };
	char phone2[MAX_PHONE_LEN] = { 0 };

	char token1[BUFFSIZE] = { 0 };
	char token2[BUFFSIZE] = { 0 };
	char op[BUFFSIZE] = { 0 };

	if (!SplitSearchExpression(input, token1, token2, op))
		return PARSE_FAILED;

	if (!ClassifyToken(token1, &age1, name1, phone1))
		return CONVERT_FAILED;

	if (token2[0] != 0)
	{
		if (strcmp(op, "AND") != 0 && strcmp(op, "and") != 0 &&
			strcmp(op, "OR") != 0 && strcmp(op, "or") != 0)
		{
			return CONVERT_FAILED;
		}

		if (!ClassifyToken(token2, &age2, name2, phone2))
			return CONVERT_FAILED;
	}

	if (op[0] == 0)
	{
		if (age1 != 0)
		{
			LoadRecordsFromFileByAge(result, age1, path);
		}
		else if (name1[0] != 0)
		{
			LoadRecordsFromFileByName(result, name1, path);
		}
		else if (phone1[0] != 0)
		{
			LoadRecordsFromFileByPhone(result, phone1, path);
		}
	}
	else if (op[0] != 0)	// op is "AND" or "OR"
	{
		LOAD_FUNC pfLoadWrapper[3] = {
			LoadWrapper_Age,
			LoadWrapper_Name,
			LoadWrapper_Phone
		};

		HANDLE handles[2] = { 0 };

		ContactStore* pLeftStore = ContactStore_Create();
		ContactStore* pRightStore = ContactStore_Create();
		if (pLeftStore == NULL || pRightStore == NULL)
			return SEARCH_ERROR;

		SearchThreadParam leftParam = {
			NULL,
			path,
			pLeftStore,
			pfLoadWrapper,
			0
		};

		SearchThreadParam rightParam = {
			NULL,
			path,
			pRightStore,
			pfLoadWrapper,
			0
		};

		leftParam.type =
			(age1 != 0) ? BY_AGE :
			(name1[0] != 0) ? BY_NAME :	BY_PHONE;

		rightParam.type =
			(age2 != 0) ? BY_AGE :
			(name2[0] != 0) ? BY_NAME : BY_PHONE;

		if (leftParam.type == BY_AGE)
			leftParam.keyword = &age1;
		else if (leftParam.type == BY_NAME)
			leftParam.keyword = name1;
		else if (leftParam.type == BY_PHONE)
			leftParam.keyword = phone1;

		if (rightParam.type == BY_AGE)
			rightParam.keyword = &age2;
		else if (rightParam.type == BY_NAME)
			rightParam.keyword = name2;
		else if (rightParam.type == BY_PHONE)
			rightParam.keyword = phone2;

		handles[0] = (HANDLE)_beginthreadex(
			NULL,
			0,
			SearchThreadProc,
			&leftParam,
			0,
			NULL
		);

		handles[1] = (HANDLE)_beginthreadex(
			NULL,
			0,
			SearchThreadProc,
			&rightParam,
			0,
			NULL
		);
		if (handles[0] == NULL || handles[1] == NULL)
			return SEARCH_ERROR;
		
		WaitForMultipleObjects(2, handles, TRUE, INFINITE);
		ContactStore_CombineByOp(result, pLeftStore, pRightStore, op);

		ContactStore_Destroy(pLeftStore);
		ContactStore_Destroy(pRightStore);
	}

	if (!ContactStore_IsEmpty(result))
		return SEARCH_SUCCESS;
	else
		return NO_MATCH;
}