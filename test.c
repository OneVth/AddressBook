#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "common.h"
#include "control.h"
#include "ui.h"
#include "test.h"

#define NODE_MATCH(n, a, b, p) ((n)->age == a && strcmp((n)->name, b) == 0 && strcmp((n)->phone, p) == 0)

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
	return ;
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

int CreateTestDataFile(void)
{
	_mkdir("Test");

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	List_InsertAtEnd(pList, 10, "Test1", "010-0000-0001");
	List_InsertAtEnd(pList, 20, "Test2", "010-0000-0002");
	List_InsertAtEnd(pList, 30, "Test3", "010-0000-0003");

	FILE* fp = NULL;
	fopen_s(&fp, "./Test/test.dat", "wb");
	if (fp == NULL)
	{
		return 0;
	}

	NODE* ptr = pList->head.next;
	while (ptr != &pList->tail)
	{
		fwrite(ptr, sizeof(NODE), 1, fp);
		ptr = ptr->next;
	}

	fclose(fp);
	List_Release(pList);
	free(pList);
	return 1;
}

void Test_CreateTestDataFile(void)
{
	int pass = 1;

	int firstCorrect = 0;
	int secondCorrect = 0;
	int thirdCorrect = 0;
	if (!CreateTestDataFile())
	{
		pass = 0;
		printf("FAIL: CreateTestDataFile() failed to create test file\n");
	}
	else
	{
		FILE* fp = NULL;
		fopen_s(&fp, "./Test/test.dat", "rb");
		if (fp == NULL)
		{
			pass = 0;
		}

		NODE* ptr = (NODE*)malloc(sizeof(NODE));
		memset(ptr, 0, sizeof(NODE));
		if(fread(ptr, sizeof(NODE), 1, fp) > 0)
		{
			firstCorrect = ptr->age == 10;
			secondCorrect = strcmp(ptr->name, "Test1") == 0;
			thirdCorrect = strcmp(ptr->phone, "010-0000-0001") == 0;
			if (!firstCorrect || !secondCorrect || !thirdCorrect)
			{
				pass = 0;
				printf("FAIL: ");
			}
			else
			{
				firstCorrect = 0;
				secondCorrect = 0;
				thirdCorrect = 0;
				memset(ptr, 0, sizeof(NODE));
				if (fread(ptr, sizeof(NODE), 1, fp) > 0)
				{
					firstCorrect = ptr->age == 20;
					secondCorrect = strcmp(ptr->name, "Test2") == 0;
					thirdCorrect = strcmp(ptr->phone, "010-0000-0002") == 0;
					if (!firstCorrect || !secondCorrect || !thirdCorrect)
					{
						pass = 0;
						printf("FAIL: ");
					}
					else
					{
						firstCorrect = 0;
						secondCorrect = 0;
						thirdCorrect = 0;
						memset(ptr, 0, sizeof(NODE));
						if (fread(ptr, sizeof(NODE), 1, fp) > 0)
						{
							firstCorrect = ptr->age == 30;
							secondCorrect = strcmp(ptr->name, "Test3") == 0;
							thirdCorrect = strcmp(ptr->phone, "010-0000-0003") == 0;
							if (!firstCorrect || !secondCorrect || !thirdCorrect)
							{
								pass = 0;
								printf("FAIL: ");
							}
						}
					}
				}
			}
		}
	}

	if (pass)
	{
		printf("PASS: CreateTestDataFile() correctly created test file\n");
	}

	putchar('\n');
	return;
}

void Test_LoadRecordsFromFileByPhone(void)
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
	if (LoadRecordsFromFileByPhone(pList, ptr->phone, FILE_PATH_TEST))
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
	if (LoadRecordsFromFileByName(pList, ptr->name, FILE_PATH_TEST))
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
	if (LoadRecordsFromFileByAge(pList, ptr->age, FILE_PATH_TEST))
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
	LoadRecordsFromFileByPhone(pList, temp->phone, FILE_PATH_TEST);
	EditRecordFromFileByAge(pList->head.next, 93, FILE_PATH_TEST);
	EditRecordFromFileByName(pList->head.next, "Test", FILE_PATH_TEST);
	EditRecordFromFileByPhone(pList->head.next, "010-1234-5678", FILE_PATH_TEST);
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
		SearchRecordsFromFile(pSearched, testCases[i], FILE_PATH_TEST);
	}

	//UI_PrintAll(FILE_PATH_TEST);

	Test_ReadFile();
}