#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "control.h"
#include "ui.h"
#include "test.h"

void CreateTestFile(void)
{
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	InitList(pList);

	InsertNodeAtEnd(pList, 10, "Kim", "010-0000-0000");
	InsertNodeAtEnd(pList, 11, "Kim", "010-0000-0001");
	InsertNodeAtEnd(pList, 12, "Kim", "010-0000-0002");
	InsertNodeAtEnd(pList, 13, "Kim", "010-0000-0003");
	InsertNodeAtEnd(pList, 14, "Lee", "010-0000-0004");
	InsertNodeAtEnd(pList, 15, "Lee", "010-0000-0005");
	InsertNodeAtEnd(pList, 16, "Park", "010-0000-0006");
	InsertNodeAtEnd(pList, 17, "Jung", "010-0000-0007");
	InsertNodeAtEnd(pList, 18, "Hwang", "010-0000-0008");
	InsertNodeAtEnd(pList, 19, "Sung", "010-0000-0009");
	InsertNodeAtEnd(pList, 20, "Kim", "010-0000-0010");
	InsertNodeAtEnd(pList, 20, "Lee", "010-0000-0011");
	InsertNodeAtEnd(pList, 20, "Park", "010-0000-0012");

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
	ReleaseList(pList);
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
	InitList(pList);

	InsertNodeAtEnd(pList, 10, "Kim", "010-0000-0000");
	InsertNodeAtEnd(pList, 11, "Kim", "010-0000-0001");
	InsertNodeAtEnd(pList, 12, "Kim", "010-0000-0002");
	InsertNodeAtEnd(pList, 13, "Kim", "010-0000-0003");
	InsertNodeAtEnd(pList, 14, "Lee", "010-0000-0004");
	InsertNodeAtEnd(pList, 15, "Lee", "010-0000-0005");
	InsertNodeAtEnd(pList, 16, "Park", "010-0000-0006");
	InsertNodeAtEnd(pList, 17, "Jung", "010-0000-0007");
	InsertNodeAtEnd(pList, 18, "Hwang", "010-0000-0008");
	InsertNodeAtEnd(pList, 19, "Sung", "010-0000-0009");

	/*InsertNodeAtBeg(pList, 10, "Kim", "010-0000-0000");
	InsertNodeAtBeg(pList, 11, "Kim", "010-0000-0001");
	InsertNodeAtBeg(pList, 12, "Kim", "010-0000-0002");
	InsertNodeAtBeg(pList, 13, "Kim", "010-0000-0003");
	InsertNodeAtBeg(pList, 14, "Lee", "010-0000-0004");
	InsertNodeAtBeg(pList, 15, "Lee", "010-0000-0005");
	InsertNodeAtBeg(pList, 16, "Park", "010-0000-0006");
	InsertNodeAtBeg(pList, 17, "Jung", "010-0000-0007");
	InsertNodeAtBeg(pList, 18, "Hwang", "010-0000-0008");
	InsertNodeAtBeg(pList, 19, "Sung", "010-0000-0009");*/
	printf("Before ----------------------------------------------------------\n");
	PrintList(pList);
	printf("-----------------------------------------------------------------\n");

	DeleteNodeAtBeg(pList);
	DeleteNodeAtBeg(pList);
	DeleteNodeAtBeg(pList);
	DeleteNodeAtBeg(pList);
	DeleteNodeAtBeg(pList);
	DeleteNodeAtBeg(pList);
	DeleteNodeAtBeg(pList);
	DeleteNodeAtBeg(pList);
	DeleteNodeAtBeg(pList);
	DeleteNodeAtBeg(pList);

	/*DeleteNodeAtEnd(pList);
	DeleteNodeAtEnd(pList);
	DeleteNodeAtEnd(pList);
	DeleteNodeAtEnd(pList);
	DeleteNodeAtEnd(pList);
	DeleteNodeAtEnd(pList);
	DeleteNodeAtEnd(pList);
	DeleteNodeAtEnd(pList);
	DeleteNodeAtEnd(pList);
	DeleteNodeAtEnd(pList);*/

	InsertNodeAtEnd(pList, 10, "Kim", "010-0000-0000");
	InsertNodeAtEnd(pList, 11, "Kim", "010-0000-0001");
	InsertNodeAtEnd(pList, 12, "Kim", "010-0000-0002");
	InsertNodeAtEnd(pList, 13, "Kim", "010-0000-0003");
	InsertNodeAtEnd(pList, 14, "Lee", "010-0000-0004");
	InsertNodeAtEnd(pList, 15, "Lee", "010-0000-0005");
	InsertNodeAtEnd(pList, 16, "Park", "010-0000-0006");
	InsertNodeAtEnd(pList, 17, "Jung", "010-0000-0007");
	InsertNodeAtEnd(pList, 18, "Hwang", "010-0000-0008");
	InsertNodeAtEnd(pList, 19, "Sung", "010-0000-0009");

	/*InsertNodeAtBeg(pList, 10, "Kim", "010-0000-0000");
	InsertNodeAtBeg(pList, 12, "Kim", "010-0000-0001");
	InsertNodeAtBeg(pList, 11, "Kim", "010-0000-0002");
	InsertNodeAtBeg(pList, 13, "Kim", "010-0000-0003");
	InsertNodeAtBeg(pList, 14, "Lee", "010-0000-0004");
	InsertNodeAtBeg(pList, 15, "Lee", "010-0000-0005");
	InsertNodeAtBeg(pList, 16, "Park", "010-0000-0006");
	InsertNodeAtBeg(pList, 17, "Jung", "010-0000-0007");
	InsertNodeAtBeg(pList, 18, "Hwang", "010-0000-0008");
	InsertNodeAtBeg(pList, 19, "Sung", "010-0000-0009");*/

	printf("After -----------------------------------------------------------\n");
	PrintList(pList);
	printf("-----------------------------------------------------------------\n");

	ReleaseList(pList);
	free(pList);
}

void TestSearchFunc(void)
{
	CreateTestFile();

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	InitList(pList);

	NODE* ptr = (NODE*)malloc(sizeof(NODE));
	ptr->age = 15;
	strcpy_s(ptr->name, sizeof(ptr->name), "Kim");
	strcpy_s(ptr->phone, sizeof(ptr->phone), "010-9999-9999");

	// Test search by phone ----------------------------------------------------
	printf("Search by phone number ************\n");
	printf("Origin: %2d %s [%s]\n", ptr->age, ptr->name, ptr->phone);
	if (LoadNodeFromFileByPhone(pList, ptr->phone, FILE_PATH_TEST))
	{
		// Phone number duplication doesn't exist
		NODE* temp = pList->head.next;
		printf("Found: %3d %-5s [%s]\n", temp->age, temp->name, temp->phone);
	}
	else
	{
		printf("Not Found\n");
	}
	ReleaseList(pList);
	printf("***********************************\n\n");


	// Test search by name ----------------------------------------------------
	InitList(pList);

	printf("Search by name ********************\n");
	printf("Origin: %2d [%s] %s\n", ptr->age, ptr->name, ptr->phone);
	if (LoadNodeFromFileByName(pList, ptr->name, FILE_PATH_TEST))
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
	ReleaseList(pList);
	printf("***********************************\n\n");

	// Test search by age ----------------------------------------------------
	InitList(pList);
	printf("Search by age *********************\n");
	printf("Origin: [%2d] %s %s\n", ptr->age, ptr->name, ptr->phone);
	if (LoadNodeFromFileByAge(pList, ptr->age, FILE_PATH_TEST))
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
	ReleaseList(pList);
	printf("***********************************\n\n");

	free(ptr);
	free(pList);
}

void TestFileIOFunc(void)
{
	CreateTestFile();

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	InitList(pList);

	// don't exist
	InsertNodeAtEnd(pList, 20, "Park", "010-0001-0000");
	InsertNodeAtEnd(pList, 21, "Park", "010-0002-0000");
	InsertNodeAtEnd(pList, 22, "Park", "010-0003-0000");

	// already exist
	InsertNodeAtEnd(pList, 13, "Kim", "010-0000-0003");
	InsertNodeAtEnd(pList, 14, "Lee", "010-0000-0004");
	InsertNodeAtEnd(pList, 15, "Lee", "010-0000-0005");

	SaveListToFile(pList, FILE_PATH_TEST);
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
	InitList(pList);
	LoadNodeFromFileByPhone(pList, temp->phone, FILE_PATH_TEST);
	EditNodeFromFileByAge(pList->head.next, 93, FILE_PATH_TEST);
	EditNodeFromFileByName(pList->head.next, "Test", FILE_PATH_TEST);
	EditNodeFromFileByPhone(pList->head.next, "010-1234-5678", FILE_PATH_TEST);
	ReleaseList(pList);
	free(temp);

	printf("Test: edit function ***********\n");
	ReadTestFile();
	printf("*******************************\n\n");
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
		"30 OR 15",							// age OR age (right matching)
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
		"\n",									// empty input
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
		SearchNode(testCases[i], FILE_PATH_TEST);
	}

	//UI_PrintAll(FILE_PATH_TEST);

	ReadTestFile();
}