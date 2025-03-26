#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "control.h"
#include "ui.h"
#include "test.h"

void Test_List_InsertAtEnd(void)
{

	return;
}

void Test_CreateFile(void)
{
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	List_InsertAtEnd(pList, 10, "Kim", "010-0000-0000");
	List_InsertAtEnd(pList, 11, "Kim", "010-0000-0001");
	List_InsertAtEnd(pList, 12, "Kim", "010-0000-0002");
	List_InsertAtEnd(pList, 13, "Kim", "010-0000-0003");
	List_InsertAtEnd(pList, 14, "Lee", "010-0000-0004");
	List_InsertAtEnd(pList, 15, "Lee", "010-0000-0005");
	List_InsertAtEnd(pList, 16, "Park", "010-0000-0006");
	List_InsertAtEnd(pList, 17, "Jung", "010-0000-0007");
	List_InsertAtEnd(pList, 18, "Hwang", "010-0000-0008");
	List_InsertAtEnd(pList, 19, "Sung", "010-0000-0009");
	List_InsertAtEnd(pList, 20, "Kim", "010-0000-0010");
	List_InsertAtEnd(pList, 20, "Lee", "010-0000-0011");
	List_InsertAtEnd(pList, 20, "Park", "010-0000-0012");

	printf("Test file *********************\n");

	FILE* fp = NULL;
	fopen_s(&fp, FILE_PATH_TEST, "wb");
	if (fp == NULL)
	{
		printf("Failed to open file.\n");
		return;
	}

	NODE* ptr = pList->head.next;
	while (ptr != &pList->tail)
	{
		printf("%2d %-5s %s\n", ptr->age, ptr->name, ptr->phone);
		fwrite(ptr, sizeof(NODE), 1, fp);
		ptr = ptr->next;
	}

	List_Release(pList);
	fclose(fp);
	printf("*******************************\n\n");
	return;
}

void Test_ReadFile(void)
{
	printf("ReadTestFile() ***************\n");
	FILE* fp = NULL;
	fopen_s(&fp, FILE_PATH_TEST, "rb");
	if (fp == NULL)
	{
		printf("Failed to open file.\n");
		return;
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
	return;
}

void Test_ListFunctions(void)
{
	LIST* pList1 = (LIST*)malloc(sizeof(LIST));
	LIST* pList2 = (LIST*)malloc(sizeof(LIST));
	LIST* pList3 = (LIST*)malloc(sizeof(LIST));
	LIST* pList4 = (LIST*)malloc(sizeof(LIST));
	List_Init(pList1);
	List_Init(pList2);
	List_Init(pList3);
	List_Init(pList4);

	printf("Print before insertion:\n");
	UI_PrintList(pList1);
	printf("\nList_IsEmpty(List1): %d\n", List_IsEmpty(pList1));
	printf("List_HasPhone(%s): %d\n", "010-0000-0000", List_HasPhone(pList1, "010-0000-0000"));

	List_InsertAtBeg(pList1, 10, "Kim", "010-0000-0000");
	List_InsertAtBeg(pList1, 11, "Kim", "010-0000-0001");
	List_InsertAtBeg(pList1, 12, "Kim", "010-0000-0002");

	List_InsertAtEnd(pList2, 10, "Kim", "010-0000-0000");
	List_InsertAtEnd(pList2, 13, "Lee", "010-0000-0003");
	List_InsertAtEnd(pList2, 14, "Lee", "010-0000-0004");

	printf("\nPrint List1 after insertion:\n");
	UI_PrintList(pList1);

	printf("\nPrint List2 after insertion:\n");
	UI_PrintList(pList2);
	printf("\nList_IsEmpty(List1): %d\n", List_IsEmpty(pList1));
	printf("List_HasPhone(%s): %d\n", "010-0000-0000", List_HasPhone(pList1, "010-0000-0000"));

	printf("\nCombine List1 with List2 into List3 by \"AND\" operator:\n");
	List_CombineByOp(pList3, pList1, pList2, "AND");
	UI_PrintList(pList3);

	printf("\nRelease List3:\n");
	List_Release(pList3);
	List_Init(pList3);
	printf("List_IsEmpty(List3): %d\n", List_IsEmpty(pList3));

	printf("\nCombine List1 with List2 into List3 by \"and\" operator:\n");
	List_CombineByOp(pList3, pList1, pList2, "and");
	UI_PrintList(pList3);

	printf("\nCombine List1 with List2 into List4 by \"OR\" operator:\n");
	List_CombineByOp(pList4, pList1, pList2, "OR");
	UI_PrintList(pList4);

	printf("\nRelease List4:\n");
	List_Release(pList4);
	List_Init(pList4);
	printf("List_IsEmpty(List4): %d\n", List_IsEmpty(pList4));

	printf("\nCombine List1 with List2 into List4 by \"or\" operator:\n");
	List_CombineByOp(pList4, pList1, pList2, "or");
	UI_PrintList(pList4);

	for (int i = 0; i < 3; i++)
	{
		List_DeleteAtBeg(pList1);
		printf("\nPrint after %d deletion node at begin of list:\n", i + 1);
		UI_PrintList(pList1);
	}

	for (int i = 0; i < 3; i++)
	{
		List_DeleteAtEnd(pList2);
		printf("\nPrint after %d deletion node at end of list:\n", i + 1);
		UI_PrintList(pList2);
	}

	printf("\nBefore delettion of node phone number \"%s\" at List3:\n", "010-0000-0000");
	UI_PrintList(pList3);

	List_DeleteByPhone(pList3, "010-0000-0000");
	printf("After delettion of node phone number \"%s\" at List3:\n", "010-0000-0000");
	UI_PrintList(pList3);

	List_Release(pList1);
	List_Release(pList2);
	List_Release(pList3);
	List_Release(pList4);
	free(pList1);
	free(pList2);
	free(pList3);
	free(pList4);
	return;
}

void Test_SearchFunctions(void)
{
	Test_CreateFile();

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

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
	List_Release(pList);
	printf("***********************************\n\n");


	// Test search by name ----------------------------------------------------
	List_Init(pList);

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
	List_Release(pList);
	printf("***********************************\n\n");

	// Test search by age ----------------------------------------------------
	List_Init(pList);
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
	List_Release(pList);
	printf("***********************************\n\n");

	free(ptr);
	free(pList);
}

void Test_FileIOFunctions(void)
{
	Test_CreateFile();

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	// don't exist
	List_InsertAtEnd(pList, 20, "Park", "010-0001-0000");
	List_InsertAtEnd(pList, 21, "Park", "010-0002-0000");
	List_InsertAtEnd(pList, 22, "Park", "010-0003-0000");

	// already exist
	List_InsertAtEnd(pList, 13, "Kim", "010-0000-0003");
	List_InsertAtEnd(pList, 14, "Lee", "010-0000-0004");
	List_InsertAtEnd(pList, 15, "Lee", "010-0000-0005");

	SaveListToFile(pList, FILE_PATH_TEST);
	free(pList);

	printf("Test: file IO function ********\n");
	Test_ReadFile();
	printf("*******************************\n\n");
}

void Test_EditFunctions(void)
{
	Test_CreateFile();

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->next = NULL;
	temp->prev = NULL;
	temp->age = 13;
	strcpy_s(temp->name, sizeof(temp->name), "Kim");
	strcpy_s(temp->phone, sizeof(temp->phone), "010-0000-0003");

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);
	LoadNodeFromFileByPhone(pList, temp->phone, FILE_PATH_TEST);
	EditNodeFromFileByAge(pList->head.next, 93, FILE_PATH_TEST);
	EditNodeFromFileByName(pList->head.next, "Test", FILE_PATH_TEST);
	EditNodeFromFileByPhone(pList->head.next, "010-1234-5678", FILE_PATH_TEST);
	List_Release(pList);
	free(temp);

	printf("Test: edit function ***********\n");
	Test_ReadFile();
	printf("*******************************\n\n");
}

void Test_UIFunctions(void)
{
	Test_CreateFile();
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
	LIST* pSearched = (LIST*)malloc(sizeof(LIST));
	for (int i = 0; i < testStringCount; i++)
	{
		SearchNode(pSearched, testCases[i], FILE_PATH_TEST);
	}

	//UI_PrintAll(FILE_PATH_TEST);

	Test_ReadFile();
}