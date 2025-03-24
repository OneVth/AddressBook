/* INCLUDES		*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define MAX_NAME_LEN 20
#define MAX_PHONE_LEN 14	// 000-0000-0000 + '\0'
#define BUFFSIZE 200
#define MAXAGE 200
#define FILE_PATH "Data.dat"
#define FILE_PATH_TEST "test.dat"

typedef enum { EXIT, INSERT, DELETE, SEARCH, EDIT } OPTION;

typedef struct node {
	int age;
	char name[MAX_NAME_LEN];
	char phone[MAX_PHONE_LEN];
	struct node* next;
	struct node* prev;
} NODE;

typedef struct {
	NODE head;
	NODE tail;
} LIST;

/* GLOBALS		*******************************************************/

/* FUNCTIONS	*******************************************************/

// UI
OPTION PrintMenu(void);
int GetName(char* buffer);
int GetPhone(char* buffer);
int GetAge(int* age);
void ClearInputBuffer(void);
int InsertNode(const char* PATH);
int DeleteNode(const char* PATH);
int GetSearchString(char* buffer);
int SearchNode(const char* input, const char* PATH);
int EditNode(const char* PATH);
//int ExitMenu(void);
void PrintList(LIST* pL);

// Control
void initList(LIST* pL);
int isEmpty(LIST* pL);
int insertNodeAtBeg(LIST* pL, const int age, const char* name, const char* phone);
int insertNodeAtEnd(LIST* pL, const int age, const char* name, const char* phone);
int deleteNodeAtEnd(LIST* pL);
int deleteNodeAtBeg(LIST* pL);
int deleteNodeByPhone(LIST* pL, const char* phone);
int deleteNodeFromFile(const char* phone, const char* path);
int searchNodeByPhone(LIST* pL, const char* phone, const char* path);
int searchNodeByName(LIST* pL, const char* name, const char* path);
int searchNodeByAge(LIST* pL, const int age, const char* path);
int editNodeAge(NODE* ptr, const int age, const char* path);
int editNodeName(NODE* ptr, const char* name, const char* path);
int editNodePhone(NODE* ptr, const char* phone, const char* path);
int saveListToFile(LIST* pL, const char* path);
void releaseList(LIST* pL);

// Test
void CreateTestFile(void);
void ReadTestFile(void);
void TestControlFunc(void);
void TestFileIOFunc(void);
void TestSearchFunc(void);
void TestEditFunc(void);
void TestUIFunc(void);

//void StringSlice(void)
//{
//	char buff[200] = { "Kim" };
//
//	char op[4] = { 0 };
//	char temp1[20] = { 0 };
//	char temp2[20] = { 0 };
//
//	int age = 0;
//	char name[20] = { 0 };
//	char phone[20] = { 0 };
//
//	/*printf("Search: ");
//	gets_s(buff, sizeof(buff));*/
//
//	printf("Origin: %s\n", buff);
//
//	char* temp = buff;
//	int i = 0;
//	while (*temp != '\0')
//	{
//		if (*temp == ' ')
//		{
//			temp++;
//			break;
//		}
//
//		temp1[i++] = *temp;
//		temp++;
//	}
//	temp1[i] = '\0';
//
//	i = 0;
//	while (*temp != '\0')
//	{
//		if (*temp == ' ')
//		{
//			temp++;
//			break;
//		}
//
//		op[i++] = *temp;
//		temp++;
//	}
//	op[i] = '\0';
//
//	i = 0;
//	while (*temp != '\0')
//	{
//		temp2[i++] = *temp;
//		temp++;
//	}
//	temp2[i] = '\0';
//
//	if (strpbrk(temp1, "-") != NULL)
//	{
//		strcpy_s(phone, sizeof(phone), temp1);
//	}
//	else if (atoi(temp1) != 0)
//	{
//		age = atoi(temp1);
//	}
//	else if (*temp1 != 0)
//	{
//		strcpy_s(name, sizeof(name), temp1);
//	}
//
//	if (strpbrk(temp2, "-") != NULL)
//	{
//		strcpy_s(phone, sizeof(phone), temp2);
//
//	}
//	else if (atoi(temp2) != 0)
//	{
//		age = atoi(temp2);
//	}
//	else if (*temp2 != 0)
//	{
//		strcpy_s(name, sizeof(name), temp2);
//	}
//
//	printf("%d %s %s\n", age, name, phone);
//
//	if (strcmp(op, "or") == 0)
//	{
//
//	}
//	else if (strcmp(op, "OR") == 0)
//	{
//
//	}
//	else if (strcmp(op, "and") == 0)
//	{
//
//	}
//	else if (strcmp(op, "AND") == 0)
//	{
//
//	}
//	else
//	{
//		NODE* ptr = g_head->next;
//		if (age != 0)
//		{
//			while (ptr != g_tail)
//			{
//				if (ptr->age == age)
//					printf("%d %s %s\n", ptr->age, ptr->name, ptr->phone);
//				ptr = ptr->next;
//			}
//		}
//		else if (name[0] != 0)
//		{
//			while (ptr != g_tail)
//			{
//				if (strcmp(ptr->name, name) == 0)
//					printf("%d %s %s\n", ptr->age, ptr->name, ptr->phone);
//				ptr = ptr->next;
//			}
//		}
//		else if (phone[0] != 0)
//		{
//			while (ptr != g_tail)
//			{
//				if (strcmp(ptr->phone, phone) == 0)
//					printf("%d %s %s\n", ptr->age, ptr->name, ptr->phone);
//				ptr = ptr->next;
//			}
//		}
//	}
//}

int main(void)
{
	TestUIFunc();
	//InsertNode();

	/*int (*pfMenu[5])(void) = { ExitMenu, InsertNode, DeleteNode, SearchNode, EditNode };

	initList();
	loadListFromFile();

	OPTION option = PrintMenu();
	do
	{
		system("cls");
		pfMenu[option]();
		_getch();
	} while ((option = PrintMenu()) != EXIT);*/

	return 0;
}

void CreateTestFile(void)
{
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	initList(pList);

	insertNodeAtEnd(pList, 10, "Kim", "010-0000-0000");
	insertNodeAtEnd(pList, 11, "Kim", "010-0000-0001");
	insertNodeAtEnd(pList, 12, "Kim", "010-0000-0002");
	insertNodeAtEnd(pList, 13, "Kim", "010-0000-0003");
	insertNodeAtEnd(pList, 14, "Lee", "010-0000-0004");
	insertNodeAtEnd(pList, 15, "Lee", "010-0000-0005");
	insertNodeAtEnd(pList, 16, "Park", "010-0000-0006");
	insertNodeAtEnd(pList, 17, "Jung", "010-0000-0007");
	insertNodeAtEnd(pList, 18, "Hwang", "010-0000-0008");
	insertNodeAtEnd(pList, 19, "Sung", "010-0000-0009");
	insertNodeAtEnd(pList, 20, "Kim", "010-0000-0010");
	insertNodeAtEnd(pList, 20, "Lee", "010-0000-0011");
	insertNodeAtEnd(pList, 20, "Park", "010-0000-0012");

	printf("Test file *********************\n");

	FILE* fp = NULL;
	fopen_s(&fp, FILE_PATH_TEST, "wb");
	if (fp == NULL)
	{
		printf("Failed to open file.\n");
	}

	NODE* ptr = pList->head.next;
	while (ptr != &pList->tail)
	{
		printf("%2d %-5s %s\n", ptr->age, ptr->name, ptr->phone);
		fwrite(ptr, sizeof(NODE), 1, fp);
		ptr = ptr->next;
	}
	releaseList(pList);
	fclose(fp);
	printf("*******************************\n\n");
}

void ReadTestFile(void)
{
	printf("\nReadTestFile() ***************\n");
	FILE* fp = NULL;
	fopen_s(&fp, FILE_PATH_TEST, "rb");
	if (fp == NULL)
	{
		printf("Failed to open file.\n");
	}

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		printf("%2d %-5s %s\n", temp->age, temp->name, temp->phone);
	}

	free(temp);
	fclose(fp);
	printf("*******************************\n\n");
}

void TestControlFunc(void)
{
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	initList(pList);

	insertNodeAtEnd(pList, 10, "Kim", "010-0000-0000");
	insertNodeAtEnd(pList, 11, "Kim", "010-0000-0001");
	insertNodeAtEnd(pList, 12, "Kim", "010-0000-0002");
	insertNodeAtEnd(pList, 13, "Kim", "010-0000-0003");
	insertNodeAtEnd(pList, 14, "Lee", "010-0000-0004");
	insertNodeAtEnd(pList, 15, "Lee", "010-0000-0005");
	insertNodeAtEnd(pList, 16, "Park", "010-0000-0006");
	insertNodeAtEnd(pList, 17, "Jung", "010-0000-0007");
	insertNodeAtEnd(pList, 18, "Hwang", "010-0000-0008");
	insertNodeAtEnd(pList, 19, "Sung", "010-0000-0009");

	/*insertNodeAtBeg(pList, 10, "Kim", "010-0000-0000");
	insertNodeAtBeg(pList, 11, "Kim", "010-0000-0001");
	insertNodeAtBeg(pList, 12, "Kim", "010-0000-0002");
	insertNodeAtBeg(pList, 13, "Kim", "010-0000-0003");
	insertNodeAtBeg(pList, 14, "Lee", "010-0000-0004");
	insertNodeAtBeg(pList, 15, "Lee", "010-0000-0005");
	insertNodeAtBeg(pList, 16, "Park", "010-0000-0006");
	insertNodeAtBeg(pList, 17, "Jung", "010-0000-0007");
	insertNodeAtBeg(pList, 18, "Hwang", "010-0000-0008");
	insertNodeAtBeg(pList, 19, "Sung", "010-0000-0009");*/
	printf("Before ----------------------------------------------------------\n");
	PrintList(pList);
	printf("-----------------------------------------------------------------\n");

	deleteNodeAtBeg(pList);
	deleteNodeAtBeg(pList);
	deleteNodeAtBeg(pList);
	deleteNodeAtBeg(pList);
	deleteNodeAtBeg(pList);
	deleteNodeAtBeg(pList);
	deleteNodeAtBeg(pList);
	deleteNodeAtBeg(pList);
	deleteNodeAtBeg(pList);
	deleteNodeAtBeg(pList);

	/*deleteNodeAtEnd(pList);
	deleteNodeAtEnd(pList);
	deleteNodeAtEnd(pList);
	deleteNodeAtEnd(pList);
	deleteNodeAtEnd(pList);
	deleteNodeAtEnd(pList);
	deleteNodeAtEnd(pList);
	deleteNodeAtEnd(pList);
	deleteNodeAtEnd(pList);
	deleteNodeAtEnd(pList);*/

	insertNodeAtEnd(pList, 10, "Kim", "010-0000-0000");
	insertNodeAtEnd(pList, 11, "Kim", "010-0000-0001");
	insertNodeAtEnd(pList, 12, "Kim", "010-0000-0002");
	insertNodeAtEnd(pList, 13, "Kim", "010-0000-0003");
	insertNodeAtEnd(pList, 14, "Lee", "010-0000-0004");
	insertNodeAtEnd(pList, 15, "Lee", "010-0000-0005");
	insertNodeAtEnd(pList, 16, "Park", "010-0000-0006");
	insertNodeAtEnd(pList, 17, "Jung", "010-0000-0007");
	insertNodeAtEnd(pList, 18, "Hwang", "010-0000-0008");
	insertNodeAtEnd(pList, 19, "Sung", "010-0000-0009");

	/*insertNodeAtBeg(pList, 10, "Kim", "010-0000-0000");
	insertNodeAtBeg(pList, 12, "Kim", "010-0000-0001");
	insertNodeAtBeg(pList, 11, "Kim", "010-0000-0002");
	insertNodeAtBeg(pList, 13, "Kim", "010-0000-0003");
	insertNodeAtBeg(pList, 14, "Lee", "010-0000-0004");
	insertNodeAtBeg(pList, 15, "Lee", "010-0000-0005");
	insertNodeAtBeg(pList, 16, "Park", "010-0000-0006");
	insertNodeAtBeg(pList, 17, "Jung", "010-0000-0007");
	insertNodeAtBeg(pList, 18, "Hwang", "010-0000-0008");
	insertNodeAtBeg(pList, 19, "Sung", "010-0000-0009");*/

	printf("After -----------------------------------------------------------\n");
	PrintList(pList);
	printf("-----------------------------------------------------------------\n");

	releaseList(pList);
	free(pList);
}

void TestSearchFunc(void)
{
	CreateTestFile();

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	initList(pList);

	NODE* ptr = (NODE*)malloc(sizeof(NODE));
	ptr->age = 15;
	strcpy_s(ptr->name, sizeof(ptr->name), "Kim");
	strcpy_s(ptr->phone, sizeof(ptr->phone), "010-9999-9999");

	// Test search by phone ----------------------------------------------------
	printf("Search by phone number ************\n");
	printf("Origin: %2d %s [%s]\n", ptr->age, ptr->name, ptr->phone);
	if (searchNodeByPhone(pList, ptr->phone, FILE_PATH_TEST))
	{
		// Phone number duplication doesn't exist
		NODE* temp = pList->head.next;
		printf("Found: %3d %-5s [%s]\n", temp->age, temp->name, temp->phone);
	}
	else
	{
		printf("Not Found\n");
	}
	releaseList(pList);
	printf("***********************************\n\n");


	// Test search by name ----------------------------------------------------
	initList(pList);

	printf("Search by name ********************\n");
	printf("Origin: %2d [%s] %s\n", ptr->age, ptr->name, ptr->phone);
	if (searchNodeByName(pList, ptr->name, FILE_PATH_TEST))
	{
		NODE* temp = pList->head.next;
		while (temp != &pList->tail)
		{
			printf("Found: %2d - [%s] - %s\n", temp->age, temp->name, temp->phone);
			temp = temp->next;
		}
	}
	else
	{
		printf("Not Found\n");
	}
	releaseList(pList);
	printf("***********************************\n\n");

	// Test search by age ----------------------------------------------------
	initList(pList);
	printf("Search by age *********************\n");
	printf("Origin: [%2d] %s %s\n", ptr->age, ptr->name, ptr->phone);
	if (searchNodeByAge(pList, ptr->age, FILE_PATH_TEST))
	{
		NODE* temp = pList->head.next;
		while (temp != &pList->tail)
		{
			printf("Found: [%2d] - %s - %s\n", temp->age, temp->name, temp->phone);
			temp = temp->next;
		}
	}
	else
	{
		printf("Not Found\n");
	}
	releaseList(pList);
	printf("***********************************\n\n");

	free(ptr);
	free(pList);
}

void TestFileIOFunc(void)
{
	CreateTestFile();

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	initList(pList);

	// don't exist
	insertNodeAtEnd(pList, 20, "Park", "010-0001-0000");
	insertNodeAtEnd(pList, 21, "Park", "010-0002-0000");
	insertNodeAtEnd(pList, 22, "Park", "010-0003-0000");

	// already exist
	insertNodeAtEnd(pList, 13, "Kim", "010-0000-0003");
	insertNodeAtEnd(pList, 14, "Lee", "010-0000-0004");
	insertNodeAtEnd(pList, 15, "Lee", "010-0000-0005");

	saveListToFile(pList, FILE_PATH_TEST);
	free(pList);

	printf("Test: file IO function ********\n");
	ReadTestFile();
	printf("*******************************\n\n");
}

void TestEditFunc(void)
{
	CreateTestFile();

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->next = NULL;
	temp->prev = NULL;
	temp->age = 13;
	strcpy_s(temp->name, sizeof(temp->name), "Kim");
	strcpy_s(temp->phone, sizeof(temp->phone), "010-0000-0003");

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	initList(pList);
	searchNodeByPhone(pList, temp->phone, FILE_PATH_TEST);
	editNodeAge(pList->head.next, 93, FILE_PATH_TEST);
	editNodeName(pList->head.next, "Test", FILE_PATH_TEST);
	editNodePhone(pList->head.next, "010-1234-5678", FILE_PATH_TEST);
	releaseList(pList);
	free(temp);

	printf("Test: edit function ***********\n");
	ReadTestFile();
	printf("*******************************\n\n");
}

int GetName(char* buffer)
{
	char name[MAX_NAME_LEN] = { 0 };
	while (1)
	{
		printf("Enter the name (max %d chars): ", MAX_NAME_LEN - 1);
		if (fgets(name, sizeof(name), stdin) != NULL)
		{
			size_t len = strlen(name);
			if (len > 1 && name[len - 1] == '\n')
			{
				name[len - 1] = '\0';

				int invalid = 0;
				char* ch = name;
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
					strcpy_s(buffer, MAX_NAME_LEN, name);
					return 1;
				}
			}
			else
			{
				if (len == 1)
					printf("Input failed: Name cannot be empty.\n");
				else
					printf("Input too long. Max allowed is %d characters.\n", MAX_NAME_LEN);

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

			*age = atoi(temp);
			if (*age > 0 && *age <= MAXAGE)
			{
				return 1;
			}
			else
			{
				*age = 0;
				printf("Insert failed: Invalid value.\n");
			}
		}
		else
		{
			if (len == 1)
				printf("Insert failed: Age cannot be empty.\n");
			else
				printf("Insert failed: Invalid value.\n");
		}
		_getch();
		system("cls");

	}
}

void TestUIFunc(void)
{
	CreateTestFile();
	//InsertNode(FILE_PATH_TEST);
	//EditNode(FILE_PATH_TEST);
	//DeleteNode(FILE_PATH_TEST);

	const char* testCases[] = {
		// ********************** Single ***********************
		"Lee",								// name (multiple matching)
		"Sung",								// name (single matching)
		"20",								// age (multiple matching)
		"10",								// age (single matching)
		"010-0000-0000",					// phone (single matching)
		"010-0000-0012",					// phone (single matching)

		// ********************** AND **************************
		"20 AND Kim",						// age AND name (matching)
		"20 AND Lee",						// age AND name (non-matching)
		"12 AND 010-0000-0002",				// age AND phone (matching)
		"12 AND 010-0000-0001",				// age AND phone (non-matching)
		"Jung AND 17",						// name AND age (matching)
		"Lee AND 10",						// name AND age (non-matching)
		"Lee AND 010-0000-0011",			// name AND phone (matching)
		"Kim AND 010-0000-0007",			// name AND phone (non-matching)
		"010-0000-0000 AND 10",				// phone AND age (matching)
		"010-0000-0001 AND 15",				// phone AND age (non-matching)

		// ********************** OR ***************************
		"14 OR 20",							// age OR age (both matching)
		"10 OR 30",							// age OR age (left matching)
		"10 OR 30",							// age OR age (right matching)
		"30 OR 40",							// age OR age (non-matching)

		"20 OR Hwang",						// age OR name (both matching)
		"18 OR Kwon",						// age OR name (left matching) 
		"30 OR Kim",						// age OR name (right matching) 
		"30 OR Jeon",						// age OR name (non-matching) 

		"15 OR 010-0000-0012",				// age OR phone (both matching)
		"19 OR 010-0000-1111",				// age OR phone (left matching)
		"30 OR 010-0000-0008",				// age OR phone (right matching)
		"40 OR 010-0000-2222",				// age OR phone (non-matching)

		"Kim OR 14",						// name OR age (both matching)
		"Lee OR 30",						// name OR age (left matching)
		"Kwon OR 17",						// name OR age (right matching)
		"Kwon OR 30",						// name OR age (non-matching)

		"Kim OR Park",						// name OR name (both matching)
		"Kim OR Kwon",						// name OR name (left matching)
		"Kwon OR Lee",						// name OR name (right matching)
		"Kwon OR Jeon",						// name OR name (non-matching)

		"Park OR 010-0000-0006",			// name OR phone (both matching)
		"Lee OR 010-0000-3333",				// name OR phone (left matching)
		"Kwon OR 010-0000-0011",			// name OR phone (right matching)
		"Jeon OR 010-0000-4444",			// name OR phone (non-matching)

		"010-0000-0000 OR 10",				// phone OR age (both matching) 
		"010-0000-0004 OR 30",				// phone OR age (left matching) 
		"010-0000-5555 OR 20",				// phone OR age (right matching)
		"010-0000-6666 OR 40",				// phone OR age (non-matching)

		"010-0000-0003 OR Kim",				// phone OR name (both matching)
		"010-0000-0006 OR Kwon",			// phone OR name (left matching) 
		"010-0000-7777 OR Lee",				// phone OR name (right matching) 
		"010-0000-8888 OR Jeon",			// phone OR name (non-matching) 

		"010-0000-0003 OR 010-0000-0005",	// phone OR phone (both matching)
		"010-0000-0004 OR 010-0000-9999",	// phone OR phone (left matching)
		"010-0000-1111 OR 010-0000-0007",	// phone OR phone (right matching)
		"010-0000-2222 OR 010-0000-3333",	// phone OR phone (non-matching)

		// ********************* Invalid ************************
		"",									// empty input
		"abc",								// invalid name
		"999",								// invalid age
		"010-9999-9999",					// nonexistent phone
		"Kim XOR Park",						// invalid operator
		"Kim AND",							// incomplete expression
		"AND Kim Lee",						// misplaced operator
		"20 AND abc@"						// special characters
	};

	int testStringCount = sizeof(testCases) / sizeof(testCases[0]);
	for (int i = 0; i < testStringCount; i++)
	{
		printf("\nTest case %d: \"%s\"\n", i + 1, testCases[i]);
		SearchNode(testCases[i], FILE_PATH_TEST);
	}

	ReadTestFile();
}

void ClearInputBuffer(void)
{
	char ch = 0;
	while ((ch = getchar()) != '\n');
}

int InsertNode(const char* PATH)
{
	int age = 0;
	int flag = 1;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	initList(pList);

	printf("Insert node at \"%s\"\n", PATH);
	do
	{
		printf("\nEnter new data: need [Name] [Age] [Phone number]\n");
		GetName(name);

		GetAge(&age);

		GetPhone(phone);

		if (searchNodeByPhone(NULL, phone, PATH))
		{
			printf("\nInsert failed: Phone number is already exist.\n");
			break;
		}
		else
		{
			insertNodeAtEnd(pList, age, name, phone);
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

	saveListToFile(pList, PATH);
	releaseList(pList);
	return 1;
}

int DeleteNode(const char* PATH)
{
	int flag = 1;
	char phone[MAX_PHONE_LEN] = { 0 };

	do
	{
		printf("Need the phone number to delete **************\n");
		GetPhone(phone);

		if (searchNodeByPhone(NULL, phone, PATH) != 1)
		{
			printf("Deletion failed: No matching record found.\n");
			return 0;
		}
		else
		{
			if (deleteNodeFromFile(phone, PATH) == 1)
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

int isAllDigit(const char* str)
{
	if (*str == '\0')
		return 0;

	while (*str != '\0')
	{
		if (!isdigit(*str))
			return 0;
		str++;
	}
	return 1;
}

int isAllAlpha(const char* str)
{
	if (*str == '\0')
		return 0;

	while (*str != '\0')
	{
		if (!isalpha(*str))
			return 0;
		str++;
	}
	return 1;
}

int isPhoneFormat(const char* str)
{
	if (*str == '\0')
		return 0;

	return ((strlen(str) == 13) && (str[3] == '-') && (str[8] == '-') ? 1 : 0);
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

int SearchNode(const char* input, const char* PATH)
{
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
	initList(pListName1);
	initList(pListName2);
	initList(pListPhone1);
	initList(pListPhone2);
	initList(pListAge1);
	initList(pListAge2);

	char temp1[MAX_NAME_LEN] = { 0 };
	char temp2[MAX_NAME_LEN] = { 0 };
	char op[4] = { 0 };

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

	if (temp1[0] == 0)
	{
		printf("Input failed: Invalid input.\n");
		return 0;
	}

	if (isAllDigit(temp1))
	{
		age1 = atoi(temp1);
		if (age1 < 0 || age1 > MAXAGE)
		{
			printf("Input failed: Invalid age.\n");
			return 0;
		}
	}
	else
	{
		if (isAllAlpha(temp1))
			strcpy_s(name1, sizeof(name1), temp1);
		else if (isPhoneFormat(temp1))
			strcpy_s(phone1, sizeof(phone1), temp1);
		else
			printf("Input failed: Invalid input.\n");
	}

	if (temp2[0] != 0)
	{
		if (isAllDigit(temp2))
		{
			age2 = atoi(temp2);
			if (age2 < 0 || age2 > MAXAGE)
			{
				printf("Input failed: Invalid age.\n");
				return 0;
			}
		}
		else
		{
			if (isAllAlpha(temp2))
				strcpy_s(name2, sizeof(name2), temp2);
			else if (isPhoneFormat(temp2))
				strcpy_s(phone2, sizeof(phone2), temp2);
			else
				printf("Input failed: Invalid input.\n");
		}
	}

	printf("Search result **********************************\n");
	if (op[0] == 0)
	{
		if (age1 != 0)
		{
			if (searchNodeByAge(pListAge1, age1, PATH) == 1)
				PrintList(pListAge1);
			else
				printf("No matching record found.\n");
		}
		else if (name1[0] != 0)
		{
			if (searchNodeByName(pListName1, name1, PATH) == 1)
				PrintList(pListName1);
			else
				printf("No matching record found.\n");
		}
		else if (phone1[0] != 0)
		{
			if (searchNodeByPhone(pListPhone1, phone1, PATH) == 1)
				PrintList(pListPhone1);
			else
				printf("No matching record found.\n");
		}
	}
	else
	{
		// op is "AND" or "OR"
		int name1Searched = 0;
		int name2Searched = 0;
		int phone1Searched = 0;
		int phone2Searched = 0;
		int age1Searched = 0;
		int age2Searched = 0;
		if (strcmp(op, "or") == 0 || strcmp(op, "OR") == 0)
		{
			if (age1 != 0 && age2 != 0)
			{
				age1Searched = searchNodeByAge(pListAge1, age1, PATH);
				age2Searched = searchNodeByAge(pListAge2, age2, PATH);
				if (age1Searched == 1 || age2Searched == 1)
				{
					PrintList(pListAge1);
					PrintList(pListAge2);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (age1 != 0 && name2[0] != 0)
			{
				age1Searched = searchNodeByAge(pListAge1, age1, PATH);
				name2Searched = searchNodeByName(pListName2, name2, PATH);
				if (age1Searched == 1 || name2Searched == 1)
				{
					NODE* ptrAge = pListAge1->head.next;
					NODE* ptrName = pListName2->head.next;
					if (age1Searched && name2Searched)
					{
						LIST* pList = (LIST*)malloc(sizeof(LIST));
						initList(pList);
						while (ptrAge != &pListAge1->tail)
						{
							int flag = 0;
							ptrName = pListName2->head.next;
							while (ptrName != &pListName2->tail)
							{
								if (strcmp(ptrAge->phone, ptrName->phone) == 0)
								{
									flag = 1;
									NODE* ptr = ptrName;
									ptrName = ptrName->next;
									ptrAge = ptrAge->next;
									insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
									deleteNodeByPhone(pListAge1, ptr->phone);
									deleteNodeByPhone(pListName2, ptr->phone);
									break;
								}
								else
									ptrName = ptrName->next;
							}

							if (!flag)
								ptrAge = ptrAge->next;
						}

						PrintList(pList);
						PrintList(pListAge1);
						PrintList(pListName2);

						releaseList(pList);
					}
					else if (age1Searched)
					{
						PrintList(pListAge1);
					}
					else if (name2Searched)
					{
						PrintList(pListName2);
					}
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (age1 != 0 && phone2[0] != 0)
			{
				age1Searched = searchNodeByAge(pListAge1, age1, PATH);
				phone2Searched = searchNodeByPhone(pListPhone2, phone2, PATH);
				if (age1Searched == 1 || phone2Searched == 1)
				{
					NODE* ptrAge = pListAge1->head.next;
					NODE* ptrPhone = pListPhone2->head.next;

					if (age1Searched && phone2Searched)
					{
						LIST* pList = (LIST*)malloc(sizeof(LIST));
						initList(pList);

						while (ptrAge != &pListAge1->tail)
						{
							if (strcmp(ptrAge->phone, ptrPhone->phone) == 0)
							{
								NODE* ptr = ptrAge;
								ptrAge = ptrAge->next;
								insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
								deleteNodeByPhone(pListPhone2, ptr->phone);
								deleteNodeByPhone(pListAge1, ptr->phone);
							}
							else
								ptrAge = ptrAge->next;
						}

						PrintList(pList);
						PrintList(pListAge1);
						PrintList(pListPhone2);
						releaseList(pList);
					}
					else if (age1Searched)
						PrintList(pListAge1);
					else if (phone2Searched)
						PrintList(pListPhone2);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (name1[0] != 0 && age2 != 0)
			{
				name1Searched = searchNodeByName(pListName1, name1, PATH);
				age2Searched = searchNodeByAge(pListAge2, age2, PATH);
				if (name1Searched == 1 || age2Searched == 1)
				{
					NODE* ptrAge = pListAge2->head.next;
					NODE* ptrName = pListName1->head.next;
					if (name1Searched && age2Searched)
					{
						LIST* pList = (LIST*)malloc(sizeof(LIST));
						initList(pList);
						while (ptrAge != &pListAge2->tail)
						{
							int flag = 0;
							ptrName = pListName1->head.next;
							while (ptrName != &pListName1->tail)
							{
								if (strcmp(ptrAge->phone, ptrName->phone) == 0)
								{
									flag = 1;
									NODE* ptr = ptrName;
									ptrName = ptrName->next;
									ptrAge = ptrAge->next;
									insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
									deleteNodeByPhone(pListAge2, ptr->phone);
									deleteNodeByPhone(pListName1, ptr->phone);
									break;
								}
								else
									ptrName = ptrName->next;
							}

							if (!flag)
								ptrAge = ptrAge->next;
						}

						PrintList(pList);
						PrintList(pListName1);
						PrintList(pListAge2);

						releaseList(pList);
					}
					else if (name1Searched)
						PrintList(pListName1);
					else if (age2Searched)
						PrintList(pListAge2);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (name1[0] != 0 && name2[0] != 0)
			{
				name1Searched = searchNodeByName(pListName1, name1, PATH);
				name2Searched = searchNodeByName(pListName2, name2, PATH);
				if (name1Searched || name2Searched)
				{
					PrintList(pListName1);
					PrintList(pListName2);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (name1[0] != 0 && phone2[0] != 0)
			{
				name1Searched = searchNodeByName(pListName1, name1, PATH);
				phone2Searched = searchNodeByPhone(pListPhone2, phone2, PATH);
				if (name1Searched == 1 || phone2Searched == 1)
				{
					NODE* ptrName = pListName1->head.next;
					NODE* ptrPhone = pListPhone2->head.next;
					if (name1Searched && phone2Searched)
					{
						int flag = 0;
						LIST* pList = (LIST*)malloc(sizeof(LIST));
						initList(pList);
						while (ptrName != &pListName1->tail)
						{
							if (strcmp(ptrName->phone, ptrPhone->phone) != 0)
							{
								NODE* ptr = ptrName;
								ptrName = ptrName->next;
								insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
								deleteNodeByPhone(pListPhone2, ptr->phone);
								deleteNodeByPhone(pListName1, ptr->phone);
							}
							else
								ptrName = ptrName->next;
						}

						PrintList(pList);
						PrintList(pListName1);
						PrintList(pListPhone2);
						releaseList(pList);
					}
					else if (name1Searched)
						PrintList(pListName1);
					else if (phone2Searched)
						PrintList(pListPhone2);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (phone1[0] != 0 && age2 != 0)
			{
				phone1Searched = searchNodeByPhone(pListPhone1, phone1, PATH);
				age2Searched = searchNodeByAge(pListAge2, age2, PATH);
				if (age2Searched == 1 || phone1Searched == 1)
				{
					NODE* ptrAge = pListAge2->head.next;
					NODE* ptrPhone = pListPhone1->head.next;
					if (age2Searched && phone1Searched)
					{
						LIST* pList = (LIST*)malloc(sizeof(LIST));
						initList(pList);
						while (ptrAge != &pListAge2->tail)
						{
							if (strcmp(ptrAge->phone, ptrPhone->phone) == 0)
							{
								NODE* ptr = ptrAge;
								ptrAge = ptrAge->next;
								insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
								deleteNodeByPhone(pListPhone1, ptr->phone);
								deleteNodeByPhone(pListAge2, ptr->phone);
							}
							else
								ptrAge = ptrAge->next;
						}

						PrintList(pList);
						PrintList(pListPhone1);
						PrintList(pListAge2);
						releaseList(pList);
					}
					else if (age2Searched)
						PrintList(pListAge2);
					else if (phone1Searched)
						PrintList(pListPhone1);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (phone1[0] != 0 && name2[0] != 0)
			{
				phone1Searched = searchNodeByPhone(pListPhone1, phone1, PATH);
				name2Searched = searchNodeByName(pListName2, name2, PATH);
				if (name2Searched == 1 || phone1Searched == 1)
				{
					NODE* ptrName = pListName2->head.next;
					NODE* ptrPhone = pListPhone1->head.next;
					if (name2Searched && phone1Searched)
					{
						LIST* pList = (LIST*)malloc(sizeof(LIST));
						initList(pList);
						while (ptrName != &pListName2->tail)
						{
							if (strcmp(ptrName->phone, ptrPhone->phone) == 0)
							{
								NODE* ptr = ptrName;
								ptrName = ptrName->next;
								insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
								deleteNodeByPhone(pListPhone1, ptr->phone);
								deleteNodeByPhone(pListName2, ptr->phone);
							}
							else
								ptrName = ptrName->next;
						}

						PrintList(pList);
						PrintList(pListPhone1);
						PrintList(pListName2);
						releaseList(pList);
					}
					else if (name2Searched)
						PrintList(pListName2);
					else if (phone1Searched)
						PrintList(pListPhone1);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (phone1[0] != 0 && phone2[0] != 0)
			{
				phone1Searched = searchNodeByPhone(pListPhone1, phone1, PATH);
				phone2Searched = searchNodeByPhone(pListPhone2, phone2, PATH);
				if (phone1Searched == 1 || phone2Searched == 1)
				{
					PrintList(pListPhone1);
					PrintList(pListPhone2);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
		}
		else if (strcmp(op, "and") == 0 || strcmp(op, "AND") == 0)
		{
			if (age1 != 0 && name2[0] != 0)
			{
				age1Searched = searchNodeByAge(pListAge1, age1, PATH);
				name2Searched = searchNodeByName(pListName2, name2, PATH);

				if (age1Searched && name2Searched)
				{
					LIST* pList = (LIST*)malloc(sizeof(LIST));
					initList(pList);

					NODE* ptrAge = pListAge1->head.next;
					while (ptrAge != &pListAge1->tail)
					{
						int flag = 0;
						NODE* ptrName = pListName2->head.next;
						while (ptrName != &pListName2->tail)
						{
							if (strcmp(ptrAge->phone, ptrName->phone) == 0)
							{
								flag = 1;
								NODE* ptr = ptrName;
								ptrName = ptrName->next;
								ptrAge = ptrAge->next;
								insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
								deleteNodeByPhone(pListAge1, ptr->phone);
								deleteNodeByPhone(pListName2, ptr->phone);
							}
							else
								ptrName = ptrName->next;
						}
						if (!flag)
							ptrAge = ptrAge->next;

					}

					if (!isEmpty(pList))
						PrintList(pList);
					else
						printf("No matching record found.\n");

					releaseList(pList);
				}
				else
				{
					printf("No matching record found.\n");
				}

			}
			else if (age1 != 0 && phone2[0] != 0)
			{
				age1Searched = searchNodeByAge(pListAge1, age1, PATH);
				phone2Searched = searchNodeByPhone(pListPhone2, phone2, PATH);

				NODE* ptrAge = pListAge1->head.next;
				NODE* ptrPhone = pListPhone2->head.next;
				if (age1Searched && phone2Searched)
				{
					LIST* pList = (LIST*)malloc(sizeof(LIST));
					initList(pList);
					while (ptrAge != &pListAge1->tail)
					{
						if (strcmp(ptrAge->phone, ptrPhone->phone) == 0)
						{
							NODE* ptr = ptrAge;
							ptrAge = ptrAge->next;
							insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
							deleteNodeByPhone(pListPhone2, ptr->phone);
							deleteNodeByPhone(pListAge1, ptr->phone);
						}
						else
							ptrAge = ptrAge->next;
					}

					if (!isEmpty(pList))
						PrintList(pList);
					else
						printf("No matching record found.\n");
					releaseList(pList);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (name1[0] != 0 && age2 != 0)
			{
				age2Searched = searchNodeByAge(pListAge2, age2, PATH);
				name1Searched = searchNodeByName(pListName1, name1, PATH);
				if (age2Searched && name1Searched)
				{
					LIST* pList = (LIST*)malloc(sizeof(LIST));
					initList(pList);

					NODE* ptrAge = pListAge2->head.next;
					while (ptrAge != &pListAge2->tail)
					{
						int flag = 0;
						NODE* ptrName = pListName1->head.next;
						while (ptrName != &pListName1->tail)
						{
							if (strcmp(ptrAge->phone, ptrName->phone) == 0)
							{
								flag = 1;
								NODE* ptr = ptrName;
								ptrName = ptrName->next;
								ptrAge = ptrAge->next;
								insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
								deleteNodeByPhone(pListAge2, ptr->phone);
								deleteNodeByPhone(pListName1, ptr->phone);
							}
							else
								ptrName = ptrName->next;
						}

						if (!flag)
							ptrAge = ptrAge->next;
					}

					if (!isEmpty(pList))
						PrintList(pList);
					else
						printf("No matching record found.\n");
					releaseList(pList);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (name1[0] != 0 && phone2[0] != 0)
			{
				name1Searched = searchNodeByName(pListName1, name1, PATH);
				phone2Searched = searchNodeByPhone(pListPhone2, phone2, PATH);

				NODE* ptrName = pListName1->head.next;
				NODE* ptrPhone = pListPhone2->head.next;
				if (name1Searched && phone2Searched)
				{
					LIST* pList = (LIST*)malloc(sizeof(LIST));
					initList(pList);
					while (ptrName != &pListName1->tail)
					{
						if (strcmp(ptrName->phone, ptrPhone->phone) == 0)
						{
							NODE* ptr = ptrName;
							ptrName = ptrName->next;
							insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
							deleteNodeByPhone(pListPhone2, ptr->phone);
							deleteNodeByPhone(pListName1, ptr->phone);
						}
						else
							ptrName = ptrName->next;
					}

					if (!isEmpty(pList))
						PrintList(pList);
					else
						printf("No matching record found.\n");
					releaseList(pList);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (phone1[0] != 0 && age2 != 0)
			{
				age2Searched = searchNodeByAge(pListAge2, age2, PATH);
				phone1Searched = searchNodeByPhone(pListPhone1, phone1, PATH);

				NODE* ptrAge = pListAge2->head.next;
				NODE* ptrPhone = pListPhone1->head.next;
				if (age2Searched && phone1Searched)
				{
					LIST* pList = (LIST*)malloc(sizeof(LIST));
					initList(pList);
					while (ptrAge != &pListAge2->tail)
					{
						if (strcmp(ptrAge->phone, ptrPhone->phone) == 0)
						{
							NODE* ptr = ptrAge;
							ptrAge = ptrAge->next;
							insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
							deleteNodeByPhone(pListPhone1, ptr->phone);
							deleteNodeByPhone(pListAge2, ptr->phone);
						}
						else
							ptrAge = ptrAge->next;
					}

					if (!isEmpty(pList))
						PrintList(pList);
					else
						printf("No matching record found.\n");
					releaseList(pList);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else if (phone1[0] != 0 && name2[0] != 0)
			{
				name2Searched = searchNodeByName(pListName2, name2, PATH);
				phone1Searched = searchNodeByPhone(pListPhone1, phone1, PATH);

				NODE* ptrName = pListName2->head.next;
				NODE* ptrPhone = pListPhone1->head.next;
				if (name2Searched && phone1Searched)
				{
					LIST* pList = (LIST*)malloc(sizeof(LIST));
					initList(pList);
					while (ptrName != &pListName2->tail)
					{
						if (strcmp(ptrName->phone, ptrPhone->phone) == 0)
						{
							NODE* ptr = ptrName;
							ptrName = ptrName->next;
							insertNodeAtEnd(pList, ptr->age, ptr->name, ptr->phone);
							deleteNodeByPhone(pListPhone1, ptr->phone);
							deleteNodeByPhone(pListName2, ptr->phone);
						}
						else
							ptrName = ptrName->next;
					}

					if (!isEmpty(pList))
						PrintList(pList);
					else
						printf("No matching record found.\n");
					releaseList(pList);
				}
				else
				{
					printf("No matching record found.\n");
				}
			}
			else
			{
				printf("No matching record found.\n");
			}
		}
		else
		{
			printf("Invalid operator.\n");
			return 0;
		}
	}

	releaseList(pListAge1);
	releaseList(pListAge2);
	releaseList(pListName1);
	releaseList(pListName2);
	releaseList(pListPhone1);
	releaseList(pListPhone2);
	return 1;
}

int EditNode(const char* PATH)
{
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	initList(pList);

	printf("Need phone number of the node to edit **************\n");
	GetPhone(phone);

	if (searchNodeByPhone(pList, phone, PATH) != 1)
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
				editNodeAge(ptr, age, PATH);

				break;
			case 2:
				GetName(name);
				editNodeName(ptr, name, PATH);

				break;
			case 3:
				GetPhone(phone);

				if (searchNodeByPhone(NULL, phone, PATH) == 1)
				{
					printf("Edit failed: Phone number is already exist.\n");
				}
				else
					editNodePhone(ptr, phone, PATH);
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

int ExitMenu(void)
{
	printf("Exit.\n");
	return 1;
}

OPTION PrintMenu(void)
{
	OPTION val = -1;
	while (1)
	{
		system("cls");
		printf("[1] Insert [2] Delete [3] Search [4] Edit [0] Exit\n");
		printf("Enter the number: ");
		val = getchar() - '0';
		while (getchar() != '\n');	// clear input buffer
		if (val <= EDIT && val >= EXIT)
			break;

		printf("Enter valid number\n");
		_getch();
	}
	return val;
}

void initList(LIST* pL)
{
	pL->head.next = &pL->tail;
	pL->head.prev = NULL;
	pL->tail.next = NULL;
	pL->tail.prev = &pL->head;
}

int isEmpty(LIST* pL)
{
	if (pL->head.next == &pL->tail)
		return 1;

	return 0;
}

int insertNodeAtBeg(LIST* pL, const int age, const char* name, const char* phone)
{
	if (pL == NULL)
		return 0;

	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->age = age;
	strcpy_s(newNode->name, sizeof(newNode->name), name);
	strcpy_s(newNode->phone, sizeof(newNode->phone), phone);

	NODE* ptr = pL->head.next;
	newNode->next = ptr;
	newNode->prev = &pL->head;
	pL->head.next = newNode;
	ptr->prev = newNode;

	return 1;
}

int insertNodeAtEnd(LIST* pL, const int age, const char* name, const char* phone)
{
	if (pL == NULL)
		return 0;

	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->age = age;
	strcpy_s(newNode->name, sizeof(newNode->name), name);
	strcpy_s(newNode->phone, sizeof(newNode->phone), phone);

	NODE* ptr = pL->tail.prev;
	newNode->next = &pL->tail;
	newNode->prev = ptr;
	ptr->next = newNode;
	pL->tail.prev = newNode;

	return 1;
}

int searchNodeByPhone(LIST* pL, const char* phone, const char* path)
{
	FILE* fp = NULL;
	fopen_s(&fp, path, "rb");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));

	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (strcmp(phone, temp->phone) == 0)
		{
			insertNodeAtEnd(pL, temp->age, temp->name, temp->phone);
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);
	free(temp);
	return 0;
}

int searchNodeByName(LIST* pL, const char* name, const char* path)
{
	int flag = 0;

	FILE* fp = NULL;
	fopen_s(&fp, path, "rb");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));

	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (strcmp(name, temp->name) == 0)
		{
			flag = 1;
			insertNodeAtEnd(pL, temp->age, temp->name, temp->phone);
		}
	}

	fclose(fp);
	free(temp);
	return flag;
}

int searchNodeByAge(LIST* pL, const int age, const char* path)
{
	int flag = 0;

	FILE* fp = NULL;
	fopen_s(&fp, path, "rb");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));

	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (age == temp->age)
		{
			flag = 1;
			insertNodeAtEnd(pL, temp->age, temp->name, temp->phone);
		}
	}

	free(temp);
	fclose(fp);
	return flag;
}

int editNodeAge(NODE* ptr, const int age, const char* path)
{
	FILE* fp = NULL;
	fopen_s(&fp, path, "rb+");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (strcmp(temp->phone, ptr->phone) == 0)
		{
			temp->age = age;
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

int editNodeName(NODE* ptr, const char* name, const char* path)
{
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
			strcpy_s(temp->name, sizeof(temp->name), name);
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

int editNodePhone(NODE* ptr, const char* phone, const char* path)
{
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

int deleteNodeAtEnd(LIST* pL)
{
	if (isEmpty(pL))
		return 0;

	NODE* ptr = pL->tail.prev;
	ptr->prev->next = &pL->tail;
	pL->tail.prev = ptr->prev;

	free(ptr);
	return 1;
}

int deleteNodeAtBeg(LIST* pL)
{
	if (isEmpty(pL))
		return 0;

	NODE* ptr = pL->head.next;
	ptr->next->prev = &pL->head;
	pL->head.next = ptr->next;

	free(ptr);
	return 1;
}

int deleteNodeByPhone(LIST* pL, const char* phone)
{
	if (isEmpty(pL))
		return 0;

	NODE* ptr = pL->head.next;
	while (ptr != &pL->tail)
	{
		if (strcmp(ptr->phone, phone) == 0)
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			free(ptr);
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

int deleteNodeFromFile(const char* phone, const char* path)
{
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
	}

	free(temp);
	fclose(fpTmp);
	fclose(fp);

	remove(path);
	rename("temp.dat", path);
	return 1;
}

void PrintList(LIST* pL)
{
	if (isEmpty(pL))
		return;

	NODE* ptr = pL->head.next;
	while (ptr != &pL->tail)
	{
		printf("[%p] %3d - %-5s - %s [%p]\n", ptr,
			ptr->age, ptr->name, ptr->phone,
			ptr->next);
		ptr = ptr->next;
	}
}

int saveListToFile(LIST* pL, const char* path)
{
	if (isEmpty(pL))
		return 0;

	NODE* ptr = pL->head.next;
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	while (ptr != &pL->tail)
	{
		int flag = 1;
		if (searchNodeByPhone(NULL, ptr->phone, path) == 1)
			flag = 0;

		if (flag)
		{
			FILE* fp = NULL;
			fopen_s(&fp, path, "ab+");
			if (fp == NULL)
			{
				free(temp);
				return -1;
			}

			if (fwrite(ptr, sizeof(NODE), 1, fp) != 1)
			{
				fclose(fp);
				free(temp);
				return -1;
			}
			fclose(fp);
		}
		ptr = ptr->next;
	}

	free(temp);
	return 1;
}

void releaseList(LIST* pL)
{
	if (isEmpty(pL))
		return;

	NODE* ptr = pL->head.next;
	while (ptr != &pL->tail)
	{
		NODE* del = ptr;
		ptr = ptr->next;
		free(del);
	}
}

