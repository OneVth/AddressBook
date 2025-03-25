#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "common.h"
#include "control.h"
#include "ui.h"

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

int GetName(char* buffer)
{
	char temp[MAX_NAME_LEN] = { 0 };
	while (1)
	{
		printf("Enter the name (max %d chars): ", MAX_NAME_LEN - 1);
		if (fgets(temp, sizeof(temp), stdin) != NULL)
		{
			size_t len = strlen(temp);
			if (len > 1 && temp[len - 1] == '\n')
			{
				temp[len - 1] = '\0';

				if (!IsAllAlpha(temp))
				{
					printf("Input failed: Name must not contain spaces, digits, or special characters.\n");
					return 0;
				}

				int invalid = 0;
				char* ch = temp;
				while (*ch != '\0')
				{
					if (!isalpha(*ch))
					{
						invalid = 1;
						printf("Input failed: Name must not contain spaces, digits, or special characters.\n");
						break;
					}
					ch++;
				}

				if (!invalid)
				{
					strcpy_s(buffer, MAX_NAME_LEN, temp);
					return 1;
				}
			}
			else
			{
				if (len == 1)
					printf("Input failed: Name cannot be empty.\n");
				else
					printf("Input too long. Max allowed is %d characters.\n", MAX_NAME_LEN);
				return 0;
			}
		}
		else
			printf("Input failed. Try again.\n");
		_getch();
		system("cls");
	}
	return 0;
}

int GetPhone(char* buffer)
{
	char temp[MAX_PHONE_LEN] = { 0 };
	while (1)
	{
		printf("Enter the phone number (without hyphens '-'): ");
		if (fgets(temp, sizeof(temp), stdin) != NULL)
		{
			size_t len = strlen(temp);
			if ((len == MAX_PHONE_LEN - 2) && (temp[len - 1] == '\n'))
			{
				temp[len - 1] = '\0';

				int i = 0;
				int invalid = 0;
				char* ch = temp;
				while (*ch != '\0')
				{
					if (isdigit(*ch))
					{
						if (i == 3 || i == 8)
							buffer[i++] = '-';
						buffer[i++] = *ch;
					}
					else
					{
						invalid = 1;
						printf("Input failed: Only digits are allowed.\n");
						break;
					}
					ch++;
				}

				
				if (!IsPhoneFormat(temp))
				{
					invalid = 1;
					printf("Input faile: Invalid format.\n");
					return 0;
				}

				if (!invalid)
				{
					buffer[i] = '\0';
					return 1;
				}
			}
			else
			{
				if (len == 1)
					printf("Input failed: Phone number cannot be empty.\n");
				else
				{
					printf("Phone number must be exactly %d digits (e.g., 01012345678.)\n", MAX_PHONE_LEN - 3);	// hyphens and null character.
				}
				return 0;
			}
		}
		else
		{
			printf("Input failed. Try again.\n");
		}
		_getch();
		system("cls");
	}
	return 0;
}

int GetAge(int* age)
{
	char temp[BUFFSIZE] = { 0 };
	while (1)
	{
		printf("Enter the age : ");
		fgets(temp, sizeof(temp), stdin);
		size_t len = strlen(temp);
		if (len > 1 && temp[len - 1] == '\n')
		{
			temp[len - 1] = '\0';

			if (!IsAllDigit(temp))
				printf("Insert failed: Invalid input.\n");

			*age = atoi(temp);
			if (*age > 0 && *age <= MAXAGE)
			{
				return 1;
			}
			else
			{
				*age = 0;
				printf("Insert failed: Invalid value.\n");
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
		_getch();
		system("cls");
	}
	return 0;
}

int GetSearchString(char* buffer)
{
	char temp[BUFFSIZE] = { 0 };
	printf("Search string: ");
	fgets(temp, sizeof(temp), stdin);
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
			printf("Invalid input.\n");
		return 0;
	}

	strcpy_s(buffer, BUFFSIZE, temp);
	return 1;
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
	int flag = 1;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	InitList(pList);

	do
	{
		printf("\nEnter new data: need [Name] [Age] [Phone number]\n");
		GetName(name);

		GetAge(&age);

		GetPhone(phone);

		if (LoadNodeFromFileByPhone(NULL, phone, PATH))
		{
			printf("\nInsert failed: Phone number is already exist.\n");
			break;
		}
		else
		{
			InsertNodeAtEnd(pList, age, name, phone);
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

	SaveListToFile(pList, PATH);
	ReleaseList(pList);
	return 1;
}

int UI_DeleteNode(const char* PATH)
{
	int flag = 1;
	char phone[MAX_PHONE_LEN] = { 0 };

	do
	{
		printf("Need the phone number to delete **************\n");
		GetPhone(phone);

		if (LoadNodeFromFileByPhone(NULL, phone, PATH) != 1)
		{
			printf("Deletion failed: No matching record found.\n");
			return 0;
		}
		else
		{
			if (DeleteNodeFromFile(phone, PATH) == 1)
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
	printf("You can use \"AND\" or \"OR\" to search.\n");
	char buffer[BUFFSIZE] = { 0 };
	if (GetSearchString(buffer))
	{
		SearchNode(buffer, PATH);
	}
	return 1;
}

int UI_EditNode(const char* PATH)
{
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	InitList(pList);

	printf("Need phone number of the node to edit **************\n");
	GetPhone(phone);

	if (LoadNodeFromFileByPhone(pList, phone, PATH) != 1)
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
				GetAge(&age);
				EditNodeFromFileByAge(ptr, age, PATH);

				break;
			case 2:
				GetName(name);
				EditNodeFromFileByName(ptr, name, PATH);

				break;
			case 3:
				GetPhone(phone);

				if (LoadNodeFromFileByPhone(NULL, phone, PATH) == 1)
				{
					printf("Edit failed: Phone number is already exist.\n");
				}
				else
					EditNodeFromFileByPhone(ptr, phone, PATH);
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

int ConvertInputToSearchString(const char* str, int* age, char* name, char* phone)
{
	if (IsAllDigit(str))
	{
		*age = atoi(str);
		if (*age < 0 || *age > MAXAGE)
		{
			printf("Input failed: Invalid age.\n");
			return 0;
		}
	}
	else
	{
		if (IsAllAlpha(str))
			strcpy_s(name, MAX_NAME_LEN, str);
		else if (IsPhoneFormat(str))
			strcpy_s(phone, MAX_PHONE_LEN, str);
		else
		{
			printf("Input failed: Invalid input.\n");
			return 0;
		}
	}
	return 1;
}

int ParseSearchInput(const char* input, char temp1[], char temp2[], char op[])
{
	int i = 0;
	const char* ch = input;
	while (*ch != '\0')
	{
		if (*ch == ' ')
		{
			ch++;
			break;
		}

		temp1[i++] = *ch;
		ch++;
	}
	temp1[i] = '\0';

	i = 0;
	while (*ch != '\0')
	{
		if (*ch == ' ')
		{
			ch++;
			break;
		}

		op[i++] = *ch;
		ch++;
	}
	op[i] = '\0';

	i = 0;
	while (*ch != '\0')
	{
		temp2[i++] = *ch;
		ch++;
	}
	temp2[i] = '\0';

	return 1;
}

int SearchNode(const char* input, const char* PATH)
{
	printf("Input: %s\n", input);
	if (*input == '\n')
	{
		printf("Input failed: Input cannot be empty.\n");
		return 0;
	}

	int searched = 0;
	int age1 = 0;
	char name1[MAX_NAME_LEN] = { 0 };
	char phone1[MAX_PHONE_LEN] = { 0 };
	int age2 = 0;
	char name2[MAX_NAME_LEN] = { 0 };
	char phone2[MAX_PHONE_LEN] = { 0 };

	LIST* pListName1 = (LIST*)malloc(sizeof(LIST));
	LIST* pListName2 = (LIST*)malloc(sizeof(LIST));
	LIST* pListPhone1 = (LIST*)malloc(sizeof(LIST));
	LIST* pListPhone2 = (LIST*)malloc(sizeof(LIST));
	LIST* pListAge1 = (LIST*)malloc(sizeof(LIST));
	LIST* pListAge2 = (LIST*)malloc(sizeof(LIST));
	InitList(pListName1);
	InitList(pListName2);
	InitList(pListPhone1);
	InitList(pListPhone2);
	InitList(pListAge1);
	InitList(pListAge2);

	char temp1[MAX_NAME_LEN] = { 0 };
	char temp2[MAX_NAME_LEN] = { 0 };
	char op[BUFFSIZE] = { 0 };

	int isValid = 1;

	if (!ParseSearchInput(input, temp1, temp2, op))
		isValid = 0;

	if (temp1[0] == 0)
		isValid = 0;

	if (!ConvertInputToSearchString(temp1, &age1, name1, phone1))
		isValid = 0;

	if (temp2[0] != 0)
	{
		if (strcmp(op, "AND") != 0 && strcmp(op, "and") != 0 &&
			strcmp(op, "OR") != 0 && strcmp(op, "or") != 0)
		{
			printf("Input failed: Invalid operator.\n");
			return 0;
		}
		ConvertInputToSearchString(temp2, &age2, name2, phone2);
	}

	if (isValid)
	{
		printf("Search result **********************************\n");
		LIST* pResultList = (LIST*)malloc(sizeof(LIST));
		InitList(pResultList);
		if (op[0] == 0)
		{
			if (age1 != 0)
			{
				LoadNodeFromFileByAge(pResultList, age1, PATH);
			}
			else if (name1[0] != 0)
			{
				LoadNodeFromFileByName(pResultList, name1, PATH);
			}
			else if (phone1[0] != 0)
			{
				LoadNodeFromFileByPhone(pResultList, phone1, PATH);
			}

			if (!IsEmpty(pResultList))
				PrintList(pResultList);
			else
				printf("No matching record found.\n");
		}
		else if (op[0] != 0)
		{
			// op is "AND" or "OR"
			if (age1 != 0 && age2 != 0)
			{
				LoadNodeFromFileByAge(pListAge1, age1, PATH);
				LoadNodeFromFileByAge(pListAge2, age2, PATH);
				CombineList(pResultList, pListAge1, pListAge2, op);
			}
			else if (age1 != 0 && name2[0] != 0)
			{
				LoadNodeFromFileByAge(pListAge1, age1, PATH);
				LoadNodeFromFileByName(pListName2, name2, PATH);
				CombineList(pResultList, pListAge1, pListName2, op);
			}
			else if (age1 != 0 && phone2[0] != 0)
			{
				LoadNodeFromFileByAge(pListAge1, age1, PATH);
				LoadNodeFromFileByPhone(pListPhone2, phone2, PATH);
				CombineList(pResultList, pListAge1, pListPhone2, op);
			}
			else if (name1[0] != 0 && age2 != 0)
			{
				LoadNodeFromFileByName(pListName1, name1, PATH);
				LoadNodeFromFileByAge(pListAge2, age2, PATH);
				CombineList(pResultList, pListName1, pListAge2, op);
			}
			else if (name1[0] != 0 && name2[0] != 0)
			{
				LoadNodeFromFileByName(pListName1, name1, PATH);
				LoadNodeFromFileByName(pListName2, name2, PATH);
				CombineList(pResultList, pListName1, pListName2, op);
			}
			else if (name1[0] != 0 && phone2[0] != 0)
			{
				LoadNodeFromFileByName(pListName1, name1, PATH);
				LoadNodeFromFileByPhone(pListPhone2, phone2, PATH);
				CombineList(pResultList, pListName1, pListPhone2, op);
			}
			else if (phone1[0] != 0 && age2 != 0)
			{
				LoadNodeFromFileByPhone(pListPhone1, phone1, PATH);
				LoadNodeFromFileByAge(pListAge2, age2, PATH);
				CombineList(pResultList, pListPhone1, pListAge2, op);
			}
			else if (phone1[0] != 0 && name2[0] != 0)
			{
				LoadNodeFromFileByPhone(pListPhone1, phone1, PATH);
				LoadNodeFromFileByName(pListName2, name2, PATH);
				CombineList(pResultList, pListPhone1, pListName2, op);
			}
			else if (phone1[0] != 0 && phone2[0] != 0)
			{
				LoadNodeFromFileByPhone(pListPhone1, phone1, PATH);
				LoadNodeFromFileByPhone(pListPhone2, phone2, PATH);
				CombineList(pResultList, pListPhone1, pListPhone2, op);
			}

			if (!IsEmpty(pResultList))
				PrintList(pResultList);
			else
			{
				printf("No matching record found.\n");
				_getch();
			}

			ReleaseList(pResultList);
			free(pResultList);
		}
		else
			printf("Input failed: Invalid operator.\n");

		ReleaseList(pListAge1);
		ReleaseList(pListAge2);
		ReleaseList(pListName1);
		ReleaseList(pListName2);
		ReleaseList(pListPhone1);
		ReleaseList(pListPhone2);
		free(pListAge1);
		free(pListAge2);
		free(pListName1);
		free(pListName2);
		free(pListPhone1);
		free(pListPhone2);
		putchar('\n');
	}
	else
	{
		_getch();
		return 0;
	}
	return 1;
}

void PrintList(LIST* pL)
{
	if (IsEmpty(pL))
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

		printf("************************************************\n");
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