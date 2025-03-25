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

void ClearInputBuffer(void);
int IsAllDigit(const char* str);
int IsAllAlpha(const char* str);
int IsPhoneFormat(const char* str);

void InitList(LIST* pL);
void ReleaseList(LIST* pL);
int IsEmpty(LIST* pL);
int InsertNodeAtBeg(LIST* pL, const int age, const char* name, const char* phone);
int InsertNodeAtEnd(LIST* pL, const int age, const char* name, const char* phone);
int DeleteNodeAtEnd(LIST* pL);
int DeleteNodeAtBeg(LIST* pL);
int DeleteNodeByPhone(LIST* pL, const char* phone);
int HasPhoneInList(LIST* pL, const char* phone);
int CombineList(LIST* pResultList, LIST* pList1, LIST* pList2, const char* op);