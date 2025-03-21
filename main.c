/* INCLUDES		*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define FILE_NAME "Data.dat"
#define FILE_NAME_TEST "test.dat"

typedef enum { EXIT, INSERT, DELETE, SEARCH, EDIT } OPTION;

typedef struct node {
	int age;
	char name[20];
	char phone[20];
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
//OPTION PrintMenu(void);
//int InsertNode(void);
//int DeleteNode(void);
//int SearchNode(void);
//int EditNode(void);
//int ExitMenu(void);
void PrintList(LIST* pL);

// Control
void initList(LIST* pL);
int isEmpty(LIST* pL);
int insertNodeAtBeg(LIST* pL, const int age, const char* name, const char* phone);
int insertNodeAtEnd(LIST* pL, const int age, const char* name, const char* phone);
int deleteNodeAtEnd(LIST* pL);
int deleteNodeAtBeg(LIST* pL);
int deleteNodeFromFile(const char* phone, const char* path);
int searchNodeByPhone(LIST* pL, NODE* ptr, const char* path);
int searchNodeByName(LIST* pL, NODE* ptr, const char* path);
int searchNodeByAge(LIST* pL, NODE* ptr, const char* path);
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
	TestFileIOFunc();
	TestEditFunc();
	TestSearchFunc();

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

	printf("Test file *********************\n");

	FILE* fp = NULL;
	fopen_s(&fp, FILE_NAME_TEST, "wb");
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
	FILE* fp = NULL;
	fopen_s(&fp, FILE_NAME_TEST, "rb");
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
	if (searchNodeByPhone(pList, ptr, FILE_NAME_TEST))
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
	if (searchNodeByName(pList, ptr, FILE_NAME_TEST))
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
	if (searchNodeByAge(pList, ptr, FILE_NAME_TEST))
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

	saveListToFile(pList, FILE_NAME_TEST);
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
	searchNodeByPhone(pList, temp, FILE_NAME_TEST);
	editNodeAge(pList->head.next, 93, FILE_NAME_TEST);
	editNodeName(pList->head.next, "Test", FILE_NAME_TEST);
	editNodePhone(pList->head.next, "010-1234-5678", FILE_NAME_TEST);
	releaseList(pList);
	free(temp);

	printf("Test: edit function ***********\n");
	ReadTestFile();
	printf("*******************************\n\n");
}

//int InsertNode(void)
//{
//	int age = 0;
//	char name[20] = { 0 };
//	char phone[20] = { 0 };
//	char temp[20] = { 0 };
//
//	printf("Enter new data: need [Name] [Age] [Phone number]\n");
//	printf("Name: ");
//	gets_s(name, sizeof(name));
//
//	printf("[Age]: ");
//	gets_s(temp, sizeof(temp));
//	age = atoi(temp);
//
//	printf("[Phone number] ");
//	gets_s(phone, sizeof(phone));
//
//	if (!insertNodeAtBeg(age, name, phone))
//	{
//		printf("\nInsert failed: Invalid value or phone number already exist.\n");
//		return 0;
//	}
//
//	saveListToFile();
//	return 1;
//}
//
//int DeleteNode(void)
//{
//	if (isEmpty())
//	{
//		printf("The list is already empty.\n");
//		return 0;
//	}
//
//	char phone[20] = { 0 };
//	printf("Enter the phone number to delete: ");
//	gets_s(phone, sizeof(phone));
//	if (!deleteNode(phone))
//	{
//		printf("Deletion failed.\n");
//		return 0;
//	}
//
//	saveListToFile();
//	printf("Deletion successful.\n");
//	return 1;
//}
//
//int SearchNode(void)
//{
//	if (isEmpty())
//	{
//		printf("The list is already empty.\n");
//		return 0;
//	}
//
//	char phone[20] = { 0 };
//	printf("Enter the phone number to search for: ");
//	gets_s(phone, sizeof(phone));
//
//	NODE* ptr = searchNodeByPhone(phone);
//	if (ptr == NULL)
//	{
//		printf("No matching record found.\n");
//		return 0;
//	}
//
//	system("cls");
//	printf("Search results ----------------------------------\n");
//	printf("%d %s %s\n", ptr->age, ptr->name, ptr->phone);
//	printf("-------------------------------------------------\n");
//	return 1;
//}
//
//int EditNode(void)
//{
//	char phone[20] = { 0 };
//	printf("Enter phone number of the node to edit: ");
//	gets_s(phone, sizeof(phone));
//	NODE* ptr = searchNodeByPhone(phone);
//	if (ptr == NULL)
//	{
//		printf("Cannot find the node.\n");
//		return 0;
//	}
//
//	int option = -1;
//	printf("Edit: [0] Name [1] Age [2] Phone\n");
//	option = getchar() - '0';
//	while (getchar() != '\n');
//	if (option <= 2 && option >= 0)
//	{
//		int age = 0;
//		char name[20] = { 0 };
//		char temp[20] = { 0 };
//
//		system("cls");
//		switch (option)
//		{
//		case 0:
//			printf("Enter the new name: ");
//			gets_s(name, sizeof(name));
//			editNodeName(ptr, name);
//			break;
//		case 1:
//			printf("Enter the new age: ");
//			gets_s(temp, sizeof(temp));
//			age = atoi(temp);
//			editNodeAge(ptr, age);
//			break;
//		case 2:
//			printf("Enter the new phone: ");
//			gets_s(phone, sizeof(phone));
//			editNodePhone(ptr, phone);
//			break;
//		default:
//			break;
//		}
//	}
//
//	saveListToFile();
//	return 1;
//}
//
//int ExitMenu(void)
//{
//	printf("Exit.\n");
//	return 1;
//}

//OPTION PrintMenu(void)
//{
//	OPTION val = -1;
//	while (1)
//	{
//		system("cls");
//		printf("[1] Insert [2] Delete [3] Search [4] Edit [0] Exit\n");
//		printf("Enter the number: ");
//		val = getchar() - '0';
//		while (getchar() != '\n');	// clear input buffer
//		if (val <= EDIT && val >= EXIT)
//			break;
//
//		printf("Enter valid number\n");
//		_getch();
//	}
//	return val;
//}

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

int searchNodeByPhone(LIST* pL, NODE* ptr, const char* path)
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
		if (strcmp(ptr->phone, temp->phone) == 0)
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

int searchNodeByName(LIST* pL, NODE* ptr, const char* path)
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
		if (strcmp(ptr->name, temp->name) == 0)
		{
			flag = 1;
			insertNodeAtEnd(pL, temp->age, temp->name, temp->phone);
		}
	}

	fclose(fp);
	free(temp);
	return flag;
}

int searchNodeByAge(LIST* pL, NODE* ptr, const char* path)
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
		if (ptr->age == temp->age)
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
			fwrite(temp, sizeof(NODE), 1, fp);
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
			fwrite(temp, sizeof(NODE), 1, fp);
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
			fwrite(temp, sizeof(NODE), 1, fp);
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
			fwrite(temp, sizeof(NODE), 1, fpTmp);
		}
	}

	free(temp);
	fclose(fpTmp);
	fclose(fp);

	remove(FILE_NAME);
	rename("temp.dat", FILE_NAME);
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
		if (searchNodeByPhone(NULL, ptr, path) == 1)
			flag = 0;

		if (flag)
		{
			FILE* fp = NULL;
			fopen_s(&fp, path, "ab+");
			if (fp == NULL)
				return 0;

			fwrite(ptr, sizeof(NODE), 1, fp);
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

