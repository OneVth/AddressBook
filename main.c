/* INCLUDES		*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef enum { EXIT, INSERT, DELETE, SEARCH, EDIT } OPTION;

typedef struct node {
	int age;
	char name[20];
	char phone[20];
	struct node* next;
	struct node* prev;
} NODE;

/* GLOBALS		*******************************************************/
NODE* g_head;
NODE* g_tail;

/* FUNCTIONS	*******************************************************/

// UI
OPTION PrintMenu(void);
int InsertNode(void);
int DeleteNode(void);
int SearchNode(void);
int EditNode(void);
int ExitMenu(void);
void PrintList(void);

// Control
void initList(void);
int isEmpty(void);
int insertNode(const int age, const char* name, const char* phone);
int deleteNode(const char* phone);
NODE* searchNodeByPhone(const char* phone);
NODE* searchNodeByName(const char* name);
NODE* searchNodeByAge(const int age);
int editNodeAge(NODE* ptr, const int age);
int editNodeName(NODE* ptr, const char* name);
int editNodePhone(NODE* ptr, const char* phone);
int saveListToFile(void);
int loadListFromFile(void);
void releaseList(void);

// Test
void TestControlFunc(void);
void TestFileIO(void);
void TestEdit(void);

int main(void)
{
	int (*pfMenu[5])(void) = { ExitMenu, InsertNode, DeleteNode, SearchNode, EditNode };

	initList();
	loadListFromFile();

	OPTION option = PrintMenu();
	do
	{
		system("cls");
		pfMenu[option]();
		_getch();
	} while ((option = PrintMenu()) != EXIT);

	return 0;
}

void TestControlFunc(void)
{
	initList();
	insertNode(10, "Joon", "010-0000-0000");
	insertNode(11, "Hoon", "010-0000-0001");
	insertNode(12, "Jing", "010-0000-0002");

	deleteNode("010-0000-0002");
	deleteNode("010-0000-0001");
	deleteNode("010-0000-0000");

	insertNode(10, "Joon", "010-0000-0000");
	insertNode(10, "Hoon", "010-0000-0001");
	insertNode(10, "Jing", "010-0000-0002");

	NODE* ptr = searchNodeByPhone("010-0000-0002");
	if (ptr != NULL)
		printf("%s\n", ptr->name);

	PrintList();
	releaseList();
}

void TestFileIO(void)
{
	initList();

	insertNode(10, "Joon", "010-0000-0000");
	insertNode(11, "Hoon", "010-0000-0001");
	insertNode(12, "Jing", "010-0000-0002");

	printf("Print before save -----------------------------------------------\n");
	PrintList();
	printf("-----------------------------------------------------------------\n");
	saveListToFile();
	releaseList();

	initList();
	loadListFromFile();
	printf("Print after load -----------------------------------------------\n");
	PrintList();
	printf("-----------------------------------------------------------------\n");

	releaseList();
}

void TestEdit(void)
{
	initList();
	insertNode(10, "Joon", "010-0000-0000");
	insertNode(11, "Hoon", "010-0000-0001");
	insertNode(12, "Jing", "010-0000-0002");
	printf("Print before edit age --------------------------------------------\n");
	PrintList();
	printf("----------------------------------------------------------------\n");

	NODE* ptr = searchNodeByPhone("010-0000-0000");
	editNodeAge(ptr, 15);
	editNodeName(ptr, "Hwang");
	editNodePhone(ptr, "010-0000-0009");
	printf("Print after edit age --------------------------------------------\n");
	PrintList();
	printf("--------------------------------------------------------------\n");

	releaseList();
}

int InsertNode(void)
{
	int age = 0;
	char name[20] = { 0 };
	char phone[20] = { 0 };
	char temp[20] = { 0 };

	printf("Insert new data: need [Name] [Age] [Phone number]\n");
	printf("Name: ");
	gets_s(name, sizeof(name));

	printf("[Age]: ");
	gets_s(temp, sizeof(temp));
	age = atoi(temp);

	printf("[Phone number] ");
	gets_s(phone, sizeof(phone));

	if (!insertNode(age, name, phone))
	{
		printf("\nCannot insert: invalid value or same phone number already exist.\n");
		return 0;
	}

	saveListToFile();
	return 1;
}

int DeleteNode(void)
{
	if (isEmpty())
	{
		printf("The list is already empty.\n");
		return 0;
	}

	char phone[20] = { 0 };
	printf("Enter the phone number to delete: ");
	gets_s(phone, sizeof(phone));
	if (!deleteNode(phone))
	{
		printf("Deletion failed.\n");
		return 0;
	}
	
	saveListToFile();
	printf("Deletion successful.\n");
	return 1;
}

int SearchNode(void)
{
	if(isEmpty())
	{
		printf("The list is already empty.\n");
		return 0;
	}

	char phone[20] = { 0 };
	printf("Enter the phone number to search for: ");
	gets_s(phone, sizeof(phone));

	NODE* ptr = searchNodeByPhone(phone);
	if (ptr == NULL)
	{
		printf("Search failed.\n");
		return 0;
	}

	system("cls");
	printf("Search results ----------------------------------\n");
	printf("%d %s %s\n", ptr->age, ptr->name, ptr->phone);
	printf("-------------------------------------------------\n");
	return 1;
}

int EditNode(void)
{
	char phone[20] = { 0 };
	printf("Enter phone number of the node to edit: ");
	gets_s(phone, sizeof(phone));
	NODE* ptr = searchNodeByPhone(phone);
	if (ptr == NULL)
	{
		printf("Cannot find the node.\n");
		return 0;
	}

	int option = -1;
	printf("Edit: [0] Name [1] Age [2] Phone\n");
	option = getchar() - '0';
	while (getchar() != '\n');
	if (option <= 2 && option >= 0)
	{
		int age = 0;
		char name[20] = { 0 };
		char temp[20] = { 0 };

		system("cls");
		switch (option)
		{
		case 0:
			printf("Enter the new name: ");
			gets_s(name, sizeof(name));
			editNodeName(ptr, name);
			break;
		case 1:
			printf("Enter the new age: ");
			gets_s(temp, sizeof(temp));
			age = atoi(temp);
			editNodeAge(ptr, age);
			break;
		case 2:
			printf("Enter the new phone: ");
			gets_s(phone, sizeof(phone));
			editNodePhone(ptr, phone);
			break;
		default:
			break;
		}
	}

	saveListToFile();
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

void initList(void)
{
	g_head = (NODE*)malloc(sizeof(NODE));
	g_tail = (NODE*)malloc(sizeof(NODE));
	g_head->next = g_tail;
	g_head->prev = NULL;
	g_tail->prev = g_head;
	g_tail->next = NULL;
}

int isEmpty(void)
{
	if (g_head->next == g_tail)
		return 1;

	return 0;
}

int insertNode(const int age, const char* name, const char* phone)
{
	if (searchNodeByPhone(phone))
		return 0;

	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->age = age;
	strcpy_s(newNode->name, sizeof(newNode->name), name);
	strcpy_s(newNode->phone, sizeof(newNode->phone), phone);

	NODE* ptr = g_head->next;
	if (ptr == NULL)
		g_head->next = newNode;
	else
	{
		newNode->next = ptr;
		newNode->prev = g_head;
		g_head->next = newNode;
		ptr->prev = newNode;
	}
	return 1;
}

NODE* searchNodeByPhone(const char* phone)
{
	if (isEmpty())
		return NULL;

	NODE* ptr = g_head->next;
	while (ptr != g_tail)
	{
		int val = strcmp(ptr->phone, phone);
		if (val == 0)
			return ptr;

		ptr = ptr->next;
	}
	return NULL;
}

NODE* searchNodeByName(const char* name)
{
	if (isEmpty())
		return NULL;

	NODE* ptr = g_head->next;
	while (ptr != g_tail)
	{
		int val = strcmp(ptr->name, name);
		if (val == 0)
			return ptr;

		ptr = ptr->next;
	}
	return NULL;
}

NODE* searchNodeByAge(const int age)
{
	if (isEmpty())
		return NULL;

	NODE* ptr = g_head->next;
	while (ptr != g_tail)
	{
		if (ptr->age == age)
			return ptr;
	}
	return NULL;
}

int editNodeAge(NODE* ptr, const int age)
{
	if (isEmpty())
		return 0;

	ptr->age = age;
	return 1;
}

int editNodeName(NODE* ptr, const char* name)
{
	if (isEmpty())
		return 0;

	strcpy_s(ptr->name, sizeof(ptr->name), name);
	return 1;
}

int editNodePhone(NODE* ptr, const char* phone)
{
	if (isEmpty())
		return 0;

	strcpy_s(ptr->phone, sizeof(ptr->phone), phone);
	return 1;
}

int deleteNode(const char* phone)
{
	if (isEmpty())
		return 0;

	NODE* ptr = searchNodeByPhone(phone);
	if (ptr == NULL)
		return 0;

	NODE* prev = ptr->prev;
	prev->next = ptr->next;
	ptr->next->prev = prev;

	return 1;
}

void PrintList(void)
{
	if (isEmpty())
		return;

	NODE* ptr = g_head->next;
	while (ptr != g_tail)
	{
		printf("[%p] %d - %s - %s [%p]\n", ptr,
			ptr->age, ptr->name, ptr->phone,
			ptr->next);
		ptr = ptr->next;
	}
}

int saveListToFile(void)
{
	if (isEmpty())
		return 0;

	FILE* fp = NULL;
	fopen_s(&fp, "Data.dat", "wb");
	if (fp == NULL)
		return 0;

	NODE* ptr = g_head->next;
	while (ptr != g_tail)
	{
		fwrite(&ptr->age, sizeof(int), 1, fp);
		fwrite(ptr->name, sizeof(char), sizeof(ptr->name), fp);
		fwrite(ptr->phone, sizeof(char), sizeof(ptr->phone), fp);
		ptr = ptr->next;
	}

	fclose(fp);
	return 1;
}

int loadListFromFile(void)
{
	FILE* fp = NULL;
	fopen_s(&fp, "Data.dat", "rb");
	if (fp == NULL)
	{
		puts("ERROR: Failed to open file\n");
		return 0;
	}

	while (1)
	{
		NODE* temp = (NODE*)malloc(sizeof(NODE));
		memset(temp, 0, sizeof(NODE));

		if (fread(&temp->age, sizeof(int), 1, fp) == 0) break;
		if (fread(temp->name, sizeof(char), sizeof(temp->name), fp) == 0) break;
		if (fread(temp->phone, sizeof(char), sizeof(temp->phone), fp) == 0) break;

		insertNode(temp->age, temp->name, temp->phone);
		free(temp);
	}

	fclose(fp);
	return 1;
}

void releaseList(void)
{
	if (isEmpty())
		return;

	NODE* ptr = g_head;
	while (ptr != NULL)
	{
		NODE* del = ptr;
		ptr = ptr->next;
		free(del);
	}
}

