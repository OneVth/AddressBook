#pragma once

#define MAX_NAME_LEN 32
#define MAX_PHONE_LEN 14	// 000-0000-0000 + '\0'
#define BUFFSIZE 200
#define MAXAGE 150
#define FILE_PATH "Data.dat"

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

// Util functions *******************************************

void ClearInputBuffer(void);
int Str_IsAllDigit(const char* str);
int Str_IsAllAlpha(const char* str);
int Str_IsPhoneFormat(const char* str);

// These below functions are utility helpers used primarily by UI input parsing.
// They assume input of the form: [str] [AND/OR] [str]

int ConvertInputToSearchString(const char* str, int* age, char* name, char* phone);
int ParseSearchInput(const char* input, char temp1[], char temp2[], char op[]);

// Data structure functions *******************************************

void List_Init(LIST* pL);
void List_Release(LIST* pL);
int List_IsEmpty(LIST* pL);
int List_InsertAtBeg(LIST* pL, const int age, const char* name, const char* phone);
int List_InsertAtEnd(LIST* pL, const int age, const char* name, const char* phone);
int List_DeleteAtEnd(LIST* pL);
int List_DeleteAtBeg(LIST* pL);
int List_DeleteByPhone(LIST* pL, const char* phone);
int List_HasPhone(LIST* pL, const char* phone);
int List_CombineByOp(LIST* pResultList, LIST* pList1, LIST* pList2, const char* op);