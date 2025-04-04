// Provides core logic for file-based data manipulation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <PathCch.h>
#include "common.h"
#include "control.h"

#pragma comment(lib, "Pathcch.lib")

int SaveListToFile(LIST* pL, LPCWSTR path)
{
	if (List_IsEmpty(pL))
		return 0;

	CreateDirectory(L"../Data", NULL);

	NODE* ptr = pL->head.next;
	while (ptr != &pL->tail)
	{
		if (LoadRecordsFromFileByPhone(NULL, ptr->phone, path) == LOAD_NOT_FOUND)
		{
			BOOL bResult = FALSE;
			DWORD dwWritten = 0;
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
			bResult = WriteFile(hFile, ptr, sizeof(NODE), &dwWritten, NULL);
			if (!bResult || dwWritten < sizeof(NODE))
			{
				CloseHandle(hFile);
				return -1;
			}
			CloseHandle(hFile);
		}
		ptr = ptr->next;
	}
	return 1;
}

LOADRESULT LoadRecordsFromFileByPhone(LIST* pL, const char* phone, LPCWSTR path)
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

	DWORD dwRecordSize = sizeof(NODE);
	DWORD dwReadSize = -1;
	BOOL bResult = FALSE;

	NODE* temp = (NODE*)malloc(dwRecordSize);
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return LOAD_ERROR;
	}

	while (1)
	{
		ZeroMemory(temp, dwRecordSize);
		bResult = ReadFile(hFile, temp, dwRecordSize, &dwReadSize, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (dwReadSize == 0) // EOF
			break;

		if (dwReadSize < dwRecordSize)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (strcmp(phone, temp->phone) == 0)
		{
			List_InsertAtEnd(pL, temp->age, temp->name, temp->phone);
			free(temp);
			CloseHandle(hFile);
			return LOAD_SUCCESS;
		}
	}
	
	free(temp);
	CloseHandle(hFile);
	return LOAD_NOT_FOUND;
}

LOADRESULT LoadRecordsFromFileByName(LIST* pL, const char* name, LPCWSTR path)
{
	if (!Str_IsAllAlpha(name))
		return LOAD_ERROR;

	LOADRESULT flag = LOAD_NOT_FOUND;

	DWORD dwRead = 0;
	BOOL bResult = FALSE;
	HANDLE hFile = CreateFile(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return LOAD_ERROR;
	}

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return LOAD_ERROR;
	}
	while (1)
	{
		ZeroMemory(temp, sizeof(NODE));
		bResult = ReadFile(hFile, temp, sizeof(NODE), &dwRead, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (dwRead == 0)	// EOF
			break;

		if (dwRead < sizeof(NODE))
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (strcmp(temp->name, name) == 0)
		{
			flag = LOAD_SUCCESS;
			List_InsertAtEnd(pL, temp->age, temp->name, temp->phone);
		}
	}

	free(temp);
	CloseHandle(hFile);
	return flag;
}

LOADRESULT LoadRecordsFromFileByAge(LIST* pL, const int age, LPCWSTR path)
{
	if (age < 0 || age >= MAXAGE)
		return LOAD_ERROR;

	LOADRESULT flag = LOAD_NOT_FOUND;

	DWORD dwRead = 0;
	BOOL bResult = FALSE;
	HANDLE hFile = CreateFile(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return LOAD_ERROR;
	}

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return LOAD_ERROR;
	}
	while (1)
	{
		ZeroMemory(temp, sizeof(NODE));
		bResult = ReadFile(hFile, temp, sizeof(NODE), &dwRead, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (dwRead == 0)	// EOF
			break;

		if (dwRead < sizeof(NODE))
		{
			free(temp);
			CloseHandle(hFile);
			return LOAD_ERROR;
		}

		if (temp->age == age)
		{
			flag = LOAD_SUCCESS;
			List_InsertAtEnd(pL, temp->age, temp->name, temp->phone);
		}
	}

	free(temp);
	CloseHandle(hFile);
	return flag;
}

EDITRESULT EditRecordAgeFromFile(NODE* ptr, const int age, LPCWSTR path)
{
	if (age < 0 || age >= MAXAGE)
		return EDIT_ERROR;

	DWORD dwRead = 0, dwWritten = 0;
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

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return EDIT_ERROR;
	}
	while (1)
	{
		ZeroMemory(temp, sizeof(NODE));
		bResult = ReadFile(hFile, temp, sizeof(NODE), &dwRead, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (dwRead == 0)
			break;

		if (dwRead < sizeof(NODE))
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (strcmp(temp->phone, ptr->phone) == 0)
		{
			temp->age = age;
			SetFilePointer(hFile, -(LONG)sizeof(NODE), NULL, FILE_CURRENT);
			bResult = WriteFile(hFile, temp, sizeof(NODE), &dwWritten, NULL);
			free(temp);
			CloseHandle(hFile);
			
			if (!bResult || dwWritten < sizeof(NODE))
				return EDIT_ERROR;

			return EDIT_SUCCESS;
		}
	}
	
	free(temp);
	CloseHandle(hFile);
	return EDIT_NOT_FOUND;
}

EDITRESULT EditRecordNameFromFile(NODE* ptr, const char* name, LPCWSTR path)
{
	if (!Str_IsAllAlpha(name) || (strlen(name) >= MAX_NAME_LEN - 1))
	{
		return EDIT_ERROR;
	}

	DWORD dwRead = 0, dwWritten = 0;
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

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return EDIT_ERROR;
	}
	while (1)
	{
		ZeroMemory(temp, sizeof(NODE));
		bResult = ReadFile(hFile, temp, sizeof(NODE), &dwRead, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (dwRead == 0)
			break;

		if (dwRead < sizeof(NODE))
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (strcmp(temp->phone, ptr->phone) == 0)
		{
			strcpy_s(temp->name, MAX_NAME_LEN, name);
			SetFilePointer(hFile, -(LONG)sizeof(NODE), NULL, FILE_CURRENT);
			bResult = WriteFile(hFile, temp, sizeof(NODE), &dwWritten, NULL);
			free(temp);
			CloseHandle(hFile);

			if (!bResult || dwWritten < sizeof(NODE))
				return EDIT_ERROR;

			return EDIT_SUCCESS;
		}
	}

	free(temp);
	CloseHandle(hFile);
	return EDIT_NOT_FOUND;
}

EDITRESULT EditRecordPhoneFromFile(NODE* ptr, const char* phone, LPCWSTR path)
{
	if (!Str_IsPhoneFormat(phone))
		return EDIT_ERROR;

	DWORD dwRead = 0, dwWritten = 0;
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

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	if (temp == NULL)
	{
		CloseHandle(hFile);
		return EDIT_ERROR;
	}
	while (1)
	{
		ZeroMemory(temp, sizeof(NODE));
		bResult = ReadFile(hFile, temp, sizeof(NODE), &dwRead, NULL);
		if (!bResult)
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (dwRead == 0)
			break;

		if (dwRead < sizeof(NODE))
		{
			free(temp);
			CloseHandle(hFile);
			return EDIT_ERROR;
		}

		if (strcmp(temp->phone, ptr->phone) == 0)
		{
			strcpy_s(temp->phone, MAX_PHONE_LEN, phone);
			SetFilePointer(hFile, -(LONG)sizeof(NODE), NULL, FILE_CURRENT);
			bResult = WriteFile(hFile, temp, sizeof(NODE), &dwWritten, NULL);
			free(temp);
			CloseHandle(hFile);

			if (!bResult || dwWritten < sizeof(NODE))
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
	PathCchAppend(wTempPath, MAX_PATH, L"temp.dat");

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

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	while (1)
	{
		ZeroMemory(temp, sizeof(NODE));
		bResult = ReadFile(hFileSource, temp, sizeof(NODE), &dwRead, NULL);
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

		if (dwRead < sizeof(NODE))
		{
			free(temp);
			CloseHandle(hFileSource);
			CloseHandle(hFileTarget);
			DeleteFile(wTempPath);
			return DELETE_ERROR;
		}

		if (strcmp(temp->phone, phone) != 0)
		{
			bResult = WriteFile(hFileTarget, temp, sizeof(NODE), &dwWritten, NULL);
			if (!bResult || dwWritten < sizeof(NODE))
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

SEARCHRESULT SearchRecordsFromFile(LIST* pResult, const char* input, LPCWSTR path)
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
			LoadRecordsFromFileByAge(pResult, age1, path);
		}
		else if (name1[0] != 0)
		{
			LoadRecordsFromFileByName(pResult, name1, path);
		}
		else if (phone1[0] != 0)
		{
			LoadRecordsFromFileByPhone(pResult, phone1, path);
		}
	}
	else if (op[0] != 0)	// op is "AND" or "OR"
	{
		LIST* pTempList1 = (LIST*)malloc(sizeof(LIST));
		LIST* pTempList2 = (LIST*)malloc(sizeof(LIST));
		List_Init(pTempList1);
		List_Init(pTempList2);

		if (age1 != 0 && age2 != 0)
		{
			LoadRecordsFromFileByAge(pTempList1, age1, path);
			LoadRecordsFromFileByAge(pTempList2, age2, path);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (age1 != 0 && name2[0] != 0)
		{
			LoadRecordsFromFileByAge(pTempList1, age1, path);
			LoadRecordsFromFileByName(pTempList2, name2, path);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (age1 != 0 && phone2[0] != 0)
		{
			LoadRecordsFromFileByAge(pTempList1, age1, path);
			LoadRecordsFromFileByPhone(pTempList2, phone2, path);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (name1[0] != 0 && age2 != 0)
		{
			LoadRecordsFromFileByName(pTempList1, name1, path);
			LoadRecordsFromFileByAge(pTempList2, age2, path);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (name1[0] != 0 && name2[0] != 0)
		{
			LoadRecordsFromFileByName(pTempList1, name1, path);
			LoadRecordsFromFileByName(pTempList2, name2, path);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (name1[0] != 0 && phone2[0] != 0)
		{
			LoadRecordsFromFileByName(pTempList1, name1, path);
			LoadRecordsFromFileByPhone(pTempList2, phone2, path);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (phone1[0] != 0 && age2 != 0)
		{
			LoadRecordsFromFileByPhone(pTempList1, phone1, path);
			LoadRecordsFromFileByAge(pTempList2, age2, path);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (phone1[0] != 0 && name2[0] != 0)
		{
			LoadRecordsFromFileByPhone(pTempList1, phone1, path);
			LoadRecordsFromFileByName(pTempList2, name2, path);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (phone1[0] != 0 && phone2[0] != 0)
		{
			LoadRecordsFromFileByPhone(pTempList1, phone1, path);
			LoadRecordsFromFileByPhone(pTempList2, phone2, path);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}

		List_Release(pTempList1);
		List_Release(pTempList2);
		free(pTempList1);
		free(pTempList2);
	}

	if (!List_IsEmpty(pResult))
		return SEARCH_SUCCESS;
	else
		return NO_MATCH;
}