// Contains unit tests for all core mudules (list, utility, control).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "contact.h"
#include "contact_store.h"
#include "common.h"
#include "control.h"
#include "ui.h"
#include "test.h"

#define NODE_MATCH(n, a, b, p) ((n)->age == a && strcmp((n)->name, b) == 0 && strcmp((n)->phone, p) == 0)
#define NUM_TEST_NODE 5

void RunAllTests(void)
{
	Test_ListFunctions();
	Test_UtilFunctions();
	Test_ControlFunctions();
}

void Test_ListFunctions(void)
{
	Test_List_Init();
	Test_List_IsEmpty();
	Test_List_HasPhone();
	Test_List_Release();
	Test_List_InsertAtEnd();
	Test_List_InsertAtBeg();
	Test_List_DeleteAtEnd();
	Test_List_DeleteAtBeg();
	Test_List_DeleteByPhone();
	Test_List_CombineByOp();
}

void Test_UtilFunctions(void)
{
	Test_Str_IsAllDigit();
	Test_Str_IsAllAlpha();
	Test_Str_IsPhoneFormat();
	Test_ClassifyToken();
	Test_SplitSearchExpression();
}

void Test_ControlFunctions(void)
{
	CreateTestDataFile_Minimal();
	Test_CreateTestDataFile_Minimal();
	Test_LoadRecordsFromFileByPhone();
	Test_SaveListToFile();
	Test_LoadRecordsFromFileByName();
	Test_LoadRecordsFromFileByAge();
	Test_EditRecordPhoneFromFile();
	Test_EditRecordAgeFromFile();
	Test_EditRecordNameFromFile();
	Test_DeleteRecordByPhoneFromFile();
	Test_SearchRecordsFromFile();
}

// ***********************************************

void Test_Str_IsAllDigit(void)
{
	int pass = 1;

	// Case 1: all digits
	if (!Str_IsAllDigit("123456"))
	{
		printf("FAIL: Str_IsAllDigit() failed to recognize digits only string\n");
		pass = 0;
	}

	// Case 2: contain space
	if (Str_IsAllDigit("123 456"))
	{
		printf("FAIL: Str_IsAllDigit() incorrectly returned true for string with space\n");
		pass = 0;
	}

	// Case 3: contain alphabet
	if (Str_IsAllDigit("12a45"))
	{
		printf("FAIL: Str_IsAllDigit() incorrectly returned true for string with alphabet\n");
		pass = 0;
	}

	// Case 4: contain special character
	if (Str_IsAllDigit("123-456"))
	{
		printf("FAIL: Str_IsAllDigit() incorrectly returned true for string with special character\n");
		pass = 0;
	}

	// Case 5: empty string
	if (Str_IsAllDigit(""))
	{
		printf("FAIL: Str_IsAllDigit() incorrectly returned true for empty string\n");
		pass = 0;
	}

	// Case 6: leading zero
	if (!Str_IsAllDigit("012345"))
	{
		printf("FAIL: Str_IsAllDigit() failed to recognize digits with leading zero\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: Str_IsAllDigit() with with only digits\n");
		printf("PASS: Str_IsAllDigit() returns false for string with space\n");
		printf("PASS: Str_IsAllDigit() returns false for string with alphabet\n");
		printf("PASS: Str_IsAllDigit() returns false for string with special character\n");
		printf("PASS: Str_IsAllDigit() returns false for empty string\n");
		printf("PASS: Str_IsAllDigit() with digits including leading zero\n");
	}

	putchar('\n');
	return;
}

void Test_Str_IsAllAlpha(void)
{
	int pass = 1;

	// Case 1: all alphabet
	if (!Str_IsAllAlpha("abcde"))
	{
		printf("FAIL: Str_IsAllAlpha() with only alphabet\n");
		pass = 0;
	}

	// Case 2: contain space
	if (Str_IsAllAlpha("ab cde"))
	{
		printf("FAIL: Str_IsAllAlpha() incorrectly returned true for string with space\n");
		pass = 0;
	}

	// Case 3: contain digit
	if (Str_IsAllAlpha("ab1de"))
	{
		printf("FAIL: Str_IsAllAlpha() incorrectly returned true for string with digit\n");
		pass = 0;
	}

	// Case 4: contain special character
	if (Str_IsAllAlpha("ab@de"))
	{
		printf("FAIL: Str_IsAllAlpha() incorrectly returned true for string with special character\n");
		pass = 0;
	}

	// Case 5: empty string
	if (Str_IsAllAlpha(""))
	{
		printf("FAIL: Str_IsAllAlpha() incorrectly returned true for empty string\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: Str_IsAllAlpha() with with only alphabet\n");
		printf("PASS: Str_IsAllAlpha() returns false for string with space\n");
		printf("PASS: Str_IsAllAlpha() returns false for string with digit\n");
		printf("PASS: Str_IsAllAlpha() returns false for string with special character\n");
		printf("PASS: Str_IsAllAlpha() returns false for empty string\n");
	}

	putchar('\n');
	return;
}

void Test_Str_IsPhoneFormat(void)
{
	int pass = 1;

	// Case 1: phone format
	if (!Str_IsPhoneFormat("000-0000-0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() with valid format\n");
		pass = 0;
	}

	// Case 2: conatin alphabet
	if (Str_IsPhoneFormat("000-aaaa-0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for string with alphabets\n");
		pass = 0;
	}

	// Case 3: contain space
	if (Str_IsPhoneFormat("000-0000 -0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for string with space\n");
		pass = 0;
	}

	// Case 4: contain special character
	if (Str_IsPhoneFormat("000-@000-0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for string with specail characters\n");
		pass = 0;
	}

	// Case 5: invalid hyphen position
	if (Str_IsPhoneFormat("0000-000-0000"))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for string with invalid hyphen position\n");
		pass = 0;
	}

	// Case 6: empty string
	if (Str_IsPhoneFormat(""))
	{
		printf("FAIL: Str_IsPhoneFormat() incorrectly returned true for empty string\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: Str_IsPhoneFormat() with with valid format\n");
		printf("PASS: Str_IsPhoneFormat() returns false for string with alphabets\n");
		printf("PASS: Str_IsPhoneFormat() returns false for string with space\n");
		printf("PASS: Str_IsPhoneFormat() returns false for string with special character\n");
		printf("PASS: Str_IsPhoneFormat() returns false for string with invalid hyphen position\n");
		printf("PASS: Str_IsPhoneFormat() returns false for empty string\n");
	}

	putchar('\n');
	return;
}

void Test_SplitSearchExpression(void)
{
	int pass = 1;

	char token1[BUFFSIZE] = { 0 };
	char token2[BUFFSIZE] = { 0 };
	char op[BUFFSIZE] = { 0 };

	// Case 1: single item input
	if (!SplitSearchExpression("10", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		if (strcmp(token1, "10") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("Test", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		if (strcmp(token1, "Test") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("010-0000-0000", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		if (strcmp(token1, "010-0000-0000") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	// Case 2: two items with operator(AND, OR)
	int token1Correct = 0;
	int token2Correct = 0;
	int opCorrect = 0;

	if (!SplitSearchExpression("10 OR 20", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		token1Correct = strcmp(token1, "10") == 0;
		token2Correct = strcmp(token2, "20") == 0;
		opCorrect = strcmp(op, "OR") == 0;
		if (!token1Correct || !token2Correct || !opCorrect)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("10 OR 010-0000-0000", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		token1Correct = strcmp(token1, "10") == 0;
		token2Correct = strcmp(token2, "010-0000-0000") == 0;
		opCorrect = strcmp(op, "OR") == 0;
		if (!token1Correct || !token2Correct || !opCorrect)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("Test AND 10", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		token1Correct = strcmp(token1, "Test") == 0;
		token2Correct = strcmp(token2, "10") == 0;
		opCorrect = strcmp(op, "AND") == 0;
		if (!token1Correct || !token2Correct || !opCorrect)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	if (!SplitSearchExpression("010-0000-0000 AND Test", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid input\n");
	}
	else
	{
		token1Correct = strcmp(token1, "010-0000-0000") == 0;
		token2Correct = strcmp(token2, "Test") == 0;
		opCorrect = strcmp(op, "AND") == 0;
		if (!token1Correct || !token2Correct || !opCorrect)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect token for valid input\n");
		}
	}

	// Case 3: failures
	if (SplitSearchExpression("10 20", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned true for invalid input\n");
	}

	if (SplitSearchExpression("OR 20", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned true for invalid input\n");
	}

	if (SplitSearchExpression("", token1, token2, op))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned true for invalid input\n");
	}

	if (pass)
	{
		printf("PASS: SplitSearchExpression() correctly parsed single token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed single token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed single token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed double token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed double token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed double token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly parsed double token for valid input\n");
		printf("PASS: SplitSearchExpression() correctly returned false for invalid input\n");
		printf("PASS: SplitSearchExpression() correctly returned false for invalid input\n");
		printf("PASS: SplitSearchExpression() correctly returned false for invalid input\n");
	}
	putchar('\n');
	return;
}

void Test_ClassifyToken(void)
{
	int pass = 1;
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	// Case 1: classify token to numeric
	if (!ClassifyToken("10", &age, NULL, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}
	else
	{
		if (age != 10)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect age for valid string\n");
		}
	}

	// Case 2: classify token to alphabetical string
	age = 0; memset(name, 0, sizeof(name)); memset(phone, 0, sizeof(phone));
	if (!ClassifyToken("Test", NULL, name, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}
	else
	{
		if (strcmp(name, "Test") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect name for valid string\n");
		}
	}

	// Case 3: classify token to phone number format string
	age = 0; memset(name, 0, sizeof(name)); memset(phone, 0, sizeof(phone));
	if (!ClassifyToken("010-0000-0000", NULL, NULL, phone))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}
	else
	{
		if (strcmp(phone, "010-0000-0000") != 0)
		{
			pass = 0;
			printf("FAIL: SplitSearchExpression() returned incorrect phone for valid string\n");
		}
	}

	// Case 4: invalid string
	if (ClassifyToken("", NULL, NULL, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}

	if (ClassifyToken("10Test", NULL, NULL, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}

	if (ClassifyToken("010-aaaa-0000", NULL, NULL, NULL))
	{
		pass = 0;
		printf("FAIL: SplitSearchExpression() returned false for valid string\n");
	}


	if (pass)
	{
		printf("PASS: ClassifyToken() correctly classify token for valid string\n");
		printf("PASS: ClassifyToken() correctly classify token for valid string\n");
		printf("PASS: ClassifyToken() correctly classify token for valid string\n");
		printf("PASS: ClassifyToken() correctly returned false for invalid string\n");
		printf("PASS: ClassifyToken() correctly returned false for invalid string\n");
		printf("PASS: ClassifyToken() correctly returned false for invalid string\n");
	}

	putchar('\n');
	return;
}

void Test_List_Init(void)
{
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pList);

	if (pList->head.next == &pList->tail &&
		pList->tail.prev == &pList->head &&
		pList->head.prev == NULL &&
		pList->tail.next == NULL)
		printf("PASS: List_Init\n");
	else
		printf("FAIL: List_Init\n");

	free(pList);
	putchar('\n');
	return;
}

void Test_List_IsEmpty(void)
{
	int pass = 1;
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pList);

	// Case 1: empty list
	if (!List_IsEmpty(pList))
		printf("FAIL: List_IsEmpty(empty list)\n");

	// Case 2: non-empty list
	List_InsertAtEnd(pList, 10, "TestName", "010-0000-0000");

	if (List_IsEmpty(pList))
		printf("FAIL: List_IsEmpty(non-empty list)\n");

	if (pass)
	{
		printf("PASS: List_IsEmpty(empty list)\n");
		printf("PASS: List_IsEmpty(non-empty list)\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_List_HasPhone(void)
{
	int pass = 1;
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pList);

	// Case 1: phone number doesn't exist
	if (List_HasPhone(pList, "010-0000-0000"))
		printf("FAIL: List_HasPhone() returned true for nonexistent phone\n");

	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	pNewNode->next = NULL;
	pNewNode->prev = NULL;
	pNewNode->age = 10;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), "TestName");
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), "010-0000-0000");

	pList->head.next = pNewNode;
	pNewNode->prev = &pList->head;
	pNewNode->next = &pList->tail;
	pList->tail.prev = pNewNode;

	// Case 2: phone number exits
	if (!List_HasPhone(pList, "010-0000-0000"))
		printf("FAIL: List_HasPhone()\n");

	if (pass)
	{
		printf("PASS: List_HasPhone() correctly returns false for nonexistent phone\n");
		printf("PASS: List_HasPhone()\n");

	}

	free(pNewNode);
	free(pList);
	putchar('\n');
	return;
}

void Test_List_Release(void)
{
	int pass = 1;
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pList);

	NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
	pNewNode->next = NULL;
	pNewNode->prev = NULL;
	pNewNode->age = 10;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), "TestName");
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), "010-0000-0000");

	pList->head.next = pNewNode;
	pNewNode->prev = &pList->head;
	pNewNode->next = &pList->tail;
	pList->tail.prev = pNewNode;

	if (List_IsEmpty(pList))
	{
		printf("FAIL: List_Release(before release: not empty)\n");
		pass = 0;
	}

	List_Release(pList);

	if (!List_IsEmpty(pList))
	{
		printf("FAIL: List_Release(after release: empty)\n");
		free(pNewNode);
	}

	if (pass)
	{
		printf("PASS: List_Release(before release: not empty)\n");
		printf("PASS: List_Release(after release: empty)\n");
	}

	free(pList);
	putchar('\n');
	return;
}

void Test_List_InsertAtEnd(void)
{
	int pass = 1;
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pList);

	// Case 1: check insertion
	if (!List_InsertAtEnd(pList, 10, "A", "010-0000-0001"))
	{
		printf("FAIL: List_InsertAtEnd()\n");
		pass = 0;
	}

	// Case 2: check order of list with several insertion
	List_InsertAtEnd(pList, 20, "B", "010-0000-0002");

	// Expect: head -> A -> B -> tail
	NODE* first = pList->head.next;
	NODE* second = first->next;
	int firstCorrect = first->age == 10 &&
		strcmp(first->name, "A") == 0 &&
		strcmp(first->phone, "010-0000-0001") == 0 &&
		first->next == second;

	int secondCorrect = second->age == 20 &&
		strcmp(second->name, "B") == 0 &&
		strcmp(second->phone, "010-0000-0002") == 0 &&
		second->next == &pList->tail;

	if (!firstCorrect || !secondCorrect)
	{
		printf("FAIL: List_InsertAtEnd() did not maintain expected A->B order or node contents\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: List_InsertAtEnd() inserted first node successfully\n");
		printf("PASS: List_InsertAtEnd() maintains correct insertion order (A->B)\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_List_InsertAtBeg(void)
{
	int pass = 1;
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pList);

	// Case 1: check insertion
	if (!List_InsertAtBeg(pList, 10, "A", "010-0000-0001"))
	{
		printf("FAIL: List_InsertAtBeg()\n");
		pass = 0;
	}

	// Case 2: check order of list with several insertion
	List_InsertAtBeg(pList, 20, "B", "010-0000-0002");

	// Expect: head -> B -> A -> tail
	NODE* first = pList->head.next;
	NODE* second = first->next;
	int firstCorrect = first->age == 20 &&
		strcmp(first->name, "B") == 0 &&
		strcmp(first->phone, "010-0000-0002") == 0 &&
		first->next == second;

	int secondCorrect = (second->age == 10 &&
		strcmp(second->name, "A") == 0 &&
		strcmp(second->phone, "010-0000-0001") == 0 &&
		second->next == &pList->tail);

	if (!firstCorrect || !secondCorrect)
	{
		printf("FAIL: List_InsertAtBeg() did not maintain expected B->A order or node contents\n");
	}

	if (pass)
	{
		printf("PASS: List_InsertAtBeg() inserted first node successfully\n");
		printf("PASS: List_InsertAtBeg() maintains order B -> A\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_List_DeleteAtEnd(void)
{
	int pass = 1;
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pList);

	// Case 1: delete node at empty list
	if (List_DeleteAtEnd(pList))
	{
		printf("FAIL: List_DeleteAtEnd() return true for empty list\n");
		pass = 0;
	}

	// Case 2: delete node
	List_InsertAtEnd(pList, 10, "A", "010-0000-0001");
	if (!List_DeleteAtEnd(pList))
	{
		printf("FAIL: List_DeleteAtEnd()\n");
		pass = 0;
	}

	// Case 3: delete correct order
	// Expect order: head -> A -> B -> tail
	List_InsertAtEnd(pList, 10, "A", "010-0000-0001");
	List_InsertAtEnd(pList, 11, "B", "010-0000-0002");
	List_DeleteAtEnd(pList);
	NODE* ptr = pList->head.next;
	if (strcmp(ptr->name, "A") != 0 || ptr->next != &pList->tail)
	{
		printf("FAIL: List_DeleteAtEnd() did not maintain expected head -> A -> tail order or node contents\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: List_DeleteAtEnd() on empty list\n");
		printf("PASS: List_DeleteAtEnd() on valid list\n");
		printf("PASS: List_DeleteAtEnd() maintains correct head -> A -> tail structure\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_List_DeleteAtBeg(void)
{
	int pass = 1;
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pList);

	// Case 1: delete node at empty list
	if (List_DeleteAtBeg(pList))
	{
		printf("FAIL: List_DeleteAtBeg() returns true for empty list\n");
		pass = 0;
	}

	// Case 2: delete node
	List_InsertAtBeg(pList, 10, "A", "010-0000-0001");
	if (!List_DeleteAtBeg(pList))
	{
		printf("FAIL: List_DeleteAtBeg()\n");
		pass = 0;
	}

	// Case 3: delete correct order
	// Expect order: head -> B -> A -> tail
	List_InsertAtBeg(pList, 10, "A", "010-0000-0001");
	List_InsertAtBeg(pList, 11, "B", "010-0000-0002");
	List_DeleteAtBeg(pList);
	NODE* ptr = pList->head.next;
	if (strcmp(ptr->name, "A") != 0 || ptr->next != &pList->tail)
	{
		printf("FAIL: List_DeleteAtBeg() did not maintain expected head -> A -> tail order or node contents\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: List_DeleteAtBeg() on empty list\n");
		printf("PASS: List_DeleteAtBeg() on valid list\n");
		printf("PASS: List_DeleteAtBeg() maintains correct head -> A -> tail structure\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_List_DeleteByPhone(void)
{
	int pass = 1;
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pList);

	// Case 1: delete on empty list
	if (List_DeleteByPhone(pList, "010-0000-0000"))
	{
		printf("FAIL: List_DeleteByPhone() returns true for empty list\n");
		pass = 0;
	}
	// Case 2: delete non-existence node
	List_InsertAtBeg(pList, 10, "TestName", "010-0000-0000");
	if (List_DeleteByPhone(pList, "010-0000-0001"))
	{
		printf("FAIL: List_DeleteByPhone() returns true for non-existent pohone number\n");
		pass = 0;
	}

	// Case 3: delete existence node
	if (!List_DeleteByPhone(pList, "010-0000-0000"))
	{
		printf("FAIL: List_DeleteByPhone() returns false for existent phone number\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: List_DeleteByPhone() fails on empty list as expected\n");
		printf("PASS: List_DeleteByPhone() on non-existent phone number\n");
		printf("PASS: List_DeleteByPhone() on existent phone number\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_List_CombineByOp(void)
{
	int pass = 1;
	int firstCorrect = 0;
	int secondCorrect = 0;
	int thirdCorrect = 0;
	int fourthCorrect = 0;
	NODE* firstNode = NULL;
	NODE* secondNode = NULL;
	NODE* thirdNode = NULL;
	NODE* fourthNode = NULL;

	LIST* pLeftList = (LIST*)malloc(sizeof(LIST));
	LIST* pRightList = (LIST*)malloc(sizeof(LIST));
	LIST* pCombinedList = (LIST*)malloc(sizeof(LIST));
	if (pLeftList == NULL || pRightList == NULL || pCombinedList == NULL)
	{
		printf("FAIL: malloc()\n");
		return;
	}
	List_Init(pLeftList);
	List_Init(pRightList);
	List_Init(pCombinedList);

	// Case 1: combine both lists are empty by "AND"
	// Expect: head -> tail
	List_CombineByOp(pCombinedList, pLeftList, pRightList, "AND");
	if (!List_IsEmpty(pCombinedList))
	{
		printf("FAIL: List_CombineByOp(Result, Empty, Empty, \"AND\")\n");
		pass = 0;
	}
	List_Release(pCombinedList);

	// Case 2: combine both lists are valid and have one duplication by "AND"
	// Expect: head -> A -> tail
	List_InsertAtEnd(pLeftList, 10, "A", "010-0000-0001");
	List_InsertAtEnd(pLeftList, 11, "B", "010-0000-0002");
	List_InsertAtEnd(pRightList, 10, "A", "010-0000-0001");
	List_InsertAtEnd(pRightList, 12, "C", "010-0000-0003");

	List_CombineByOp(pCombinedList, pLeftList, pRightList, "AND");
	firstNode = pCombinedList->head.next;
	firstCorrect = NODE_MATCH(firstNode, 10, "A", "010-0000-0001") &&
		firstNode->next == &pCombinedList->tail;

	if (!firstCorrect)
	{
		printf("FAIL: List_CombineByOp(Result, Valid, Valid, \"AND\") with one duplication\n");
		pass = 0;
	}

	List_Release(pCombinedList);
	List_Release(pLeftList);
	List_Release(pRightList);

	// Case 3: combine both lists are valid and have no duplication by "AND"
	// Expect: head -> tail
	List_InsertAtEnd(pLeftList, 10, "A", "010-0000-0001");
	List_InsertAtEnd(pLeftList, 11, "B", "010-0000-0002");
	List_InsertAtEnd(pRightList, 12, "C", "010-0000-0003");
	List_InsertAtEnd(pRightList, 13, "D", "010-0000-0004");

	List_CombineByOp(pCombinedList, pLeftList, pRightList, "AND");
	firstNode = pCombinedList->head.next;
	firstCorrect = firstNode == &pCombinedList->tail;

	if (!firstCorrect)
	{
		printf("FAIL: List_CombineByOp(Result, Valid, Valid, \"AND\") with no duplication\n");
		pass = 0;
	}

	List_Release(pCombinedList);
	List_Release(pLeftList);
	List_Release(pRightList);

	// Case 4: combine when only left list valid by "OR"
	// Expect: head -> A -> B -> tail
	List_InsertAtEnd(pLeftList, 10, "A", "010-0000-0001");
	List_InsertAtEnd(pLeftList, 11, "B", "010-0000-0002");

	List_CombineByOp(pCombinedList, pLeftList, pRightList, "OR");
	firstNode = pCombinedList->head.next;
	secondNode = firstNode->next;

	firstCorrect = NODE_MATCH(firstNode, 10, "A", "010-0000-0001") &&
		firstNode->next == secondNode;

	secondCorrect = NODE_MATCH(secondNode, 11, "B", "010-0000-0002") &&
		secondNode->next == &pCombinedList->tail;

	if (!firstCorrect || !secondCorrect)
	{
		printf("FAIL: List_CombineByOp(Result, Valid, Invalid, \"OR\")\n");
		pass = 0;
	}

	List_Release(pCombinedList);
	List_Release(pLeftList);
	List_Release(pRightList);

	// Case 5: combine both lists are valid and have one duplication by "OR"
	// Expect: head -> A -> B -> C -> tail
	List_InsertAtEnd(pLeftList, 10, "A", "010-0000-0001");
	List_InsertAtEnd(pLeftList, 11, "B", "010-0000-0002");
	List_InsertAtEnd(pRightList, 10, "A", "010-0000-0001");
	List_InsertAtEnd(pRightList, 12, "C", "010-0000-0003");

	List_CombineByOp(pCombinedList, pLeftList, pRightList, "OR");
	firstNode = pCombinedList->head.next;
	secondNode = firstNode->next;
	thirdNode = secondNode->next;

	firstCorrect = NODE_MATCH(firstNode, 10, "A", "010-0000-0001") &&
		firstNode->next == secondNode;

	secondCorrect = NODE_MATCH(secondNode, 11, "B", "010-0000-0002") &&
		secondNode->next == thirdNode;

	thirdCorrect = NODE_MATCH(thirdNode, 12, "C", "010-0000-0003") &&
		thirdNode->next == &pCombinedList->tail;

	if (!firstCorrect || !secondCorrect || !thirdCorrect)
	{
		printf("FAIL: List_CombineByOp(Result, Valid, Valid, \"OR\") with one duplication\n");
		pass = 0;
	}

	List_Release(pCombinedList);
	List_Release(pLeftList);
	List_Release(pRightList);

	// Case 6: combine both lists are valid and have no duplication by "OR"
	// Expect: head -> A -> B -> C -> D -> tail
	List_InsertAtEnd(pLeftList, 10, "A", "010-0000-0001");
	List_InsertAtEnd(pLeftList, 11, "B", "010-0000-0002");
	List_InsertAtEnd(pRightList, 12, "C", "010-0000-0003");
	List_InsertAtEnd(pRightList, 13, "D", "010-0000-0004");

	List_CombineByOp(pCombinedList, pLeftList, pRightList, "OR");
	firstNode = pCombinedList->head.next;
	secondNode = firstNode->next;
	thirdNode = secondNode->next;
	fourthNode = thirdNode->next;

	firstCorrect = NODE_MATCH(firstNode, 10, "A", "010-0000-0001") &&
		firstNode->next == secondNode;

	secondCorrect = NODE_MATCH(secondNode, 11, "B", "010-0000-0002") &&
		secondNode->next == thirdNode;

	thirdCorrect = NODE_MATCH(thirdNode, 12, "C", "010-0000-0003") &&
		thirdNode->next == fourthNode;

	fourthCorrect = NODE_MATCH(fourthNode, 13, "D", "010-0000-0004") &&
		fourthNode->next == &pCombinedList->tail;

	if (!firstCorrect || !secondCorrect || !thirdCorrect || !fourthCorrect)
	{
		printf("FAIL: List_CombineByOp(Result, Valid, Valid, \"OR\") with no duplication\n");
		pass = 0;
	}

	if (pass)
	{
		printf("PASS: List_CombineByOp(Result, Empty, Empty, \"AND\")\n");
		printf("PASS: List_CombineByOp(Result, Valid, Valid, \"AND\") with one duplication\n");
		printf("PASS: List_CombineByOp(Result, Valid, Valid, \"AND\") with no duplication\n");
		printf("PASS: List_CombineByOp(Result, Valid, Empty, \"OR\")\n");
		printf("PASS: List_CombineByOp(Result, Valid, Valid, \"OR\") with one duplication\n");
		printf("PASS: List_CombineByOp(Result, Valid, Valid, \"OR\") with no duplication\n");
	}

	List_Release(pCombinedList);
	List_Release(pLeftList);
	List_Release(pRightList);
	free(pCombinedList);
	free(pLeftList);
	free(pRightList);
	putchar('\n');
	return;
}

int CreateTestDataFile_Minimal(void)
{
	CreateDirectory(L"./Test", NULL);

	int ages[] = { 10, 11, 20, 20, 30 };
	char* names[] = { "A", "A", "B", "C", "D" };
	char* phones[] = {
		"010-0000-0001",
		"010-0000-0011",
		"010-0000-0002",
		"010-0000-0022",
		"010-0000-0003"
	};

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	for (int i = 0; i < NUM_TEST_NODE; i++)
	{
		List_InsertAtEnd(pList, ages[i], names[i], phones[i]);
	}

	DWORD dwWritten = 0;
	BOOL bResult = FALSE;

	HANDLE hFile = CreateFile(
		FILE_PATH_TEST,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	NODE* ptr = pList->head.next;
	while (ptr != &pList->tail)
	{
		bResult = WriteFile(hFile, ptr, sizeof(NODE), &dwWritten, NULL);
		if (!bResult)
		{
			CloseHandle(hFile);
			return 0;
		}

		if (dwWritten < sizeof(NODE))
		{
			CloseHandle(hFile);
			return 0;
		}

		ptr = ptr->next;
	}

	CloseHandle(hFile);
	List_Release(pList);
	free(pList);
	return 1;
}

int CheckNode(NODE* ptr, int expectedAge, const char* expectedName, const char* expectedPhone)
{
	int firstCorrect = 0;
	int secondCorrect = 0;
	int thirdCorrect = 0;
	firstCorrect = ptr->age == expectedAge;
	secondCorrect = strcmp(ptr->name, expectedName) == 0;
	thirdCorrect = strcmp(ptr->phone, expectedPhone) == 0;
	if (!firstCorrect || !secondCorrect || !thirdCorrect)
	{
		return 0;
	}
	return 1;
}

void Test_CreateTestDataFile_Minimal(void)
{
	int pass = 1;

	int ages[] = { 10, 11, 20, 20, 30 };
	char* names[] = { "A", "A", "B", "C", "D" };
	char* phones[] = {
		"010-0000-0001",
		"010-0000-0011",
		"010-0000-0002",
		"010-0000-0022",
		"010-0000-0003"
	};

	if (!CreateTestDataFile_Minimal())
	{
		pass = 0;
		printf("FAIL: Test_CreateTestDataFile_Minimal() failed to create test file\n");
	}
	else
	{
		LARGE_INTEGER llFileSize = { 0 };
		LONGLONG llTotalReadSize = 0;
		DWORD dwRead = 0;
		BOOL bResult = FALSE;

		HANDLE hFile = CreateFile(
			FILE_PATH_TEST,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			pass = 0;
			printf("FAIL: Test_CreateTestDataFile_Minimal() could not open test data file\n");
			return;
		}

		if (!GetFileSizeEx(hFile, &llFileSize))
		{
			printf("FAIL: Test_CreateTestDataFile_Minimal() couldn't get file size\n");
			CloseHandle(hFile);
			return;
		}

		NODE* ptr = (NODE*)malloc(sizeof(NODE));
		for (int i = 0; i < NUM_TEST_NODE; i++)
		{
			ZeroMemory(ptr, sizeof(NODE));
			bResult = ReadFile(hFile, ptr, sizeof(NODE), &dwRead, NULL);
			if (bResult && dwRead == sizeof(NODE))
			{
				llTotalReadSize += dwRead;
				if (!CheckNode(ptr, ages[i], names[i], phones[i]))
				{
					pass = 0;
					printf("FAIL: Test_CreateTestDataFile_Minimal() test file doesn't match with [%d]-th expected data\n", i + 1);
					break;
				}
			}
		}

		if (pass && (llTotalReadSize != llFileSize.QuadPart))
		{
			pass = 0;
			printf("FAIL: Test_CreateTestDataFile_Minimal() get wrong file size\n");
		}

		free(ptr);
		CloseHandle(hFile);
	}

	if (pass)
	{
		printf("PASS: CreateTestDataFile_Minimal() correctly created test file\n");
	}

	putchar('\n');
	return;
}

void Test_LoadRecordsFromFileByPhone(void)
{
	if (!CreateTestDataFile_Minimal())
	{
		printf("FAIL: Test_LoadRecordsFromFileByPhone() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	// Case 1: valid phone number
	if (LoadRecordsFromFileByPhone(pList, "010-0000-0001", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: LoadRecordsFromFileByPhone() returned false for valid phone number\n");
	}
	else
	{
		NODE* ptr = pList->head.next;
		if (!CheckNode(ptr, 10, "A", "010-0000-0001"))
		{
			pass = 0;
			printf("FAIL: LoadRecordsFromFileByPhone() failed to load expected data\n");
		}
	}
	List_Release(pList);

	// Case 2: invalid phone number
	if (LoadRecordsFromFileByPhone(pList, "010-9999-9999", FILE_PATH_TEST) == LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: LoadRecordsFromFileByPhone() returned true for invalid phone number\n");
	}

	if (pass)
	{
		printf("PASS: LoadRecordsFromFileByPhone() returned correct result for valid phone number\n");
		printf("PASS: LoadRecordsFromFileByPhone() returned correct result for invalid phone number\n");
	}

	putchar('\n');
	List_Release(pList);
	free(pList);
	return;
}

void Test_SaveListToFile(void)
{
	if (!CreateTestDataFile_Minimal())
	{
		printf("FAIL: Test_SaveListToFile() file creation failed\n");
		return;
	}

	int ages[] = { 10, 99, 98, 97 };
	char* names[] = { "A", "Z", "Y", "X" };
	char* phones[] = {
		"010-0000-0001",	// already existing data
		"010-9999-9999",
		"010-9999-9998",
		"010-9999-9997"
	};

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	for (int i = 0; i < 4; i++)
	{
		if (!List_InsertAtEnd(pList, ages[i], names[i], phones[i]))
		{
			printf("FAIL: Test_SaveListToFile() failed to call List_InsertAtEnd()\n");
			putchar('\n');
			return;
		}
	}

	int pass = 1;
	if (!SaveListToFile(pList, FILE_PATH_TEST))
	{
		pass = 0;
		printf("FAIL: Test_SaveListToFile() returned false for valid list\n");
	}
	else
	{
		LARGE_INTEGER llFileSize = { 0 };
		HANDLE hFile = CreateFile(
			FILE_PATH_TEST,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("FAIL: Test_SaveListToFile() failed to open file\n");
			return;
		}

		if (!GetFileSizeEx(hFile, &llFileSize))
		{
			printf("FAIL: Test_SaveListToFile() failed to get file size\n");
			return;
		}

		if (llFileSize.QuadPart != (NUM_TEST_NODE + 3) * sizeof(NODE))
		{
			pass = 0;
			printf("FAIL: Test_SaveListToFile() file size doesn't match with expected size\n");
		}
		CloseHandle(hFile);

		if (LoadRecordsFromFileByPhone(NULL, "010-9999-9999", FILE_PATH_TEST) != LOAD_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_SaveListToFile() didn't save the list properly\n");
		}
	}

	if (pass)
	{
		printf("PASS: Test_SaveListToFile() correctly save list to file\n");
		printf("PASS: Test_SaveListToFile() wrote correct number of bytes\n");
		printf("PASS: Test_SaveListToFile() created file successfully\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_LoadRecordsFromFileByName(void)
{
	if (!CreateTestDataFile_Minimal())
	{
		printf("FAIL: Test_LoadRecordsFromFileByName() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	// Case 1: valid name
	if (LoadRecordsFromFileByName(pList, "A", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: LoadRecordsFromFileByName() returned false for valid name\n");
	}
	else
	{
		NODE* ptr = pList->head.next;
		if (!CheckNode(ptr, 10, "A", "010-0000-0001"))
		{
			pass = 0;
			printf("FAIL: LoadRecordsFromFileByName() failed to load first expected record\n");
		}
		else
		{
			ptr = ptr->next;
			if (!CheckNode(ptr, 11, "A", "010-0000-0011"))
			{
				pass = 0;
				printf("FAIL: LoadRecordsFromFileByName() failed to load second expected record\n");
			}
			else
			{
				if (!(ptr->next == &pList->tail))
				{
					pass = 0;
					printf("FAIL: LoadRecordsFromFileByName() loaded more nodes than expected\n");
				}
			}
		}
	}

	// Case 2: invalid name
	if (LoadRecordsFromFileByName(pList, "Z", FILE_PATH_TEST) == LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: LoadRecordsFromFileByName() returned true for invalid name\n");
	}

	if (pass)
	{
		printf("PASS: LoadRecordsFromFileByName() correctly load first record\n");
		printf("PASS: LoadRecordsFromFileByName() correctly load second record\n");
		printf("PASS: LoadRecordsFromFileByName() correctly returned false for invalid name\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_LoadRecordsFromFileByAge(void)
{
	if (!CreateTestDataFile_Minimal())
	{
		printf("FAIL: Test_LoadRecordsFromFileByAge() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: Test_LoadRecordsFromFileByAge() failed to allocate memory\n");
		putchar('\n');
		return;
	}
	List_Init(pList);

	// Case 1: valid age
	if (LoadRecordsFromFileByAge(pList, 20, FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: LoadRecordsFromFileByAge() returned false for valid age\n");
	}
	else
	{
		NODE* ptr = pList->head.next;
		if (!CheckNode(ptr, 20, "B", "010-0000-0002"))
		{
			pass = 0;
			printf("FAIL: LoadRecordsFromFileByAge() failed to load first expected record\n");
		}
		else
		{
			ptr = ptr->next;
			if (!CheckNode(ptr, 20, "C", "010-0000-0022"))
			{
				pass = 0;
				printf("FAIL: LoadRecordsFromFileByAge() failed to load second expected record\n");
			}
			else
			{
				if (!(ptr->next == &pList->tail))
				{
					pass = 0;
					printf("FAIL: LoadRecordsFromFileByAge() loaded more nodes than expected\n");
				}
			}
		}
	}

	// Case 2: invalid age
	if (LoadRecordsFromFileByAge(pList, 99, FILE_PATH_TEST) == LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: LoadRecordsFromFileByAge() returned true for invalid age\n");
	}

	if (pass)
	{
		printf("PASS: LoadRecordsFromFileByAge() correctly load first record\n");
		printf("PASS: LoadRecordsFromFileByAge() correctly load second record\n");
		printf("PASS: LoadRecordsFromFileByAge() correctly returned false for invalid age\n");
	}
	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_EditRecordAgeFromFile(void)
{
	if (!CreateTestDataFile_Minimal())
	{
		printf("FAIL: Test_EditRecordAgeFromFile() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: Test_EditRecordAgeFromFile() failed to allocate memory\n");
		putchar('\n');
		return;
	}

	List_Init(pList);
	if (LoadRecordsFromFileByPhone(pList, "010-0000-0001", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_EditRecordAgeFromFile() failed to load test records\n");
	}
	else
	{
		NODE* ptr = pList->head.next;
		if (EditRecordAgeFromFile(ptr, 99, FILE_PATH_TEST) != EDIT_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_EditRecordAgeFromFile() properly open/write to file\n");
		}
		else
		{
			List_Release(pList);
			if (LoadRecordsFromFileByAge(pList, 99, FILE_PATH_TEST) != LOAD_SUCCESS)
			{
				pass = 0;
				printf("FAIL: Test_EditRecordAgeFromFile() failed to load edited record\n");
			}
			else
			{
				ptr = pList->head.next;
				if (!CheckNode(ptr, 99, "A", "010-0000-0001"))
				{
					pass = 0;
					printf("FAIL: Test_EditRecordAgeFromFile() didn't correctly edit record\n");
				}
			}
		}
	}

	if (pass)
	{
		printf("PASS: Test_EditRecordAgeFromFile() correctly edit record for valid age\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_EditRecordNameFromFile(void)
{
	if (!CreateTestDataFile_Minimal())
	{
		printf("FAIL: Test_EditRecordNameFromFile() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: Test_EditRecordNameFromFile() failed to allocate memory\n");
		putchar('\n');
		return;
	}

	List_Init(pList);
	if (LoadRecordsFromFileByPhone(pList, "010-0000-0001", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_EditRecordNameFromFile() failed to load test records");
	}
	else
	{
		NODE* ptr = pList->head.next;
		if (EditRecordNameFromFile(ptr, "Z", FILE_PATH_TEST) != EDIT_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_EditRecordNameFromFile() properly open/write to file\n");
		}
		else
		{
			List_Release(pList);
			if (LoadRecordsFromFileByName(pList, "Z", FILE_PATH_TEST) != LOAD_SUCCESS)
			{
				pass = 0;
				printf("FAIL: Test_EditRecordNameFromFile() failed to load edited record\n");
			}
			else
			{
				ptr = pList->head.next;
				if (!CheckNode(ptr, 10, "Z", "010-0000-0001"))
				{
					pass = 0;
					printf("FAIL: Test_EditRecordNameFromFile() didn't correctly edit record\n");
				}
			}
		}
	}

	if (pass)
	{
		printf("PASS: Test_EditRecordNameFromFile() correctly edit record for valid name\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_EditRecordPhoneFromFile(void)
{
	if (!CreateTestDataFile_Minimal())
	{
		printf("FAIL: Test_EditRecordPhoneFromFile() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if (pList == NULL)
	{
		printf("FAIL: Test_EditRecordPhoneFromFile() failed to allocate memory\n");
		putchar('\n');
		return;
	}

	List_Init(pList);
	if (LoadRecordsFromFileByPhone(pList, "010-0000-0001", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_EditRecordPhoneFromFile() failed to load test records");
	}
	else
	{
		NODE* ptr = pList->head.next;
		if (EditRecordPhoneFromFile(ptr, "010-0000-9999", FILE_PATH_TEST) != EDIT_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_EditRecordPhoneFromFile() properly open/write to file\n");
		}
		else
		{
			List_Release(pList);
			if (LoadRecordsFromFileByPhone(pList, "010-0000-9999", FILE_PATH_TEST) != LOAD_SUCCESS)
			{
				pass = 0;
				printf("FAIL: Test_EditRecordPhoneFromFile() failed to load edited record\n");
			}
			else
			{
				ptr = pList->head.next;
				if (!CheckNode(ptr, 10, "A", "010-0000-9999"))
				{
					pass = 0;
					printf("FAIL: Test_EditRecordPhoneFromFile() didn't correctly edit record\n");
				}
			}
		}
	}

	if (pass)
	{
		printf("PASS: Test_EditRecordPhoneFromFile() correctly edit record for valid phone number\n");
	}

	List_Release(pList);
	free(pList);
	putchar('\n');
	return;
}

void Test_DeleteRecordByPhoneFromFile(void)
{
	if (!CreateTestDataFile_Minimal())
	{
		printf("FAIL: Test_EditRecordNameFromFile() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	// Case 1: invalid phone number
	if (DeleteRecordFromFileByPhone("010-0000-9999", FILE_PATH_TEST) == DELETE_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_DeleteRecordByPhoneFromFile() returned true for invalid phone number\n");
	}

	// Case 2: valid phone number
	if (DeleteRecordFromFileByPhone("010-0000-0001", FILE_PATH_TEST) != DELETE_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_DeleteRecordByPhoneFromFile() cannot properly open/write to file\n");
	}
	else
	{
		LARGE_INTEGER llFileSize = { 0 };
		DWORD dwRead = 0;
		BOOL bResult = FALSE;

		HANDLE hFile = CreateFile(
			FILE_PATH_TEST,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("FAIL: Test_DeleteRecordByPhoneFromFile() failed to open file\n");
			putchar('\n');
			return;
		}

		GetFileSizeEx(hFile, &llFileSize);
		LIST* pList = (LIST*)malloc(sizeof(LIST));
		if (pList == NULL)
		{
			printf("FAIL: Test_DeleteRecordByPhoneFromFile() failed to allocate memory\n");
			putchar('\n');
			return;
		}
		List_Init(pList);
		if (LoadRecordsFromFileByPhone(pList, "010-0000-0001", FILE_PATH_TEST) == LOAD_SUCCESS || llFileSize.QuadPart != sizeof(NODE) * (NUM_TEST_NODE - 1))
		{
			pass = 0;
			printf("FAIL: Test_DeleteRecordByPhoneFromFile() failed to remove existing record\n");
		}
		List_Release(pList);
		CloseHandle(hFile);
	}

	if (pass)
	{
		printf("PASS: Test_DeleteRecordByPhoneFromFile() successfully removed the record with given phone\n");
		printf("PASS: Test_DeleteRecordByPhoneFromFile() correctly return false for invalid phone number\n");
	}

	putchar('\n');
	return;
}

void Test_SearchRecordsFromFile(void)
{
	if (!CreateTestDataFile_Minimal())
	{
		printf("FAIL: Test_EditRecordNameFromFile() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	LIST* pResult = (LIST*)malloc(sizeof(LIST));
	List_Init(pResult);

	NODE* ptr = NULL;
	int ageCorrect = 0;
	int nameCorrect = 0;
	int phoneCorrect = 0;

	// Case 1: single result
	if (SearchRecordsFromFile(pResult, "10", FILE_PATH_TEST) != SEARCH_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_SearchRecordsFromFile() failed to search record for valid input\n");
	}
	else
	{
		ptr = pResult->head.next;
		ageCorrect = ptr->age == 10;
		nameCorrect = strcmp(ptr->name, "A") == 0;
		phoneCorrect = strcmp(ptr->phone, "010-0000-0001") == 0;
		if (!ageCorrect || !nameCorrect || !phoneCorrect)
		{
			pass = 0;
			printf("FAIL: Test_SearchRecordsFromFile() failed to search from given record\n");
		}
		List_Release(pResult);
	}


	// Case 2: multiple result
	if (SearchRecordsFromFile(pResult, "A", FILE_PATH_TEST) != SEARCH_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_SearchRecordsFromFile() failed to search record for valid input\n");
	}
	else
	{
		ptr = pResult->head.next;
		ageCorrect = ptr->age == 10;
		nameCorrect = strcmp(ptr->name, "A") == 0;
		phoneCorrect = strcmp(ptr->phone, "010-0000-0001") == 0;
		if (!ageCorrect || !nameCorrect || !phoneCorrect)
		{
			pass = 0;
			printf("FAIL: Test_SearchRecordsFromFile() failed to search for first expected record\n");
		}
		else
		{
			ptr = ptr->next;
			ageCorrect = ptr->age == 11;
			nameCorrect = strcmp(ptr->name, "A") == 0;
			phoneCorrect = strcmp(ptr->phone, "010-0000-0011") == 0;
			if (!ageCorrect || !nameCorrect || !phoneCorrect)
			{
				pass = 0;
				printf("FAIL: Test_SearchRecordsFromFile() failed to search for second expected record\n");
			}
		}
		List_Release(pResult);
	}

	// Case 3: search with operator
	if (SearchRecordsFromFile(pResult, "10 OR 010-0000-0003", FILE_PATH_TEST) != SEARCH_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_SearchRecordsFromFile() failed to search record for valid input\n");
	}
	else
	{
		ptr = pResult->head.next;
		ageCorrect = ptr->age == 10;
		nameCorrect = strcmp(ptr->name, "A") == 0;
		phoneCorrect = strcmp(ptr->phone, "010-0000-0001") == 0;
		if (!ageCorrect || !nameCorrect || !phoneCorrect)
		{
			pass = 0;
			printf("FAIL: Test_SearchRecordsFromFile() failed to search for first expected record\n");
		}
		else
		{
			ptr = ptr->next;
			ageCorrect = ptr->age == 30;
			nameCorrect = strcmp(ptr->name, "D") == 0;
			phoneCorrect = strcmp(ptr->phone, "010-0000-0003") == 0;
			if (!ageCorrect || !nameCorrect || !phoneCorrect)
			{
				pass = 0;
				printf("FAIL: Test_SearchRecordsFromFile() failed to search for second expected record\n");
			}
		}
		List_Release(pResult);
	}
	free(pResult);

	if (pass)
	{
		printf("PASS: Test_SearchRecordsFromFile() correctly search single record\n");
		printf("PASS: Test_SearchRecordsFromFile() correctly search multiple record\n");
		printf("PASS: Test_SearchRecordsFromFile() correctly search single record with operator\n");
	}
	putchar('\n');
	return;
}

int CreateTestDataFile_CS(void)
{
	CreateDirectory(L"./Test", NULL);

	int ages[] = { 10, 11, 20, 20, 30 };
	char* names[] = { "A", "A", "B", "C", "D" };
	char* phones[] = {
		"010-0000-0001",
		"010-0000-0011",
		"010-0000-0002",
		"010-0000-0022",
		"010-0000-0003"
	};

	DWORD dwContactSize = (DWORD)Contact_GetSize();
	DWORD dwWritten = 0;
	BOOL bResult = FALSE;

	HANDLE hFile = CreateFile(
		FILE_PATH_TEST,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	for (int i = 0; i < NUM_TEST_NODE; i++)
	{
		Contact* temp = Contact_Create(ages[i], names[i], phones[i]);
		if (temp == NULL)
		{
			CloseHandle(hFile);
			return 0;
		}
		
		bResult = WriteFile(hFile, temp, dwContactSize, &dwWritten, NULL);
		if (!bResult)
		{
			CloseHandle(hFile);
			return 0;
		}

		if (dwWritten < dwContactSize)
		{
			CloseHandle(hFile);
			return 0;
		}
		Contact_Destroy(temp);
	}

	CloseHandle(hFile);
	return 1;
}

int CheckNode_CS(const Contact* contact, int expectedAge, const char* expectedName, const char* expectedPhone)
{
	int firstCorrect = 0;
	int secondCorrect = 0;
	int thirdCorrect = 0;
	firstCorrect = Contact_GetAge(contact) == expectedAge;
	secondCorrect = strcmp(Contact_GetName(contact), expectedName) == 0;
	thirdCorrect = strcmp(Contact_GetPhone(contact), expectedPhone) == 0;
	if (!firstCorrect || !secondCorrect || !thirdCorrect)
	{
		return 0;
	}
	return 1;
}

void Test_CreateTestDataFile_CS(void)
{
	int pass = 1;

	int ages[] = { 10, 11, 20, 20, 30 };
	char* names[] = { "A", "A", "B", "C", "D" };
	char* phones[] = {
		"010-0000-0001",
		"010-0000-0011",
		"010-0000-0002",
		"010-0000-0022",
		"010-0000-0003"
	};

	if (!CreateTestDataFile_CS())
	{
		pass = 0;
		printf("FAIL: Test_CreateTestDataFile_CS() failed to create test file\n");
	}
	else
	{
		LARGE_INTEGER llFileSize = { 0 };
		LONGLONG llTotalReadSize = 0;
		DWORD dwContactSize = (DWORD)Contact_GetSize();
		DWORD dwRead = 0;
		BOOL bResult = FALSE;

		HANDLE hFile = CreateFile(
			FILE_PATH_TEST,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			pass = 0;
			printf("FAIL: Test_CreateTestDataFile_CS() could not open test data file\n");
			return;
		}

		if (!GetFileSizeEx(hFile, &llFileSize))
		{
			printf("FAIL: Test_CreateTestDataFile_CS() couldn't get file size\n");
			CloseHandle(hFile);
			return;
		}

		Contact* temp = (Contact*)malloc(dwContactSize);
		if (temp == NULL)
		{
			pass = 0;
			printf("FAIL: Test_CreateTestDataFile_CS() failed to allocate memory\n");
			CloseHandle(hFile);
			return;
		}

		for (int i = 0; i < NUM_TEST_NODE; i++)
		{
			ZeroMemory(temp, dwContactSize);
			bResult = ReadFile(hFile, temp, dwContactSize, &dwRead, NULL);
			if (bResult && dwRead == dwContactSize)
			{
				llTotalReadSize += dwRead;
				if (!CheckNode_CS(temp, ages[i], names[i], phones[i]))
				{
					pass = 0;
					printf("FAIL: Test_CreateTestDataFile_CS() test file doesn't match with [%d]-th expected data\n", i + 1);
					break;
				}
			}
		}

		if (pass && (llTotalReadSize != llFileSize.QuadPart))
		{
			pass = 0;
			printf("FAIL: Test_CreateTestDataFile_CS() get wrong file size\n");
		}

		free(temp);
		CloseHandle(hFile);
	}

	if (pass)
	{
		printf("PASS: Test_CreateTestDataFile_CS() correctly created test file\n");
	}

	putchar('\n');
	return;
}

void Test_ContactStore_Take(void)
{
	int pass = 1;

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_ContactStore_Take() failed to create ContactStore\n");
		ContactStore_Destroy(pStore);
		putchar('\n');
		return;
	}

	Contact* firstContact = Contact_Create(10, "Alice", "010-0000-1111");
	Contact* secondContact = Contact_Create(20, "Betty", "010-0000-2222");
	ContactStore_AddToEnd(pStore, firstContact);
	ContactStore_AddToEnd(pStore, secondContact);

	const Contact* ptr = ContactStore_Take(pStore);
	if (!CheckNode_CS(ptr, 10, "Alice", "010-0000-1111"))
	{
		pass = 0;
		printf("FAIL: Test_ContactStore_Take() failed to take first contact\n");
		Contact_Destroy(ptr);
	}
	else
	{
		Contact_Destroy(ptr);
		ptr = ContactStore_Take(pStore);
		if (!CheckNode_CS(ptr, 20, "Betty", "010-0000-2222"))
		{
			pass = 0;
			printf("FAIL: Test_ContactStore_Take() failed to take second contact\n");
			Contact_Destroy(ptr);
		}
		else
		{
			Contact_Destroy(ptr);
			ptr = ContactStore_Take(pStore);
			if (ptr != NULL)
			{
				pass = 0;
				printf("FAIL: Test_ContactStore_Take() took more contacts than expected\n");
			}
			Contact_Destroy(ptr);
		}
	}
	
	if (pass)
	{
		printf("PASS: Test_ContactStore_Take() correctly took first contact\n");
		printf("PASS: Test_ContactStore_Take() correctly took second contact\n");
		printf("PASS: Test_ContactStore_Take() correctly returned NULL for empty store\n");
	}

	Contact_Destroy(firstContact);
	Contact_Destroy(secondContact);
	ContactStore_Destroy(pStore);
	putchar('\n');
	return;
}

void Test_LoadRecordsFromFileByPhone_CS(void)
{
	if (!CreateTestDataFile_CS())
	{
		printf("FAIL: Test_LoadRecordsFromFileByPhone_CS() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_LoadRecordsFromFileByPhone_CS() failed to create ContactStore\n");
		putchar('\n');
		return;
	}

	// Case 1: valid phone number
	if (LoadRecordsFromFileByPhone_CS(pStore, "010-0000-0001", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_LoadRecordsFromFileByPhone_CS() returned false for valid phone number\n");
	}
	else
	{
		const Contact* ptr = ContactStore_Take(pStore);
		if (!CheckNode_CS(ptr, 10, "A", "010-0000-0001"))
		{
			pass = 0;
			printf("FAIL: Test_LoadRecordsFromFileByPhone_CS() failed to load expected data\n");
		}
		Contact_Destroy(ptr);
	}

	// Case 2: invalid phone number
	if (LoadRecordsFromFileByPhone_CS(pStore, "010-9999-9999", FILE_PATH_TEST) == LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_LoadRecordsFromFileByPhone_CS() returned true for invalid phone number\n");
	}

	if (pass)
	{
		printf("PASS: Test_LoadRecordsFromFileByPhone_CS() returned correct result for valid phone number\n");
		printf("PASS: Test_LoadRecordsFromFileByPhone_CS() returned correct result for invalid phone number\n");
	}

	putchar('\n');
	ContactStore_Destroy(pStore);
	return;
}

void Test_SaveListToFile_CS(void)
{
	if (!CreateTestDataFile_CS())
	{
		printf("FAIL: Test_SaveStoreToFile_CS() file creation failed\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	int ages[] = { 10, 99, 98, 97 };
	char* names[] = { "A", "Z", "Y", "X" };
	char* phones[] = {
		"010-0000-0001",	// already existing data
		"010-9999-9999",
		"010-9999-9998",
		"010-9999-9997"
	};

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_SaveStoreToFile_CS() failed to create ContactStore\n");
		ContactStore_Destroy(pStore);
		putchar('\n');
		return;
	}

	Contact* ptr = Contact_Create(ages[0], names[0], phones[0]);
	if (TryAddContact(pStore, ptr, FILE_PATH_TEST) != 0)
	{
		pass = 0;
		printf("FAIL: Test_SaveListToFile_CS() failed check existence contact to the list\n");
	}
	Contact_Destroy(ptr);

	for (int i = 1; i < 4; i++)
	{
		ptr = Contact_Create(ages[i], names[i], phones[i]);
		if (TryAddContact(pStore, ptr, FILE_PATH_TEST) != 1)
		{
			pass = 0;
			printf("FAIL: Test_SaveListToFile_CS() failed to add non-existence contact to the list\n");
		}
		Contact_Destroy(ptr);
	}

	if (SaveListToFile_CS(pStore, FILE_PATH_TEST) != 1)
	{
		pass = 0;
		printf("FAIL: Test_SaveListToFile_CS() failed to save list to file\n");
	}
	else
	{
		LARGE_INTEGER llFileSize = { 0 };
		HANDLE hFile = CreateFile(
			FILE_PATH_TEST,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("FAIL: Test_SaveListToFile_CS() failed to open file\n");
			return;
		}

		if (!GetFileSizeEx(hFile, &llFileSize))
		{
			printf("FAIL: Test_SaveListToFile_CS() failed to get file size\n");
			return;
		}

		if (llFileSize.QuadPart != (NUM_TEST_NODE + 3) * Contact_GetSize())
		{
			pass = 0;
			printf("FAIL: Test_SaveListToFile_CS() file size doesn't match with expected size\n");
		}
		CloseHandle(hFile);

		if (LoadRecordsFromFileByPhone_CS(NULL, "010-9999-9999", FILE_PATH_TEST) != LOAD_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_SaveListToFile_CS() didn't save the list properly\n");
		}
	}

	if (pass)
	{
		printf("PASS: Test_SaveListToFile_CS() correctly save list to file\n");
		printf("PASS: Test_SaveListToFile_CS() wrote correct number of bytes\n");
		printf("PASS: Test_SaveListToFile_CS() created file successfully\n");
	}

	ContactStore_Destroy(pStore);
	putchar('\n');
	return;
}

void Test_LoadRecordsFromFileByName_CS(void)
{
	if (!CreateTestDataFile_CS())
	{
		printf("FAIL: Test_LoadRecordsFromFileByName_CS() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_LoadRecordsFromFileByName_CS() failed to create ContactStore\n");
		putchar('\n');
		return;
	}

	// Case 1: valid name
	if (LoadRecordsFromFileByName_CS(pStore, "A", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_LoadRecordsFromFileByName_CS() returned false for valid phone number\n");
	}
	else
	{
		const Contact* ptr = ContactStore_Take(pStore);
		if (!CheckNode_CS(ptr, 10, "A", "010-0000-0001"))
		{
			pass = 0;
			printf("FAIL: Test_LoadRecordsFromFileByName_CS() failed to load first expected data\n");
		}
		else
		{
			Contact_Destroy(ptr);
			ptr = ContactStore_Take(pStore);
			if (!CheckNode_CS(ptr, 11, "A", "010-0000-0011"))
			{
				pass = 0;
				printf("FAIL: Test_LoadRecordsFromFileByName_CS() failed to load second expected data\n");
			}
			Contact_Destroy(ptr);
		}
	}

	// Case 2: invalid phone number
	if (LoadRecordsFromFileByName_CS(pStore, "Z", FILE_PATH_TEST) == LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_LoadRecordsFromFileByName_CS() returned true for invalid name\n");
	}

	if (pass)
	{
		printf("PASS: Test_LoadRecordsFromFileByName_CS() returned correct result for valid name\n");
		printf("PASS: Test_LoadRecordsFromFileByName_CS() returned correct result for invalid name\n");
	}

	putchar('\n');
	ContactStore_Destroy(pStore);
	return;
}

void Test_LoadRecordsFromFileByAge_CS(void)
{
	if (!CreateTestDataFile_CS())
	{
		printf("FAIL: Test_LoadRecordsFromFileByAge_CS() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_LoadRecordsFromFileByAge_CS() failed to create ContactStore\n");
		putchar('\n');
		return;
	}

	// Case 1: valid name
	if (LoadRecordsFromFileByAge_CS(pStore, 20, FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_LoadRecordsFromFileByAge_CS() returned false for valid phone number\n");
	}
	else
	{
		const Contact* ptr = ContactStore_Take(pStore);
		if (!CheckNode_CS(ptr, 20, "B", "010-0000-0002"))
		{
			pass = 0;
			printf("FAIL: Test_LoadRecordsFromFileByAge_CS() failed to load first expected data\n");
		}
		else
		{
			Contact_Destroy(ptr);
			ptr = ContactStore_Take(pStore);
			if (!CheckNode_CS(ptr, 20, "C", "010-0000-0022"))
			{
				pass = 0;
				printf("FAIL: Test_LoadRecordsFromFileByAge_CS() failed to load second expected data\n");
			}
			Contact_Destroy(ptr);
		}
	}

	// Case 2: invalid phone number
	if (LoadRecordsFromFileByAge_CS(pStore, 99, FILE_PATH_TEST) == LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_LoadRecordsFromFileByAge_CS() returned true for invalid name\n");
	}

	if (pass)
	{
		printf("PASS: Test_LoadRecordsFromFileByAge_CS() returned correct result for valid name\n");
		printf("PASS: Test_LoadRecordsFromFileByAge_CS() returned correct result for invalid name\n");
	}

	putchar('\n');
	ContactStore_Destroy(pStore);
	return;
}

void Test_EditRecordAgeFromFile_CS(void)
{
	if (!CreateTestDataFile_CS())
	{
		printf("FAIL: Test_EditRecordAgeFromFile_CS() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_EditRecordAgeFromFile_CS() failed to create ContactStore\n");
		putchar('\n');
		return;
	}

	// Case 1: valid age
	if (LoadRecordsFromFileByPhone_CS(pStore, "010-0000-0001", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_EditRecordAgeFromFile_CS() failed to load test records\n");
	}
	else
	{
		const Contact* ptr = ContactStore_Take(pStore);
		if (EditRecordAgeFromFile_CS(ptr, 99, FILE_PATH_TEST) != EDIT_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_EditRecordAgeFromFile_CS() properly open/write to file\n");
		}
		else
		{
			Contact_Destroy(ptr);
			if (LoadRecordsFromFileByAge_CS(pStore, 99, FILE_PATH_TEST) != LOAD_SUCCESS)
			{
				pass = 0;
				printf("FAIL: Test_EditRecordAgeFromFile_CS() failed to load edited record\n");
			}
			else
			{
				ptr = ContactStore_Take(pStore);
				if (!CheckNode_CS(ptr, 99, "A", "010-0000-0001"))
				{
					pass = 0;
					printf("FAIL: Test_EditRecordAgeFromFile_CS() didn't correctly edit record\n");
				}
				Contact_Destroy(ptr);
			}
		}
	}

	// Case 2: invalid age
	if (LoadRecordsFromFileByPhone_CS(pStore, "010-0000-0001", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_EditRecordAgeFromFile_CS() failed to load test records\n");
	}
	else
	{
		const Contact* ptr = ContactStore_Take(pStore);
		if (EditRecordAgeFromFile_CS(ptr, MAXAGE + 1, FILE_PATH_TEST) == EDIT_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_EditRecordAgeFromFile_CS() return EDIT_SUCCESS for invalid age\n");
		}
		Contact_Destroy(ptr);
	}

	if (pass)
	{
		printf("PASS: Test_EditRecordAgeFromFile_CS() correctly edit record for valid age\n");
		printf("PASS: Test_EditRecordAgeFromFile_CS() correctly return false for invalid age\n");
	}

	ContactStore_Destroy(pStore);
	putchar('\n');
	return;
}

void Test_EditRecordNameFromFile_CS(void)
{
	if (!CreateTestDataFile_CS())
	{
		printf("FAIL: Test_EditRecordNameFromFile_CS() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_EditRecordNameFromFile_CS() failed to create ContactStore\n");
		putchar('\n');
		return;
	}

	// Case 1: valid name
	if (LoadRecordsFromFileByPhone_CS(pStore, "010-0000-0001", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_EditRecordNameFromFile_CS() failed to load test records\n");
	}
	else
	{
		const Contact* ptr = ContactStore_Take(pStore);
		if (EditRecordNameFromFile_CS(ptr, "Z", FILE_PATH_TEST) != EDIT_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_EditRecordNameFromFile_CS() properly open/write to file\n");
		}
		else
		{
			Contact_Destroy(ptr);
			if (LoadRecordsFromFileByName_CS(pStore, "Z", FILE_PATH_TEST) != LOAD_SUCCESS)
			{
				pass = 0;
				printf("FAIL: Test_EditRecordNameFromFile_CS() failed to load edited record\n");
			}
			else
			{
				ptr = ContactStore_Take(pStore);
				if (!CheckNode_CS(ptr, 10, "Z", "010-0000-0001"))
				{
					pass = 0;
					printf("FAIL: Test_EditRecordNameFromFile_CS() didn't correctly edit record\n");
				}
				Contact_Destroy(ptr);
			}
		}
	}

	// Case 2: invalid name
	if (!LoadRecordsFromFileByPhone_CS(pStore, "010-0000-0001", FILE_PATH_TEST))
	{
		pass = 0;
		printf("FAIL: Test_EditRecordNameFromFile_CS() failed to load test records\n");
	}
	else
	{
		const Contact* ptr = ContactStore_Take(pStore);
		if (EditRecordNameFromFile_CS(ptr, "InvalidName!", FILE_PATH_TEST) == EDIT_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_EditRecordNameFromFile_CS() return EDIT_SUCCESS for invalid name\n");
		}
		Contact_Destroy(ptr);
	}

	if (pass)
	{
		printf("PASS: Test_EditRecordNameFromFile_CS() correctly edit record for valid name\n");
		printf("PASS: Test_EditRecordNameFromFile_CS() correctly return false for invalid name\n");
	}

	ContactStore_Destroy(pStore);
	putchar('\n');
	return;
}

void Test_EditRecordPhoneFromFile_CS(void)
{
	if (!CreateTestDataFile_CS())
	{
		printf("FAIL: Test_EditRecordPhoneFromFile_CS() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_EditRecordPhoneFromFile_CS() failed to create ContactStore\n");
		putchar('\n');
		return;
	}

	// Case 1: valid phone number
	if (LoadRecordsFromFileByPhone_CS(pStore, "010-0000-0001", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_EditRecordPhoneFromFile_CS() failed to load test records\n");
	}
	else
	{
		const Contact* ptr = ContactStore_Take(pStore);
		if (EditRecordPhoneFromFile_CS(ptr, "010-0000-9999", FILE_PATH_TEST) != EDIT_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_EditRecordPhoneFromFile_CS() properly open/write to file\n");
		}
		else
		{
			Contact_Destroy(ptr);
			if (LoadRecordsFromFileByPhone_CS(pStore, "010-0000-9999", FILE_PATH_TEST) != LOAD_SUCCESS)
			{
				pass = 0;
				printf("FAIL: Test_EditRecordPhoneFromFile_CS() failed to load edited record\n");
			}
			else
			{
				ptr = ContactStore_Take(pStore);
				if (!CheckNode_CS(ptr, 10, "A", "010-0000-9999"))
				{
					pass = 0;
					printf("FAIL: Test_EditRecordPhoneFromFile_CS() didn't correctly edit record\n");
				}
				Contact_Destroy(ptr);
			}
		}
	}

	// Case 2: invalid phone number
	if (LoadRecordsFromFileByPhone_CS(pStore, "010-0000-0011", FILE_PATH_TEST) != LOAD_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_EditRecordPhoneFromFile_CS() failed to load test records\n");
	}
	else
	{
		const Contact* ptr = ContactStore_Take(pStore);
		if (EditRecordPhoneFromFile_CS(ptr, "0000-0000-0000", FILE_PATH_TEST) == EDIT_SUCCESS)
		{
			pass = 0;
			printf("FAIL: Test_EditRecordPhoneFromFile_CS() return EDIT_SUCCESS for invalid phone number\n");
		}
		Contact_Destroy(ptr);
	}

	if (pass)
	{
		printf("PASS: Test_EditRecordPhoneFromFile_CS() correctly edit record for valid phone number\n");
		printf("PASS: Test_EditRecordPhoneFromFile_CS() correctly return false for invalid phone number\n");
	}

	ContactStore_Destroy(pStore);
	putchar('\n');
	return;
}

void Test_DeleteRecordFromFileByPhone_CS(void)
{
	if (!CreateTestDataFile_CS())
	{
		printf("FAIL: Test_DeleteRecordFromFileByPhone_CS() failed to create test file\n");
		putchar('\n');
		return;
	}

	int pass = 1;

	// Case 1: invalid phone number
	if (DeleteRecordFromFileByPhone_CS("010-0000-9999", FILE_PATH_TEST) == DELETE_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_DeleteRecordFromFileByPhone_CS() returned true for invalid phone number\n");
	}

	// Case 2: valid phone number
	if (DeleteRecordFromFileByPhone_CS("010-0000-0001", FILE_PATH_TEST) != DELETE_SUCCESS)
	{
		pass = 0;
		printf("FAIL: Test_DeleteRecordFromFileByPhone_CS() cannot properly open/write to file\n");
	}
	else
	{
		LARGE_INTEGER llFileSize = { 0 };
		DWORD dwContactSize = (DWORD)Contact_GetSize();
		DWORD dwRead = 0;
		BOOL bResult = FALSE;

		HANDLE hFile = CreateFile(
			FILE_PATH_TEST,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("FAIL: Test_DeleteRecordFromFileByPhone_CS() failed to open file\n");
			putchar('\n');
			return;
		}

		GetFileSizeEx(hFile, &llFileSize);
		ContactStore* pStore = ContactStore_Create();
		if (pStore == NULL)
		{
			printf("FAIL: Test_DeleteRecordFromFileByPhone_CS() failed to create ContactStore\n");
			putchar('\n');
			return;
		}
		
		if (LoadRecordsFromFileByPhone_CS(pStore, "010-0000-0001", FILE_PATH_TEST) == LOAD_SUCCESS || llFileSize.QuadPart != dwContactSize * (NUM_TEST_NODE - 1))
		{
			pass = 0;
			printf("FAIL: Test_DeleteRecordFromFileByPhone_CS() failed to remove existing record\n");
		}
		ContactStore_Destroy(pStore);
		CloseHandle(hFile);
	}

	if (pass)
	{
		printf("PASS: Test_DeleteRecordFromFileByPhone_CS() successfully removed the record with given phone number\n");
		printf("PASS: Test_DeleteRecordFromFileByPhone_CS() correctly return false for invalid phone number\n");
	}

	putchar('\n');
	return;
}

// ***********************************************

void Test_Contact_Destroy(void)
{
	Contact* pContact = Contact_Create(10, "Test", "010-0000-0000");

	Contact_Destroy(pContact);

	printf("PASS: Contact_Destroy() completed without crash\n");
	return;
}

void Test_ContactLifecycle(void)
{
	int pass = 1;

	Contact* pContact = Contact_Create(10, "Allice", "010-0000-1111");
	if (pContact == NULL)
	{
		printf("FAIL: Contact_Create returned NULL\n");
		return;
	}

	if (Contact_GetAge(pContact) != 10)
	{
		pass = 0;
		printf("FAIL: Contact_GetAge() returned wrong value\n");
	}

	if (strcmp(Contact_GetName(pContact), "Allice") != 0)
	{
		pass = 0;
		printf("FAIL: Contact_GetName() returned wrong value\n");
	}

	if (strcmp(Contact_GetName(pContact), "Allice") != 0)
	{
		pass = 0;
		printf("FAIL: Contact_GetPhone() returned wrong value\n");
	}

	if (pass)
	{
		printf("PASS: Contact_GetAge() returned correct value\n");
		printf("PASS: Contact_GetName() returned correct value\n");
		printf("PASS: Contact_GetPhone() returned correct value\n");

	}

	Contact_Destroy(pContact);
	return;
}

void Test_Contact_SetAge(void)
{
	int pass = 1;

	Contact* ptr = Contact_Create(10, "Alice", "010-0000-1111");
	if (ptr == NULL)
	{
		printf("FAIL: Test_Contact_SetAge() failed to create a contact\n");
		return;
	}

	int beforeAge = 0;
	int afterAge = 0;

	beforeAge = Contact_GetAge(ptr);
	Contact_SetAge(ptr, 20);
	afterAge = Contact_GetAge(ptr);
	if (beforeAge == afterAge || afterAge != 20)
	{
		pass = 0;
		printf("FAIL: Test_Contact_SetAge() didn't set age correctly\n");
	}

	if(pass)
	{
		printf("PASS: Test_Contact_SetAge() set age correctly\n");
	}
	
	Contact_Destroy(ptr);
	return;
}

void Test_Contact_SetName(void)
{
	int pass = 1;

	Contact* ptr = Contact_Create(10, "Alice", "010-0000-1111");
	if (ptr == NULL)
	{
		printf("FAIL: Test_Contact_SetName() failed to create a contact\n");
		return;
	}

	char beforeName[MAX_NAME_LEN] = { 0 };
	char afterName[MAX_NAME_LEN] = { 0 };

	strcpy_s(beforeName, sizeof(beforeName), Contact_GetName(ptr));
	Contact_SetName(ptr, "Betty");
	strcpy_s(afterName, sizeof(afterName), Contact_GetName(ptr));
	if (strcmp(beforeName, afterName) == 0 || strcmp(afterName, "Betty") != 0)
	{
		pass = 0;
		printf("FAIL: Test_Contact_SetName() didn't set name correctly\n");
	}

	if (pass)
	{
		printf("PASS: Test_Contact_SetName() set name correctly\n");
	}

	Contact_Destroy(ptr);
	return;
}

void Test_Contact_SetPhone(void)
{
	int pass = 1;

	Contact* ptr = Contact_Create(10, "Alice", "010-0000-1111");
	if (ptr == NULL)
	{
		printf("FAIL: Test_Contact_SetPhone() failed to create a contact\n");
		return;
	}

	char beforePhone[MAX_PHONE_LEN] = { 0 };
	char afterPhone[MAX_PHONE_LEN] = { 0 };

	strcpy_s(beforePhone, sizeof(beforePhone), Contact_GetPhone(ptr));
	Contact_SetPhone(ptr, "010-0000-2222");
	strcpy_s(afterPhone, sizeof(afterPhone), Contact_GetPhone(ptr));
	if (strcmp(beforePhone, afterPhone) == 0 || strcmp(afterPhone, "010-0000-2222") != 0)
	{
		pass = 0;
		printf("FAIL: Test_Contact_SetPhone() didn't set Phone correctly\n");
	}

	if (pass)
	{
		printf("PASS: Test_Contact_SetPhone() set Phone correctly\n");
	}

	Contact_Destroy(ptr);
	return;
}

void Test_ContactStore_IsEmpty(void)
{
	int pass = 1;

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_ContactStore_IsEmpty() failed to create ContactStore\n");
		return;
	}

	if (!ContactStore_IsEmpty(pStore))
	{
		pass = 0;
		printf("FAIL: Test_ContactStore_IsEmpty() failed to check empty store\n");
	}
	else
	{
		ContactStore_AddToEnd(pStore,
			Contact_Create(10, "Alice", "010-0000-1111"));
		if (ContactStore_IsEmpty(pStore))
		{
			pass = 0;
			printf("FAIL: Test_ContactStore_IsEmpty() failed to check non-empty store\n");
		}
	}

	if (pass)
	{
		printf("PASS: Test_ContactStore_IsEmpty() correctly check empty store\n");
		printf("PASS: Test_ContactStore_IsEmpty() correctly check non-empty store\n");
	}

	ContactStore_Destroy(pStore);
	putchar('\n');
	return;
}

void Test_ContactStore_HasPhone(void)
{
	int pass = 1;

	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_ContactStore_HasPhone() failed to create ContactStore\n");
		return;
	}

	if (ContactStore_HasPhone(pStore, "010-0000-1111"))
	{
		pass = 0;
		printf("FAIL: Test_ContactStore_HasPhone() returned true for empty store\n");
	}
	else
	{
		ContactStore_AddToEnd(pStore,
			Contact_Create(10, "Alice", "010-0000-1111"));
		if (ContactStore_HasPhone(pStore, "010-0000-0000"))
		{
			pass = 0;
			printf("FAIL: Test_ContactStore_HasPhone() failed to check for non-exist phone number\n");
		}
		else
		{
			if (!ContactStore_HasPhone(pStore, "010-0000-1111"))
			{
				pass = 0;
				printf("FAIL: Test_ContactStore_HasPhone() failed to check for exist phone number\n");
			}
		}
	}

	if (pass)
	{
		printf("PASS: Test_ContactStore_HasPhone() correctly check empty store\n");
		printf("PASS: Test_ContactStore_HasPhone() correctly check non-exist phone number\n");
		printf("PASS: Test_ContactStore_HasPhone() correctly check exist phone number\n");
	}
	ContactStore_Destroy(pStore);
	putchar('\n');
	return;
}

void Test_ContactStore_Destroy(void)
{
	ContactStore* pStore = ContactStore_Create();

	ContactStore_Destroy(pStore);

	printf("PASS: ContactStore_Destroy() completed without crash\n");
	return;
}

void Test_ContactStore_Add(void)
{
	ContactStore* pStore = ContactStore_Create();
	if (pStore == NULL)
	{
		printf("FAIL: Test_AddContact() failed to create ContactStore\n");
		return;
	}

	ContactStore_AddToEnd(pStore, Contact_Create(10, "Alice", "010-0000-1111"));
	ContactStore_AddToEnd(pStore, Contact_Create(20, "Betty", "010-0000-2222"));
	ContactStore_AddToEnd(pStore, Contact_Create(30, "John", "010-0000-3333"));

	printf("Expected order: Alice -> Betty -> John\n");
	ContactStore_PrintAll(pStore);
	ContactStore_Destroy(pStore);
	putchar('\n');

	pStore = ContactStore_Create();
	ContactStore_AddToFront(pStore, Contact_Create(10, "Alice", "010-0000-1111"));
	ContactStore_AddToFront(pStore, Contact_Create(20, "Betty", "010-0000-2222"));
	ContactStore_AddToFront(pStore, Contact_Create(30, "John", "010-0000-3333"));

	printf("Expected order: John -> Betty -> Alice\n");
	ContactStore_PrintAll(pStore);
	ContactStore_Destroy(pStore);
	putchar('\n');
	return;
}

void Test_ContactStore_CombineByOp(void)
{
	ContactStore* pLeftStore = ContactStore_Create();
	ContactStore* pRightStore = ContactStore_Create();
	ContactStore* pResultStore = ContactStore_Create();

	ContactStore_AddToEnd(pLeftStore,
		Contact_Create(10, "Alice", "010-0000-1111"));
	ContactStore_AddToEnd(pLeftStore,
		Contact_Create(20, "Betty", "010-0000-2222"));

	ContactStore_AddToEnd(pRightStore,
		Contact_Create(20, "Betty", "010-0000-2222"));
	ContactStore_AddToEnd(pRightStore,
		Contact_Create(30, "John", "010-0000-3333"));

	ContactStore_CombineByOp(pResultStore, pLeftStore, pRightStore, "OR");

	printf("Expected order: Alice -> Betty -> John\n");
	ContactStore_PrintAll(pResultStore);

	ContactStore_Destroy(pResultStore);
	pResultStore = ContactStore_Create();

	ContactStore_CombineByOp(pResultStore, pLeftStore, pRightStore, "AND");

	printf("\nExpected order: Betty\n");
	ContactStore_PrintAll(pResultStore);

	ContactStore_Destroy(pResultStore);
	ContactStore_Destroy(pLeftStore);
	ContactStore_Destroy(pRightStore);
	return;
}