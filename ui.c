// Handles all user interface interactions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "common.h"
#include "control.h"
#include "ui.h"


int UI_GetInsertInfo(char* name, int* age, char* phone)
{
	while (1)
	{
		system("cls");
		printf("\nEnter new data: need [Name] [Age] [Phone number]\n");

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

	printf("[Name]\n");
	printf("Enter the name (max %d chars): ", MAX_NAME_LEN - 1);
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
	_getch();
	return 1;
}

int UI_GetPhone(char* buffer)
{
	char temp[MAX_PHONE_LEN] = { 0 };
	printf("[Phone]\n");
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

				if (!Str_IsPhoneFormat(temp))
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
	_getch();
	return 1;
}

int UI_GetAge(int* age)
{
	char temp[BUFFSIZE] = { 0 };
	printf("[Age]\n");
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
	_getch();
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

void UI_PrintList(LIST* pL)
{
	if (List_IsEmpty(pL))
		return;

	char ch = 0;
	int pageNumber = 0;
	int isEnd = 0;
	NODE* ptr = pL->head.next;
	do
	{
		pageNumber++;
		printf("\nPage #%d:\n", pageNumber);
		for (int i = 0; i < RECORDS_PER_PAGE; i++)
		{
			if (ptr == &pL->tail)
			{
				isEnd = 1;
				break;
			}

			printf("[%p] %3d - %-5s - %s [%p]\n", ptr, ptr->age, ptr->name, ptr->phone, ptr->next);
			ptr = ptr->next;
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

	_getch();
	return;
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
		if (val <= UI_FUNC_COUNT && val >= EXIT)
			break;

		printf("Enter valid number\n");
		_getch();
	}
	return val;
}

int UI_ExitMenu(const char* PATH)
{
	return 1;
}

int UI_PrintAll(const char* PATH)
{
	printf("Print all records ******************************\n");

	FILE* fp = NULL;
	fopen_s(&fp, PATH, "rb");
	if (fp == NULL)
	{
		printf("Failed to open file.\n");
		return 0;
	}
	char ch = 0;
	int pageNumber = 0;
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	do
	{
		system("cls");
		pageNumber++;
		printf("Page #%d **************************\n", pageNumber);
		int isEnd = 0;
		for (int i = 0; i < RECORDS_PER_PAGE; i++)
		{
			if (fread(temp, sizeof(NODE), 1, fp) > 0)
				printf("[%d]: %2d %-5s %s\n", i + 1,
					temp->age, temp->name, temp->phone);
			else
			{
				isEnd = 1;
				break;
			}
		}

		if (isEnd)
		{
			printf("\nEnd of file: Press any key to exit.\n");
			break;
		}
		else
			printf("\nPress any key to continue (or 'q' to exit) : ");
		ch = getchar();
	} while (ch != 'q' || ch != 'Q');
	_getch();

	free(temp);
	fclose(fp);
	return 0;
}

int UI_InsertNode(const char* PATH)
{
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	if (UI_GetInsertInfo(name, &age, phone))
	{
		if (!LoadRecordsFromFileByPhone(NULL, phone, PATH))
		{
			List_InsertAtEnd(pList, age, name, phone);
			SaveListToFile(pList, PATH);
		}
		else
		{
			printf("\nInsert failed: Phone number is already exist.\n");
			List_Release(pList);
			free(pList);
			return 0;
		}
	}
	else
	{
		printf("Insertion terminate.\n");
		List_Release(pList);
		free(pList);
		return 0;
	}

	List_Release(pList);
	free(pList);
	return 1;
}

int UI_DeleteNode(const char* PATH)
{
	int flag = 1;
	char phone[MAX_PHONE_LEN] = { 0 };

	do
	{
		printf("Need the phone number to delete **************\n");
		UI_GetPhone(phone);

		if (LoadRecordsFromFileByPhone(NULL, phone, PATH) != 1)
		{
			printf("Deletion failed: No matching record found.\n");
			return 0;
		}
		else
		{
			if (DeleteRecordFromFileByPhone(phone, PATH) == 1)
			{
				printf("Deletion successful.\n");
			}
			else
			{
				printf("Deletion failed.\n");
				return 0;
			}
		}

		char ch = 0;
		printf("Press any key to continue (or 'q' to exit) : ");
		ch = getchar();
		if (ch == 'q' || ch == 'Q')
		{
			flag = 0;
		}
		ClearInputBuffer();
	} while (flag);

	return 1;
}

int UI_Search(const char* PATH)
{
	ERR_SEARCH err_no = 0;
	LIST* pResult = (LIST*)malloc(sizeof(LIST));
	List_Init(pResult);

	printf("You can use \"AND\" or \"OR\" to search.\n");
	char buffer[BUFFSIZE] = { 0 };
	if (UI_GetSearchString(buffer))
	{
		err_no = SearchRecordsFromFile(pResult, buffer, PATH);
		if (err_no == SEARCH_SUCCESS)
		{
			printf("Search result **********************************\n");
			UI_PrintList(pResult);
		}
		else if (err_no == PARSE_FAILED)
		{
			printf("Input failed: Input format must be [str] [AND/OR] [str].\n");
			return 0;
		}
		else if (err_no == CONVERT_FAILED)
		{
			printf("Input failed: Allowed max [AGE: %d], [NAME LEN: %d], [PHONE LEN: %d]\n", MAXAGE, MAX_NAME_LEN, MAX_PHONE_LEN);
			return 0;
		}
		else if (err_no == NO_MATCH)
		{
			printf("Search failed: No matching records here.\n");
			return 0;
		}
	}
	else
	{
		return 0;
	}

	List_Release(pResult);
	free(pResult);
	return 1;
}

int UI_EditNode(const char* PATH)
{
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	printf("Need phone number of the node to edit **************\n");
	UI_GetPhone(phone);

	if (LoadRecordsFromFileByPhone(pList, phone, PATH) != 1)
	{
		printf("Cannot find the node.\n");
		return 0;
	}

	int flag = 1;
	NODE* ptr = pList->head.next;
	do
	{
		system("cls");
		printf("Now: %d %s %s\n", ptr->age, ptr->name, ptr->phone);
		printf("Edit [0] Exit [1] Age [2] Name [3] Phone\n");
		printf("Enter: ");
		int option = getchar() - '0';
		ClearInputBuffer();

		if (option <= 3 && option >= 0)
		{
			switch (option)
			{
			case 0:
				break;
			case 1:
				UI_GetAge(&age);
				EditRecordAgeFromFile(ptr, age, PATH);

				break;
			case 2:
				UI_GetName(name);
				EditRecordNameFromFile(ptr, name, PATH);

				break;
			case 3:
				UI_GetPhone(phone);

				if (LoadRecordsFromFileByPhone(NULL, phone, PATH) == 1)
				{
					printf("Edit failed: Phone number is already exist.\n");
				}
				else
					EditRecordPhoneFromFile(ptr, phone, PATH);
				break;
			default:
				break;
			}
		}
		else
		{
			printf("Invalid option.\n");
		}

		char ch = 0;
		printf("Press any key to continue (or 'q' to exit) : ");
		ch = getchar();
		if (ch == 'q' || ch == 'Q')
		{
			flag = 0;
		}
		ClearInputBuffer();
	} while (flag);

	return 1;
}

