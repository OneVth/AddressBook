// Handles all user interface interactions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <process.h>
#include "common.h"
#include "control.h"
#include "ui.h"

typedef struct {
	char phone[MAX_PHONE_LEN];
	LPCWSTR path;
	DELETERESULT result;
} DELETEPARAM;

typedef struct {
	int count;
	int pageNum;
} PrintStoreInfo;

int UI_GetInsertInfo(char* name, int* age, char* phone)
{
	while (1)
	{
		system("cls");
		printf("Enter new data: need [Name] [Age] [Phone number]\n");

		if (UI_GetName(name) && UI_GetAge(age) && UI_GetPhone(phone))
		{
			return 1;
		}
		else
		{
			char ch = 0;
			printf("\nPress any key to retry (or 'q' to exit) : ");
			ch = getchar();
			if (ch == 'q' || ch == 'Q')
			{
				break;
			}
		}
		ClearInputBuffer();
	}
	ClearInputBuffer();
	return 0;
}

int UI_GetName(char* buffer)
{
	char temp[MAX_NAME_LEN] = { 0 };

	printf("\n[Name]\n");
	printf("Enter the name (max %d characters): ", MAX_NAME_LEN - 1);
	if (fgets(temp, sizeof(temp), stdin) != NULL)
	{
		size_t len = strlen(temp);
		if (len > 1 && temp[len - 1] == '\n')
		{
			temp[len - 1] = '\0';

			if (Str_IsAllAlpha(temp))
			{
				strcpy_s(buffer, MAX_NAME_LEN, temp);
			}
			else
			{
				printf("Input failed: Name must not contain spaces, digits, or special characters.\n");
				return 0;
			}
		}
		else
		{
			if (len == 1)
			{
				printf("Input failed: Name cannot be empty.\n");
				return 0;
			}
			else
			{
				printf("Input failed: Max allowed is %d characters.\n", MAX_NAME_LEN);
				return 0;
			}
		}
	}
	else
	{
		printf("Input failed: Try again.\n");
		return 0;
	}
	return 1;
}

int UI_GetPhone(char* buffer)
{
	char temp[MAX_PHONE_LEN] = { 0 };
	printf("\n[Phone]\n");
	printf("Enter the phone number (without hyphens '-'): ");
	if (fgets(temp, sizeof(temp), stdin) != NULL)
	{
		size_t len = strlen(temp);
		if ((len == MAX_PHONE_LEN - 2) && (temp[len - 1] == '\n'))
		{
			temp[len - 1] = '\0';

			if (Str_IsAllDigit(temp))
			{
				// Convert string to phone format
				int i = 0;
				char* ch = temp;
				while (*ch != '\0')
				{
					if (i == 3 || i == 8)
						buffer[i++] = '-';
					buffer[i++] = *ch;
					ch++;
				}
				buffer[i] = '\0';

				if (!Str_IsPhoneFormat(buffer))
				{
					printf("Input failed: Invalid format.\n");
					return 0;
				}
			}
			else
			{
				printf("Input failed: Only digits are allowed.\n");
				return 0;
			}
		}
		else
		{
			if (len == 1)
				printf("Input failed: Phone number cannot be empty.\n");
			else
			{
				printf("Input failed: Phone number must be exactly %d digits (e.g., 01012345678.)\n", MAX_PHONE_LEN - 3);	// hyphens and null character.
			}
			return 0;
		}
	}
	else
	{
		printf("Input failed. Try again.\n");
		return 0;
	}
	return 1;
}

int UI_GetAge(int* age)
{
	char temp[BUFFSIZE] = { 0 };
	printf("\n[Age]\n");
	printf("Enter the age : ");
	if (fgets(temp, sizeof(temp), stdin) != NULL)
	{
		size_t len = strlen(temp);
		if (len > 1 && temp[len - 1] == '\n')
		{
			temp[len - 1] = '\0';

			if (!Str_IsAllDigit(temp))
			{
				printf("Input failed: Only digits are allowed.\n");
				return 0;
			}

			*age = atoi(temp);
			if (*age < 0 || *age > MAXAGE)
			{
				*age = -1;
				printf("Insert failed: Max allowed %d.\n", MAXAGE);
				return 0;
			}
		}
		else
		{
			if (len == 1)
				printf("Insert failed: Age cannot be empty.\n");
			else
				printf("Insert failed: Invalid value.\n");
			return 0;
		}
	}
	else
	{
		printf("Input failed. Try again.\n");
		return 0;
	}
	return 1;
}

int UI_GetSearchString(char* buffer)
{
	char temp[BUFFSIZE] = { 0 };
	printf("Search string: ");
	if (fgets(temp, sizeof(temp), stdin) != NULL)
	{
		size_t len = strlen(temp);
		if (len > 1 && temp[len - 1] == '\n')
		{
			temp[len - 1] = '\0';
		}
		else
		{
			if (len == 1)
				printf("Input cannot be empty.\n");
			else
				printf("Input failed: Invalid input.\n");
			return 0;
		}
	}
	else
	{
		printf("Input failed: Input format must be [str] [AND/OR] [str].\n");
		return 0;
	}

	strcpy_s(buffer, BUFFSIZE, temp);
	return 1;
}

int PrintStoreCallback(const Contact* c, void* userData)
{
	PrintStoreInfo* pStoreInfo = (PrintStoreInfo*)userData;
	if (pStoreInfo->count % RECORDS_PER_PAGE == 0)
	{
		system("cls");
		printf("Print records in the list:\n");
		pStoreInfo->pageNum = pStoreInfo->count / RECORDS_PER_PAGE;
		printf("Page #%d\n", pStoreInfo->pageNum + 1);
	}

	printf("%d %s %s\n", Contact_GetAge(c), Contact_GetName(c), Contact_GetPhone(c));

	pStoreInfo->count++;
	if (pStoreInfo->count % RECORDS_PER_PAGE == 0)
	{
		char c = 0;
		printf("\nPress any key to continue (or 'q' to exit) : ");
		c = getchar();
		if (c == 'q' || c == 'Q')
			return 0;
	}
	return 1;
}

static int PrintRBTCallback(const Contact* c, void* userData)
{

	PrintStoreInfo* pStoreInfo = (PrintStoreInfo*)userData;
	if (pStoreInfo->count % RECORDS_PER_PAGE == 0)
	{
		system("cls");
		printf("Print records in the list:\n");
		pStoreInfo->pageNum = pStoreInfo->count / RECORDS_PER_PAGE;
		printf("Page #%d\n", pStoreInfo->pageNum + 1);
	}

	printf("%d %s %s\n", Contact_GetAge(c), Contact_GetName(c), Contact_GetPhone(c));

	pStoreInfo->count++;
	if (pStoreInfo->count % RECORDS_PER_PAGE == 0)
	{
		char c = 0;
		printf("\nPress any key to continue (or 'q' to exit) : ");
		c = getchar();
		if (c == 'q' || c == 'Q')
			return 0;
	}
	return 1;
}

void UI_PrintRBT(ContactStore* store)
{
	PrintStoreInfo storeInfo = { 0, 0 };
	ContactStore_Iterate(store, PrintRBTCallback, &storeInfo);
	printf("\nEnd of list: Press any key to exit.\n");
	_getch();
}

OPTION PrintMenu(void)
{
	OPTION val = -1;
	while (1)
	{
		system("cls");
		printf("[1] Print [2] Insert [3] Delete [4] Search [5] Edit [0] Exit\n");
		printf("Enter the number: ");
		val = getchar() - '0';
		while (getchar() != '\n');	// clear input buffer
		if (val <= UI_FUNC_COUNT && val >= MENU_EXIT)
			break;

		printf("Enter valid number\n");
		_getch();
	}
	return val;
}

int UI_ExitMenu(LPCWSTR path)
{
	return 1;
}

int UI_PrintAll(LPCWSTR path)
{
	printf("Print all records ******************************\n");

	DWORD dwContactSize = (DWORD)Contact_GetSize();
	DWORD dwRead = 0;
	BOOL bResult = FALSE;
	HANDLE hFile = CreateFile(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Failed to open file.\n");
		_getch();
		return 0;
	}

	char ch = 0;
	int pageNumber = 0;
	Contact* pContact = (Contact*)malloc(dwContactSize);
	do
	{
		system("cls");
		pageNumber++;
		printf("Page #%d **************************\n", pageNumber);
		int isEnd = 0;
		for (int i = 0; i < RECORDS_PER_PAGE; i++)
		{
			ZeroMemory(pContact, dwContactSize);
			bResult = ReadFile(hFile, pContact, dwContactSize, &dwRead, NULL);
			if (!bResult)
			{
				printf("Failed to read file.\n");
				CloseHandle(hFile);
				_getch();
				return 0;
			}

			if (dwRead == 0)
			{
				isEnd = 1;
				break;
			}

			if (dwRead < dwContactSize)
			{
				printf("File format error.\n");
				CloseHandle(hFile);
				_getch();
				return 0;
			}

			printf("[%d]: %2d %-5s %s\n", i + 1, 
				Contact_GetAge(pContact), 
				Contact_GetName(pContact), 
				Contact_GetPhone(pContact)
			);
		}

		if (isEnd)
		{
			printf("\nEnd of file: Press any key to exit.\n");
			break;
		}
		else
			printf("\nPress any key to continue (or 'q' to exit) : ");
		ch = getchar();
	} while (ch != 'q' && ch != 'Q');
	ClearInputBuffer();
	free(pContact);
	CloseHandle(hFile);
	return 0;
}

int UI_InsertNode(LPCWSTR path)
{
	char c = 0;
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	ContactStore* pStore = ContactStore_Create();
	while (1)
	{
		if (UI_GetInsertInfo(name, &age, phone))
		{
			Contact* pContact = Contact_Create(age, name, phone);
			if (TryInsertContact(pStore, pContact, path) != 1)
			{
				printf("[ERROR] The record(phone number) is already in the file\n");
			}
			Contact_Destroy(pContact);
		}
		
		printf("\nPress any key to continue (or 'q' to exit) : ");
		c = getchar();
		if (c == 'q' || c == 'Q')
			break;
	}
	ClearInputBuffer();
	SaveListToFile(pStore, path);
	ContactStore_Destroy(pStore);
	return 1;
}

DWORD WINAPI Thread_DeleteRecord(void* param)
{
	DELETEPARAM* params = (DELETEPARAM*)param;
	if (LoadRecordsFromFileByPhone(NULL, params->phone, params->path) != LOAD_SUCCESS)
	{
		return 0;
	}
	else
	{
		if ((params->result = DeleteRecordFromFileByPhone(params->phone, params->path)) != DELETE_SUCCESS)
		{
			return 0;
		}
	}
	return 1;
}

int UI_DeleteNode(LPCWSTR path)
{
	int flag = 1;
	char phone[MAX_PHONE_LEN] = { 0 };

	const char* dots[] = { " ", ".", "..", "..." };
	int dotIndex = 0;
	DELETEPARAM* param = (DELETEPARAM*)malloc(sizeof(DELETEPARAM));
	param->path = path;
	do
	{
		system("cls");
		printf("Need the phone number to delete **************\n");
		UI_GetPhone(phone);

		param->result = -1;
		strcpy_s(param->phone, sizeof(param->phone), phone);
		HANDLE hThread = (HANDLE)_beginthreadex(
			NULL,
			0,
			Thread_DeleteRecord,
			(LPVOID)param,
			0,
			NULL);
		if (hThread == 0)
		{
			printf("Failed to create thread.\n");
			free(param);
			return 0;
		}

		while (WaitForSingleObject(hThread, 300) == WAIT_TIMEOUT)
		{
			printf("\rDeleting%s  ", dots[dotIndex]);
			fflush(stdout);
			dotIndex = (dotIndex + 1) % 4;	// Console animation
		}
		CloseHandle((HANDLE)hThread);

		if (param->result == DELETE_SUCCESS)
			printf("Record deleted successfully.\n");
		else
			printf("Failed to delete record.\n");

		char ch = 0;
		printf("Press any key to continue (or 'q' to exit) : ");
		ch = getchar();
		if (ch == 'q' || ch == 'Q')
		{
			flag = 0;
		}
		ClearInputBuffer();
		putchar('\n');
	} while (flag);

	free(param);
	return 1;
}

int UI_Search(LPCWSTR path)
{
	SEARCHRESULT result = SEARCH_ERROR;
	ContactStore* pResult = ContactStore_Create();

	printf("You can use \"AND\" or \"OR\" to search.\n");
	char buffer[BUFFSIZE] = { 0 };
	if (UI_GetSearchString(buffer))
	{
		result = SearchRecordsFromFile(pResult, buffer, path);
		if (result == SEARCH_SUCCESS)
		{
			printf("Search result **********************************\n");
			UI_PrintRBT(pResult);
		}
		else if (result == PARSE_FAILED)
		{
			printf("Input failed: Input format must be [str] [AND/OR] [str].\n");
			ContactStore_Destroy(pResult);
			return 0;
		}
		else if (result == CONVERT_FAILED)
		{
			printf("Input failed: Allowed max [AGE: %d], [NAME LEN: %d], [PHONE LEN: %d]\n", MAXAGE, MAX_NAME_LEN, MAX_PHONE_LEN);
			ContactStore_Destroy(pResult);
			return 0;
		}
		else if (result == NO_MATCH)
		{
			printf("Search failed: No matching records here.\n");
			ContactStore_Destroy(pResult);
			return 0;
		}
	}
	else
	{
		ContactStore_Destroy(pResult);
		return 0;
	}

	ContactStore_Destroy(pResult);
	return 1;
}

int UI_EditNode(LPCWSTR path)
{
	char c = 0;
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	ContactStore* pStore = ContactStore_Create();

	printf("Need phone number of the node to edit **************\n");
	UI_GetPhone(phone);

	if (LoadRecordsFromFileByPhone(pStore, phone, path) != LOAD_SUCCESS)
	{
		printf("Cannot find the node. Returning to main menu...\n");
		_getch();
		ContactStore_Destroy(pStore);
		return 0;
	}

	const Contact* pContact = ContactStore_FindByPhone(pStore, phone);
	system("cls");
	printf("Now: %d %s %s\n",
		Contact_GetAge(pContact),
		Contact_GetName(pContact),
		Contact_GetPhone(pContact)
	);
	printf("Edit: [0] Exit [1] Age [2] Name [3] Phone\n");
	printf("Choose an option: ");
	char input = getchar();
	ClearInputBuffer();
	if (isdigit(input))
	{
		int option = input - '0';
		if (option <= 3 && option >= 0)
		{
			switch (option)
			{
			case 0:
				break;
			case 1:
				UI_GetAge(&age);
				if (EditRecordAgeFromFile(pContact, age, path) == EDIT_SUCCESS)
					printf("Edit successful\n");
				else
					printf("Edit failure\n");
				break;
			case 2:
				UI_GetName(name);
				if (EditRecordNameFromFile(pContact, name, path) == EDIT_SUCCESS)
					printf("Edit successful\n");
				else
					printf("Edit failure\n");
				break;
			case 3:
				UI_GetPhone(phone);
				if (LoadRecordsFromFileByPhone(NULL, phone, path) == LOAD_SUCCESS)
				{
					printf("Edit failed: Phone number already exists.\n");
				}
				else
				{
					if (EditRecordPhoneFromFile(pContact, phone, path) == EDIT_SUCCESS)
						printf("Edit successful\n");
					else
						printf("Edit failure\n");
				}
				break;
			default:
				break;
			}
		}
		else
			printf("Invalid option.\n");
	}
	else
		printf("Invalid input.\n");

	ContactStore_Destroy(pStore);
	_getch();
	return 1;
}