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
#define BENCH_ITERATION 10

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
	wchar_t wLogPath[MAX_PATH] = { 0 };
	wchar_t buffer[MAX_PATH] = { 0 };
	wcscpy_s(wPath, MAX_PATH, FILE_PATH);
	wcscpy_s(wLogPath, MAX_PATH, FILE_PATH);
	PathCchRemoveFileSpec(wPath, MAX_PATH);
	PathCchRemoveFileSpec(wLogPath, MAX_PATH);

	swprintf(buffer, MAX_PATH, L"\\Test\\dummy_%d.dat", GENERATE_NUM);
	swprintf(wPath, MAX_PATH, L"%s%s", wPath, buffer);
	swprintf(buffer, MAX_PATH, L"\\Test\\benchmark_%d.txt", GENERATE_NUM);
	swprintf(wLogPath, MAX_PATH, L"%s%s", wLogPath, buffer);

	int age = 0;
	char name[MAX_NAME_LEN] = { 0 };
	char phone[MAX_PHONE_LEN] = { 0 };
	srand((unsigned int)time(NULL));

	double initDuration = 0.0;
	double total = 0.0;
	for (int i = 0; i < BENCH_ITERATION; i++)
	{
		clock_t start = clock();

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
			DWORD err = GetLastError();
			wprintf(L"File creation failed with error code: %lu\n", err);
			return -1;
		}
		CloseHandle(hFile);

		if (SaveListToFile(pStore, wPath) == 1)
			wprintf(L"Saved generated addresses to %s\n", wPath);
		else
			printf("Failed to save records to file\n");

		ContactStore_Destroy(pStore);

		clock_t end = clock();
		if (i == 0)
		{
			initDuration = (double)(end - start) / CLOCKS_PER_SEC;
		}
		total += (double)(end - start) / CLOCKS_PER_SEC;
	}

	// check file size
	LARGE_INTEGER llFileSize = { 0 };
	HANDLE hFile = CreateFile(
		wPath,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		wprintf(L"File creation failed with error code: %lu\n", err);
		return -1;
	}

	GetFileSizeEx(hFile, &llFileSize);
	CloseHandle(hFile);

	// write log file
	DWORD dwWritten = 0;
	BOOL bResult = FALSE;
	HANDLE hLogFile = CreateFile(
		wLogPath,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hLogFile == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		wprintf(L"File creation failed with error code: %lu\n", err);
		return -1;
	}

	wchar_t logContent[BUFFSIZE] = { 0 };
	swprintf(logContent, BUFFSIZE, L"Number of nodes: %d\nInitial load time: %.6f sec\nAvg time: %.6f sec\n", 
		(int)(llFileSize.QuadPart / Contact_GetSize()), initDuration, total / BENCH_ITERATION);
	
	DWORD len = (DWORD)(wcslen(logContent) * sizeof(wchar_t));
	bResult = WriteFile(hLogFile, logContent, len, &dwWritten, NULL);
	if (!bResult)
	{
		printf("Failed to write log file\n");
		CloseHandle(hLogFile);
		return -1;
	}
	wprintf(L"Benchmark result saved to: %s\n", wLogPath);
	CloseHandle(hLogFile);
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