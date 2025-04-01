#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../AddressBook/common.h"

#define NAME_POOL_SIZE 50

const char* g_namePool[NAME_POOL_SIZE] = {
		"James", "Mary", "John", "Patricia", "Robert",
		"Jennifer", "Michael", "Linda", "William", "Elizabeth",
		"David", "Barbara", "Richard", "Susan",	"Joseph",
		"Jessica", "Thomas", "Sarah", "Charles", "Karen",
		"Christopher", "Nancy", "Daniel", "Lisa", "Matthew",
		"Betty", "Anthony", "Margaret", "Mark", "Sandra",
		"Donald", "Ashley", "Steven", "Kimberly", "Paul",
		"Emily", "Andrew", "Donna", "Joshua", "Michelle",
		"Kenneth", "Dorothy", "Kevin", "Carol", "Brian",
		"Amanda", "George", "Melissa", "Edward", "Deborah"
};

void CreateRandomFields(int* age, char name[], char phone[]);
void Test_CreateRandomFields(void);

int main(void)
{
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };
	srand((unsigned int)time(NULL));

	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	for (int i = 0; i < 10; i++)
	{
		CreateRandomFields(&age, name, phone);
		List_InsertAtEnd(pList, age, name, phone);
	}
	
	List_Release(pList);
	free(pList);
	return 0;
}

void CreateRandomFields(int* age, char name[], char phone[])
{
	*age = rand() % MAXAGE;
	strcpy_s(name, MAX_NAME_LEN, g_namePool[rand() % NAME_POOL_SIZE]);
	snprintf(phone, MAX_PHONE_LEN, "%03d-%04d-%04d", rand() % 1000, rand() % 10000, rand() % 10000);
	return;
}

void Test_CreateRandomFields(void)
{
	int loopCount = 1000;
	int fail = 0;
	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	for (int i = 0; i < loopCount; i++)
	{
		CreateRandomFields(&age, name, phone);
		printf("[%02d]: %d %s %s\n", i + 1, age, name, phone);
		if (!(age >= 0 && age < MAXAGE)) fail++;
		if (!Str_IsAllAlpha(name)) fail++;
		if (!Str_IsPhoneFormat(phone)) fail++;
	}

	printf("Total fails: %d/%d\n", fail, loopCount);
	return;
}