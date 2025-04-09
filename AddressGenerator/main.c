#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <Pathcch.h>
#include "../AddressBook/common.h"
#include "../AddressBook/control.h"

#pragma comment(lib, "Pathcch.lib")

#define NAME_POOL_SIZE 50
#define	GENERATE_NUM 1000

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
	CreateDirectory(L"..\\Data", NULL);
	CreateDirectory(L"..\\Data\\Test", NULL);

	wchar_t wPath[MAX_PATH] = { 0 };
	wchar_t buffer[MAX_PATH] = { 0 };
	wcscpy_s(wPath, MAX_PATH, FILE_PATH);
	PathCchRemoveFileSpec(wPath, MAX_PATH);
	swprintf(buffer, MAX_PATH, L"\\Test\\dummy_%d.dat", GENERATE_NUM);
	swprintf(wPath, MAX_PATH, L"%s%s", wPath, buffer);

	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };
	srand((unsigned int)time(NULL));

	ContactStore* pStore = ContactStore_Create();

	for (int i = 0; i < GENERATE_NUM; i++)
	{
		CreateRandomFields(&age, name, phone);
		Contact* pContact = Contact_Create(age, name, phone);
		if (ContactStore_HasPhone(pStore, phone) == 0)
			ContactStore_AddToEnd(pStore, pContact);
		Contact_Destroy(pContact);
	}

	// To delete existing file and create the new file
	HANDLE hFile = CreateFile(
		wPath,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	CloseHandle(hFile);

	if (SaveListToFile_CS(pStore, wPath) == 1)
		wprintf(L"Saved generated addresses to %s\n", wPath);
	else
		printf("Failed to save to data.dat\n");

	ContactStore_Destroy(pStore);
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