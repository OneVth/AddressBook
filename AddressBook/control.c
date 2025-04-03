// Provides core logic for file-based data manipulation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#include "common.h"
#include "control.h"

int SaveListToFile(LIST* pL, const char* path)
{
	if (List_IsEmpty(pL))
		return 0;

	_mkdir("../Data");

	NODE* ptr = pL->head.next;
	while (ptr != &pL->tail)
	{
		if (LoadRecordsFromFileByPhone(NULL, ptr->phone, path) == LOAD_NOT_FOUND)
		{
			BOOL bResult = FALSE;
			DWORD dwWritten = 0;
			wchar_t wPath[MAX_PATH] = { 0 };
			MultiByteToWideChar(CP_ACP, 0, path, -1, wPath, MAX_PATH);
			HANDLE hFile = CreateFile(
				wPath,
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

LOADRESULT LoadRecordsFromFileByPhone(LIST* pL, const char* phone, const char* path)
{
	if (!Str_IsPhoneFormat(phone))
		return LOAD_ERROR;

	wchar_t wPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, path, -1, wPath, MAX_PATH);

	HANDLE hFile = CreateFile(
		wPath,
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

LOADRESULT LoadRecordsFromFileByName(LIST* pL, const char* name, const char* path)
{
	if (!Str_IsAllAlpha(name))
		return LOAD_ERROR;

	LOADRESULT flag = LOAD_NOT_FOUND;

	DWORD dwRead = 0;
	BOOL bResult = FALSE;
	wchar_t wPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, path, -1, wPath, MAX_PATH);
	HANDLE hFile = CreateFile(
		wPath,
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

LOADRESULT LoadRecordsFromFileByAge(LIST* pL, const int age, const char* path)
{
	if (age < 0 || age >= MAXAGE)
		return LOAD_ERROR;

	LOADRESULT flag = LOAD_NOT_FOUND;

	DWORD dwRead = 0;
	BOOL bResult = FALSE;
	wchar_t wPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, path, -1, wPath, MAX_PATH);
	HANDLE hFile = CreateFile(
		wPath,
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

EDITRESULT EditRecordAgeFromFile(NODE* ptr, const int age, const char* path)
{
	if (age < 0 || age >= MAXAGE)
		return EDIT_ERROR;

	DWORD dwRead = 0, dwWritten = 0;
	BOOL bResult = FALSE;
	wchar_t wPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, path, -1, wPath, MAX_PATH);

	HANDLE hFile = CreateFile(
		wPath,
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

EDITRESULT EditRecordNameFromFile(NODE* ptr, const char* name, const char* path)
{
	if (!Str_IsAllAlpha(name) || (strlen(name) >= MAX_NAME_LEN - 1))
	{
		return EDIT_ERROR;
	}

	DWORD dwRead = 0, dwWritten = 0;
	BOOL bResult = FALSE;
	wchar_t wPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, path, -1, wPath, MAX_PATH);

	HANDLE hFile = CreateFile(
		wPath,
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

int EditRecordPhoneFromFile(NODE* ptr, const char* phone, const char* path)
{
	if (!Str_IsPhoneFormat(phone))
		return -1;

	FILE* fp = NULL;
	fopen_s(&fp, path, "rb+");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	while (fread(temp, sizeof(NODE), 1, fp))
	{
		if (strcmp(temp->phone, ptr->phone) == 0)
		{
			strcpy_s(temp->phone, sizeof(temp->phone), phone);
			fseek(fp, -(long)sizeof(NODE), SEEK_CUR);
			if (fwrite(temp, sizeof(NODE), 1, fp) != 1)
			{
				free(temp);
				fclose(fp);
				return -1;
			}
			break;
		}
	}

	free(temp);
	fclose(fp);
	return 1;
}

int DeleteRecordFromFileByPhone(const char* phone, const char* path)
{
	if (!Str_IsPhoneFormat(phone))
		return -1;

	int recordFound = 0;
	FILE* fp = NULL;
	FILE* fpTmp = NULL;
	fopen_s(&fp, path, "rb");
	fopen_s(&fpTmp, "temp.dat", "ab+");
	if (fp == NULL || fpTmp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));

	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (strcmp(temp->phone, phone) != 0)
		{
			if (fwrite(temp, sizeof(NODE), 1, fpTmp) != 1)
			{
				free(temp);
				fclose(fpTmp);
				fclose(fp);
				remove("temp.dat");
				return 0;
			}
		}
		else
			recordFound = 1;
	}

	free(temp);
	fclose(fpTmp);
	fclose(fp);

	
	if (remove(path) != 0)
		return -1;
	if (rename("temp.dat", path) != 0)
		return -1;
	return recordFound;
}

ERR_SEARCH SearchRecordsFromFile(LIST* pResult, const char* input, const char* PATH)
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
			LoadRecordsFromFileByAge(pResult, age1, PATH);
		}
		else if (name1[0] != 0)
		{
			LoadRecordsFromFileByName(pResult, name1, PATH);
		}
		else if (phone1[0] != 0)
		{
			LoadRecordsFromFileByPhone(pResult, phone1, PATH);
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
			LoadRecordsFromFileByAge(pTempList1, age1, PATH);
			LoadRecordsFromFileByAge(pTempList2, age2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (age1 != 0 && name2[0] != 0)
		{
			LoadRecordsFromFileByAge(pTempList1, age1, PATH);
			LoadRecordsFromFileByName(pTempList2, name2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (age1 != 0 && phone2[0] != 0)
		{
			LoadRecordsFromFileByAge(pTempList1, age1, PATH);
			LoadRecordsFromFileByPhone(pTempList2, phone2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (name1[0] != 0 && age2 != 0)
		{
			LoadRecordsFromFileByName(pTempList1, name1, PATH);
			LoadRecordsFromFileByAge(pTempList2, age2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (name1[0] != 0 && name2[0] != 0)
		{
			LoadRecordsFromFileByName(pTempList1, name1, PATH);
			LoadRecordsFromFileByName(pTempList2, name2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (name1[0] != 0 && phone2[0] != 0)
		{
			LoadRecordsFromFileByName(pTempList1, name1, PATH);
			LoadRecordsFromFileByPhone(pTempList2, phone2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (phone1[0] != 0 && age2 != 0)
		{
			LoadRecordsFromFileByPhone(pTempList1, phone1, PATH);
			LoadRecordsFromFileByAge(pTempList2, age2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (phone1[0] != 0 && name2[0] != 0)
		{
			LoadRecordsFromFileByPhone(pTempList1, phone1, PATH);
			LoadRecordsFromFileByName(pTempList2, name2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (phone1[0] != 0 && phone2[0] != 0)
		{
			LoadRecordsFromFileByPhone(pTempList1, phone1, PATH);
			LoadRecordsFromFileByPhone(pTempList2, phone2, PATH);
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