#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <direct.h>
#include "common.h"
#include "control.h"

#define LOG_DIR L"../Logs"
#define BENCH_ITERATION 10
#define NUM_VARIANTS 15

//int main(void)
//{
//	CreateDirectory(LOG_DIR, NULL);
//	int variants[NUM_VARIANTS] = {
//		1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
//		20000, 30000, 40000, 50000, 100000
//	};
//
//	for (int i = 0; i < NUM_VARIANTS; i++)
//	{
//		wchar_t wPath[MAX_PATH] = { 0 };
//		swprintf(wPath, MAX_PATH, L"..\\Data\\Test\\dummy_%d.dat", variants[i]);
//		int nNodes = 0;
//
//		// Estimate time searching the last record of the file
//		double initDuration = 0.0;
//		double total = 0.0;
//		for (int i = 0; i < BENCH_ITERATION; i++)
//		{
//			// Get last record of the target file
//			LARGE_INTEGER llFileSize = { 0 };
//			DWORD dwContactSize = (DWORD)Contact_GetSize();
//			DWORD dwRead = 0;
//			BOOL bResult = FALSE;
//			HANDLE hFile = NULL;
//			hFile = CreateFile(
//				wPath,
//				GENERIC_READ,
//				FILE_SHARE_READ,
//				NULL,
//				OPEN_EXISTING,
//				FILE_ATTRIBUTE_NORMAL,
//				NULL
//			);
//			if (hFile == INVALID_HANDLE_VALUE)
//			{
//				return -1;
//			}
//			GetFileSizeEx(hFile, &llFileSize);
//			nNodes = (int)(llFileSize.QuadPart / dwContactSize);
//			DWORD dwPos = SetFilePointer(hFile, -(long)dwContactSize, NULL, FILE_END);
//			if (dwPos == INVALID_SET_FILE_POINTER)
//			{
//				CloseHandle(hFile);
//				return -1;
//			}
//
//			Contact* pContact = (Contact*)malloc(dwContactSize);
//			bResult = ReadFile(hFile, pContact, dwContactSize, &dwRead, NULL);
//			if (!bResult || dwRead < dwContactSize)
//			{
//				free(pContact);
//				CloseHandle(hFile);
//				return -1;
//			}
//			CloseHandle(hFile);
//
//			clock_t start = clock();
//
//			DeleteRecordFromFileByPhone(Contact_GetPhone(pContact), wPath);
//
//			clock_t end = clock();
//			if (i == 0)
//			{
//				initDuration = (double)(end - start) / CLOCKS_PER_SEC;
//			}
//			total += (double)(end - start) / CLOCKS_PER_SEC;
//			free(pContact);
//		}
//
//		// log file
//		wchar_t wLogPath[MAX_PATH] = { 0 };
//		swprintf(wLogPath, MAX_PATH, L"%s/benchmark_%d.log", LOG_DIR, variants[i]);
//
//		DWORD dwWritten = 0;
//		BOOL bResult = FALSE;
//		HANDLE hLogFile = NULL;
//		hLogFile = CreateFile(
//			wLogPath,
//			GENERIC_WRITE,
//			0,
//			NULL,
//			CREATE_ALWAYS,
//			FILE_ATTRIBUTE_NORMAL,
//			NULL
//		);
//		if (hLogFile == INVALID_HANDLE_VALUE)
//		{
//			return -1;
//		}
//
//		wchar_t wLogContent[BUFFSIZE] = { 0 };
//		swprintf(wLogContent, BUFFSIZE, L"Number of nodes: %d\nInitial load time: %.6f sec\nAvg time: %.6f sec\n", nNodes, initDuration, total / BENCH_ITERATION);
//
//		DWORD len = (DWORD)(wcslen(wLogContent) * sizeof(wchar_t));
//		bResult = WriteFile(hLogFile, wLogContent, len, &dwWritten, NULL);
//		if (!bResult || dwWritten < len)
//			return -1;
//		wprintf(L"Benchmark result saved to: %s\n", wLogPath);
//		CloseHandle(hLogFile);
//	}
//
//	return 0;
//}