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

void CreateRandomFields(int* age, char* name, char* phone);



int main(void)
{
	printf("Address Generator start.\n");

	srand((unsigned int)time(NULL));

	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };

	LIST* pList = (LIST*)malloc(sizeof(NODE));
	List_Init(pList);

	for (int i = 0; i < 10; i++)
	{
		CreateRandomFields(&age, name, phone);
		List_InsertAtEnd(pList, age, name, phone);
	}
	
	NODE* ptr = pList->head.next;
	while (ptr != &pList->tail)
	{
		printf("%d, %s, %s\n", ptr->age, ptr->name, ptr->phone);
		ptr = ptr->next;
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